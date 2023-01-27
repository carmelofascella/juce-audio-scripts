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
    
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-40.0, 0.0);
    gainSlider.setValue(-1.0);
    gainSlider.addListener(this);
}

GainsliderAudioProcessorEditor::~GainsliderAudioProcessorEditor()
{
}

//==============================================================================
void GainsliderAudioProcessorEditor::paint (juce::Graphics& g)
{
    gainSlider.setBounds(getLocalBounds());
    
}

void GainsliderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void GainsliderAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &gainSlider)
    {
        audioProcessor.rawVolume = pow (10, slider->getValue() / 20);
    }
}
