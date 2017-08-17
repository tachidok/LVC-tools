# Indicate source files
SET(SRC_serial serial.cpp)

# Create executable (check whether compilation was requested or not)
IF(${LVC-TOOLS_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(serial ${SRC_serial})
ELSE(${LVC-TOOLS_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(serial EXCLUDE_FROM_ALL ${SRC_serial})
ENDIF(${LVC-TOOLS_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_serial serial_lib rs232_lib) # Reversed dependency order to make it compile
#SET(LIB_demo_serial rs232_lib serial_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(serial ${LIB_serial})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( serial
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )
