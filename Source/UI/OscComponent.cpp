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
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    const juce::StringArray& waveshapeOptions = (dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter(waveshapeSelectorID)))->choices;
    oscWaveshapeSelector.addItemList(waveshapeOptions, 1);

    oscWaveshapeSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, deadColour);
    oscWaveshapeSelector.setColour(juce::ComboBox::ColourIds::textColourId, labelColour);
    oscWaveshapeSelector.setColour(juce::ComboBox::ColourIds::arrowColourId, borderColour);
    oscWaveshapeSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, borderColour);
    addAndMakeVisible(oscWaveshapeSelector);
    oscWaveshapeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveshapeSelectorID, oscWaveshapeSelector);
    
    setSliderWithLabel(coarsePitchSlider, coarsePitchLabel, coarsePitchSliderAttachment, apvts, "OSC1COARSEPITCH");
    setSliderWithLabel(finePitchSlider, finePitchLabel, finePitchSliderAttachment, apvts, "OSC1FINEPITCH");
    setSliderWithLabel(lfoFrequencySlider, fmFrequencyLabel, lfoFrequencySliderAttachment, apvts, "FMFREQUENCY");
    setSliderWithLabel(lfoDepthSlider, fmDepthLabel, lfoDepthSliderAttachment, apvts, "FMDEPTH");

    titleLabel.setText(juce::String("Oscillator").toUpperCase(), juce::NotificationType::dontSendNotification);
    titleLabel.setColour(juce::Label::ColourIds::backgroundColourId, borderColour);
    titleLabel.setColour(juce::Label::ColourIds::textColourId, titleColour);
    titleLabel.setFont(juce::Font(juce::Font::getDefaultSansSerifFontName(), 22.0f, 1));
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    //setLabelParams(waveshapeLabel);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (backgroundColour);

    g.setColour (borderColour);
    g.drawRect (getLocalBounds(), 2);   // draw an outline around the component


}

void OscComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
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

    oscWaveshapeSelector.setBounds (coarsePitchSlider.getX(), coarsePitchLabel.getY() - labelHeight - padding, rotorSize, labelHeight);
    waveshapeLabel.setBounds (coarsePitchSlider.getX(), oscWaveshapeSelector.getY(), rotorSize, labelHeight);

    titleLabel.setBounds(0, 0, 140, 30);
}

void OscComponent::setSliderParams (juce::Slider& slider)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 40, 15);
    slider.setColour (juce::Slider::ColourIds::textBoxTextColourId, labelColour);
    slider.setColour (juce::Slider::ColourIds::textBoxOutlineColourId, borderColour.withAlpha(0.0f));
    slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, borderColour);
    slider.setColour(juce::Slider::ColourIds::thumbColourId, sliderFillColour);
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, deadColour);

    addAndMakeVisible (slider);
}

void OscComponent::setLabelParams (juce::Label& label)
{
    label.setColour (juce::Label::ColourIds::textColourId, labelColour);
    label.setFont (18.0f);
    label.setJustificationType (juce::Justification::centred);
    label.setText(label.getText().toUpperCase(), juce::dontSendNotification);
    addAndMakeVisible(label);
}

void OscComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID)
{
    setSliderParams(slider);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramID, slider);
    setLabelParams(label);
}