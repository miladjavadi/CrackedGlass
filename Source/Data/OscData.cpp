/*
  ==============================================================================

    OscData.cpp
    Created: 9 Apr 2026 10:55:46am
    Author:  milad

  ==============================================================================
*/

#include "OscData.h"
#include <cmath>
#include <JuceHeader.h>

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    lfo.prepare(spec);
    prepare(spec);
}

void OscData::setWaveshape(Waveshape selection)
{
    switch (selection)
    {
    case Waveshape::sine:
        initialise([](float x) { return std::sin(x); });
        break;
    case Waveshape::saw:
        initialise([](float x) { return x / juce::MathConstants<float>::pi; });
        break;
    case Waveshape::square:
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
        break;
    case Waveshape::whiteNoise:
        initialise([this](float) { return whiteRNG.nextFloat() - 0.5f; });
    default:
        jassert(false && "no bitches");
    }
}

void OscData::setWaveFrequency(int midiNoteNumber, bool updateLastMidiNote)
{
    float modulatedFrequency{ static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)) * tuningFactor * pitchBend * (1.0f + fm) };
    setFrequency(modulatedFrequency > 0.0f ? modulatedFrequency : -modulatedFrequency, true);

    if (updateLastMidiNote)
    {
        lastMidiNote = midiNoteNumber;
    }
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (size_t channel{ 0 }; channel < block.getNumChannels(); ++channel)
    {
        for (size_t sample{ 0 }; sample < block.getNumSamples(); ++sample)
        {
            fm = lfo.processSample(block.getSample(channel, sample)) * fmDepth;
        }
    }

    process(juce::dsp::ProcessContextReplacing<float> (block));
}

void OscData::setLFOParams(float depth, float frequency)
{
    lfo.setFrequency(frequency);
    fmDepth = depth;
    setWaveFrequency(lastMidiNote, false);
}

void OscData::setTuningFactor(int coarse, int fine)
{
    tuningFactor = std::pow(2, (coarse * 100 + fine) / 1200.0f);
}

void OscData::setPitchBend(int pitchWheelValue)
{
    constexpr int maxPitchBendInSemitones{ 2 };
    float pitchBendInCents{ (pitchWheelValue - 8192) * maxPitchBendInSemitones * 100.0f / 8192.0f };
    
    pitchBend = std::pow(2, pitchBendInCents / 1200.0f);
}