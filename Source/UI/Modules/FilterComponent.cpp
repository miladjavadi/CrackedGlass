/*
  ==============================================================================

    FilterComponent.cpp
    Created: 10 Apr 2026 10:02:06pm
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& filterTypeSelectorID)
    : SynthModule{ "Filter", juce::Colours::limegreen, true, apvts, "FILTERENABLE" }
    , filterTypeSelector{ apvts, filterTypeSelectorID, juce::FlexBox::Direction::row, 1, 3, getActiveColourPalette().backgroundColour, getActiveColourPalette().borderColour, getActiveColourPalette().borderColour, getActiveColourPalette().titleColour, getActiveColourPalette().borderColour }
{
    addAndMakeVisible(filterTypeSelector);

    parameterSliders.push_back(std::make_unique<LabeledRotarySlider>("Cutoff", apvts, "CUTOFFFREQUENCY"));
    parameterSliders.push_back(std::make_unique<LabeledRotarySlider>("Resonance", apvts, "RESONANCE"));

    setComponentColoursFromPalette(parameterSliders);

    for (auto& slider : parameterSliders)
    {
        addAndMakeVisible(*slider);
    }
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    SynthModule::paint(g);
}

void FilterComponent::resized()
{
    SynthModule::resized();

    constexpr int padding{ 10 };
    constexpr int margin{ 10 };

    constexpr int sliderLayoutHeight{ 120 };
    const juce::Rectangle<int> bounds{ getLocalBounds().reduced (margin) };
    const juce::Rectangle<int> sliderBounds{ padding + margin, bounds.getBottom() - sliderLayoutHeight, bounds.getWidth() - 2 * margin, sliderLayoutHeight};

    constexpr int labelHeight{ 20 };

    layoutSliderArray(parameterSliders, sliderBounds, padding);

    filterTypeSelector.setBounds (sliderBounds.getX() + padding, sliderBounds.getY() - labelHeight - 2 * padding - 5, sliderBounds.getWidth() - 2 * padding, labelHeight + 5);
}

void FilterComponent::updateDerivedComponentColours()
{
    setComponentColoursFromPalette(filterTypeSelector);
    setComponentColoursFromPalette(parameterSliders);
}