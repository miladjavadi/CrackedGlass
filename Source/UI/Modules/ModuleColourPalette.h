#pragma once

#include <JuceHeader.h>

namespace CrackedGlass
{
    struct ModuleColourPalette
    {
        juce::Colour backgroundColour{};
        juce::Colour labelColour{};
        juce::Colour borderColour{};
        juce::Colour titleColour{};
        juce::Colour sliderFillColour{};
        juce::Colour deadColour{};
    };
}