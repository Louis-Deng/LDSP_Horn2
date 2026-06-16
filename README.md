# LDSP_Horn2

Portable CMake/JUCE project for the `TootYourOwnHorn` audio plugin.

This repository is intended to be built from CMake only. The `.jucer` file is kept as metadata reference; generated Projucer/Xcode/JUCE glue is not part of the source tree.

## Requirements

- CMake 3.22 or newer
- A C++20 compiler
- macOS with Xcode Command Line Tools for AU, VST3, and standalone app builds
- Internet access on first configure, unless JUCE is provided locally

## JUCE Setup

CMake resolves JUCE in this order:

1. `-DJUCE_DIR=/path/to/JUCE`
2. `external/JUCE` inside this repo
3. An installed JUCE CMake package
4. `FetchContent`, which downloads JUCE `8.0.13`

For the simplest portable setup with internet access, no manual JUCE install is needed:

```sh
cmake -S . -B Builds/CMake/Debug -DCMAKE_BUILD_TYPE=Debug
```

For an offline or pinned dependency setup, add JUCE as a repo-local dependency:

```sh
git submodule add https://github.com/juce-framework/JUCE.git external/JUCE
git submodule update --init --recursive
```

Then configure normally:

```sh
cmake -S . -B Builds/CMake/Debug -DCMAKE_BUILD_TYPE=Debug
```

If you already have JUCE elsewhere, keep the path local to your machine:

```sh
cmake -S . -B Builds/CMake/Debug -DCMAKE_BUILD_TYPE=Debug -DJUCE_DIR=/path/to/JUCE
```

Do not commit local absolute paths or generated CMake cache files.

## Build

Configure Debug:

```sh
cmake -S . -B Builds/CMake/Debug -DCMAKE_BUILD_TYPE=Debug
```

Configure Release:

```sh
cmake -S . -B Builds/CMake/Release -DCMAKE_BUILD_TYPE=Release
```

Build standalone:

```sh
cmake --build Builds/CMake/Debug --target LDSP_Horn2_Standalone --config Debug --parallel
cmake --build Builds/CMake/Release --target LDSP_Horn2_Standalone --config Release --parallel
```

Build AU:

```sh
cmake --build Builds/CMake/Debug --target LDSP_Horn2_AU --config Debug --parallel
cmake --build Builds/CMake/Release --target LDSP_Horn2_AU --config Release --parallel
```

Build VST3:

```sh
cmake --build Builds/CMake/Debug --target LDSP_Horn2_VST3 --config Debug --parallel
cmake --build Builds/CMake/Release --target LDSP_Horn2_VST3 --config Release --parallel
```

## Output

Build products are written to:

```text
Output/Debug/standalone/
Output/Debug/au/
Output/Debug/vst3/
Output/Release/standalone/
Output/Release/au/
Output/Release/vst3/
```

`Builds/` contains generated CMake files only. `Output/` contains local build products. Both are ignored by git.

## Cursor / VS Code

The repository includes tasks for:

- `Standalone Debug`
- `Standalone Release`
- `AU Debug`
- `AU Release`
- `VST3 Debug`
- `VST3 Release`
- `AU Validation`

The debug launch configuration builds `Standalone Debug` first, then launches:

```text
Output/Debug/standalone/LDSP_Horn2.app/Contents/MacOS/LDSP_Horn2
```

## Version

The project version is defined in:

```text
ProjectVersion.cmake
```

Change `LDSP_HORN2_VERSION` there, then reconfigure CMake.

## Clean Generated Files

To remove local generated state:

```sh
rm -rf Builds Output build
```

Then configure again with CMake.
