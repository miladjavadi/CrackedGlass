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
    : filterTypeSelector{ apvts, filterTypeSelectorID, juce::FlexBox::Direction::row, 1, 3, backgroundColour, borderColour, borderColour, titleColour, borderColour }
{
    addAndMakeVisible(filterTypeSelector);

    setSliderWithLabel(cutoffFrequencySlider, cutoffFrequencyLabel, cutoffFrequencySliderAttachment, apvts, "CUTOFFFREQUENCY", false);
    setSliderWithLabel(resonanceSlider, resonanceLabel, resonanceSliderAttachment, apvts, "RESONANCE", false);

    titleButton.setClickingTogglesState(true);
    titleButton.setToggleState(false, juce::dontSendNotification);
    titleButton.setColour(juce::TextButton::ColourIds::buttonColourId, backgroundColour);
    titleButton.setColour(juce::TextButton::ColourIds::textColourOffId, borderColour);
    titleButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, borderColour);
    titleButton.setColour(juce::TextButton::ColourIds::textColourOnId, titleColour);
    titleButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "FILTERENABLE", titleButton);
    addAndMakeVisible(titleButton);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{

    g.fillAll(backgroundColour);

    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 2);
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
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

    titleButton.setBounds(0, 0, 140, 35);
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
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, borderColour);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, sliderFillColour);
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, deadColour);

    addAndMakeVisible (slider);
}

void FilterComponent::setLabelParams (juce::Label& label)
{
    label.setColour (juce::Label::ColourIds::textColourId, labelColour);
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
