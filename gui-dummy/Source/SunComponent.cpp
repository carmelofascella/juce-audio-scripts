/*
  ==============================================================================

    SunComponent.cpp
    Created: 12 Jan 2023 5:18:26pm
    Author:  Carmelo Fascella

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SunComponent.h"

//==============================================================================
SunComponent::SunComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SunComponent::~SunComponent()
{
}

void SunComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::yellow);
    g.drawEllipse(400, 50, 50, 50, 10.0f);
}

void SunComponent::resized()
{


}
