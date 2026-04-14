/*
  ==============================================================================

    FilterData.h
    Created: 10 Apr 2026 9:22:10pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(bool enable, juce::dsp::StateVariableTPTFilterType filterType, float cutoffFrequency, float resonance, float modulator = 1.0f);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };
    bool isEnabled{ false };
};
