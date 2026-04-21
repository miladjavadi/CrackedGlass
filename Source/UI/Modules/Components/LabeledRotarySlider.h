/*
  ==============================================================================

    LabeledRotarySlider.h
    Created: 20 Apr 2026 10:23:12pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LabeledRotarySlider  : public juce::Component
{
public:
    enum ColourIds
    {
        sliderFillColourId,
        sliderOutlineColourId,
        labelColourId,
        boxTextColourId,
    };

    LabeledRotarySlider();
    ~LabeledRotarySlider() override;

    bool hasTextBox{ false };

    void setColour(ColourIds colourId, juce::Colour colour);
    void setPadding(int padding);
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider slider{};
    juce::Label label{};
    int padding{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabeledRotarySlider)
};
