/*
  ==============================================================================

    SynthModule.cpp
    Created: 15 Apr 2026 10:06:14am
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SynthModule.h"
#include "Components/RadioButtonGroup.h"
#include "Components/AdsrGraphComponent.h"

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

void SynthModule::setComponentColoursFromPalette(juce::Component& component)
{
    if (auto* c = dynamic_cast<juce::Slider*>(&component))
    {
        component.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, getActiveColourPalette().borderColour);
        component.setColour(juce::Slider::ColourIds::thumbColourId, getActiveColourPalette().sliderFillColour);
        component.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, getActiveColourPalette().deadColour);
        component.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colour(0));
        component.setColour(juce::Slider::ColourIds::textBoxTextColourId, getActiveColourPalette().labelColour);
    }
    else if (auto* c = dynamic_cast<juce::TextButton*>(&component))
    {
        component.setColour(juce::TextButton::ColourIds::buttonColourId, getActiveColourPalette().backgroundColour);
        component.setColour(juce::TextButton::ColourIds::textColourOffId, getActiveColourPalette().borderColour);
        component.setColour(juce::TextButton::ColourIds::buttonOnColourId, getActiveColourPalette().borderColour);
        component.setColour(juce::TextButton::ColourIds::textColourOnId, getActiveColourPalette().titleColour);
    }
    else if (auto* c = dynamic_cast<juce::Label*>(&component)) // use this for parameter labels only
    {
        component.setColour (juce::Label::ColourIds::textColourId, getActiveColourPalette().labelColour);
    }
    else if (auto* c = dynamic_cast<RadioButtonGroup*>(&component))
    {
        c->setAndUpdateColours(
            getActiveColourPalette().backgroundColour,
            getActiveColourPalette().borderColour,
            getActiveColourPalette().borderColour,
            getActiveColourPalette().titleColour,
            getActiveColourPalette().borderColour
        );
    }
    else if (auto* c = dynamic_cast<AdsrGraphComponent*>(&component))
    {
        c->setBorderColour(getActiveColourPalette().borderColour);
    }
    else
    {
        jassert(false && "setComponentColoursFromPalette() is incompatible with this component type.");
    }
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
    setComponentColoursFromPalette(titleButton);
    
    // titleLabel colour-setting is handled separately, since the "juce::Label" case in setComponentColoursFromPalette() is reserved for parameter labels
    titleLabel.setColour(juce::Label::ColourIds::backgroundColourId, getActiveColourPalette().borderColour);
    titleLabel.setColour(juce::Label::ColourIds::textColourId, getActiveColourPalette().titleColour);
}

void SynthModule::lookAndFeelChanged()
{
    updateBaseComponentColours();
    updateDerivedComponentColours();
}

