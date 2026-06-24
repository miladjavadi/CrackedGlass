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

    juce::Slider slider;
    juce::Label label;
    int m_padding{}; // distance between label and slider

    LabeledRotarySlider(const juce::String& labelText, juce::AudioProcessorValueTreeState& apvts, const juce::String& parameterID, bool useTextBox = false);
    ~LabeledRotarySlider() override;

    bool hasTextBox{};

    void setColour(ColourIds colourId, const juce::Colour& colour);

    void setPadding(int padding)
    {
        m_padding = padding;
    }

    int getPadding()
    {
        return m_padding;
    }

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabeledRotarySlider)
};
