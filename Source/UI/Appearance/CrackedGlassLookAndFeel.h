/*
  ==============================================================================

    CrackedGlassLookAndFeel.h
    Created: 13 Apr 2026 8:13:55pm
    Author:  milad

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CrackedGlassLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CrackedGlassLookAndFeel()
        : LookAndFeel_V4{}
    {

        setDefaultSansSerifTypeface(getCustomRegularFont());

        juce::LookAndFeel::setDefaultLookAndFeel(this);
    }

    ~CrackedGlassLookAndFeel()
    {
        juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
    }

    void drawButtonBackground(juce::Graphics& g,
        juce::Button& button,
        const juce::Colour& backgroundColour,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown) override;

    void drawButtonText(juce::Graphics& g,
        juce::TextButton& button,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown) override;

    void drawRotarySlider(juce::Graphics& g,
        int x,
        int y,
        int width,
        int height,
        float sliderPos,
        float rotaryStartAngle,
        float rotaryEndAngle,
        juce::Slider& slider) override;

    void drawLinearSlider(juce::Graphics& g,
        int x,
        int y,
        int width,
        int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const juce::Slider::SliderStyle style,
        juce::Slider& slider) override;
    
    juce::Typeface::Ptr getTypefaceForFont(const juce::Font& font) override;

    static const juce::Typeface::Ptr getCustomRegularFont()
    {
        static auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::QuanticoItalic_ttf, BinaryData::QuanticoItalic_ttfSize);
        return juce::Typeface::Ptr(typeface);
    }

    static const juce::Typeface::Ptr getCustomBoldFont()
    {
        static auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::QuanticoBoldItalic_ttf, BinaryData::QuanticoBold_ttfSize);
        return juce::Typeface::Ptr(typeface);
    }

    static const juce::Typeface::Ptr getCustomItalicFont()
    {
        static auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::QuanticoItalic_ttf, BinaryData::QuanticoItalic_ttfSize);
        return juce::Typeface::Ptr(typeface);
    }

    static const juce::Typeface::Ptr getCustomBoldItalicFont()
    {
        static auto typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::QuanticoBoldItalic_ttf, BinaryData::QuanticoBoldItalic_ttfSize);
        return juce::Typeface::Ptr(typeface);
    }

private:
};