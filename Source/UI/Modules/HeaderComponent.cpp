/*
  ==============================================================================

    HeaderComponent.cpp
    Created: 10 Apr 2026 12:25:28pm
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HeaderComponent.h"

//==============================================================================
HeaderComponent::HeaderComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (apvts, "GAIN", gainSlider);

    gainSlider.setSliderStyle (juce::Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxRight, true, 45, 25);
    gainSlider.setTextValueSuffix("%");
    gainSlider.setColour (juce::Slider::ColourIds::textBoxTextColourId, borderColour);
    gainSlider.setColour (juce::Slider::ColourIds::textBoxOutlineColourId, mainColour.withAlpha(0.0f));
    gainSlider.setColour(juce::Slider::ColourIds::trackColourId, borderColour);
    gainSlider.setColour(juce::Slider::ColourIds::thumbColourId, sliderFillColour);
    gainSlider.setColour(juce::Slider::ColourIds::backgroundColourId, deadColour);
    addAndMakeVisible (gainSlider);

    gainLabel.setColour(juce::Label::ColourIds::textColourId, borderColour);
    gainLabel.setFont(18.0f);
    gainLabel.setJustificationType(juce::Justification::centredRight);
    addAndMakeVisible(gainLabel);
}

HeaderComponent::~HeaderComponent()
{
}

void HeaderComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (backgroundColour);   // clear the background

    g.setColour (borderColour);
    //g.fillRect(getLocalBounds().getX(), getLocalBounds().getBottom() - 2, getLocalBounds().getWidth(), 2);   // draw an outline around the component

    g.setColour (borderColour);
    g.setFont (juce::Font (juce::Font::getDefaultSansSerifFontName(), 26.0f, 1));
    g.drawText (juce::String("CrackedGlass").toUpperCase(), juce::Rectangle<int>{20, 0, getLocalBounds().getWidth() - 10, getLocalBounds().getHeight() },
                juce::Justification::left, true);
}

void HeaderComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    gainSlider.setBounds(getLocalBounds().getWidth() - 180, 0, 150, getLocalBounds().getHeight());
    gainLabel.setBounds(gainSlider.getX() - 65, gainSlider.getY(), 60, getLocalBounds().getHeight());
}
