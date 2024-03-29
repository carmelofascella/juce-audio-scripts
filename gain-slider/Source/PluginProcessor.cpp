/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainsliderAudioProcessor::GainsliderAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState(*this,
          nullptr,
          juce::Identifier("GainSliderPlugin"),
          {std::make_unique<juce::AudioParameterFloat>(GAIN_ID,
                                                       GAIN_NAME,
                                                       juce::Range<float>{-40.f, 1.0f},
                                                       0.0f)
            })

#endif
{
    gainSliderParameter = treeState.getRawParameterValue(GAIN_ID);
    //juce::AudioProcessorValueTreeState
    //juce::NormalisableRange<float> gainRange (0.0f, 1.0f);
    //treeState.createAndAddParameter(GAIN_ID, GAIN_NAME, GAIN_NAME, gainRange, 0.5f, nullptr, //nullptr);

}

GainsliderAudioProcessor::~GainsliderAudioProcessor()
{
}

//==============================================================================
const juce::String GainsliderAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainsliderAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainsliderAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainsliderAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainsliderAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainsliderAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainsliderAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainsliderAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GainsliderAudioProcessor::getProgramName (int index)
{
    return {};
}

void GainsliderAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GainsliderAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GainsliderAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainsliderAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void GainsliderAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for(int sample=0; sample < buffer.getNumSamples(); ++sample)
        {
            // in C++, std::atomic<T> to T conversion is equivalent to a load.
            //conversion from dB value to linear value.
            const auto gainParameter = pow( 10, gainSliderParameter->load() / 20);
                
            channelData[sample] = buffer.getSample(channel, sample) * gainParameter;
        }
    }
}

//==============================================================================
bool GainsliderAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GainsliderAudioProcessor::createEditor()
{
    return new GainsliderAudioProcessorEditor (*this);
}

//==============================================================================
void GainsliderAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainsliderAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainsliderAudioProcessor();
}




