/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LDSP_Horn2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LDSP_Horn2AudioProcessorEditor (LDSP_Horn2AudioProcessor&);
    ~LDSP_Horn2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LDSP_Horn2AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LDSP_Horn2AudioProcessorEditor)
};
