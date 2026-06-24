/*
  ==============================================================================

    AdsrComponent.h
    Created: 9 Feb 2026 5:55:35pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "Components/AdsrGraphComponent.h"
#include <JuceHeader.h>
#include "Components/RadioButton.h"
#include "SynthModule.h"
#include "Components/LabeledRotarySlider.h"

//==============================================================================
/*
*/
class AdsrComponent : public SynthModule
{
public:
    AdsrComponent(const juce::String& name, juce::AudioProcessorValueTreeState& apvts, const juce::String& attackParameterID, const juce::String& decayParameterID, const juce::String& sustainParameterId, const juce::String& releaseParameterId, juce::Colour mainColour = juce::Colours::orange, bool canBeDisabled = false, const juce::String& enableParameterID = "");
    ~AdsrComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    AdsrGraphComponent adsrGraph;

    std::vector<std::unique_ptr<LabeledRotarySlider>> parameterSliders{};

    void updateDerivedComponentColours() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
