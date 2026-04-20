/*
  ==============================================================================

    DistortionData.h
    Created: 13 Apr 2026 5:47:45pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <functional>

class DistortionData
{
public:
    enum Function
    {
        tanh,
        hardClip,
        crack,
        shatter,
        numFunctions,
    };

    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(bool enable, float newDrive, Function function);
    void reset();

private:
    juce::dsp::WaveShaper<float> distortion;
    //std::function<float(float)> crush{ [this](float x)
    //    {
    //        return static_cast<float>(static_cast<int>(x * 10.0f / gain) * gain);
    //    }
    //};
    float (*crackPlaceholder)(float) { [] (float x) { return 0.0f; } };

    float oldGain{ 1.0f };
    float gain{ 1.0f };

    bool isPrepared{ false };
    bool isEnabled{ false };

    void crackBuffer(juce::AudioBuffer<float>& buffer, float drive);

};