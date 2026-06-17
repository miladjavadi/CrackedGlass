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
    , functionSelector{ apvts, functionParameterID, juce::FlexBox::Direction::row, 2, 2, backgroundColour, borderColour, borderColour, titleColour, borderColour }
{
    addAndMakeVisible(functionSelector);

    setSliderWithLabel(driveSlider, driveLabel, driveSliderAttachment, apvts, driveParameterID, false);
    setSliderWithLabel(mixSlider, mixLabel, mixSliderAttachment, apvts, mixParameterID, false);
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

void DistortionComponent::updateDerivedComponentColours()
{

}