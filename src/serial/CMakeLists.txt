# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES cc_serial.cpp)

# Create a library with the above files based on the requested library
# version
IF(${LVC-TOOLS_LIB_TYPE} STREQUAL STATIC)
  ADD_LIBRARY(serial_comm_lib STATIC ${SRC_FILES})
ELSEIF(${LVC-TOOLS_LIB_TYPE} STREQUAL SHARED)
  ADD_LIBRARY(serial_comm_lib SHARED ${SRC_FILES})
ELSE(${LVC-TOOLS_LIB_TYPE} STREQUAL STATIC)
  ADD_LIBRARY(serial_comm_lib ${SRC_FILES})
ENDIF(${LVC-TOOLS_LIB_TYPE} STREQUAL STATIC)
