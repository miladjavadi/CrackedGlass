/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 9 Feb 2026 5:55:35pm
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(const juce::String& name, juce::AudioProcessorValueTreeState& apvts, const juce::String& attackParameterID, const juce::String& decayParameterID, const juce::String& sustainParameterID, const juce::String& releaseParameterID, juce::Colour mainHue, bool canBeDisabled, const juce::String& enableParameterID)
    : SynthModule{ name, mainHue, canBeDisabled, apvts, enableParameterID }
    , adsrGraph{ apvts, attackParameterID, decayParameterID, sustainParameterID, releaseParameterID, getActiveColourPalette().borderColour }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(adsrGraph);

    parameterSliders.push_back(std::make_unique<LabeledRotarySlider>("Attack", apvts, attackParameterID));
    parameterSliders.push_back(std::make_unique<LabeledRotarySlider>("Decay", apvts, decayParameterID));
    parameterSliders.push_back(std::make_unique<LabeledRotarySlider>("Sustain", apvts, sustainParameterID));
    parameterSliders.push_back(std::make_unique<LabeledRotarySlider>("Release", apvts, releaseParameterID));

    setComponentColoursFromPalette(parameterSliders);

    for (auto& slider : parameterSliders)
    {
        addAndMakeVisible(*slider);
    }
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint(juce::Graphics& g)
{
    SynthModule::paint(g);
}

void AdsrComponent::resized()
{
    SynthModule::resized();

    constexpr int padding{ 10 };
    constexpr int margin{ 10 };
    juce::Rectangle<int> bounds{ getLocalBounds().reduced(margin + 30, margin)};
    constexpr int sliderLayoutHeight{ 110 };
    const juce::Rectangle<int> sliderBounds{ bounds.getX(), bounds.getBottom() - sliderLayoutHeight, bounds.getWidth(), sliderLayoutHeight};

    layoutSliderArray(parameterSliders, sliderBounds, padding);

    const int graphWidth{ bounds.getWidth() - 2 * padding };
    const int graphHeight{ 70 };
    adsrGraph.setBounds(bounds.getX() + padding, sliderBounds.getY() - graphHeight - padding, graphWidth, graphHeight);
}

void AdsrComponent::updateDerivedComponentColours()
{
    setComponentColoursFromPalette(adsrGraph);
    setComponentColoursFromPalette(parameterSliders);
}