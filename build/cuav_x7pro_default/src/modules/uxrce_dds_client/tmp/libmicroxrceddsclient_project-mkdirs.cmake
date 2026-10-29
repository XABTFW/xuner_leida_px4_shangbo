# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/src/modules/uxrce_dds_client/Micro-XRCE-DDS-Client")
  file(MAKE_DIRECTORY "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/src/modules/uxrce_dds_client/Micro-XRCE-DDS-Client")
endif()
file(MAKE_DIRECTORY
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_x7pro_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_x7pro_default/src/modules/uxrce_dds_client"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_x7pro_default/src/modules/uxrce_dds_client/tmp"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_x7pro_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-stamp"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_x7pro_default/src/modules/uxrce_dds_client/src"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_x7pro_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_x7pro_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_x7pro_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-stamp${cfgdir}") # cfgdir has leading slash
endif()
