if(EXISTS "D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/unitTests/unitTests[1]_tests.cmake")
  include("D:/ETUDES/TSP/3A/CSC4526/MiniProjet/out/build/x64-Debug/unitTests/unitTests[1]_tests.cmake")
else()
  add_test(unitTests_NOT_BUILT unitTests_NOT_BUILT)
endif()
