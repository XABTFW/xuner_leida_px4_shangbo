# - Config file for the OpticalFlow package
# It defines the following variables
#  OpticalFlow_INCLUDE_DIRS - include directories
#  OpticalFlow_LIBRARIES    - libraries to link against
 
set(OpticalFlow_INCLUDE_DIRS "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/install/include")
#set(OpticalFlow_LIBRARY_DIR "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/install/lib")
FIND_LIBRARY(OpticalFlow_LIBRARIES OpticalFlow PATHS "/home/btfw/tpy/px4_net_communication/PX4_Network_communication/build/px4_sitl_default/OpticalFlow/install/lib" NO_DEFAULT_PATH)
