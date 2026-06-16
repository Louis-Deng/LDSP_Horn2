/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LDSP_Horn2AudioProcessorEditor::LDSP_Horn2AudioProcessorEditor (LDSP_Horn2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (900, 600);
}

LDSP_Horn2AudioProcessorEditor::~LDSP_Horn2AudioProcessorEditor()
{
}

//==============================================================================
void LDSP_Horn2AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (18.0f));
    // version string is OWNED in CMakeLists.txt (3)
    g.drawFittedText ("TootYourOwnHorn v" JucePlugin_VersionString, getLocalBounds(), juce::Justification::topLeft, 1);
}

void LDSP_Horn2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
