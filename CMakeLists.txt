cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(PROJECT_LaBr)

#----------------------------------------------------------------------------

set(useROOT false)
set(SOURCE_DIRECTORIES src)
set(EXECUTABLES Ladecay)
set(SCRIPTS vis.mac run.mac)

#----------------------------------------------------------------------------

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

if(useROOT)
  list(APPEND SOURCE_DIRECTORIES)
  list(APPEND EXECUTABLES)
endif(useROOT)

set(SOURCES_DIRECTORIES_FULL)
foreach(_directory ${SOURCE_DIRECTORIES})
  list(APPEND SOURCE_DIRECTORIES_FULL ${PROJECT_SOURCE_DIR}/${_directory})
endforeach(_directory)

set(SOURCES)
foreach(_directory ${SOURCE_DIRECTORIES_FULL})
  list(APPEND SOURCES ${_directory}/*.cc)
endforeach(_directory)

set(HEADERS)
foreach(_directory ${SOURCE_DIRECTORIES_FULL})
  list(APPEND HEADERS ${_directory}/*.hh)
endforeach(_directory)

include(${Geant4_USE_FILE})
include_directories(${SOURCE_DIRECTORIES_FULL})

if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
endif(useROOT)

file(GLOB sources ${SOURCES})
file(GLOB headers ${HEADERS})

foreach(_executable ${EXECUTABLES})
  add_executable(${_executable} ${_executable}.cc ${sources} ${headers})
if(useROOT)
  EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
endif(useROOT)
  target_link_libraries(${_executable} ${Geant4_LIBRARIES})
endforeach(_executable)

foreach(_script ${SCRIPTS})
  configure_file( ${PROJECT_SOURCE_DIR}/${_script} ${PROJECT_BINARY_DIR}/${_script} COPYONLY)
endforeach(_script)

add_custom_target(PROJECT_LaBr DEPENDS ${EXECUTABLES})

foreach(_executable ${EXECUTABLES})
  install(TARGETS ${_executable} DESTINATION bin)
endforeach(_executable)
