/*
  ==============================================================================

    FilterComponent.h
    Created: 10 Apr 2026 10:02:06pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "Components/RadioButtonGroup.h"
#include "Components/LabeledRotarySlider.h"
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

    std::vector<std::unique_ptr<LabeledRotarySlider>> parameterSliders{};

    void updateDerivedComponentColours() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
