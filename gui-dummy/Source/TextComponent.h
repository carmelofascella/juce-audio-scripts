/*
  ==============================================================================

    TextComponent.h
    Created: 12 Jan 2023 5:21:25pm
    Author:  Carmelo Fascella

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TextComponent  : public juce::Component
{
public:
    TextComponent();
    ~TextComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextComponent)
};
