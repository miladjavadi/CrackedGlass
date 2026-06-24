/*
  ==============================================================================

    FilterComponent.h
    Created: 10 Apr 2026 10:02:06pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "Components/RadioButtonGroup.h"
#include "SynthModule.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public SynthModule
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& filterTypeSelectorID);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    RadioButtonGroup filterTypeSelector;

    juce::Slider cutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffFrequencySliderAttachment;
    juce::Label cutoffFrequencyLabel{ "Cutoff", "Cutoff" };

    juce::Slider resonanceSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceSliderAttachment;
    juce::Label resonanceLabel{ "Resonance", "Resonance" };

    juce::TextButton titleButton{ "Filter", "Filter" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> titleButtonAttachment;

    void updateDerivedComponentColours() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
