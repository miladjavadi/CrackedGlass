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
    SynthModule(const juce::String& title, const juce::Colour& mainHue, bool canBeDisabled, juce::AudioProcessorValueTreeState& apvts, const juce::String& enableParameterID = "");
    ~SynthModule() override;

    void paint (juce::Graphics&) override;
    void resized() override;

protected:
    virtual void updateDerivedComponentColours() = 0; // use this to update colours of additional child components in derived classes, see updateBaseComponentColours()

private:
    const CrackedGlass::ModuleColourPalette m_greyscaleColourPalette{
    juce::Colour(0.0f, 0.0f, 0.7f, 0.15f),
    juce::Colour(0.0f, 0.0f, 0.7f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.7f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.7f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.25f, 1.0f)
    };

    juce::String m_title{};

    juce::Colour m_mainHue{};

    CrackedGlass::ModuleColourPalette m_colourPalette{};

    const bool m_canBeDisabled{};
    bool m_enabled{ true };

    // used when module cannot be disabled (i.e., when title button is not clickable)
    juce::Label titleLabel;

    // used when module can be disabled (i.e., when clicking the title button toggles module bypass)
    juce::TextButton titleButton{};
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> titleButtonAttachment;

    void setColourPaletteFromMainHue();
    void setColourPaletteFromColour(const juce::Colour& colour);

    //void setSliderParams(juce::Slider& slider, bool useTextBox = false);
    //void setLabelParams(juce::Label& label);
    //void setSliderWithLabel(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, const juce::String& paramID, bool useTextBox = true);
    void performSliderArrayLayout();

    void updateBaseComponentColours();

    void lookAndFeelChanged() override;

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
