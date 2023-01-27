#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    //if (juce::RuntimePermissions::isRequired //(juce::RuntimePermissions::recordAudio)
    //    && ! juce::RuntimePermissions::isGranted //(juce::RuntimePermissions::recordAudio))
    //{
    //    juce::RuntimePermissions::request //(juce::RuntimePermissions::recordAudio,
    //                                       [&] (bool granted) { //setAudioChannels //(granted ? 2 : 0, 2); //});
    //}
    //else
    //{
    //    // Specify the number of input and output channels that we //want to open
    //    setAudioChannels (2, 2);
    //}
    //
    setAudioChannels (0, 2);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    juce::String message;
    message << "Preparing to play audio...\n";
    message << " samplesPerBlockExpected = " << samplesPerBlockExpected << "\n";
    message << " sampleRate = " << sampleRate;
    juce::Logger::getCurrentLogger()->writeToLog (message);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    int numChannels = bufferToFill.buffer->getNumChannels();
    for (int channel = 0; channel < numChannels; ++channel)
    {
        // Get a pointer to the start sample in the buffer for this audio output channel
        auto* buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);

        // Fill the required number of samples with noise between -0.125 and +0.125
        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
            buffer[sample] = 0.1f * (random.nextFloat() * 2.0f - 1.0f);
    }
    
}

void MainComponent::releaseResources()
{
    juce::Logger::getCurrentLogger()->writeToLog ("Releasing audio resources");
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
