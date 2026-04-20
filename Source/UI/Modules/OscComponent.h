/*
  ==============================================================================

    OscComponent.h
    Created: 9 Apr 2026 12:07:02pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "Components/RadioButtonGroup.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& waveshapeSelectorID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Colour mainColour{ juce::Colours::cadetblue };
    juce::Colour backgroundColour = mainColour.withAlpha(0.15f);
    juce::Colour labelColour = mainColour.withBrightness(1.0f).withSaturation(0.3f);
    juce::Colour borderColour = mainColour.withBrightness(1.0f).withSaturation(0.6f);
    juce::Colour titleColour = mainColour.withBrightness(0.1f);
    juce::Colour sliderFillColour = mainColour.withBrightness(1.0f).withSaturation(0.2f);
    juce::Colour deadColour = mainColour.withBrightness(0.5f).withSaturation(0.7f);

    juce::Label titleLabel;

    juce::Slider coarsePitchSlider;
    juce::Slider finePitchSlider;
    juce::Slider lfoFrequencySlider;
    juce::Slider lfoDepthSlider;

    RadioButtonGroup waveshapeSelector;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> coarsePitchSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> finePitchSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoFrequencySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoDepthSliderAttachment;

    juce::Label coarsePitchLabel{ "Coarse", "Coarse" };
    juce::Label finePitchLabel{ "Fine", "Fine" };
    juce::Label fmFrequencyLabel{ "FM Frequency", "FM Frequency" };
    juce::Label fmDepthLabel{ "FM Depth", "FM Depth" };

    juce::Label waveshapeLabel{ "Shape", "Shape" };

    void setSliderParams(juce::Slider& slider);
    void setLabelParams(juce::Label& label);
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
