/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Modules/AdsrComponent.h"
#include "UI/Modules/OscComponent.h"
#include "UI/Modules/HeaderComponent.h"
#include "UI/Modules/FilterComponent.h"
#include "UI/Modules/DistortionComponent.h"
#include "UI/Appearance/CrackedGlassLookAndFeel.h"

//==============================================================================
/**
*/
class CrackedGlassAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CrackedGlassAudioProcessorEditor (CrackedGlassAudioProcessor&);
    ~CrackedGlassAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //juce::Rectangle<int> getCellBounds(int row, int column, int componentRows=1, int componentColumns=1);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    static constexpr int windowWidth{ 1000 };
    static constexpr int windowHeight{ 600 };

    // spacing
    static constexpr int numberOfRows{ 2 };
    static constexpr int numberOfColumns{ 4 };

    static constexpr int marginTop{ 10 };
    static constexpr int marginSides{ 10 };
    static constexpr int marginBottom{ 10 };

    static constexpr int padding{ 10 };

    static constexpr int headerWidth{ windowWidth };
    static constexpr float headerHeightRatio{ 1.0f/11.0f };

    //static constexpr int componentWidth{ (windowWidth - 2 * marginSides - (numberOfColumns - 1) * padding) / numberOfColumns };
    //static constexpr int componentHeight{ (windowHeight - marginTop - marginBottom - headerHeight - (numberOfRows - 1) * padding) / numberOfRows };

    CrackedGlassAudioProcessor& audioProcessor;
    std::unique_ptr<CrackedGlassLookAndFeel> crackedGlassLookAndFeel;

    HeaderComponent header;
    OscComponent osc;
    AdsrComponent adsr;
    FilterComponent filter;
    AdsrComponent modAdsr;
    DistortionComponent distortion;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrackedGlassAudioProcessorEditor)
};
