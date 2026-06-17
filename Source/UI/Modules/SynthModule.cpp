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
SynthModule::SynthModule(const juce::String& title, const juce::Colour& mainHue, bool canBeDisabled, bool initialState)
    : m_title{ title }
    , m_mainHue{ mainHue }
    , m_canBeDisabled{ canBeDisabled }
    , m_enabled{ initialState }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

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