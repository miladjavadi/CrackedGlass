/*
  ==============================================================================

    AdsrComponent.h
    Created: 9 Feb 2026 5:55:35pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "AdsrGraphComponent.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent (const juce::String& name, juce::AudioProcessorValueTreeState& apvts, const juce::String& attackParameterID, const juce::String& decayParameterID, const juce::String& sustainParameterId, const juce::String& releaseParameterId, juce::Colour mainColour = juce::Colours::orange, bool canBeDisabled = false, const juce::String& enableParameterID = "");
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    bool m_canBeDisabled;
    juce::String m_name;

    juce::Colour m_mainColour;

    juce::Colour backgroundColour;
    juce::Colour labelColour;
    juce::Colour borderColour;
    juce::Colour titleColour;
    juce::Colour sliderFillColour;
    juce::Colour deadColour;

    AdsrGraphComponent adsrGraph;

    juce::Label titleLabel;

    juce::TextButton titleButton{ "Filter", "Filter" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> titleButtonAttachment;

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

    void setSliderParams(juce::Slider& slider, bool useTextBox = true);
    void setLabelParams(juce::Label& label);
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, bool useTextBox = true);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
