/*
  ==============================================================================

    DistortionComponent.h
    Created: 13 Apr 2026 6:38:39pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "Components/RadioButtonGroup.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistortionComponent  : public juce::Component
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& enableParameterID, const juce::String& functionParameterID, const juce::String& driveParameterID, const juce::String& mixParameterID);
    ~DistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Colour mainColour{ juce::Colours::red };
    juce::Colour backgroundColour = mainColour.withAlpha(0.15f);
    juce::Colour labelColour = mainColour.withBrightness(1.0f).withSaturation(0.3f);
    juce::Colour borderColour = mainColour.withBrightness(1.0f).withSaturation(0.6f);
    juce::Colour titleColour = mainColour.withBrightness(0.1f);
    juce::Colour sliderFillColour = mainColour.withBrightness(1.0f).withSaturation(0.2f);
    juce::Colour deadColour = mainColour.withBrightness(0.5f).withSaturation(0.7f);

    RadioButtonGroup functionSelector;

    juce::Slider driveSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    juce::Label driveLabel{ "Drive", "Drive" };

    juce::Slider mixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;
    juce::Label mixLabel{ "Mix", "Mix" };

    juce::TextButton titleButton{ "Distortion", "Distortion" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> titleButtonAttachment;

    void setSliderParams(juce::Slider& slider, bool useTextBox = true);
    void setLabelParams(juce::Label& label);
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, bool useTextBox = true);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};
