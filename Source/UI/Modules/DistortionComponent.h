/*
  ==============================================================================

    DistortionComponent.h
    Created: 13 Apr 2026 6:38:39pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include "Components/RadioButtonGroup.h"
#include "SynthModule.h"
#include "Components/LabeledRotarySlider.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistortionComponent  : public SynthModule
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& enableParameterID, const juce::String& functionParameterID, const juce::String& driveParameterID, const juce::String& mixParameterID);
    ~DistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    RadioButtonGroup functionSelector;

    std::vector<std::unique_ptr<LabeledRotarySlider>> parameterSliders{};

    void updateDerivedComponentColours() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};
