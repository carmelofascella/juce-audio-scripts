/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainsliderAudioProcessorEditor::GainsliderAudioProcessorEditor (GainsliderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (200, 400);
    //sliderAttach = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, GAIN_ID, gainSlider);
    
    
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    //gainSlider.setRange(-40.0, 0.0);
    //gainSlider.setValue(-1.0);
    //gainSlider.addListener(this);
    gainSliderAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(
            audioProcessor.treeState, GAIN_ID, gainSlider));
}

GainsliderAudioProcessorEditor::~GainsliderAudioProcessorEditor()
{
}

//==============================================================================
void GainsliderAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    gainSlider.setBounds(getLocalBounds());
    
}

void GainsliderAudioProcessorEditor::resized()
{
    gainSlider.setBounds(getLocalBounds());
}

void GainsliderAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &gainSlider)
    {
        audioProcessor.rawVolume = pow (10, slider->getValue() / 20);
    }
}
