# This is the main binary. List your C files here.
add_executable(hello_freertos
    hello_freertos.c
    )

pico_set_program_name(hello_freertos "test")
pico_set_program_version(hello_freertos "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(hello_freertos 1)
pico_enable_stdio_usb(hello_freertos 0)

# Add the libraries to the build
target_link_libraries(hello_freertos PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  can2040
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(hello_freertos PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(hello_freertos)

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

# add_custom_target(flash ${PICOTOOL} load -f $<TARGET_FILE:hello_freertos> DEPENDS hello_freertos)
# add_custom_target(openocd_flash ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c program "$<TARGET_FILE:hello_freertos>" verify reset exit' DEPENDS hello_freertos)


# This is the main binary. List your C files here.
add_executable(can2040_sender
    can2040_sender.c
    )

pico_set_program_name(can2040_sender "test")
pico_set_program_version(can2040_sender "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(can2040_sender 1)
pico_enable_stdio_usb(can2040_sender 0)

# Add the libraries to the build
target_link_libraries(can2040_sender PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  can2040
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(can2040_sender PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(can2040_sender)

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash_tx ${PICOTOOL} load -f $<TARGET_FILE:can2040_sender> DEPENDS can2040_sender)
add_custom_target(openocd_flash_tx ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c program "$<TARGET_FILE:can2040_sender>" verify reset exit' DEPENDS can2040_sender)


# This is the main binary. List your C files here.
add_executable(can2040_receiver
    can2040_receiver.c
    )

pico_set_program_name(can2040_receiver "test")
pico_set_program_version(can2040_receiver "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(can2040_receiver 0)
pico_enable_stdio_usb(can2040_receiver 1)

# Add the libraries to the build
target_link_libraries(can2040_receiver PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  can2040
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(can2040_receiver PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(can2040_receiver)

find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash_rx ${PICOTOOL} load -f $<TARGET_FILE:can2040_receiver> DEPENDS can2040_receiver)
add_custom_target(openocd_flash_rx ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c program "$<TARGET_FILE:can2040_receiver>" verify reset exit' DEPENDS can2040_receiver)



add_executable(can_high can2040_tx_rx.c)
target_compile_definitions(can_high PRIVATE CAN_ID=0x100 TX_DELAY_MS=1)
pico_enable_stdio_uart(can_high 0)
pico_enable_stdio_usb(can_high 1)
target_link_libraries(can_high PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  can2040
)
if(PICO_CYW43_SUPPORTED)
    target_link_libraries(can_high PRIVATE pico_cyw43_arch_none)
endif()
pico_add_extra_outputs(can_high)
add_custom_target(flash_high ${PICOTOOL} load -f $<TARGET_FILE:can_high> DEPENDS can_high)


add_executable(can_low can2040_tx_rx.c)
target_compile_definitions(can_low PRIVATE CAN_ID=0x200 TX_DELAY_MS=20)
pico_enable_stdio_uart(can_low 0)
pico_enable_stdio_usb(can_low 1)
target_link_libraries(can_low PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  can2040
)
if(PICO_CYW43_SUPPORTED)
    target_link_libraries(can_low PRIVATE pico_cyw43_arch_none)
endif()
pico_add_extra_outputs(can_low)
add_custom_target(flash_low ${PICOTOOL} load -f $<TARGET_FILE:can_low> DEPENDS can_low)
