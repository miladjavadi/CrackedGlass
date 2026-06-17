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

    setSliderWithLabel(cutoffFrequencySlider, cutoffFrequencyLabel, cutoffFrequencySliderAttachment, apvts, "CUTOFFFREQUENCY", false);
    setSliderWithLabel(resonanceSlider, resonanceLabel, resonanceSliderAttachment, apvts, "RESONANCE", false);
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

void FilterComponent::setSliderParams (juce::Slider& slider, bool useTextBox)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    if (useTextBox)
    {
        slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 40, 20);
    }
    else
    {
        slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    }
    setComponentColoursFromPalette(slider);

    addAndMakeVisible (slider);
}

void FilterComponent::setLabelParams (juce::Label& label)
{
    setComponentColoursFromPalette(label);
    label.setFont (18.0f);
    label.setJustificationType (juce::Justification::centred);
    label.setText(label.getText().toUpperCase(), juce::dontSendNotification);
    addAndMakeVisible(label);
}

void FilterComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, bool useTextBox)
{
    setSliderParams(slider, useTextBox);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramID, slider);
    setLabelParams(label);
}

void FilterComponent::updateDerivedComponentColours()
{
    setComponentColoursFromPalette(filterTypeSelector);
    setComponentColoursFromPalette(cutoffFrequencySlider);
    setComponentColoursFromPalette(resonanceSlider);
    setComponentColoursFromPalette(cutoffFrequencyLabel);
    setComponentColoursFromPalette(resonanceLabel);
}