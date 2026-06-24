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

    setSliderWithLabel(attackSlider, attackLabel, attackAttachment, apvts, attackParameterID, juce::Slider::SliderStyle::RotaryVerticalDrag, false);
    setSliderWithLabel(decaySlider, decayLabel, decayAttachment, apvts, decayParameterID, juce::Slider::SliderStyle::RotaryVerticalDrag, false);
    setSliderWithLabel(sustainSlider, sustainLabel, sustainAttachment, apvts, sustainParameterID, juce::Slider::SliderStyle::RotaryVerticalDrag, false);
    setSliderWithLabel(releaseSlider, releaseLabel, releaseAttachment, apvts, releaseParameterID, juce::Slider::SliderStyle::RotaryVerticalDrag, false);

    addAndMakeVisible(adsrGraph);
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
    juce::Rectangle<int> bounds{ getLocalBounds().reduced (margin) };
    bounds.reduce(30, 0);
    const int rotorSize{ (bounds.getWidth() - 5 * padding) / 4 };
    const int sliderStartX{ bounds.getX() + padding };
    const int sliderStartY{ bounds.getBottom() - rotorSize };
    constexpr int labelHeight{ 20 };

    attackSlider.setBounds(sliderStartX, sliderStartY, rotorSize, rotorSize);
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY() - labelHeight, rotorSize, labelHeight);

    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, rotorSize, rotorSize);
    decayLabel.setBounds(decaySlider.getX(), decaySlider.getY() - labelHeight, rotorSize, labelHeight);

    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, rotorSize, rotorSize);
    sustainLabel.setBounds(sustainSlider.getX(), sustainSlider.getY() - labelHeight, rotorSize, labelHeight);

    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, rotorSize, rotorSize);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY() - labelHeight, rotorSize, labelHeight);

    const int graphWidth{ bounds.getWidth() - 2 * padding };
    const int graphHeight{ 70 };
    adsrGraph.setBounds(bounds.getX() + padding, attackLabel.getY() - graphHeight - padding, graphWidth, graphHeight);
}

void AdsrComponent::updateDerivedComponentColours()
{
    setComponentColoursFromPalette(adsrGraph);
    setComponentColoursFromPalette(attackSlider);
    setComponentColoursFromPalette(decaySlider);
    setComponentColoursFromPalette(sustainSlider);
    setComponentColoursFromPalette(releaseSlider);
    setComponentColoursFromPalette(attackLabel);
    setComponentColoursFromPalette(decayLabel);
    setComponentColoursFromPalette(sustainLabel);
    setComponentColoursFromPalette(releaseLabel);
}