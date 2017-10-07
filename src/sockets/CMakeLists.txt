# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES cc_socket_server.cpp ac_socket.cpp cc_tcp_socket_client.cpp)

# Create a library with the above files based on the requested library
# version
IF(${LVC-TOOLS_LIB_TYPE} STREQUAL STATIC)
  ADD_LIBRARY(socket_lib STATIC ${SRC_FILES})
ELSEIF(${LVC-TOOLS_LIB_TYPE} STREQUAL SHARED)
  ADD_LIBRARY(socket_lib SHARED ${SRC_FILES})
ELSE(${LVC-TOOLS_LIB_TYPE} STREQUAL STATIC)
  ADD_LIBRARY(socket_lib ${SRC_FILES})
ENDIF(${LVC-TOOLS_LIB_TYPE} STREQUAL STATIC)
