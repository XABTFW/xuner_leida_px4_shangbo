# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr")
  file(MAKE_DIRECTORY "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr")
endif()
file(MAKE_DIRECTORY
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr-build"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr-build/ucdr-prefix"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr-build/ucdr-prefix/tmp"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr-build/ucdr-prefix/src/ucdr-stamp"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr-build/ucdr-prefix/src"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr-build/ucdr-prefix/src/ucdr-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr-build/ucdr-prefix/src/ucdr-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/cuav_7-nano_default/src/modules/uxrce_dds_client/src/libmicroxrceddsclient_project-build/microcdr/src/microcdr-build/ucdr-prefix/src/ucdr-stamp${cfgdir}") # cfgdir has leading slash
endif()
