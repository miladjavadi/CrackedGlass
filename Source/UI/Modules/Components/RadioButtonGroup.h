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
class RadioButtonGroup  : public juce::Component
{
public:
    RadioButtonGroup(juce::AudioParameterChoice* radioParameter,
        const juce::Colour& buttonOffColour,
        const juce::Colour& buttonOnColour,
        const juce::Colour& textColourOff,
        const juce::Colour& textColourOn,
        const juce::Colour& outlineColour);
    ~RadioButtonGroup() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RadioButtonGroup)
};
