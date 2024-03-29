# -*- mode: cmake -*-
# - Try to find APPMON
# Once done this will define
#
#  APPMON_FOUND - system has APPMON
#  APPMON_INCLUDE_DIR - the APPMON include directory
#  APPMON_LIBRARIES - The libraries needed to use APPMON

MESSAGE(STATUS "Looking for AppMon ... ")

if (APPMON_INCLUDE_DIR AND APPMON_LIBRARIES)
  SET (APPMON_INCLUDE_DIR APPMON_INCLUDE_DIR-NOTFOUND)
  SET (APPMON_LIB APPMON_LIB-NOTFOUND)
endif (APPMON_INCLUDE_DIR AND APPMON_LIBRARIES)

# SET(MY_APPMON_DIR $ENV{APPMON_DIR})

FIND_PATH(APPMON_INCLUDE_DIR
  NAMES ApMon.h
  PATHS /usr/local/include NO_DEFAULT_PATH
  PATHS $ENV{APPMON_DIR}/include NO_DEFAULT_PATH
)

FIND_LIBRARY(APPMON_LIB 
  NAMES apmoncpp
  PATHS /usr/local/lib NO_DEFAULT_PATH
  PATHS $ENV{APPMON_DIR}/lib $ENV{APPMON_DIR}/lib64 NO_DEFAULT_PATH
)

SET(APPMON_LIBRARIES ${APPMON_LIB})


if (APPMON_INCLUDE_DIR AND APPMON_LIBRARIES)
   set(APPMON_FOUND TRUE)
endif (APPMON_INCLUDE_DIR AND APPMON_LIBRARIES)

if (APPMON_FOUND)
    MESSAGE(STATUS "Found AppMon in ${APPMON_LIBRARIES}")
#     MESSAGE(STATUS "Found APPMON in ${APPMON_INCLUDE_DIR}")
#     MESSAGE(STATUS "Found APPMON in ${APPMON_LIB_PATH}")
#  TODO find out if it can be before LD_LIBRARY_PATH
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${APPMON_LIBRARY_DIR})
#     SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${APPMON_LIB_PATH})
    set(HAS_APPMON 1)
else (APPMON_FOUND)
  set(HAS_APPMON 0)
  if (APPMON_FIND_REQUIRED)
    MESSAGE(STATUS "$APPMON_DIR is probably not set. Make sure that you set $APPMON_DIR !!!")
    MESSAGE(FATAL_ERROR "Looking for AppMon ... - Not found ")
  endif (APPMON_FIND_REQUIRED)
#     MESSAGE(STATUS "Not Found AppMon ...")
endif (APPMON_FOUND)
