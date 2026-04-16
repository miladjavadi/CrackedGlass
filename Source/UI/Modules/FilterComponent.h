/*
  ==============================================================================

    FilterComponent.h
    Created: 10 Apr 2026 10:02:06pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "Components/RadioButtonGroup.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& filterTypeSelectorID);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Colour mainColour{ juce::Colours::limegreen };
    juce::Colour backgroundColour = mainColour.withAlpha(0.15f);
    juce::Colour labelColour = mainColour.withBrightness(1.0f).withSaturation(0.3f);
    juce::Colour borderColour = mainColour.withBrightness(1.0f).withSaturation(0.6f);
    juce::Colour titleColour = mainColour.withBrightness(0.1f);
    juce::Colour sliderFillColour = mainColour.withBrightness(1.0f).withSaturation(0.2f);
    juce::Colour deadColour = mainColour.withBrightness(0.5f).withSaturation(0.7f);

    //juce::ComboBox filterTypeSelector;
    //std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;
    //juce::Label filterTypeLabel{ "Type", "Type" };

    RadioButtonGroup filterTypeSelector;

    juce::Slider cutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffFrequencySliderAttachment;
    juce::Label cutoffFrequencyLabel{ "Cutoff", "Cutoff" };

    juce::Slider resonanceSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceSliderAttachment;
    juce::Label resonanceLabel{ "Resonance", "Resonance" };

    juce::TextButton titleButton{ "Filter", "Filter" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> titleButtonAttachment;

    void setSliderParams(juce::Slider& slider, bool useTextBox = true);
    void setLabelParams(juce::Label& label);
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, bool useTextBox = true);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
