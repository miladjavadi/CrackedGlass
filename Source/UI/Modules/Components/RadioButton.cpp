/*
  ==============================================================================

    RadioButton.cpp
    Created: 15 Apr 2026 7:55:39pm
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RadioButton.h"

//==============================================================================
RadioButton::RadioButton()
    : juce::TextButton{}
{

}

RadioButton::RadioButton(const juce::String& buttonName)
    : juce::TextButton{ buttonName }
{

}

RadioButton::RadioButton(const juce::String& buttonName, const juce::String& toolTip)
    : juce::TextButton{ buttonName, toolTip }
{

}

RadioButton::~RadioButton()
{
}

void RadioButton::paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    juce::Rectangle<float> bounds{ getLocalBounds().toFloat() };

    juce::Colour backgroundColour{ getToggleState() ? findColour(juce::TextButton::ColourIds::buttonOnColourId) : findColour(juce::TextButton::ColourIds::buttonColourId) };
    juce::Colour textColour{ getToggleState() ? findColour(juce::TextButton::ColourIds::textColourOnId) : findColour(juce::TextButton::ColourIds::textColourOffId) };

    if (shouldDrawButtonAsDown && !getToggleState())
    {
        backgroundColour = backgroundColour.darker();
        textColour = textColour.darker();
    }

    g.setColour(backgroundColour);

    g.fillAll();

    g.setColour(textColour);
    g.setFont(bounds.getHeight() * 0.8f);
    g.drawText(getButtonText().toUpperCase(), bounds, juce::Justification::centred);
}