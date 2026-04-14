/*
  ==============================================================================

    SynthSound.h
    Created: 2 Feb 2026 6:31:10pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }

};