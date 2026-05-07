/*
  ==============================================================================

    SynthModule.h
    Created: 15 Apr 2026 10:06:14am
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "ModuleColourPalette.h"

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SynthModule  : public juce::Component
{
public:
    SynthModule();
    ~SynthModule() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CrackedGlass::ModuleColourPalette m_greyscaleColourPalette{
    juce::Colour(0.0f, 0.0f, 0.9f, 0.15f),
    juce::Colour(0.0f, 0.0f, 0.9f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.9f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.9f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.5f, 1.0f)
    };

    juce::Colour m_mainHue{};

    CrackedGlass::ModuleColourPalette m_colourPalette{};

    bool m_canBeDisabled{};
    bool m_enabled{};

    void updateColoursFromMainHue();
    //void setSliderParams(juce::Slider& slider, bool useTextBox = false);
    //void setLabelParams(juce::Label& label);
    //void setSliderWithLabel(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, const juce::String& paramID, bool useTextBox = true);
    void performSliderArrayLayout();

    void setMainHueFromColour(const juce::Colour& colour)
    {
        m_mainHue = colour;
    }

    const CrackedGlass::ModuleColourPalette& getActiveColourPalette()
    {
        return m_enabled ? m_colourPalette : m_greyscaleColourPalette;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthModule)
};
