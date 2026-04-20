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
    size_t numRows,
    size_t numCols,
    const juce::Colour& buttonOffColour,
    const juce::Colour& buttonOnColour,
    const juce::Colour& textColourOff,
    const juce::Colour& textColourOn,
    const juce::Colour& outlineColour)
    : m_apvts{ apvts }
    , m_radioParameterID{ radioParameterID }
    , m_direction{ direction }
    , m_numRows{ numRows }
    , m_numCols{ numCols }
    , m_buttonOffColour{ buttonOffColour }
    , m_buttonOnColour{ buttonOnColour }
    , m_textColourOff{ textColourOff }
    , m_textColourOn{ textColourOn }
    , m_outlineColour{ outlineColour }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    apvts.addParameterListener(m_radioParameterID, this);

    if (juce::RangedAudioParameter* radioParameter = apvts.getParameter(m_radioParameterID))
    {
        if (juce::AudioParameterChoice* radioChoiceParameter = dynamic_cast<juce::AudioParameterChoice*>(radioParameter))
        {
            const juce::StringArray& choices{ radioChoiceParameter->choices };

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
        }
    }
    else
    {
        jassert(false);
    }

    jassert(getNumButtons() == m_numRows * m_numCols);

    parameterChanged(radioParameterID, apvts.getRawParameterValue(m_radioParameterID)->load());
}

RadioButtonGroup::~RadioButtonGroup()
{
    m_apvts.removeParameterListener(m_radioParameterID, this);
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

    int buttonWidth{ getLocalBounds().getWidth() / static_cast<int>(m_numCols) };
    int buttonHeight{ getLocalBounds().getHeight() / static_cast<int>(m_numRows) };

    for (size_t i{ 1 }; i < m_numCols; ++i)
    {
        g.drawVerticalLine(getLocalBounds().getX() + i * buttonWidth, getLocalBounds().getY(), getLocalBounds().getBottom());
    }
    for (size_t i{ 1 }; i < m_numRows; ++i)
    {
        g.drawHorizontalLine(getLocalBounds().getY() + i * buttonHeight, getLocalBounds().getX(), getLocalBounds().getRight());
    }
}

void RadioButtonGroup::resized()
{
    juce::Grid grid;

    using TrackInfo = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    for (size_t row{ 0 }; row < m_numRows; ++row)
    {
        grid.templateRows.add(TrackInfo(Fr(1)));
    }
    for (size_t col{ 0 }; col < m_numCols; ++col)
    {
        grid.templateColumns.add(TrackInfo(Fr(1)));
    }

    for (size_t row{ 1 }; row <= m_numRows; ++row)
    {
        for (size_t col{ 1 }; col <= m_numCols; ++col)
        {
            switch (m_direction)
            {
            case juce::FlexBox::Direction::row:
            case juce::FlexBox::Direction::rowReverse:
                grid.items.add(juce::GridItem(*(buttonArray[(row - 1) * m_numRows + (col - 1)])).withArea(row, col));
                break;
            case juce::FlexBox::Direction::column:
            case juce::FlexBox::Direction::columnReverse:
                grid.items.add(juce::GridItem(*(buttonArray[(row - 1) * m_numRows + (col - 1)])).withArea(col, row));
                break;
            default:
                jassert(false);
            }
        }
    }

    grid.performLayout(getLocalBounds());
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
    if (juce::RangedAudioParameter* radioParameter = m_apvts.getParameter(m_radioParameterID))
    {
        if (juce::AudioParameterChoice* radioChoiceParameter = dynamic_cast<juce::AudioParameterChoice*>(radioParameter))
        {
            radioChoiceParameter->beginChangeGesture();
            radioChoiceParameter->setValueNotifyingHost(radioChoiceParameter->convertTo0to1(newValue));
            radioChoiceParameter->endChangeGesture();
        }
    }
}

void RadioButtonGroup::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == m_radioParameterID)
    {
        size_t selectedIndex{ static_cast<size_t>(std::roundf(newValue)) };

        jassert(selectedIndex < getNumButtons());

        for (size_t i{ 0 }; i < getNumButtons(); ++i)
        {
            buttonArray[i]->setToggleState(i == selectedIndex, juce::NotificationType::sendNotification);
        }
    }
}