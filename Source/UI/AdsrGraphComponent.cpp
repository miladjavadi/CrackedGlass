/*
  ==============================================================================

    AdsrGraphComponent.cpp
    Created: 12 Apr 2026 3:36:32pm
    Author:  milad

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrGraphComponent.h"

//==============================================================================
AdsrGraphComponent::AdsrGraphComponent(juce::AudioProcessorValueTreeState& apvts, const juce::String& attackParameterID, const juce::String& decayParameterID, const juce::String& sustainParameterID, const juce::String& releaseParameterID, juce::Colour mainColour)
    : m_apvts{ apvts }
    , m_attackParameterID{ attackParameterID }
    , m_decayParameterID{ decayParameterID }
    , m_sustainParameterID{ sustainParameterID }
    , m_releaseParameterID{ releaseParameterID }
    , borderColour{ mainColour.withBrightness(1.0f).withSaturation(0.6f) }
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    m_apvts.addParameterListener(m_attackParameterID, this);
    m_apvts.addParameterListener(m_decayParameterID, this);
    m_apvts.addParameterListener(m_sustainParameterID, this);
    m_apvts.addParameterListener(m_releaseParameterID, this);

    maxAttack = m_apvts.getParameterRange(m_attackParameterID).end;
    maxDecay = m_apvts.getParameterRange(m_decayParameterID).end;
    maxRelease = m_apvts.getParameterRange(m_releaseParameterID).end;
    maxEnvelopeDuration = maxAttack + maxDecay + maxRelease;

    lastAttack = m_apvts.getRawParameterValue(m_attackParameterID)->load();
    lastDecay = m_apvts.getRawParameterValue(m_decayParameterID)->load();
    lastSustain = m_apvts.getRawParameterValue(m_sustainParameterID)->load();
    lastRelease = m_apvts.getRawParameterValue(m_releaseParameterID)->load();
}

AdsrGraphComponent::~AdsrGraphComponent()
{
    m_apvts.removeParameterListener(m_attackParameterID, this);
    m_apvts.removeParameterListener(m_decayParameterID, this);
    m_apvts.removeParameterListener(m_sustainParameterID, this);
    m_apvts.removeParameterListener(m_releaseParameterID, this);
}

void AdsrGraphComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (static_cast<juce::Colour>(0x00000000));   // clear the background

    g.setColour(borderColour);
    g.drawRect (getLocalBounds(), 1);

    constexpr int marginTop{ 5 };
    constexpr int marginSides{ 8 };
    juce::Rectangle<int> bounds{ getLocalBounds() };
    bounds.reduce(marginSides, 0);
    bounds.setY(bounds.getY() + 10);
    bounds.setHeight(bounds.getHeight() - 10);

    constexpr int pointRadius{ 3 };

    juce::Path graph;

    juce::Point<float> attackStart{ static_cast<float>(bounds.getX()), static_cast<float>(bounds.getBottom())};
    juce::Point<float> decayStart{ static_cast<float>(bounds.getX()) + bounds.getWidth() * lastAttack / maxEnvelopeDuration, static_cast<float>(bounds.getY()) };
    //juce::Point<float> sustainStart{ static_cast<float>(decayStart.getX()) + graphWidth * lastDecay / maxEnvelopeDuration, static_cast<float>(decayStart.getY()) + (1.0f - lastSustain) * graphHeight };
    juce::Point<float> releaseStart{ static_cast<float>(decayStart.getX()) + bounds.getWidth() * lastDecay / maxEnvelopeDuration, static_cast<float>(decayStart.getY()) + (1.0f - lastSustain) * bounds.getHeight()};
    juce::Point<float> releaseEnd{ static_cast<float>(releaseStart.getX()) + bounds.getWidth() * lastRelease / maxEnvelopeDuration, static_cast<float>(bounds.getBottom()) };
    juce::Point<float> graphEnd{ static_cast<float>(bounds.getRight()), static_cast<float>(bounds.getBottom())};
    
    graph.startNewSubPath(attackStart);
    graph.lineTo(decayStart);
    //graph.lineTo(sustainStart);
    graph.lineTo(releaseStart);
    graph.lineTo(releaseEnd);
    //graph.lineTo(graphEnd);

    g.strokePath(graph, juce::PathStrokeType(2.0f));

    graph.closeSubPath();
    g.setGradientFill(juce::ColourGradient(borderColour, 0.0f, 0.0f, static_cast<juce::Colour>(0x00000000), 0.0f, static_cast<float>(bounds.getBottom()), false));
    g.fillPath(graph);

    g.setColour(borderColour);

    g.fillEllipse(attackStart.getX() - pointRadius, attackStart.getY() - pointRadius, 2 * pointRadius, 2 * pointRadius);
    g.fillEllipse(decayStart.getX() - pointRadius, decayStart.getY() - pointRadius, 2 * pointRadius, 2 * pointRadius);
    g.fillEllipse(releaseStart.getX() - pointRadius, releaseStart.getY() - pointRadius, 2 * pointRadius, 2 * pointRadius);
    g.fillEllipse(releaseEnd.getX() - pointRadius, releaseEnd.getY() - pointRadius, 2 * pointRadius, 2 * pointRadius);
}

void AdsrGraphComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void AdsrGraphComponent::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == m_attackParameterID)
    {
        lastAttack = newValue;
    }
    else if (parameterID == m_decayParameterID)
    {
        lastDecay = newValue;
    }
    else if (parameterID == m_sustainParameterID)
    {
        lastSustain = newValue;
    }
    else if (parameterID == m_releaseParameterID)
    {
        lastRelease = newValue;
    }

    repaint();
}
