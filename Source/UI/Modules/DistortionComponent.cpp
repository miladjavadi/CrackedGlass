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
DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& enableParameterID, const juce::String& functionParameterID, const juce::String& driveParameterID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    const juce::StringArray& functionOptions = dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter(functionParameterID))->choices;
    functionSelector.addItemList(functionOptions, 1);

    functionSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, deadColour);
    functionSelector.setColour(juce::ComboBox::ColourIds::textColourId, labelColour);
    functionSelector.setColour(juce::ComboBox::ColourIds::arrowColourId, borderColour);
    functionSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, borderColour);
    addAndMakeVisible(functionSelector);
    setLabelParams(functionLabel);

    functionSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, functionParameterID, functionSelector);

    setSliderWithLabel(driveSlider, driveLabel, driveSliderAttachment, apvts, driveParameterID, false);

    //titleLabel.setColour(juce::Label::ColourIds::backgroundColourId, borderColour);
    //titleLabel.setColour(juce::Label::ColourIds::textColourId, titleColour);
    //titleLabel.setFont(juce::Font(juce::Font::getDefaultSansSerifFontName(), 18.0f, 1));
    //titleLabel.setJustificationType(juce::Justification::centredLeft);
    //addAndMakeVisible(titleLabel);

    titleButton.setClickingTogglesState(true);
    titleButton.setToggleState(false, juce::dontSendNotification);
    titleButton.setColour(juce::TextButton::ColourIds::buttonColourId, backgroundColour);
    titleButton.setColour(juce::TextButton::ColourIds::textColourOffId, borderColour);
    titleButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, borderColour);
    titleButton.setColour(juce::TextButton::ColourIds::textColourOnId, titleColour);
    titleButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, enableParameterID, titleButton);
    addAndMakeVisible(titleButton);

    //enableButton.setClickingTogglesState(true);
    //enableButton.setToggleState(false, juce::dontSendNotification);
    //juce::Path square;
    //square.addRectangle(0, 0, 20.0f, 20.0f);
    //enableButton.setColours(static_cast<juce::Colour>(0x00000000), borderColour.withAlpha(0.5f), borderColour.withAlpha(0.3f));
    //enableButton.setOnColours(borderColour, borderColour.withAlpha(0.5f), borderColour.withAlpha(0.3f));
    //enableButton.setOutline(borderColour, 1.0f);
    //enableButton.shouldUseOnColours(true);
    //enableButton.setShape(square, true, true, false);
    //enableButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "DISTORTIONENABLE", enableButton);
    //addAndMakeVisible(enableButton);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(backgroundColour);

    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 2);
}

void DistortionComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    constexpr int padding{ 10 };
    constexpr int margin{ 10 };
    const juce::Rectangle<int> bounds{ getLocalBounds().reduced (margin) };
    //const juce::Rectangle<int> filterBounds{ bounds.getX(), bounds.getY(), bounds.getWidth() / 4 - padding, bounds.getHeight() };
    const juce::Rectangle<int> sliderBounds{ bounds.reduced(40, 0) };

    const int rotorSize{ (sliderBounds.getWidth() - 2 * padding) / 1 };
    constexpr int labelHeight{ 20 };
    const int sliderStartY{ bounds.getBottom() - rotorSize - margin };

    driveSlider.setBounds (sliderBounds.getX() + padding, sliderStartY, rotorSize, rotorSize);
    driveLabel.setBounds (driveSlider.getX(), driveSlider.getY() - labelHeight, rotorSize, labelHeight);

    functionSelector.setBounds (driveSlider.getX(), driveLabel.getY() - labelHeight - padding - margin, rotorSize, labelHeight);
    //filterTypeLabel.setBounds (cutoffFrequencySlider.getX(), filterTypeSelector.getY(), rotorSize, labelHeight);

    //titleLabel.setBounds(0, 0, 120, 30);
    titleButton.setBounds(0, 0, 140, 35);
    //enableButton.setBounds(bounds.getRight() - 20, margin, 20, 20);
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