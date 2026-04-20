/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "SynthVoice.h"
#include "SynthSound.h"

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <cmath>

//==============================================================================
CrackedGlassAudioProcessor::CrackedGlassAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "PARAMETERZ", createParameters())
#endif
{
    synth.addSound (new SynthSound());
    for (int i = 0; i < 16; ++i)
    {
        synth.addVoice (new SynthVoice());
    }
}

CrackedGlassAudioProcessor::~CrackedGlassAudioProcessor()
{
}

//==============================================================================
const juce::String CrackedGlassAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CrackedGlassAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CrackedGlassAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CrackedGlassAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CrackedGlassAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CrackedGlassAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CrackedGlassAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CrackedGlassAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CrackedGlassAudioProcessor::getProgramName (int index)
{
    return {};
}

void CrackedGlassAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CrackedGlassAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    //DBG("prepareToPlay called with sample rate: " << sampleRate);

    juce::dsp::ProcessSpec spec{ sampleRate, samplesPerBlock, getTotalNumOutputChannels() };

    synth.setCurrentPlaybackSampleRate (sampleRate);

    for (int i{ 0 }; i < synth.getNumVoices(); ++i)
    {
        if (SynthVoice* voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay (sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    distortion.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    //dcBlocker.prepare(spec);
    //dcBlocker.setCutoffFrequency(5.0f);
    //dcBlocker.setType(juce::dsp::StateVariableTPTFilterType::highpass);
}

void CrackedGlassAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CrackedGlassAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CrackedGlassAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // get amplitude envelope parameters
    std::atomic<float>& attack = *apvts.getRawParameterValue("ATTACK");
    std::atomic<float>& decay = *apvts.getRawParameterValue("DECAY");
    std::atomic<float>& sustain = *apvts.getRawParameterValue("SUSTAIN");
    std::atomic<float>& release = *apvts.getRawParameterValue("RELEASE");

    // get waveshape and lfo parameters
    std::atomic<float>& waveshape = *apvts.getRawParameterValue("OSC1WAVESHAPE");
    std::atomic<float>& fmFrequency = *apvts.getRawParameterValue("FMFREQUENCY");
    std::atomic<float>& fmDepth = *apvts.getRawParameterValue("FMDEPTH");

    // get tuning parameters
    std::atomic<float>& coarsePitch = *apvts.getRawParameterValue("OSC1COARSEPITCH");
    std::atomic<float>& finePitch = *apvts.getRawParameterValue("OSC1FINEPITCH");

    // get and update filter parameters
    std::atomic<float>& filterEnable = *apvts.getRawParameterValue("FILTERENABLE");
    std::atomic<float>& filterType = *apvts.getRawParameterValue("FILTERTYPE");

    std::atomic<float>& filterCutoffFrequency = *apvts.getRawParameterValue("CUTOFFFREQUENCY");
    std::atomic<float>& filterResonance = *apvts.getRawParameterValue("RESONANCE");

    // get mod envelope parameters
    std::atomic<float>& modEnable = *apvts.getRawParameterValue("MODENABLE");

    std::atomic<float>& modAttack = *apvts.getRawParameterValue("MODATTACK");
    std::atomic<float>& modDecay = *apvts.getRawParameterValue("MODDECAY");
    std::atomic<float>& modSustain = *apvts.getRawParameterValue("MODSUSTAIN");
    std::atomic<float>& modRelease = *apvts.getRawParameterValue("MODRELEASE");

    // get distortion parameters
    std::atomic<float>& distortionEnable = *apvts.getRawParameterValue("DISTORTIONENABLE");
    std::atomic<float>& distortionFunction = *apvts.getRawParameterValue("DISTORTIONFUNCTION");
    std::atomic<float>& distortionDrive = *apvts.getRawParameterValue("DISTORTIONDRIVE");

    distortion.updateParameters(static_cast<bool>(distortionEnable.load()), distortionDrive.load(), static_cast<DistortionData::Function>(distortionFunction.load()));

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // update oscillator
            voice->getOscillator().setWaveshape(static_cast<OscData::Waveshape>(waveshape.load()));
            voice->getOscillator().setLFOParams(fmDepth.load(), fmFrequency.load());
            voice->getOscillator().setTuningFactor(static_cast<int>(coarsePitch.load()), static_cast<int>(finePitch.load()));

            // update amplitude envelope
            voice->updateAdsr (attack.load(), decay.load(), sustain.load(), release.load());

            // update filter
            voice->updateFilter(static_cast<bool>(filterEnable.load()), static_cast<juce::dsp::StateVariableTPTFilterType>(filterType.load()), filterCutoffFrequency.load(), filterResonance.load());

            // update mod envelope
            voice->updateModAdsr (static_cast<bool>(modEnable.load()), modAttack.load(), modDecay.load(), modSustain.load(), modRelease.load());
        }
    }

    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block{ buffer };
    //dcBlocker.process(juce::dsp::ProcessContextReplacing<float>(block));

    distortion.process(buffer);

    // get and update output gain
    setGain(*apvts.getRawParameterValue("GAIN") / 100.0f);
    buffer.applyGainRamp(0, buffer.getNumSamples(), lastGain, gain);
    lastGain = gain;
}

