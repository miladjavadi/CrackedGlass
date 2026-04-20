/*
  ==============================================================================

    SynthVoice.h
    Created: 2 Feb 2026 6:30:50pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"
#include "Data/FilterData.h"

#include <JuceHeader.h>

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void updateAdsr(const float attack, const float decay, const float sustain, const float release);
    void updateFilter(bool enable, juce::dsp::StateVariableTPTFilterType filterType, float cutoffFrequency, float resonance);
    void updateModAdsr(bool enable, float attack, float decay, float sustain, float release);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    OscData& getOscillator()
    {
        return osc;
    }

private:
    juce::AudioBuffer<float> synthBuffer;
    OscData osc;
    AdsrData adsr;
    FilterData filter;
    AdsrData modAdsr;

    juce::SmoothedValue<float> cutoffFrequencyRamp;
    std::atomic<bool> modAdsrIsEnabled{ false };
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
    std::atomic<bool> isFirstBlock{ true };
};