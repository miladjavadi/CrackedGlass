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

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    juce::Label attackLabel{ "Attack", "Attack" };
    juce::Label decayLabel{ "Decay", "Decay" };
    juce::Label sustainLabel{ "Sustain", "Sustain" };
    juce::Label releaseLabel{ "Release", "Release" };

    void updateDerivedComponentColours() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
