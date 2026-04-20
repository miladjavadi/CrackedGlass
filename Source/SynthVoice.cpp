/*
  ==============================================================================

    SynthVoice.cpp
    Created: 2 Feb 2026 6:30:50pm
    Author:  milad

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setPitchBend(currentPitchWheelPosition);
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
    modAdsr.noteOn();
    isFirstBlock = true;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modAdsr.noteOff();

    if (!allowTailOff || (!adsr.isActive() && !modAdsr.isActive()))
        clearCurrentNote();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    osc.setPitchBend(newPitchWheelValue);
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepareToPlay(spec);

    adsr.setSampleRate(sampleRate);

    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);

    modAdsr.setSampleRate(sampleRate);

    cutoffFrequencyRamp.reset(samplesPerBlock, 0.01f);

    gain.prepare(spec);

    gain.setGainLinear(0.2f);

    isPrepared = true;
}

void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateFilter(bool enable, juce::dsp::StateVariableTPTFilterType filterType, float cutoffFrequency, float resonance)
{
    float modulator{ modAdsrIsEnabled.load() ? modAdsr.getNextSample() : 1.0f};
    
    float smoothedCutoffFrequency{ cutoffFrequencyRamp.getNextValue() };
    cutoffFrequencyRamp.setTargetValue(cutoffFrequency);

    filter.updateParameters(enable, filterType, smoothedCutoffFrequency, resonance, modulator);
}

void SynthVoice::updateModAdsr(bool enable, float attack, float decay, float sustain, float release)
{
    modAdsrIsEnabled.store(enable);
    modAdsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);
    
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    osc.getNextAudioBlock (audioBlock);

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);

    filter.process(synthBuffer);
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));

    if (isFirstBlock.load())
    {
        synthBuffer.applyGainRamp(0, numSamples, 0.0f, 1.0f);
        isFirstBlock.store(false);
    }

    if (!adsr.isActive() && !modAdsr.isActive())
    {
        synthBuffer.applyGainRamp(0, numSamples, 1.0f, 0.0f);
    }

    for (int i{ 0 }; i < outputBuffer.getNumChannels(); ++i)
    {
        outputBuffer.addFrom(i, startSample, synthBuffer, i, 0, numSamples);
    }

    if (!adsr.isActive() && !modAdsr.isActive())
    {
        clearCurrentNote();
    }
}