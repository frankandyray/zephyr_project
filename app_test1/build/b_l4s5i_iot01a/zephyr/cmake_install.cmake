# Install script for directory: C:/Users/ray45/zephyrproject/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/ray45/zephyr-sdk-0.17.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/acpica/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/cmsis_6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/adi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_afbr/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_ambiq/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/atmel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_bouffalolab/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_espressif/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_ethos_u/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_gigadevice/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_infineon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_intel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/microchip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/nuvoton/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_nxp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/openisa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/quicklogic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_realtek/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_renesas/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_rpi_pico/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_sifli/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_silabs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_stm32/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_tdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_telink/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/ti/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_wch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/xtensa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/libmctp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/libsbc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/lora-basics-modem/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/trusted-firmware-a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/cmake/reports/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/ray45/zephyrproject/zephyr/samples/basic/app_test1/build/b_l4s5i_iot01a/zephyr/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