//==============================================================================
bool CrackedGlassAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CrackedGlassAudioProcessor::createEditor()
{
    return new CrackedGlassAudioProcessorEditor (*this);
}

//==============================================================================
void CrackedGlassAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    juce::ValueTree state{ apvts.copyState() };
    std::unique_ptr<juce::XmlElement> xml{ state.createXml() };
    copyXmlToBinary(*xml, destData);
}

void CrackedGlassAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState{ getXmlFromBinary(data, sizeInBytes) };
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(apvts.state.getType()))
        {
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout CrackedGlassAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    // amplitude envelope
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("AMPENVENABLE", "Enable Amp Envelope", true));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("ATTACK", "Attack", juce::NormalisableRange<float>{ 0.0f, 5.0f, 0.01f }, 0.01f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("DECAY", "Decay", juce::NormalisableRange<float>{ 0.0f, 3.0f, 0.01f }, 2.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("SUSTAIN", "Sustain", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 0.45f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("RELEASE", "Release", juce::NormalisableRange<float>{ 0.0f, 2.5f, 0.01f }, 0.1f));

    // output gain
    parameters.push_back (std::make_unique<juce::AudioParameterInt> ("GAIN", "Gain", 0, 150, 60));

    // waveshape and tuning
    parameters.push_back (std::make_unique<juce::AudioParameterChoice> ("OSC1WAVESHAPE", "Oscillator 1 Waveshape", juce::StringArray{ "SIN", "SAW", "SQR", "RND" }, static_cast<int>(OscData::Waveshape::sine)));
    parameters.push_back (std::make_unique<juce::AudioParameterInt> ("OSC1COARSEPITCH", "Oscillator 1 Coarse Pitch", -12, 12, 0));
    parameters.push_back (std::make_unique<juce::AudioParameterInt> ("OSC1FINEPITCH", "Oscillator 1 Fine Pitch", -50, 50, 0));

    // fm
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("FMFREQUENCY", "FM Frequency", juce::NormalisableRange<float>{ 0.0f, 30.0f, 0.1f, 0.3f }, 4.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("FMDEPTH", "FM Depth", juce::NormalisableRange<float>{ 0.0f, 2.0f, 0.001f, 0.3f }, 0.0f));

    // filter
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("FILTERENABLE", "Enable Filter", false));
    parameters.push_back (std::make_unique<juce::AudioParameterChoice> ("FILTERTYPE", "Filter Type", juce::StringArray{ "LP", "BP", "HP" }, static_cast<int>(juce::dsp::StateVariableTPTFilterType::lowpass)));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("CUTOFFFREQUENCY", "Filter Cutoff Frequency", juce::NormalisableRange<float>{ 20.0f, 20'000.0f, 0.1f, 0.2f }, 10'000.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("RESONANCE", "Filter Resonance", juce::NormalisableRange<float>{ 1 / std::sqrtf(2), 10.0f, 0.1f }, 1.0f));

    // filter envelope
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("MODENABLE", "Enable Modulation", false));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("MODATTACK", "Modulation Attack", juce::NormalisableRange<float>{ 0.0f, 5.0f, 0.01f }, 0.02f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("MODDECAY", "Modulation Decay", juce::NormalisableRange<float>{ 0.0f, 3.0f, 0.01f }, 2.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("MODSUSTAIN", "Modulation Sustain", juce::NormalisableRange<float>{ 0.0f, 1.0f, 0.01f }, 1.0f));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("MODRELEASE", "Modulation Release", juce::NormalisableRange<float>{ 0.0f, 2.5f, 0.01f }, 5.0f));

    // distortion
    parameters.push_back (std::make_unique<juce::AudioParameterBool> ("DISTORTIONENABLE", "Enable Distortion", false));
    parameters.push_back (std::make_unique<juce::AudioParameterChoice> ("DISTORTIONFUNCTION", "Distortion Function", juce::StringArray{ "TANH", "CLIP", "CRCK", "SHTR" }, static_cast<int>(DistortionData::Function::tanh)));
    parameters.push_back (std::make_unique<juce::AudioParameterFloat> ("DISTORTIONDRIVE", "Distortion Drive", juce::NormalisableRange<float>{ 0.0f, 10.0f }, 0.0f));

    return { parameters.begin(), parameters.end() };
}

void CrackedGlassAudioProcessor::setGain(float value)
{
    gain = value;
}

const juce::AudioProcessorValueTreeState& CrackedGlassAudioProcessor::getAPVTS() const
{
    return apvts;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CrackedGlassAudioProcessor();
}

// Value Tree