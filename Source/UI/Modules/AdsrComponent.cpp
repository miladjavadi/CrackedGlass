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

    setSliderWithLabel(attackSlider, attackLabel, attackAttachment, apvts, attackParameterID, false);
    setSliderWithLabel(decaySlider, decayLabel, decayAttachment, apvts, decayParameterID, false);
    setSliderWithLabel(sustainSlider, sustainLabel, sustainAttachment, apvts, sustainParameterID, false);
    setSliderWithLabel(releaseSlider, releaseLabel, releaseAttachment, apvts, releaseParameterID, false);

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

void AdsrComponent::setSliderParams(juce::Slider& slider, bool useTextBox)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    if (useTextBox)
    {
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    }
    else
    {
        slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    }
    setComponentColoursFromPalette(slider);

    addAndMakeVisible (slider);
}

void AdsrComponent::setLabelParams (juce::Label& label)
{
    setComponentColoursFromPalette(label);
    label.setFont(18.0f);
    label.setJustificationType(juce::Justification::centred);
    label.setText(label.getText().toUpperCase(), juce::dontSendNotification);
    addAndMakeVisible(label);
}

void AdsrComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, bool useTextBox)
{
    setSliderParams(slider, useTextBox);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramID, slider);
    setLabelParams(label);
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