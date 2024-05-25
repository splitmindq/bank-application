# Install script for directory: C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/bank")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/CLion 2023.2.1/bin/mingw/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_types.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_consts.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_annotation.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_catalog.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_conf.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_destination.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_doc.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_encoder.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_encrypt.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_encryptdict.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_error.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_ext_gstate.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_font.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_fontdef.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_gstate.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_image.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_info.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_list.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_mmgr.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_namedict.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_objects.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_outline.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_pages.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_page_label.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_streams.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_u3d.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_utils.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_pdfa.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_3dmeasure.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_exdata.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/include/hpdf_version.h"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/cmake-build-debug/libharu/include/hpdf_config.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/libharu" TYPE FILE FILES
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/README.md"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/CHANGES"
    "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/INSTALL"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/libharu" TYPE DIRECTORY FILES "C:/Users/mzitr/OneDrive/Рабочий стол/bank/libharu/bindings")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/mzitr/OneDrive/Рабочий стол/bank/cmake-build-debug/libharu/src/cmake_install.cmake")

endif()

