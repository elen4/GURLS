# - Find ACML library
# This module finds an installed ACML library
#
# This module sets the following variables:
#  ACML_INCLUDE_DIRS - uncached list of include directories
#
#  ACML_DEFINITIONS - uncached list of required definitions
#
#  ACML_LIBRARIES - uncached list of libraries (using full path name) to
#    link against to use ACML

set(ACML_ROOT "$ENV{ACML_DIR}")

set(ACML_LIB_PATH ${ACML_ROOT}/lib/)
option(ACML_STATIC "Link statically against ACML libraries" OFF)

find_path(ACML_INCLUDE_DIRS acml.h ${ACML_ROOT}/include )

set(ACML_DEFINITIONS -D_ACML)

if(${ACML_ROOT} MATCHES "^.*mp.*$")
    set(ACML_MULTITHREADING "_mp")
else(${ACML_ROOT} MATCHES "^.*mp.*$")
    set(ACML_MULTITHREADING "")
endif(${ACML_ROOT} MATCHES "^.*mp.*$")

if(MSVC AND NOT ACML_STATIC)
    set(SUFFIX "_dll")
else()
    set(SUFFIX "")
endif()

find_library(ACML_LIBRARIES libacml${ACML_MULTITHREADING}${SUFFIX} ${ACML_LIB_PATH})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ACML DEFAULT_MSG ACML_LIBRARIES ACML_INCLUDE_DIRS)
