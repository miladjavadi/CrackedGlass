/*
  ==============================================================================

    DistortionComponent.cpp
    Created: 13 Apr 2026 6:38:39pm
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& enableParameterID, const juce::String& functionParameterID, const juce::String& driveParameterID, const juce::String& mixParameterID)
    : SynthModule{ "Distortion", juce::Colours::red, true, apvts, "DISTORTIONENABLE" }
    , functionSelector{ apvts, functionParameterID, juce::FlexBox::Direction::row, 2, 2, getActiveColourPalette().backgroundColour, getActiveColourPalette().borderColour, getActiveColourPalette().borderColour, getActiveColourPalette().titleColour, getActiveColourPalette().borderColour }
{
    addAndMakeVisible(functionSelector);

    setSliderWithLabel(driveSlider, driveLabel, driveSliderAttachment, apvts, driveParameterID, juce::Slider::SliderStyle::RotaryVerticalDrag, false);
    setSliderWithLabel(mixSlider, mixLabel, mixSliderAttachment, apvts, mixParameterID, juce::Slider::SliderStyle::RotaryVerticalDrag, false);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
    SynthModule::paint(g);
}

void DistortionComponent::resized()
{
    SynthModule::resized();

    constexpr int padding{ 10 };
    constexpr int margin{ 10 };
    const juce::Rectangle<int> bounds{ getLocalBounds().reduced (margin) };
    const juce::Rectangle<int> sliderBounds{ bounds.reduced(0, 0) };

    const int rotorSize{ (sliderBounds.getWidth() - 3 * padding) / 2 };
    constexpr int labelHeight{ 20 };
    const int sliderStartY{ bounds.getBottom() - rotorSize - margin };

    driveSlider.setBounds (sliderBounds.getX() + padding, sliderStartY, rotorSize, rotorSize);
    driveLabel.setBounds (driveSlider.getX(), driveSlider.getY() - labelHeight, rotorSize, labelHeight);

    mixSlider.setBounds (driveSlider.getRight() + padding, driveSlider.getY(), rotorSize, rotorSize);
    mixLabel.setBounds (mixSlider.getX(), mixSlider.getY() - labelHeight, rotorSize, labelHeight);

    functionSelector.setBounds (sliderBounds.getX() + padding + margin, driveLabel.getY() - 2 * labelHeight - padding - margin - 10, sliderBounds.getWidth() - 2 * (padding + margin), 2 * labelHeight + 10);
}

void DistortionComponent::updateDerivedComponentColours()
{
    setComponentColoursFromPalette(functionSelector);
    setComponentColoursFromPalette(driveSlider);
    setComponentColoursFromPalette(mixSlider);
    setComponentColoursFromPalette(driveLabel);
    setComponentColoursFromPalette(mixLabel);
}