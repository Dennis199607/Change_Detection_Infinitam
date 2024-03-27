##########################
# LinkKinect2.cmake      #
##########################

IF(WITH_Kinect2)
  TARGET_LINK_LIBRARIES(${targetname} ${Kinect2_LIBRARY})

  IF(MSVC_IDE)
    #ADD_CUSTOM_COMMAND(TARGET ${targetname} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${Kinect2_ROOT}/Bin/freenect2.dll" "$<TARGET_FILE_DIR:${targetname}>")
  ELSE()
    #ADD_CUSTOM_COMMAND(TARGET ${targetname} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${libfreenect2_LIBRARY} $<TARGET_FILE_DIR:${targetname}>)
  ENDIF()
  #ADD_CUSTOM_COMMAND(TARGET ${targetname} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${libfreenect2_ROOT}/Redist/OpenNI2" "$<TARGET_FILE_DIR:${targetname}>/OpenNI2")
ENDIF()