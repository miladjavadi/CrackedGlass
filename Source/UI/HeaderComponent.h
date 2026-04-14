/*
  ==============================================================================

    HeaderComponent.h
    Created: 10 Apr 2026 12:25:28pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class HeaderComponent  : public juce::Component
{
public:
    HeaderComponent(juce::AudioProcessorValueTreeState& apvts);
    ~HeaderComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Colour mainColour{ juce::Colours::cornflowerblue };
    juce::Colour backgroundColour = mainColour.withAlpha(0.15f).withBrightness(1.0f);
    juce::Colour borderColour = mainColour.withBrightness(1.0f).withSaturation(0.3f);
    juce::Colour sliderFillColour = mainColour.withBrightness(1.0f).withSaturation(0.2f);
    juce::Colour deadColour = mainColour.withBrightness(0.5f).withSaturation(0.7f);

    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    juce::Label gainLabel{ "Output", "OUTPUT" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeaderComponent)
};
