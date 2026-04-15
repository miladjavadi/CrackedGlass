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
    setResizable(true, true);
    setResizeLimits(windowWidth, windowHeight, 4 * windowWidth, 4 * windowWidth);
    
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
    //g.fillAll (static_cast<juce::Colour>(0xff010114));
    g.setGradientFill (juce::ColourGradient(juce::Colours::blue.withSaturation(0.85f).withBrightness(0.1), getLocalBounds().getBottomLeft().toFloat(), juce::Colours::blue.withSaturation(0.85f).withBrightness(0.2), getLocalBounds().getTopLeft().toFloat(), false));
    g.fillAll();
}

void CrackedGlassAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //juce::Rectangle<int> bounds{ getLocalBounds().reduced(padding, padding/2) };
    //bounds.setY(getLocalBounds().getY());
    juce::Rectangle<int> bounds{ getLocalBounds() };

    const int headerHeight{ static_cast<int>(bounds.getHeight() * headerHeightRatio) };

    // set components
    header.setBounds(bounds.getX(), bounds.getY(), bounds.getWidth(), headerHeight);

    //osc.setBounds (getCellBounds(0, 0, 1, 2));
    //adsr.setBounds (getCellBounds(0, 2, 1, 2));
    //filter.setBounds (getCellBounds(1, 0, 1, 1));
    //modAdsr.setBounds (getCellBounds(1, 1, 1, 2));
    //distortion.setBounds (getCellBounds(1, 3, 1, 1));

    juce::Grid grid;

    using TrackInfo = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.setGap(juce::Grid::Px(padding));

    grid.templateColumns = {
        TrackInfo(Fr(1)),
        TrackInfo(Fr(1)),
        TrackInfo(Fr(1)),
        TrackInfo(Fr(1))
    };

    grid.templateRows = {
        TrackInfo(Fr(1)),
        TrackInfo(Fr(1))
    };

    grid.items = {
        juce::GridItem(osc).withArea(1, 1, 1, 3),
        juce::GridItem(adsr).withArea(1, 3, 1, 5),
        juce::GridItem(filter).withArea(2, 1),
        juce::GridItem(modAdsr).withArea(2, 2, 2, 4),
        juce::GridItem(distortion).withArea(2, 4)
    };

    juce::Rectangle<int> gridBounds{ bounds.getX() + padding, bounds.getY() + headerHeight, bounds.getWidth() - 2 * padding, bounds.getHeight() - headerHeight - padding };

    grid.performLayout(gridBounds);
}

//juce::Rectangle<int> CrackedGlassAudioProcessorEditor::getCellBounds(int row, int column, int componentRows, int componentColumns)
//{
//    jassert(row < numberOfRows && column < numberOfColumns);
//
//    const int x{ marginSides + column * (componentWidth + padding) };
//    const int y{ headerHeight + marginTop + row * (componentHeight + padding) };
//    const int width{ (componentWidth + padding) * componentColumns - padding };
//    const int height{ (componentHeight + padding) * componentRows - padding };
//    
//    return {x, y, width, height};
//}