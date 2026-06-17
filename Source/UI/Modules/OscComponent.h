/*
  ==============================================================================

    OscComponent.h
    Created: 9 Apr 2026 12:07:02pm
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
class OscComponent  : public SynthModule
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& waveshapeSelectorID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider coarsePitchSlider;
    juce::Slider finePitchSlider;
    juce::Slider lfoFrequencySlider;
    juce::Slider lfoDepthSlider;

    RadioButtonGroup waveshapeSelector;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> coarsePitchSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> finePitchSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoFrequencySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoDepthSliderAttachment;

    juce::Label coarsePitchLabel{ "Coarse", "Coarse" };
    juce::Label finePitchLabel{ "Fine", "Fine" };
    juce::Label fmFrequencyLabel{ "FM Frequency", "FM Frequency" };
    juce::Label fmDepthLabel{ "FM Depth", "FM Depth" };

    juce::Label waveshapeLabel{ "Shape", "Shape" };

    void setSliderParams(juce::Slider& slider);
    void setLabelParams(juce::Label& label);
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, juce::AudioProcessorValueTreeState& apvts, juce::String paramID);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
