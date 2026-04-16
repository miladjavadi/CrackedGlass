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
#include <cmath>

//==============================================================================
RadioButtonGroup::RadioButtonGroup(juce::AudioProcessorValueTreeState& apvts,
    const juce::String& radioParameterID,
    const juce::FlexBox::Direction& direction,
    const juce::Colour& buttonOffColour,
    const juce::Colour& buttonOnColour,
    const juce::Colour& textColourOff,
    const juce::Colour& textColourOn,
    const juce::Colour& outlineColour)
    : m_apvts{ apvts }
    , m_radioParameter{ dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter(radioParameterID)) }
    , m_direction{ direction }
    , m_buttonOffColour{ buttonOffColour }
    , m_buttonOnColour{ buttonOnColour }
    , m_textColourOff{ textColourOff }
    , m_textColourOn{ textColourOn }
    , m_outlineColour{ outlineColour }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    apvts.addParameterListener(radioParameterID, this);

    const juce::StringArray& choices{ m_radioParameter->choices };

    buttonArray.reserve(choices.size());

    for (size_t i{ 0 }; i < choices.size(); ++i)
    {
        buttonArray.push_back(std::make_unique<RadioButton>(choices[i], choices[i]));
        buttonArray[i]->setColour(juce::TextButton::ColourIds::buttonColourId, m_buttonOffColour);
        buttonArray[i]->setColour(juce::TextButton::ColourIds::buttonOnColourId, m_buttonOnColour);
        buttonArray[i]->setColour(juce::TextButton::ColourIds::textColourOffId, m_textColourOff);
        buttonArray[i]->setColour(juce::TextButton::ColourIds::textColourOnId, m_textColourOn);
        buttonArray[i]->setRadioGroupId(1);
        buttonArray[i]->setClickingTogglesState(true);
        buttonArray[i]->onClick = [this, i]() { setParameterValue(static_cast<int>(i)); };
        addAndMakeVisible(*(buttonArray.back()));
    }

    parameterChanged(radioParameterID, static_cast<float>(m_radioParameter->getIndex()));
}

RadioButtonGroup::~RadioButtonGroup()
{
    m_apvts.removeParameterListener(m_radioParameter->getParameterID(), this);
}

void RadioButtonGroup::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
}

void RadioButtonGroup::paintOverChildren (juce::Graphics& g)
{
    g.setColour(m_outlineColour);
    g.drawRect(getLocalBounds(), 1.0f);

    int numberOfButtons{ static_cast<int>(buttonArray.size()) };
    int buttonWidth{ getLocalBounds().getWidth() / numberOfButtons };
    int buttonHeight{ getLocalBounds().getHeight() / numberOfButtons };

    switch (m_direction)
    {
    case juce::FlexBox::Direction::row:
    case juce::FlexBox::Direction::rowReverse:
        for (int i{ 1 }; i < numberOfButtons; ++i)
        {
            g.drawVerticalLine(getLocalBounds().getX() + i * buttonWidth, getLocalBounds().getY(), getLocalBounds().getBottom());
        }
        break;
    case juce::FlexBox::Direction::column:
    case juce::FlexBox::Direction::columnReverse:
        for (int i{ 1 }; i < numberOfButtons; ++i)
        {
            g.drawHorizontalLine(getLocalBounds().getY() + i * buttonHeight, getLocalBounds().getX(), getLocalBounds().getRight());
        }
        break;
    }
    
}

void RadioButtonGroup::resized()
{
    juce::FlexBox fb;
    fb.flexDirection = m_direction;

    for (std::unique_ptr<RadioButton>& button : buttonArray)
    {
        fb.items.add(juce::FlexItem(*button).withFlex(1));
    }

    fb.performLayout(getLocalBounds());
}

void RadioButtonGroup::setAndUpdateColours(const juce::Colour& buttonOffColour,
    const juce::Colour& buttonOnColour,
    const juce::Colour& textColourOff,
    const juce::Colour& textColourOn,
    const juce::Colour& outlineColour)
{
    m_buttonOffColour = buttonOffColour;
    m_buttonOnColour = buttonOnColour;
    m_textColourOff = textColourOff;
    m_textColourOn = textColourOn;
    m_outlineColour = outlineColour;

    for (std::unique_ptr<RadioButton>& button : buttonArray)
    {
        button->setColour(juce::TextButton::ColourIds::buttonColourId, m_buttonOffColour);
        button->setColour(juce::TextButton::ColourIds::buttonOnColourId, m_buttonOnColour);
        button->setColour(juce::TextButton::ColourIds::textColourOffId, m_textColourOff);
        button->setColour(juce::TextButton::ColourIds::textColourOnId, m_textColourOn);
        button->repaint();
    }

    repaint();
}

void RadioButtonGroup::setParameterValue(int newValue)
{
    m_radioParameter->beginChangeGesture();
    //m_radioParameter->setValueNotifyingHost(m_radioParameter->convertFrom0to1(newValue));
    m_radioParameter->setValueNotifyingHost(m_radioParameter->convertTo0to1(newValue));
    m_radioParameter->endChangeGesture();
}

void RadioButtonGroup::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == m_radioParameter->getParameterID())
    {
        size_t selectedIndex{ static_cast<size_t>(std::roundf(newValue)) };

        jassert(selectedIndex < getNumButtons());

        for (size_t i{ 0 }; i < getNumButtons(); ++i)
        {
            buttonArray[i]->setToggleState(i == selectedIndex, juce::NotificationType::sendNotification);
        }
    }
}