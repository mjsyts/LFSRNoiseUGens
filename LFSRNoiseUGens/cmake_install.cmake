# Install script for directory: /Users/josiahsytsma/LFSRNoiseUGens/LFSRNoiseUGens

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/josiahsytsma/Library/Application Support/SuperCollider/Extensions")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise" TYPE MODULE FILES "/Users/josiahsytsma/LFSRNoiseUGens/LFSRNoiseUGens/LFSRNoise_scsynth.scx")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise/LFSRNoise_scsynth.scx" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise/LFSRNoise_scsynth.scx")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise/LFSRNoise_scsynth.scx")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise" TYPE MODULE FILES "/Users/josiahsytsma/LFSRNoiseUGens/LFSRNoiseUGens/LFSRNoise_supernova.scx")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise/LFSRNoise_supernova.scx" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise/LFSRNoise_supernova.scx")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise/LFSRNoise_supernova.scx")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise/Classes" TYPE FILE FILES "/Users/josiahsytsma/LFSRNoiseUGens/LFSRNoiseUGens/plugins/LFSRNoise/LFSRNoiseUGens.sc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/LFSRNoiseUGens/LFSRNoise/HelpSource/Classes" TYPE FILE FILES "/Users/josiahsytsma/LFSRNoiseUGens/LFSRNoiseUGens/plugins/LFSRNoise/LFSRNoise.schelp")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/josiahsytsma/LFSRNoiseUGens/LFSRNoiseUGens/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
