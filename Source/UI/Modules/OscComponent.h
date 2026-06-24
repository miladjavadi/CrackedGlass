/*
  ==============================================================================

    OscComponent.h
    Created: 9 Apr 2026 12:07:02pm
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
class OscComponent  : public SynthModule
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& waveshapeSelectorID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    RadioButtonGroup waveshapeSelector;

    std::vector<std::unique_ptr<LabeledRotarySlider>> parameterSliders{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
