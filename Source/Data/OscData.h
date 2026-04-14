/*
  ==============================================================================

    OscData.h
    Created: 9 Apr 2026 10:55:46am
    Author:  milad

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    enum Waveshape
    {
        sine,
        saw,
        square,
        whiteNoise,
        nWaveshapes,
    };

    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    void setWaveshape (Waveshape selection);
    void setWaveFrequency (int midiNoteNumber, bool updateLastMidiNote = true);
    void getNextAudioBlock (juce::dsp::AudioBlock<float>& block);
    void setLFOParams (float depth, float frequency);
    void setTuningFactor (int coarse, int fine);
    void setPitchBend(int pitchWheelValue);

private:
    int lastMidiNote{ 0 };
    juce::dsp::Oscillator<float> lfo{ [](float x) { return std::sin (x); } };
    float fm{ 0.0f };
    float fmDepth{ 0.0f };
    float tuningFactor{ 1.0f };
    float pitchBend{ 1.0f };
    juce::Random whiteNoiseRandom;
};