# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/_deps/googletest-src"
  "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/_deps/googletest-build"
  "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
