/*
  ==============================================================================

    WallComponent.h
    Created: 12 Jan 2023 4:50:06pm
    Author:  Carmelo Fascella

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WallComponent  : public juce::Component
{
public:
    WallComponent();
    ~WallComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WallComponent)
};
