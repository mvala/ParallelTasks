# -*- mode: cmake -*-
# - Try to find ALIEN
# Once done this will define
#
#  ALIEN_FOUND - system has ALIEN
#  ALIEN_INCLUDE_DIR - the ALIEN include directory
#  ALIEN_LIBRARIES - The libraries needed to use ALIEN

MESSAGE(STATUS "Looking for AliEn... ")

if (ALIEN_INCLUDE_DIR AND ALIEN_LIBRARIES)
  SET (ALIEN_INCLUDE_DIR ALIEN_INCLUDE_DIR-NOTFOUND)
  SET (ALIEN_LIB ALIEN_LIB-NOTFOUND)
endif (ALIEN_INCLUDE_DIR AND ALIEN_LIBRARIES)

FIND_PATH(ALIEN_INCLUDE_DIR
  NAMES gapiUI.h
  PATHS $ENV{ALIEN_DIR}/include PATHS $ENV{ALIEN_DIR}/api/include NO_DEFAULT_PATH
)
FIND_LIBRARY(ALIEN_LIB NAMES gapiUI PATHS
  $ENV{ALIEN_DIR}/lib $ENV{ALIEN_DIR}/api/lib
  NO_DEFAULT_PATH
)

MESSAGE(STATUS "Checking xrdgsiproxy ...")
FIND_PROGRAM(ALIEN_XRDGSIPROXY NAME xrdgsiproxy
  PATHS
  $ENV{ALIEN_DIR}/api/bin
  $ENV{ALIEN_DIR}/bin
  $ENV{XROOTD_DIR}/bin
  /usr/local/bin
  /usr/bin
  /bin
  NO_DEFAULT_PATH
)
if (ALIEN_XRDGSIPROXY)
    MESSAGE(STATUS "Found xrdgsiproxy in ${ALIEN_XRDGSIPROXY}")
endif (ALIEN_XRDGSIPROXY)

MESSAGE(STATUS "Checking alien-token-init ...")
FIND_PROGRAM(ALIEN_ALIEN_TOKEN_INIT NAME alien-token-init
  PATHS
  $ENV{ALIEN_DIR}/api/bin
  $ENV{ALIEN_DIR}/bin
  /usr/local/bin
  /usr/bin
  /bin
  NO_DEFAULT_PATH
)
if (ALIEN_ALIEN_TOKEN_INIT)
    MESSAGE(STATUS "Found alien-token-init in ${ALIEN_ALIEN_TOKEN_INIT}")
endif (ALIEN_ALIEN_TOKEN_INIT)

MESSAGE(STATUS "Checking alien-token-destroy ...")
FIND_PROGRAM(ALIEN_ALIEN_TOKEN_DESTROY NAME alien-token-destroy
  PATHS
  $ENV{ALIEN_DIR}/api/bin
  $ENV{ALIEN_DIR}/bin
  /usr/local/bin
  /usr/bin
  /bin
  NO_DEFAULT_PATH
)
if (ALIEN_ALIEN_TOKEN_DESTROY)
    MESSAGE(STATUS "Found alien-token-destroy in ${ALIEN_ALIEN_TOKEN_DESTROY}")
endif (ALIEN_ALIEN_TOKEN_DESTROY)

MESSAGE(STATUS "Checking alien-token-info ...")
FIND_PROGRAM(ALIEN_ALIEN_TOKEN_INFO NAME alien-token-info
PATHS
$ENV{ALIEN_DIR}/api/bin
$ENV{ALIEN_DIR}/bin
/usr/local/bin
/usr/bin
/bin
NO_DEFAULT_PATH
)
if (ALIEN_ALIEN_TOKEN_INFO)
  MESSAGE(STATUS "Found alien-token-info in ${ALIEN_ALIEN_TOKEN_INFO}")
endif (ALIEN_ALIEN_TOKEN_INFO)

MESSAGE(STATUS "Checking alien_cp ...")
FIND_PROGRAM(ALIEN_ALIEN_CP NAME alien_cp
  PATHS
  $ENV{ALIEN_DIR}/api/bin
  $ENV{ALIEN_DIR}/bin
  /usr/local/bin
  /usr/bin
  /bin
  NO_DEFAULT_PATH
)
if (ALIEN_ALIEN_CP)
    MESSAGE(STATUS "Found alien_cp in ${ALIEN_ALIEN_CP}")
endif (ALIEN_ALIEN_CP)


SET(ALIEN_LIBRARIES ${ALIEN_LIB})

if (ALIEN_INCLUDE_DIR AND ALIEN_LIBRARIES)
   set(ALIEN_FOUND TRUE)
endif (ALIEN_INCLUDE_DIR AND ALIEN_LIBRARIES)

if (ALIEN_FOUND)
  if (NOT ALIEN_FIND_QUIETLY)
    MESSAGE(STATUS "Found AliEn in ${ALIEN_LIBRARIES}")
#     MESSAGE(STATUS "Found ALIEN in ${ALIEN_INCLUDE_DIR}")
#     MESSAGE(STATUS "Found ALIEN in ${ALIEN_LIB_PATH}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${ALIEN_LIBRARY_DIR})
#     SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${ALIEN_LIB_PATH})
  endif (NOT ALIEN_FIND_QUIETLY)
else (ALIEN_FOUND)
  if (ALIEN_FIND_REQUIRED)
    MESSAGE(STATUS "$ALIEN_DIR is not set. Set $ALIEN_DIR !!!")
    MESSAGE(FATAL_ERROR "Looking for AliEn... - Not found ")
  endif (ALIEN_FIND_REQUIRED)
endif (ALIEN_FOUND)

