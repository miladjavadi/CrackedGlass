/*
  ==============================================================================

    HalationLookAndFeel.cpp
    Created: 13 Apr 2026 8:13:55pm
    Author:  milad

  ==============================================================================
*/

#include "HalationLookAndFeel.h"
#include <cmath>

void HalationLookAndFeel::drawButtonBackground(juce::Graphics& g,
    juce::Button& button,
    const juce::Colour& backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    juce::Rectangle<float> bounds{ button.getLocalBounds().toFloat() };
    juce::Rectangle<float> fillBounds{ bounds.reduced(6.0f) };

    if (dynamic_cast<juce::TextButton*>(&button))
    {
        g.setColour(button.findColour(juce::TextButton::buttonOnColourId));
    }
    else
    {
        g.setColour(backgroundColour);
    }

    g.drawRect(bounds, 2.0f);

    if (shouldDrawButtonAsDown)
    {
        g.setColour(backgroundColour.withAlpha(0.3f));
    }
    else
    {
        g.setColour(backgroundColour);
    }

    g.fillRect (fillBounds);
}

void HalationLookAndFeel::drawButtonText(juce::Graphics& g,
    juce::TextButton& button,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    juce::Rectangle<float> bounds{ button.getLocalBounds().toFloat() };
    juce::Rectangle<float> fillBounds{ bounds.reduced(6.0f) };

    if (shouldDrawButtonAsDown || !button.getToggleState())
    {
        g.setColour(button.findColour(juce::TextButton::textColourOffId));
    }
    else
    {
        g.setColour(button.findColour(juce::TextButton::textColourOnId));
    }

    g.setFont(getCustomBoldFont());
    g.setFont(20.0f);
    g.drawText(button.getButtonText().toUpperCase(), fillBounds, juce::Justification::centred);
}

void HalationLookAndFeel::drawRotarySlider(juce::Graphics& g,
    int x,
    int y,
    int width,
    int height,
    float sliderPosProportional,
    float rotaryStartAngle,
    float rotaryEndAngle,
    juce::Slider& slider)
{
    juce::Colour outline{ slider.findColour(juce::Slider::rotarySliderOutlineColourId) };
    juce::Colour fill{ slider.findColour(juce::Slider::rotarySliderFillColourId) };
    juce::Colour thumbColour{ slider.findColour(juce::Slider::thumbColourId) };

    juce::Rectangle<float> bounds{ juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10.0f) };

    float radius{ std::fmin(bounds.getWidth(), bounds.getHeight()) / 2.0f };
    float toAngle{ rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle) };
    float lineW{ std::fmin(3.0f, radius * 0.2f) };
    float arcRadius = radius - lineW * 0.5f;
    float arcSkip{ 0.2f };

    juce::Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
        bounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        std::fmin(toAngle + arcSkip, rotaryEndAngle),
        rotaryEndAngle,
        true);

    g.setColour (outline);
    g.strokePath (backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::square));

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        g.setColour(fill);
        g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::square));


        juce::Path radialArc;
        radialArc.startNewSubPath(valueArc.getPointAlongPath(valueArc.getLength()));
        radialArc.lineTo(bounds.getCentreX(), bounds.getCentreY());
        
        juce::Path thumbArc;
        thumbArc.startNewSubPath(radialArc.getPointAlongPath(0.0f));
        thumbArc.lineTo(radialArc.getPointAlongPath(0.6f * radialArc.getLength()));

        g.setGradientFill(juce::ColourGradient(fill, thumbArc.getPointAlongPath(lineW), fill.withAlpha(0.0f), thumbArc.getPointAlongPath(thumbArc.getLength()), false));
        g.strokePath(thumbArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::square));
    }
}

void HalationLookAndFeel::drawLinearSlider(juce::Graphics& g,
    int x,
    int y,
    int width,
    int height,
    float sliderPos,
    float minSliderPos,
    float maxSliderPos,
    const juce::Slider::SliderStyle style,
    juce::Slider& slider)
{
    if (slider.isBar() || style == juce::Slider::SliderStyle::TwoValueVertical || style == juce::Slider::SliderStyle::TwoValueHorizontal || style == juce::Slider::SliderStyle::ThreeValueVertical || style == juce::Slider::SliderStyle::ThreeValueHorizontal)
    {
        juce::LookAndFeel_V4::drawLinearSlider(g,
            x,
            y,
            width,
            height,
            sliderPos,
            minSliderPos,
            maxSliderPos,
            style,
            slider);
        return;
    }
    else
    {
        float trackWidth = std::fmin(6.0f, slider.isHorizontal() ? static_cast<float>(height) * 0.25f : static_cast<float>(width) * 0.25f);

        juce::Point<float> startPoint (slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
            slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y));

        juce::Point<float> endPoint (slider.isHorizontal() ? (float)(width + x) : startPoint.x,
            slider.isHorizontal() ? startPoint.y : (float)y);

        juce::Path backgroundTrack;
        backgroundTrack.startNewSubPath (startPoint);
        backgroundTrack.lineTo (endPoint);
        g.setColour (slider.findColour (juce::Slider::backgroundColourId));
        g.strokePath (backgroundTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::square });

        juce::Path valueTrack;
        juce::Point<float> minPoint, maxPoint, thumbPoint;

        auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
        auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;

        minPoint = startPoint;
        maxPoint = { kx, ky };

        auto thumbWidth = getSliderThumbRadius (slider);

        valueTrack.startNewSubPath (minPoint);
        valueTrack.lineTo (maxPoint);
        g.setColour (slider.findColour (juce::Slider::trackColourId));
        g.strokePath (valueTrack, { trackWidth, juce::PathStrokeType::curved, juce::PathStrokeType::square });
    }
}
