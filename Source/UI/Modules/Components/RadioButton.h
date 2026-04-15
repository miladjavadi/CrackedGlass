/*
  ==============================================================================

    RadioButton.h
    Created: 15 Apr 2026 7:55:39pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RadioButton  : public juce::TextButton
{
public:
    RadioButton();
    explicit RadioButton(const juce::String& buttonName);
    RadioButton (const juce::String& buttonName, const juce::String& toolTip);
    ~RadioButton() override;

    void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RadioButton)
};
