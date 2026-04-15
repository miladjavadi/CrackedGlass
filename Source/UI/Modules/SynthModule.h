/*
  ==============================================================================

    SynthModule.h
    Created: 15 Apr 2026 10:06:14am
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SynthModule  : public juce::Component
{
public:
    SynthModule();
    ~SynthModule() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Colour mainHue;

    juce::Colour backgroundColour;
    juce::Colour labelColour;
    juce::Colour borderColour;
    juce::Colour titleColour;
    juce::Colour sliderFillColour;
    juce::Colour deadColour;

    juce::Colour backgroundColour_greyscale;
    juce::Colour labelColour_greyscale;
    juce::Colour borderColour_greyscale;
    juce::Colour titleColour_greyscale;
    juce::Colour sliderFillColour_greyscale;
    juce::Colour deadColour_greyscale;

    void setSliderParams(juce::Slider& slider, bool useTextBox = false);
    void setLabelParams(juce::Label& label);
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, bool useTextBox = true);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthModule)
};
