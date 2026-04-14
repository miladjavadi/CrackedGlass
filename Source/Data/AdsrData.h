/*
  ==============================================================================

    AdsrData.h
    Created: 9 Feb 2026 5:56:15pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR (const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;
};
