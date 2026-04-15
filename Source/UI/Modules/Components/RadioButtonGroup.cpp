/*
  ==============================================================================

    RadioButtonGroup.cpp
    Created: 15 Apr 2026 7:51:43pm
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RadioButtonGroup.h"
#include "RadioButton.h"

//==============================================================================
RadioButtonGroup::RadioButtonGroup(juce::AudioParameterChoice* radioParameter,
    const juce::Colour& buttonOffColour,
    const juce::Colour& buttonOnColour,
    const juce::Colour& textColourOff,
    const juce::Colour& textColourOn,
    const juce::Colour& outlineColour)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    const juce::StringArray& choices{ radioParameter->choices };

    std::vector<std::unique_ptr<RadioButton>> buttonArray{};
    buttonArray.reserve(choices.size());

    for (const juce::String& choice : choices)
    {
        buttonArray.push_back(std::make_unique<RadioButton>(choice, choice));
        buttonArray.back()->setColour(juce::TextButton::ColourIds::buttonColourId, buttonOffColour);
        buttonArray.back()->setColour(juce::TextButton::ColourIds::buttonOnColourId, buttonOnColour);
        buttonArray.back()->setColour(juce::TextButton::ColourIds::textColourOffId, textColourOff);
        buttonArray.back()->setColour(juce::TextButton::ColourIds::textColourOnId, textColourOn);
        addAndMakeVisible(*(buttonArray.back()));
    }
}

RadioButtonGroup::~RadioButtonGroup()
{
}

void RadioButtonGroup::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void RadioButtonGroup::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
