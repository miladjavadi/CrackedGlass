/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CrackedGlassAudioProcessorEditor::CrackedGlassAudioProcessorEditor (CrackedGlassAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , osc (audioProcessor.apvts, juce::String{ "OSC1WAVESHAPE" })
    , adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , header (audioProcessor.apvts)
    , filter(audioProcessor.apvts, juce::String{"FILTERTYPE"})
    , modAdsr ("Mod Envelope", audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE", juce::Colours::purple, true, "MODENABLE")
    , distortion (audioProcessor.apvts, "DISTORTIONENABLE", "DISTORTIONFUNCTION", "DISTORTIONDRIVE")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    crackedGlassLookAndFeel = std::make_unique<CrackedGlassLookAndFeel>();
    setLookAndFeel(crackedGlassLookAndFeel.get());

    setSize (windowWidth, windowHeight);
    //setResizable(true, true);
    
    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(header);
    addAndMakeVisible(filter);
    addAndMakeVisible(modAdsr);
    addAndMakeVisible(distortion);
}

CrackedGlassAudioProcessorEditor::~CrackedGlassAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void CrackedGlassAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (static_cast<juce::Colour>(0xff010114));
}

void CrackedGlassAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // set components
    header.setBounds(0, 0, headerWidth, headerHeight);

    osc.setBounds (getCellBounds(0, 0, 1, 2));
    adsr.setBounds (getCellBounds(0, 2, 1, 2));
    filter.setBounds (getCellBounds(1, 0, 1, 1));
    modAdsr.setBounds (getCellBounds(1, 1, 1, 2));
    distortion.setBounds (getCellBounds(1, 3, 1, 1));
}

juce::Rectangle<int> CrackedGlassAudioProcessorEditor::getCellBounds(int row, int column, int componentRows, int componentColumns)
{
    jassert(row < numberOfRows && column < numberOfColumns);

    const int x{ marginSides + column * (componentWidth + padding) };
    const int y{ headerHeight + marginTop + row * (componentHeight + padding) };
    const int width{ (componentWidth + padding) * componentColumns - padding };
    const int height{ (componentHeight + padding) * componentRows - padding };
    
    return {x, y, width, height};
}