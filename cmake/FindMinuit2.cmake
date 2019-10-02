# I found this file from:
# https://github.com/EdoardoCarlesi/cmbeasy/blob/master/cmakescripts/FindMinuit2.cmake
#
# I needed to add Minuit2 to FIND_LIBRARY NAMES
#
SET(MINUIT2_DIR "" CACHE PATH "Path to the minuit2 installation")

FIND_PATH(MINUIT2_INCLUDE_DIR Minuit2/FCNBase.h
          ${MINUIT2_DIR}/include
          /usr/include /usr/local/include)

FIND_LIBRARY(MINUIT2_LIBRARY NAMES Minuit2Base Minuit2
             PATHS ${MINUIT2_DIR}/lib /usr/lib /usr/local/lib)

IF (MINUIT2_INCLUDE_DIR AND MINUIT2_LIBRARY)
   SET(MINUIT2_FOUND TRUE)
ENDIF (MINUIT2_INCLUDE_DIR AND MINUIT2_LIBRARY)

IF (MINUIT2_FOUND)
   #Set HPPATH first to the lib path
   GET_FILENAME_COMPONENT(CFPATH ${MINUIT2_LIBRARY} PATH)
   #and then its parent dir
   GET_FILENAME_COMPONENT(CFPATH ${CFPATH} PATH)
   SET(MINUIT2_DIR ${CFPATH} CACHE PATH "Path to the MINUIT2 installation" FORCE)
   IF (NOT MINUIT2_FIND_QUIETLY)
      MESSAGE(STATUS "Found MINUIT2: ${MINUIT2_LIBRARY}")
   ENDIF (NOT MINUIT2_FIND_QUIETLY)
ELSE (MINUIT2_FOUND)
   IF (Minuit2_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find MINUIT2")
   ENDIF (Minuit2_FIND_REQUIRED)
ENDIF (MINUIT2_FOUND)

MARK_AS_ADVANCED(MINUIT2_INCLUDE_DIR MINUIT2_LIBRARY_DIR MINUIT2_LIBRARY)
