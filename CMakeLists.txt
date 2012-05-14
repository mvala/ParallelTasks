project(ParallelTasks)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(Threads REQUIRED)
find_package(XROOTD)
find_package(ALIEN)
find_package(ROOT REQUIRED)
find_package(APPMON)

MESSAGE(STATUS "Checking root.exe ...")
FIND_PROGRAM(ROOT_EXE NAME root.exe PATHS $ENV{ROOTSYS}/bin /usr/local/bin /usr/bin /bin NO_DEFAULT_PATH )
if (ROOT_EXE)
	MESSAGE(STATUS "Found root.exe in ${ROOT_EXE}")
endif (ROOT_EXE)

MESSAGE(STATUS "Checking zip ...")
FIND_PROGRAM(XRDDM_ZIP NAME zip PATHS /usr/local/bin /usr/bin /bin NO_DEFAULT_PATH )
if (XRDDM_ZIP)
    MESSAGE(STATUS "Found zip in ${XRDDM_ZIP}")
endif (XRDDM_ZIP)


if(APPMON_FOUND)
  option(HAS_APPMON "Using AppMon" ON)
endif(APPMON_FOUND)

add_subdirectory(ParallelTasks)

include(CPack)

# uninstall
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
