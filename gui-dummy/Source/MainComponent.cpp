#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    addAndMakeVisible(wall);
    addAndMakeVisible(grass);
    addAndMakeVisible(roof);
    addAndMakeVisible(sun);
    addAndMakeVisible(text);
    
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::skyblue);
}

void MainComponent::resized()
{
    wall.setBounds(getLocalBounds());
    grass.setBounds(getLocalBounds());
    roof.setBounds(getLocalBounds());
    sun.setBounds(getLocalBounds());
    text.setBounds(getLocalBounds());
    
}
