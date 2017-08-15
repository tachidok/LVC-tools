# Indicate source files
SET(SRC_demo_serial demo_serial.cpp)

# Create executable (check whether compilation was requested or not)
IF(${LVC-TOOLS_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_serial ${SRC_demo_serial})
ELSE(${LVC-TOOLS_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_serial ${SRC_demo_serial})
ENDIF(${LVC-TOOLS_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_serial rs232_lib serial_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_serial ${LIB_demo_serial})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_serial
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_serial_run
  COMMAND demo_serial)
# Validate output
ADD_TEST(NAME TEST_demo_serial_check_output
  COMMAND sdiff -s ${CMAKE_CURRENT_SOURCE_DIR}/validate/validate_demo_serial.dat ${CMAKE_CURRENT_BINARY_DIR}/output_test.dat)
