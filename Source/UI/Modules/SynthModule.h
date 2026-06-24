/*
  ==============================================================================

    SynthModule.h
    Created: 15 Apr 2026 10:06:14am
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "ModuleColourPalette.h"
#include "Components/LabeledRotarySlider.h"

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
    void setComponentColoursFromPalette(juce::Component& component);

    template <typename T>
    void setComponentColoursFromPalette(std::vector<std::unique_ptr<T>>& components)
    {
        for (auto& c : components)
        {
            setComponentColoursFromPalette(*c);
        }
    }

    const CrackedGlass::ModuleColourPalette& getActiveColourPalette()
    {
        return m_enabled ? m_colourPalette : m_greyscaleColourPalette;
    }

    void setSliderParams(juce::Slider& slider, juce::Slider::SliderStyle style = juce::Slider::SliderStyle::RotaryVerticalDrag, bool useTextBox = false);
    void setLabelParams(juce::Label& label);
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, const juce::String& paramID, const juce::Slider::SliderStyle style = juce::Slider::SliderStyle::RotaryVerticalDrag, bool useTextBox = false);
    void layoutSliderArray(std::vector<std::unique_ptr<LabeledRotarySlider>>& sliders, juce::Rectangle<int> layoutBounds, int paddingBetweenSliders = 10);

    virtual void updateDerivedComponentColours() {}; // use this to update colours of additional child components in derived classes, see updateBaseComponentColours()

private:
    const CrackedGlass::ModuleColourPalette m_greyscaleColourPalette{
    juce::Colour(0.0f, 0.0f, 0.6f, 0.15f),
    juce::Colour(0.0f, 0.0f, 0.7f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.7f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.07f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.7f, 1.0f),
    juce::Colour(0.0f, 0.0f, 0.35f, 1.0f)
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

    void updateBaseComponentColours();

    void lookAndFeelChanged() override;

    void setMainHueFromColour(const juce::Colour& colour)
    {
        m_mainHue = colour;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthModule)
};
