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
    : functionSelector{ apvts, functionParameterID, juce::FlexBox::Direction::row, backgroundColour, borderColour, borderColour, titleColour, borderColour }
{
    addAndMakeVisible(functionSelector);

    setSliderWithLabel(driveSlider, driveLabel, driveSliderAttachment, apvts, driveParameterID, false);
    setSliderWithLabel(mixSlider, mixLabel, mixSliderAttachment, apvts, mixParameterID, false);

    titleButton.setClickingTogglesState(true);
    titleButton.setToggleState(false, juce::dontSendNotification);
    titleButton.setColour(juce::TextButton::ColourIds::buttonColourId, backgroundColour);
    titleButton.setColour(juce::TextButton::ColourIds::textColourOffId, borderColour);
    titleButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, borderColour);
    titleButton.setColour(juce::TextButton::ColourIds::textColourOnId, titleColour);
    titleButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, enableParameterID, titleButton);
    addAndMakeVisible(titleButton);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
    g.fillAll(backgroundColour);

    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 2);
}

void DistortionComponent::resized()
{

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

    functionSelector.setBounds (sliderBounds.getX() + padding, driveLabel.getY() - labelHeight - padding - margin, sliderBounds.getWidth() - 2 * padding, labelHeight);

    titleButton.setBounds(0, 0, 140, 35);
}

void DistortionComponent::setSliderParams (juce::Slider& slider, bool useTextBox)
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

void DistortionComponent::setLabelParams (juce::Label& label)
{
    label.setColour (juce::Label::ColourIds::textColourId, labelColour);
    label.setFont (18.0f);
    label.setJustificationType (juce::Justification::centred);
    label.setText(label.getText().toUpperCase(), juce::dontSendNotification);
    addAndMakeVisible(label);
}

void DistortionComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, bool useTextBox)
{
    setSliderParams(slider, useTextBox);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramID, slider);
    setLabelParams(label);
}