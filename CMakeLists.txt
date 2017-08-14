# Check for cmake minimum required version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Project name (library's name)
PROJECT(lvc-tools)
SET(${CMAKE_PROJECT_NAME}_MAJOR_VERSION 0)
SET(${CMAKE_PROJECT_NAME}_MINOR_VERSION 1)
SET(${CMAKE_PROJECT_NAME}_PATCH_LEVEL 0)

# Prints a lot of stuff
#SET(CMAKE_VERBOSE_MAKEFILE TRUE)

# Output requested configuration
MESSAGE( STATUS "LVC-TOOLS_LIB_TYPE:            " ${LVC-TOOLS_LIB_TYPE} )
MESSAGE( STATUS "LVC-TOOLS_BUILD_VERSION:       " ${LVC-TOOLS_BUILD_VERSION} )
MESSAGE( STATUS "LVC-TOOLS_BUILD_DEMOS:         " ${LVC-TOOLS_BUILD_DEMOS} )
MESSAGE( STATUS "PROJECT_NAME:                 " ${PROJECT_NAME})
MESSAGE( STATUS "PROJECT_MAJOR_VERSION:        " ${chapchom_MAJOR_VERSION})
MESSAGE( STATUS "PROJECT_MINOR_VERSION:        " ${chapchom_MINOR_VERSION})
MESSAGE( STATUS "PROJECT_PATCH_LEVEL:          " ${chapchom_PATCH_LEVEL})

# Modify compilation variables
IF(${LVC-TOOLS_BUILD_VERSION} STREQUAL DEBUG)
  SET(LVC-TOOLS_C_FLAGS "-O0 -g -Wall -pedantic")
  SET(LVC-TOOLS_CXX_FLAGS "-O0 -g -Wall -pedantic")
ELSEIF(${LVC-TOOLS_BUILD_VERSION} STREQUAL RELEASE)
  SET(LVC-TOOLS_C_FLAGS "-O3 -Wall -Wextra -Wshadow -Wconversion -pedantic -DNDEBUG")
  SET(LVC-TOOLS_CXX_FLAGS "-O3 -Wall -Wextra -Wshadow -Wconversion -pedantic -DNDEBUG")
ELSEIF(${LVC-TOOLS_BUILD_VERSION} STREQUAL PROFILING)
  SET(LVC-TOOLS_C_FLAGS "-O0 -pg -Wall -Wshadow -Wconversion -Wextra -pedantic")
  SET(LVC-TOOLS_CXX_FLAGS "-O0 -pg -Wall -Wshadow -Wconversion -Wextra -pedantic")  
  MESSAGE( WARNING "You are compiling with profiling ENABLED, this will SIGNIFICANTLY increase execution times. If you do not want profiling to be ENABLED then choose another version when asked for library version" ) 
ELSE(${LVC-TOOLS_BUILD_VERSION} STREQUAL DEBUG)
  SET(LVC-TOOLS_C_FLAGS "-O0 -g -Wall -Wextra -pedantic")
  SET(LVC-TOOLS_CXX_FLAGS "-O0 -g -Wall -Wextra -pedantic")
ENDIF(${LVC-TOOLS_BUILD_VERSION} STREQUAL DEBUG)

# Use this if you require to add more libraries (do not forget to
# uncomment the respective line below to set linker variables)
#SET(LVC-TOOLS_LINKER_FLAGS "-lmath")

# Set modified compilation variables
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${LVC-TOOLS_C_FLAGS}" )
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${LVC-TOOLS_CXX_FLAGS}" )

# Uncomment this line if you added extra libraries
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

# Include testing (this function already calls enable_testing())
include(CTest)

# Output compilers versions
MESSAGE( STATUS "CMAKE_C_COMPILER:             " ${CMAKE_C_COMPILER} )
MESSAGE( STATUS "CMAKE_CXX_COMPILER:           " ${CMAKE_CXX_COMPILER} )

# Output configuration flags
# The flags passed to the C-compiler
MESSAGE( STATUS "CMAKE_C_FLAGS:                " ${CMAKE_C_FLAGS} )
# The flags passed to the C++ compiler
MESSAGE( STATUS "CMAKE_CXX_FLAGS:              " ${CMAKE_CXX_FLAGS} )
MESSAGE( STATUS "CMAKE_EXE_LINKER_FLAGS:       " ${CMAKE_EXE_LINKER_FLAGS} )

# Output some extra info.
MESSAGE( STATUS "CMAKE_VERBOSE_MAKEFILE:       " ${CMAKE_VERBOSE_MAKEFILE} )

# Add external source files sub-directories
ADD_SUBDIRECTORY(external_src)

# Add sub-directories with source files
ADD_SUBDIRECTORY(src)

# Add private folders (note that any source code in here is not
# compiled but only added to the make list)
#ADD_SUBDIRECTORY(private)

# Once all source code has been compiled add sub-directories for demos
#ADD_SUBDIRECTORY(demos)
