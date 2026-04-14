/*
  ==============================================================================

    AdsrGraphComponent.h
    Created: 12 Apr 2026 3:36:32pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrGraphComponent  : public juce::Component, public juce::AudioProcessorValueTreeState::Listener
{
public:
    AdsrGraphComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& attackParameterID, const juce::String& decayParameterID, const juce::String& sustainParameterID, const juce::String& releaseParameterID, juce::Colour mainColour);
    ~AdsrGraphComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Colour borderColour;

    juce::AudioProcessorValueTreeState& m_apvts;
    juce::String m_attackParameterID;
    juce::String m_decayParameterID;
    juce::String m_sustainParameterID;
    juce::String m_releaseParameterID;

    float maxAttack{};
    float maxDecay{};
    float maxRelease{};
    float maxEnvelopeDuration{};

    float lastAttack{};
    float lastDecay{};
    float lastSustain{};
    float lastRelease{};

    void parameterChanged (const juce::String& parameterID, float newValue) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrGraphComponent)
};
