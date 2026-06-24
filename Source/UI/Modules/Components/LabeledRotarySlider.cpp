/*
  ==============================================================================

    LabeledRotarySlider.cpp
    Created: 20 Apr 2026 10:23:12pm
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LabeledRotarySlider.h"

//==============================================================================
LabeledRotarySlider::LabeledRotarySlider(const juce::String& labelText, juce::AudioProcessorValueTreeState& apvts, const juce::String& parameterID, bool useTextBox)
    : hasTextBox{ useTextBox }
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

    addAndMakeVisible (slider);

    label.setFont(18.0f);
    label.setJustificationType(juce::Justification::centred);
    label.setText(labelText.toUpperCase(), juce::dontSendNotification);
    addAndMakeVisible(label);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
}

LabeledRotarySlider::~LabeledRotarySlider()
{
}

void LabeledRotarySlider::setColour(ColourIds colourId, const juce::Colour& colour)
{
    switch (colourId)
    {
    case sliderFillColourId:
        slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, colour);
        break;
    case sliderOutlineColourId:
        slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, colour);
        break;
    case labelColourId:
        label.setColour(juce::Label::ColourIds::textColourId, colour);
        break;
    case boxTextColourId:
        label.setColour(juce::Label::ColourIds::outlineColourId, colour);
        break;
    default:
        jassert(false && "ColourId not found.");
    }
}

void LabeledRotarySlider::paint (juce::Graphics& g)
{
}

void LabeledRotarySlider::resized()
{
    juce::Rectangle<int> bounds{ getLocalBounds()};
    constexpr int labelHeight{ 20 };
    int rotorSize{ std::min(bounds.getWidth(), bounds.getHeight() - labelHeight - m_padding) };

    slider.setBounds(bounds.getX(), bounds.getY() + labelHeight + m_padding, rotorSize, rotorSize);
    label.setBounds(bounds.getX(), bounds.getY(), bounds.getWidth(), labelHeight);
}
