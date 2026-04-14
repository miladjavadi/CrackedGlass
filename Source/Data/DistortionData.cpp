/*
  ==============================================================================

    DistortionData.cpp
    Created: 13 Apr 2026 5:47:45pm
    Author:  milad

  ==============================================================================
*/

#include "DistortionData.h"
#include <cmath>
#include <algorithm>


void DistortionData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::dsp::ProcessSpec spec{ sampleRate, samplesPerBlock, numChannels };

    distortion.prepare(spec);

    isPrepared = true;
}

void DistortionData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    if (isEnabled)
    {
        if (distortion.functionToUse == crackPlaceholder)
        {
            crackBuffer(buffer, gain);
        }

        else
        {
            buffer.applyGainRamp(0, buffer.getNumSamples(), oldGain, gain);

            juce::dsp::AudioBlock<float> block{ buffer };
            distortion.process(juce::dsp::ProcessContextReplacing<float>{ block });

            buffer.applyGainRamp(0, buffer.getNumSamples(), 1.0f / oldGain, 1.0f / gain);
        }
    }

    oldGain = gain;
}

void DistortionData::updateParameters(bool enable, float newDrive, Function function)
{
    isEnabled = enable;
    gain = (1.0f + newDrive);
    
    switch (function)
    {
    case Function::tanh:
        distortion.functionToUse = [](float x) { return static_cast<float>(std::tanh(x)); };
        break;
    case Function::hardClip:
        distortion.functionToUse = [](float x) { return std::clamp(x, -1.0f, 1.0f); };
        break;
    case Function::crack:
        distortion.functionToUse = crackPlaceholder;
        break;
    case Function::shatter:
        distortion.functionToUse = [](float x) { return (x < -1.0f || x > 1.0f) ? (std::clamp(x, -1.0f, 1.0f) - x + (std::signbit(x) ? 1 : -1)) : x; }; // wavefold
    default:
        jassert(false);
        break;
    }
}

void DistortionData::reset()
{
    distortion.reset();
}

// this was originally going to be a bitcrush effect
void DistortionData::crackBuffer(juce::AudioBuffer<float>& buffer, float gain)
{
    for (int channel{ 0 }; channel < buffer.getNumChannels(); ++channel)
    {
        for (int sample{ 0 }; sample < buffer.getNumSamples(); ++sample)
        {
            float crushedSample{ static_cast<float>(static_cast<int>(buffer.getSample(channel, sample) * 100.0f / gain) * gain / 100.0f) };
            buffer.setSample(channel, sample, crushedSample);
        }
    }
}