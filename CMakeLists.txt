cmake_minimum_required(VERSION 3.22)

include(ProjectVersion.cmake)

project(LDSP_Horn2 VERSION ${LDSP_HORN2_VERSION} LANGUAGES C CXX OBJC OBJCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(JUCE_DIR "" CACHE PATH "Optional path to a local JUCE checkout")

if(JUCE_DIR)
    add_subdirectory("${JUCE_DIR}" JUCE)
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/JUCE/CMakeLists.txt")
    add_subdirectory(external/JUCE JUCE)
else()
    find_package(JUCE CONFIG QUIET)

    if(NOT JUCE_FOUND)
        include(FetchContent)

        FetchContent_Declare(JUCE
            GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
            GIT_TAG 8.0.13
            GIT_SHALLOW TRUE)

        FetchContent_MakeAvailable(JUCE)
    endif()
endif()

juce_add_plugin(LDSP_Horn2
    VERSION ${PROJECT_VERSION}
    COMPANY_NAME "LDSP"
    BUNDLE_ID "com.ldsp.LDSP_Horn2"
    PLUGIN_NAME "TootYourOwnHorn"
    PLUGIN_MANUFACTURER_CODE LDSP
    PLUGIN_CODE Hrn2
    AU_MAIN_TYPE kAudioUnitType_Generator
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    VST_NUM_MIDI_INS 1
    VST3_CATEGORIES Instrument
    COPY_PLUGIN_AFTER_BUILD TRUE
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "LDSP_Horn2")

set(LDSP_HORN2_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/Output/$<CONFIG>")

set_target_properties(LDSP_Horn2 PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}")

set_target_properties(LDSP_Horn2_Standalone PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}/standalone"
    LIBRARY_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}/standalone"
    RUNTIME_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}/standalone")

set_target_properties(LDSP_Horn2_AU PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}/au"
    LIBRARY_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}/au"
    RUNTIME_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}/au")

set_target_properties(LDSP_Horn2_VST3 PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}/vst3"
    LIBRARY_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}/vst3"
    RUNTIME_OUTPUT_DIRECTORY "${LDSP_HORN2_OUTPUT_DIR}/vst3")

juce_generate_juce_header(LDSP_Horn2)

target_sources(LDSP_Horn2
    PRIVATE
        Source/PluginEditor.cpp
        Source/PluginProcessor.cpp)

target_compile_definitions(LDSP_Horn2
    PUBLIC
        JUCE_STRICT_REFCOUNTEDPOINTER=1
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(LDSP_Horn2
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_opengl
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
