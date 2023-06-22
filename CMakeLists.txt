cmake_minimum_required (VERSION 3.0)

if( NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "" )
	message( "Defaulting to build type of Release." )
	set(CMAKE_BUILD_TYPE  "RELEASE")
endif( NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "" )
#endif( NOT DEFINED CMAKE_BUILD_TYPE )

string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

PROJECT(ssfit)

# This gets prepdended to all CXX_FLAGS_* strings.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat \
                                        -Wstrict-aliasing -Wshadow -Wpacked \
                                        -Wmissing-noreturn -march=native \
                                        -pipe -std=gnu++11 -fopenmp" )

# Use this for debugging with valgrind.
set(CMAKE_CXX_FLAGS_DEBUG
	"${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -ggdb -O2")


# The version number.
set (ssfit_VERSION_MAJOR 0)
set (ssfit_VERSION_MINOR 6)

# configure a header file to pass some of the CMake settings
# to the source code
CONFIGURE_FILE (
   "${PROJECT_SOURCE_DIR}/config/ssfitConfig.h.in"
   "${PROJECT_BINARY_DIR}/ssfitConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find TraceHBondsConfig.h
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

IF( CMAKE_SYSTEM_NAME STREQUAL "Windows")
	MESSAGE( "Making static binary." )
	SET(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
ENDIF( CMAKE_SYSTEM_NAME STREQUAL "Windows")

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(docs)
