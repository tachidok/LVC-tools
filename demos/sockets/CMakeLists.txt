# Indicate source files
SET(SRC_demo_socket_server demo_socket_server.cpp)
SET(SRC_demo_socket_client demo_socket_client.cpp)

# Create executable (check whether compilation was requested or not)
IF(${LVC-TOOLS_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_socket_server ${SRC_demo_socket_server})
  ADD_EXECUTABLE(demo_socket_client ${SRC_demo_socket_client})
ELSE(${LVC-TOOLS_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_socket_server EXCLUDE_FROM_ALL ${SRC_demo_socket_server})
  ADD_EXECUTABLE(demo_socket_client EXCLUDE_FROM_ALL ${SRC_demo_socket_client})
ENDIF(${LVC-TOOLS_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_socket_server socket_lib)
SET(LIB_demo_socket_client socket_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_socket_server ${LIB_demo_socket_server})
TARGET_LINK_LIBRARIES(demo_socket_client ${LIB_demo_socket_client})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_socket_server
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# Set directory where to create the executables
set_target_properties( demo_socket_client
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
#ADD_TEST(NAME TEST_demo_socket_server_run
#  COMMAND demo_socket_server)
# Validate output
#ADD_TEST(NAME TEST_demo_socket_server
#  COMMAND sdiff -s ${CMAKE_CURRENT_SOURCE_DIR}/validate/validate_demo_socket_server_client.dat ${CMAKE_CURRENT_#BINARY_DIR}/output_test.dat)

# Run the application to check it works
#ADD_TEST(NAME TEST_demo_socket_client_run
#  COMMAND demo_socket_client)
# Validate output
#ADD_TEST(NAME TEST_demo_socket_client
#  COMMAND sdiff -s ${CMAKE_CURRENT_SOURCE_DIR}/validate/validate_demo_socket_server_client.dat ${CMAKE_CURRENT_#BINARY_DIR}/output_test.dat)
