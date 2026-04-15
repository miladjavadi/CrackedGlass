/*
  ==============================================================================

    FilterData.cpp
    Created: 10 Apr 2026 9:22:10pm
    Author:  milad

  ==============================================================================
*/

#include "FilterData.h"
#include <JuceHeader.h>
#include <cmath>

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    filter.reset();

    juce::dsp::ProcessSpec spec{ sampleRate, samplesPerBlock, numChannels };
    filter.prepare(spec);

    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> block{ buffer };

    if (isEnabled)
    {
        filter.process(juce::dsp::ProcessContextReplacing<float>{ block });
    }
}

void FilterData::updateParameters(bool enable, juce::dsp::StateVariableTPTFilterType filterType, float cutoffFrequency, float resonance, float modulator)
{
    isEnabled = enable;
    filter.setType(filterType);

    //float modulatedCutoffFrequency{ filterType == juce::dsp::StateVariableTPTFilterType::highpass ? std::fmin(std::fmax(20'000.0f - (20'000.0f - cutoffFrequency) * modulator , 1.0f), 20'000.0f) : std::fmin(std::fmax(cutoffFrequency * modulator, 1.0f), 20'000.0f)};
    float modulatedCutoffFrequency{ std::fmin(std::fmax(cutoffFrequency * modulator, 1.0f), 20'000.0f) };

    filter.setCutoffFrequency(modulatedCutoffFrequency);
    filter.setResonance(resonance);
}

void FilterData::reset()
{
    filter.reset();
}