#########################
# UseKinect2.cmake #
#########################

OPTION(WITH_Kinect2 "Build with Kinect2 support?" OFF)

add_definitions(-DKinect2_ROOT -DKinect2_INCLUDE_DIR -DKinect2_LIBRARY)

IF(WITH_Kinect2)
  IF(MSVC_IDE)
    FIND_PATH(Kinect2_ROOT LICENSE HINTS "C:/Program Files/libfreenect2")
  ELSEIF(APPLE)
    FIND_PATH(Kinect2_ROOT primesense-usb.rules HINTS ~/Downloads/libfreenect2)
  ELSEIF("${CMAKE_SYSTEM}" MATCHES "Linux")
    FIND_PATH(Kinect2_ROOT LICENSE HINTS ~/Software/libfreenect2)
  ELSE()
    MESSAGE(FATAL_ERROR "Kinect2 not currently set up to work on this platform.")
  ENDIF()

  FIND_PATH(Kinect2_INCLUDE_DIR libfreenect2.hpp HINTS "${libfreenect2_ROOT}/Include")
  FIND_LIBRARY(Kinect2_LIBRARY libfreenect2 HINTS "${libfreenect2_ROOT}/Lib" "${libfreenect2_ROOT}/Redist")

  INCLUDE_DIRECTORIES(${Kinect2_INCLUDE_DIR})
ELSE()
  ADD_DEFINITIONS(-DCOMPILE_WITHOUT_Kinect2)
ENDIF()