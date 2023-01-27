/*
  ==============================================================================

    TextComponent.cpp
    Created: 12 Jan 2023 5:21:25pm
    Author:  Carmelo Fascella

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TextComponent.h"

//==============================================================================
TextComponent::TextComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TextComponent::~TextComponent()
{
}

void TextComponent::paint (juce::Graphics& g)
{
    juce::Font theFont("Cooper Std", "Black Italic", 30.0f);
    g.setFont(theFont);
    g.drawText("Lesss Gooo", 0, 0, 500, 100, juce::Justification::topLeft);
}

void TextComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
