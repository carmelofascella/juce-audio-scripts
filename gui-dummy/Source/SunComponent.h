/*
  ==============================================================================

    SunComponent.h
    Created: 12 Jan 2023 5:18:26pm
    Author:  Carmelo Fascella

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SunComponent  : public juce::Component
{
public:
    SunComponent();
    ~SunComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SunComponent)
};
