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

    setSliderWithLabel(cutoffFrequencySlider, cutoffFrequencyLabel, cutoffFrequencySliderAttachment, apvts, "CUTOFFFREQUENCY", juce::Slider::SliderStyle::RotaryVerticalDrag, false);
    setSliderWithLabel(resonanceSlider, resonanceLabel, resonanceSliderAttachment, apvts, "RESONANCE", juce::Slider::SliderStyle::RotaryVerticalDrag, false);
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
    const juce::Rectangle<int> bounds{ getLocalBounds().reduced (margin) };
    const juce::Rectangle<int> filterBounds{ bounds.reduced(0, 0) };

    const int rotorSize{ (filterBounds.getWidth() - 3 * padding) / 2 };
    constexpr int labelHeight{ 20 };
    const int sliderStartY{ bounds.getBottom() - rotorSize - margin };

    cutoffFrequencySlider.setBounds (filterBounds.getX() + padding, sliderStartY, rotorSize, rotorSize);
    cutoffFrequencyLabel.setBounds (cutoffFrequencySlider.getX(), cutoffFrequencySlider.getY() - labelHeight, rotorSize, labelHeight);

    resonanceSlider.setBounds (cutoffFrequencySlider.getRight() + padding, cutoffFrequencySlider.getY(), rotorSize, rotorSize);
    resonanceLabel.setBounds (resonanceSlider.getX(), resonanceSlider.getY() - labelHeight, rotorSize, labelHeight);

    filterTypeSelector.setBounds (filterBounds.getX() + padding, resonanceLabel.getY() - labelHeight - 2 * padding - 5, filterBounds.getWidth() - 2 * padding, labelHeight + 5);
}

void FilterComponent::updateDerivedComponentColours()
{
    setComponentColoursFromPalette(filterTypeSelector);
    setComponentColoursFromPalette(cutoffFrequencySlider);
    setComponentColoursFromPalette(resonanceSlider);
    setComponentColoursFromPalette(cutoffFrequencyLabel);
    setComponentColoursFromPalette(resonanceLabel);
}