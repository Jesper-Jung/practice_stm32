BUILD_DIR		= build
TARGET_CHIP = stm32h563zitx

.PHONY: build

config: 
	cmake -B $(BUILD_DIR) -S . -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake

build:
	cmake --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

gdb-pyocd:
	pyocd gdbserver --target $(TARGET_CHIP)
