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
    
    parameterSliders.push_back(std::make_unique<LabeledRotarySlider>("Drive", apvts, driveParameterID));
    parameterSliders.push_back(std::make_unique<LabeledRotarySlider>("Mix", apvts, mixParameterID));

    setComponentColoursFromPalette(parameterSliders);

    for (auto& slider : parameterSliders)
    {
        addAndMakeVisible(*slider);
    }
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

    constexpr int sliderLayoutHeight{ 120 };
    const juce::Rectangle<int> bounds{ getLocalBounds().reduced (margin) };
    const juce::Rectangle<int> sliderBounds{ padding + margin, bounds.getBottom() - sliderLayoutHeight, bounds.getWidth() - 2 * margin, sliderLayoutHeight};

    constexpr int labelHeight{ 20 };

    layoutSliderArray(parameterSliders, sliderBounds, padding);

    functionSelector.setBounds (sliderBounds.getX() + padding, sliderBounds.getY() - 2 * labelHeight - padding - margin - 10, sliderBounds.getWidth() - 2 * (padding), 2 * labelHeight + 10);
}

void DistortionComponent::updateDerivedComponentColours()
{
    setComponentColoursFromPalette(functionSelector);
    setComponentColoursFromPalette(parameterSliders);
}