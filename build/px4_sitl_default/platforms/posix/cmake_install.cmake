# Install script for directory: /home/btfw/tpy/px4_net_communication/PX4_Network_communication/platforms/posix

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/px4" TYPE DIRECTORY FILES
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/posix-configs"
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/test"
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/etc"
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/bin"
    USE_SOURCE_PERMISSIONS)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/px4" TYPE DIRECTORY FILES
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/integrationtests"
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/launch"
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/bin"
    USE_SOURCE_PERMISSIONS)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/px4" TYPE FILE FILES
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/CMakeLists.txt"
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/package.xml"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/px4/Tools" TYPE DIRECTORY FILES "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/Tools/ecl_ekf" USE_SOURCE_PERMISSIONS)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/px4/Tools" TYPE PROGRAM FILES
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/Tools/simulation/gazebo-classic/setup_gazebo.bash"
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/Tools/upload_log.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/px4/build/px4_sitl_default" TYPE DIRECTORY FILES "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/etc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/px4/Tools/simulation/gazebo-classic/sitl_gazebo-classic" TYPE DIRECTORY OPTIONAL FILES
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/Tools/simulation/gz/models"
    "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/Tools/simulation/gz/worlds"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/ROMFS/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/platforms/posix/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
