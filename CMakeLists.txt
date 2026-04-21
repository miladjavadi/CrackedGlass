# Adapted from https://github.com/TheAudioProgrammer/JuceAudioPluginTemplate
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

project(CrackedGlass
    VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_XCODE_GENERATE_SCHEME OFF)
set(GLOBAL PROPERTY USE_FOLDERS ON)

set(CPM_DOWNLOAD_VERSION 0.42.1)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/CMakeFiles/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if (NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
    message(STATUS "CPM ${CPM_DOWNLOAD_VERSION} not found, downloading to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif ()

include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage(NAME JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG origin/master)

set(SourceFiles
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/SynthSound.h
    Source/SynthVoice.cpp
    Source/SynthVoice.h
    Source/Data/AdsrData.cpp
    Source/Data/AdsrData.h
    Source/Data/DistortionData.cpp
    Source/Data/DistortionData.h
    Source/Data/FilterData.cpp
    Source/Data/FilterData.h
    Source/Data/OscData.cpp
    Source/Data/OscData.h
    Source/UI/Appearance/CrackedGlassLookAndFeel.cpp
    Source/UI/Appearance/CrackedGlassLookAndFeel.h
    Source/UI/Modules/AdsrComponent.cpp
    Source/UI/Modules/AdsrComponent.h
    Source/UI/Modules/DistortionComponent.cpp
    Source/UI/Modules/DistortionComponent.h
    Source/UI/Modules/FilterComponent.cpp
    Source/UI/Modules/FilterComponent.h
    Source/UI/Modules/HeaderComponent.cpp
    Source/UI/Modules/HeaderComponent.h
    Source/UI/Modules/OscComponent.cpp
    Source/UI/Modules/OscComponent.h
    Source/UI/Modules/SynthModule.cpp
    Source/UI/Modules/SynthModule.h
    Source/UI/Modules/Components/AdsrGraphComponent.cpp
    Source/UI/Modules/Components/AdsrGraphComponent.h
    Source/UI/Modules/Components/LabeledRotarySlider.cpp
    Source/UI/Modules/Components/LabeledRotarySlider.h
    Source/UI/Modules/Components/RadioButton.cpp
    Source/UI/Modules/Components/RadioButton.h
    Source/UI/Modules/Components/RadioButtonGroup.cpp
    Source/UI/Modules/Components/RadioButtonGroup.h)

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME "MiladJavadi"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    JUCE_VST3_CAN_REPLACE_VST2 FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE MiJa
    PLUGIN_CODE CrGl
    FORMATS VST3 Standalone
    PRODUCT_NAME "CrackedGlass")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})

target_sources(${PROJECT_NAME} PRIVATE ${SourceFiles})

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${PROJECT_NAME}
PUBLIC
juce::juce_analytics
juce::juce_audio_basics
juce::juce_audio_devices
juce::juce_core
juce::juce_data_structures
juce::juce_graphics
juce::juce_gui_basics
juce::juce_gui_extra
juce::juce_audio_utils
juce::juce_dsp
juce::juce_recommended_config_flags
juce::juce_recommended_lto_flags
juce::juce_recommended_warning_flags)

juce_generate_juce_header(${PROJECT_NAME})

set(BINARY_RESOURCES
    Source/UI/Fonts/QuanticoBold.ttf
    Source/UI/Fonts/QuanticoBoldItalic.ttf
    Source/UI/Fonts/QuanticoItalic.ttf
    Source/UI/Fonts/QuanticoRegular.ttf)

juce_add_binary_data(BinaryData SOURCES ${BINARY_RESOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE BinaryData)