cmake_minimum_required(VERSION 2.8)

# ensures that all passed modules are available
# sets OCV_DEPENDENCIES_FOUND variable to TRUE/FALSE
macro(ocv_check_dependencies)
  set(OCV_DEPENDENCIES_FOUND TRUE)
  foreach(d ${ARGN})
    if(d MATCHES "^opencv_[^ ]+$" AND NOT HAVE_${d})
      set(OCV_DEPENDENCIES_FOUND FALSE)
      break()
    endif()
  endforeach()
endmacro()

#added include directories in such way that directories from the OpenCV source tree go first
macro(ocv_include_directories)
  set(__add_before "")
  foreach(dir ${ARGN})
    get_filename_component(__abs_dir "${dir}" ABSOLUTE)
    if("${__abs_dir}" MATCHES "^${OpenCV_SOURCE_DIR}" OR "${__abs_dir}" MATCHES "^${OpenCV_BINARY_DIR}")
      list(APPEND __add_before "${dir}")
    else()
      include_directories(AFTER "${dir}")
    endif()
  endforeach()
  include_directories(BEFORE ${__add_before})
endmacro()

# setup include paths for the list of passed modules
macro(ocv_include_modules)
  foreach(d ${ARGN})
    if(d MATCHES "^opencv_" AND HAVE_${d})
      if (EXISTS "${OPENCV_MODULE_${d}_LOCATION}/include")
        ocv_include_directories("${OPENCV_MODULE_${d}_LOCATION}/include")
      endif()
    elseif(EXISTS "${d}")
      ocv_include_directories("${d}")
    endif()
  endforeach()
endmacro()

SET(OPENCV_TRAINCASCADE_DEPS opencv_core opencv_ml opencv_imgproc opencv_objdetect opencv_highgui opencv_calib3d opencv_video opencv_features2d opencv_flann opencv_legacy)
ocv_check_dependencies(${OPENCV_TRAINCASCADE_DEPS})

project(traincascade)

ocv_include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${OpenCV_SOURCE_DIR}/include/opencv")
ocv_include_modules(${OPENCV_TRAINCASCADE_DEPS})

set(traincascade_files traincascade.cpp
  cascadeclassifier.cpp cascadeclassifier.h
  boost.cpp boost.h features.cpp traincascade_features.h
  haarfeatures.cpp haarfeatures.h
  lbpfeatures.cpp lbpfeatures.h
  HOGfeatures.cpp HOGfeatures.h
  imagestorage.cpp imagestorage.h)

set(the_target opencv_traincascade)    
add_executable(${the_target} ${traincascade_files})
target_link_libraries(${the_target} ${OPENCV_TRAINCASCADE_DEPS} opencv_haartraining_engine)

set_target_properties(${the_target} PROPERTIES
                      DEBUG_POSTFIX "${OPENCV_DEBUG_POSTFIX}"
                      ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
                      RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
                      INSTALL_NAME_DIR lib
                      OUTPUT_NAME "opencv_traincascade")
					  
if(ENABLE_SOLUTION_FOLDERS)
  set_target_properties(${the_target} PROPERTIES FOLDER "applications")
endif()	

install(TARGETS ${the_target} RUNTIME DESTINATION bin COMPONENT main)

