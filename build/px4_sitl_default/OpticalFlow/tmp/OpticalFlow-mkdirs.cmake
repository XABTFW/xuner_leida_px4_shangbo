# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/src/OpticalFlow")
  file(MAKE_DIRECTORY "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/src/OpticalFlow")
endif()
file(MAKE_DIRECTORY
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/src/OpticalFlow-build"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/install"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/tmp"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/src/OpticalFlow-stamp"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/src"
  "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/src/OpticalFlow-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/src/OpticalFlow-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/src/OpticalFlow-stamp${cfgdir}") # cfgdir has leading slash
endif()
