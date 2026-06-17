/*
  ==============================================================================

    SynthModule.cpp
    Created: 15 Apr 2026 10:06:14am
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SynthModule.h"

//==============================================================================
SynthModule::SynthModule(const juce::String& title, const juce::Colour& mainHue, bool canBeDisabled, juce::AudioProcessorValueTreeState& apvts, const juce::String& enableParameterID)
    : m_title{ title }
    , m_mainHue{ mainHue }
    , m_canBeDisabled{ canBeDisabled }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setColourPaletteFromMainHue();

    if (m_canBeDisabled)
    {
        titleButton.setClickingTogglesState(true);
        titleButton.setToggleState(m_enabled, juce::dontSendNotification);
        
        titleButton.setButtonText(m_title.toUpperCase());
        titleButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, enableParameterID, titleButton);
        m_enabled = titleButton.getToggleState();
        titleButton.onClick = [this]
        {
            m_enabled = titleButton.getToggleState();
            sendLookAndFeelChange();
            repaint();
        };
        addAndMakeVisible(titleButton);
    }
    else
    {
        titleLabel.setText(m_title.toUpperCase(), juce::NotificationType::dontSendNotification);
        titleLabel.setFont(juce::Font(20.0f, 3));
        titleLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(titleLabel);
    }

    updateBaseComponentColours();
}

SynthModule::~SynthModule()
{
}

void SynthModule::paint(juce::Graphics& g)
{
    g.fillAll(getActiveColourPalette().backgroundColour);

    g.setColour(getActiveColourPalette().borderColour);
    g.drawRect(getLocalBounds(), 2);
}

void SynthModule::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    if (m_canBeDisabled)
    {
        titleButton.setBounds(0, 0, 140, 35);
    }
    else
    {
        titleLabel.setBounds(0, 0, 140, 30);
    }
}

void SynthModule::setColourPaletteFromMainHue()
{
    m_colourPalette.backgroundColour = m_mainHue.withAlpha(0.15f).withBrightness(0.9f).withSaturation(0.9f);
    m_colourPalette.labelColour = m_mainHue.withBrightness(1.0f).withSaturation(0.3f);
    m_colourPalette.borderColour = m_mainHue.withBrightness(1.0f).withSaturation(0.6f);
    m_colourPalette.titleColour = m_mainHue.withBrightness(0.1f).withSaturation(0.9f);
    m_colourPalette.sliderFillColour = m_mainHue.withBrightness(1.0f).withSaturation(0.2f);
    m_colourPalette.deadColour = m_mainHue.withBrightness(0.5f).withSaturation(0.7f);
}

void SynthModule::setColourPaletteFromColour(const juce::Colour& colour)
{
    setMainHueFromColour(colour);
    setColourPaletteFromMainHue();
}

void SynthModule::updateBaseComponentColours()
{
    titleButton.setColour(juce::TextButton::ColourIds::buttonColourId, getActiveColourPalette().backgroundColour);
    titleButton.setColour(juce::TextButton::ColourIds::textColourOffId, getActiveColourPalette().borderColour);
    titleButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, getActiveColourPalette().borderColour);
    titleButton.setColour(juce::TextButton::ColourIds::textColourOnId, getActiveColourPalette().titleColour);

    titleLabel.setColour(juce::Label::ColourIds::backgroundColourId, getActiveColourPalette().borderColour);
    titleLabel.setColour(juce::Label::ColourIds::textColourId, getActiveColourPalette().titleColour);
}

void SynthModule::lookAndFeelChanged()
{
    updateBaseComponentColours();
    updateDerivedComponentColours();
}