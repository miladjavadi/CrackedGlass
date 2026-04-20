/*
  ==============================================================================

    RadioButtonGroup.h
    Created: 15 Apr 2026 7:51:43pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "RadioButton.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class RadioButtonGroup  : public juce::Component, public juce::AudioProcessorValueTreeState::Listener
{
public:
    RadioButtonGroup(juce::AudioProcessorValueTreeState& apvts,
        const juce::String& radioParameterID,
        const juce::FlexBox::Direction& direction,
        const juce::Colour& buttonOffColour,
        const juce::Colour& buttonOnColour,
        const juce::Colour& textColourOff,
        const juce::Colour& textColourOn,
        const juce::Colour& outlineColour);
    ~RadioButtonGroup() override;

    void paint (juce::Graphics&) override;
    void paintOverChildren(juce::Graphics& g) override;
    void resized() override;
    void setAndUpdateColours(const juce::Colour& buttonOffColour,
        const juce::Colour& buttonOnColour,
        const juce::Colour& textColourOff,
        const juce::Colour& textColourOn,
        const juce::Colour& outlineColour);
    size_t getNumButtons()
    {
        return buttonArray.size();
    }

private:
    juce::AudioProcessorValueTreeState& m_apvts;
    juce::String m_radioParameterID;
    std::vector<std::unique_ptr<RadioButton>> buttonArray{};

    juce::FlexBox::Direction m_direction{};
    juce::Colour m_buttonOffColour{};
    juce::Colour m_buttonOnColour{};
    juce::Colour m_textColourOff{};
    juce::Colour m_textColourOn{};
    juce::Colour m_outlineColour{};

    void setParameterValue(int newValue);
    void parameterChanged(const juce::String& parameterID, float newValue) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RadioButtonGroup)
};
