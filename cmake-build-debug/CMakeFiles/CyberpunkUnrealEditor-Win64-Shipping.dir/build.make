# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Jessica\Current Projects\CyberpunkUnreal"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Jessica\Current Projects\CyberpunkUnreal\cmake-build-debug"

# Utility rule file for CyberpunkUnrealEditor-Win64-Shipping.

# Include the progress variables for this target.
include CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\progress.make

CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping:
	call "D:/Epic Games Launcher/UE_4.23/Engine/Build/BatchFiles/Build.bat" CyberpunkUnrealEditor Win64 Shipping "-project=C:/Users/Jessica/Current Projects/CyberpunkUnreal/CyberpunkUnreal.uproject" -game -progress -buildscw

CyberpunkUnrealEditor-Win64-Shipping: CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping
CyberpunkUnrealEditor-Win64-Shipping: CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\build.make

.PHONY : CyberpunkUnrealEditor-Win64-Shipping

# Rule to build all files generated by this target.
CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\build: CyberpunkUnrealEditor-Win64-Shipping

.PHONY : CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\build

CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\cmake_clean.cmake
.PHONY : CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\clean

CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\Jessica\Current Projects\CyberpunkUnreal" "C:\Users\Jessica\Current Projects\CyberpunkUnreal" "C:\Users\Jessica\Current Projects\CyberpunkUnreal\cmake-build-debug" "C:\Users\Jessica\Current Projects\CyberpunkUnreal\cmake-build-debug" "C:\Users\Jessica\Current Projects\CyberpunkUnreal\cmake-build-debug\CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\CyberpunkUnrealEditor-Win64-Shipping.dir\depend

