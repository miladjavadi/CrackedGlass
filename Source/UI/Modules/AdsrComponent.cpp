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
AdsrComponent::AdsrComponent(const juce::String& name, juce::AudioProcessorValueTreeState& apvts, const juce::String& attackParameterID, const juce::String& decayParameterID, const juce::String& sustainParameterID, const juce::String& releaseParameterID, juce::Colour mainColour, bool canBeDisabled, const juce::String& enableParameterID)
    : m_name{ name }
    , m_canBeDisabled{ canBeDisabled }
    , m_mainColour{ mainColour }
    , adsrGraph{apvts, attackParameterID, decayParameterID, sustainParameterID, releaseParameterID, m_mainColour}
    , titleButton{ name, name }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    backgroundColour = mainColour.withAlpha(0.15f);
    labelColour = mainColour.withBrightness(1.0f).withSaturation(0.3f);
    borderColour = mainColour.withBrightness(1.0f).withSaturation(0.6f);
    titleColour = mainColour.withBrightness(0.1f);
    sliderFillColour = mainColour.withBrightness(1.0f).withSaturation(0.2f);
    deadColour = mainColour.withBrightness(0.5f).withSaturation(0.7f);

    setSliderWithLabel(attackSlider, attackLabel, attackAttachment, apvts, attackParameterID, false);
    setSliderWithLabel(decaySlider, decayLabel, decayAttachment, apvts, decayParameterID, false);
    setSliderWithLabel(sustainSlider, sustainLabel, sustainAttachment, apvts, sustainParameterID, false);
    setSliderWithLabel(releaseSlider, releaseLabel, releaseAttachment, apvts, releaseParameterID, false);

    if (m_canBeDisabled)
    {
        titleButton.setClickingTogglesState(true);
        titleButton.setToggleState(false, juce::dontSendNotification);
        titleButton.setColour(juce::TextButton::ColourIds::buttonColourId, backgroundColour);
        titleButton.setColour(juce::TextButton::ColourIds::textColourOffId, borderColour);
        titleButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, borderColour);
        titleButton.setColour(juce::TextButton::ColourIds::textColourOnId, titleColour);
        titleButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, enableParameterID, titleButton);
        addAndMakeVisible(titleButton);
    }
    else
    {
        titleLabel.setText(name.toUpperCase(), juce::NotificationType::dontSendNotification);
        titleLabel.setColour(juce::Label::ColourIds::backgroundColourId, borderColour);
        titleLabel.setColour(juce::Label::ColourIds::textColourId, titleColour);
        titleLabel.setFont(juce::Font(22.0f, 3));
        titleLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(titleLabel);
    }

    addAndMakeVisible(adsrGraph);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColour);

    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 2.0f);

}

void AdsrComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

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

    if (m_canBeDisabled)
    {
        titleButton.setBounds(0, 0, 140, 35);
    }
    else
    {
        titleLabel.setBounds(0, 0, 140, 30);
    }

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
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, borderColour);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, sliderFillColour);
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, deadColour);

    addAndMakeVisible (slider);
}

void AdsrComponent::setLabelParams (juce::Label& label)
{
    label.setColour(juce::Label::ColourIds::textColourId, labelColour);
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
