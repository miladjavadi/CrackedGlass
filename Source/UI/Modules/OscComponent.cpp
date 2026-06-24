/*
  ==============================================================================

    OscComponent.cpp
    Created: 9 Apr 2026 12:07:02pm
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& waveshapeSelectorID)
    : SynthModule{ "Oscillator", juce::Colours::cadetblue, false, apvts, "" }
    , waveshapeSelector{ apvts, waveshapeSelectorID, juce::FlexBox::Direction::row, 1, 4, getActiveColourPalette().backgroundColour, getActiveColourPalette().borderColour, getActiveColourPalette().borderColour, getActiveColourPalette().titleColour, getActiveColourPalette().borderColour }
{   
    setSliderWithLabel(coarsePitchSlider, coarsePitchLabel, coarsePitchSliderAttachment, apvts, "OSC1COARSEPITCH", juce::Slider::SliderStyle::RotaryVerticalDrag, true);
    setSliderWithLabel(finePitchSlider, finePitchLabel, finePitchSliderAttachment, apvts, "OSC1FINEPITCH", juce::Slider::SliderStyle::RotaryVerticalDrag, true);
    setSliderWithLabel(lfoFrequencySlider, fmFrequencyLabel, lfoFrequencySliderAttachment, apvts, "FMFREQUENCY", juce::Slider::SliderStyle::RotaryVerticalDrag, true);
    setSliderWithLabel(lfoDepthSlider, fmDepthLabel, lfoDepthSliderAttachment, apvts, "FMDEPTH", juce::Slider::SliderStyle::RotaryVerticalDrag, true);

    addAndMakeVisible(waveshapeSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    SynthModule::paint(g);
}

void OscComponent::resized()
{
    SynthModule::resized();

    constexpr int padding{ 10 };
    constexpr int margin{ 10 };
    const juce::Rectangle<int> bounds{ getLocalBounds().reduced (padding) };
    const int rotorSize{ bounds.getWidth() / 4 - margin };
    constexpr int maxLabelOverprint{ 10 };
    const int labelWidth{ rotorSize + 2 * maxLabelOverprint };
    constexpr int labelHeight{ 20 };
    const int sliderStartY{ bounds.getBottom() - rotorSize - padding };

    coarsePitchSlider.setBounds (bounds.getX() + margin, sliderStartY, rotorSize, rotorSize);
    coarsePitchLabel.setBounds (coarsePitchSlider.getX(), coarsePitchSlider.getY() - labelHeight, rotorSize, labelHeight);

    finePitchSlider.setBounds (coarsePitchSlider.getRight() + padding, coarsePitchSlider.getY(), rotorSize, rotorSize);
    finePitchLabel.setBounds (finePitchSlider.getX(), finePitchSlider.getY() - labelHeight, rotorSize, labelHeight);

    lfoDepthSlider.setBounds (finePitchSlider.getRight() + padding, finePitchSlider.getY(), rotorSize, rotorSize);
    fmDepthLabel.setBounds (lfoDepthSlider.getX(), lfoDepthSlider.getY() - labelHeight, rotorSize, labelHeight);

    lfoFrequencySlider.setBounds (lfoDepthSlider.getRight() + padding, lfoDepthSlider.getY(), rotorSize, rotorSize);
    fmFrequencyLabel.setBounds (lfoFrequencySlider.getX(), lfoFrequencySlider.getY() - labelHeight, rotorSize, labelHeight);
    
    juce::Rectangle<int> selectorBounds{ getLocalBounds() };
    selectorBounds.reduce(selectorBounds.getWidth() / 6, 0);
    selectorBounds.setY(coarsePitchLabel.getY() - labelHeight - padding - margin - 5);
    selectorBounds.setHeight(labelHeight + 5);
    waveshapeSelector.setBounds(selectorBounds);
}