#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    freqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    freqSlider.setRange(50.0f, 500.0f, 0.1);
    freqSlider.addListener(this);
    freqSlider.setValue(200);
    freqSlider.setTextValueSuffix("Hz");
    freqLabel.setText("Frequency", juce::dontSendNotification);
    freqLabel.attachToComponent(&freqSlider, true);
    
    ampSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    ampSlider.setRange(0.f, 1.0f);
    ampSlider.setValue(0.5f);
    ampSlider.addListener(this);
    
    ampSlider .setSkewFactorFromMidPoint (0.25);
    
    ampLabel.setText("Amplitude", juce::dontSendNotification);
    ampLabel.attachToComponent(&ampSlider, true);
    
    
    addAndMakeVisible(freqSlider);
    addAndMakeVisible(ampSlider);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    //currentSampleRate = sampleRate;
    frequency = freqSlider.getValue();
    amplitude = ampSlider.getValue();
    phase = 0;     //in the wavetable, the phase is the index of the element.
    wtSize = 1024; //num samples in the wavetable
    currentSampleRate = sampleRate;
    
    
    //insert sin values in the wavetable
    for(int i = 0; i < wtSize; i++)
    {
        waveTable.insert(i, std::sin(2.0f * juce::MathConstants<double>::pi * i / wtSize));
    }
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    float* const leftSpeaker = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    float* const rightSpeaker = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    
    for(int sample=0; sample<bufferToFill.numSamples; sample++)
    {
        //phase is the position of the wavetable
        leftSpeaker[sample] = waveTable[(int)phase] * amplitude;
        rightSpeaker[sample] = waveTable[(int)phase] * amplitude;
        updateFrequency();
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
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
    const int labelSpace = 100;
    const int heightSliders = 20;
    freqSlider.setBounds(labelSpace, heightSliders, getWidth() - 100, 20);
    ampSlider.setBounds(labelSpace, heightSliders + 100, getWidth() - 100, 20);
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &freqSlider)
    {
        std::cout << "update FREQ" << std::endl;
        frequency = freqSlider.getValue();
        updateFrequency();
    }
    
    else if(slider == &ampSlider)
    {
        std::cout << "update AMP" << std::endl;
        amplitude = ampSlider.getValue();
    }
}
void MainComponent::updateFrequency()
{
    increment = frequency * wtSize / currentSampleRate; //increment in the wavetable
    phase = std::fmod(phase + increment, wtSize);
}
