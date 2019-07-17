clean:
	cd ./abc_time_service; \
		MODULE_NAME=abc_terminal_controller make -f Makefile -j clean_all

	cd ./abc_io_service; \
		MODULE_NAME=abc_io_service make -f Makefile -j clean_all

	cd ./abc_terminal_controller; \
		MODULE_NAME=abc_terminal_controller make -f Makefile -j clean_all

	cd ./abc_logging_service; \
		MODULE_NAME=abc_logging_service make -f Makefile -j clean_all

	cd ./abc_brightness_service; \
		MODULE_NAME=abc_brightness_service make -f Makefile -j clean_all

	cd ./abc_brightness_service; \
		MODULE_NAME=abc_ambient_brightness_controller make -f Makefile -j clean_all

	cd ./abc_power_controller; \
		MODULE_NAME=abc_power_controller make -f Makefile -j clean_all

	cd ./abc_backlight_brightness_controller; \
		MODULE_NAME=abc_backlight_brightness_controller make -f Makefile -j clean_all

build_main:
	# Build main (with logs)
	make -j clean
	cd ./main; \
		MODULE_NAME=main ABC_LOGGING_ON=1 make -f Makefile -j exe_build

	# Build main (no logs)
	make -j clean
	cd ./main; \
		MODULE_NAME=main ABC_LOGGING_ON=0 make -f Makefile -j exe_build

build_all_tests:
	make -j clean

	# Build tests
	cd ./abc_terminal_controller; \
		MODULE_NAME=abc_terminal_controller make -f Makefile -j tests_build

	cd ./abc_logging_service; \
		MODULE_NAME=abc_logging_service make -f Makefile -j tests_build

	cd ./abc_brightness_service; \
		MODULE_NAME=abc_brightness_service make -f Makefile -j tests_build

	cd ./abc_power_controller; \
		MODULE_NAME=abc_power_controller make -f Makefile -j tests_build

	cd ./abc_backlight_brightness_controller; \
		MODULE_NAME=abc_backlight_brightness_controller make -f Makefile -j tests_build

	cd ./abc_io_service; \
		MODULE_NAME=abc_io_service make -f Makefile -j tests_build


run_all_tests:
	make -j build_main

	make -j build_all_tests

	# Run tests
	cd ./abc_terminal_controller; \
		MODULE_NAME=abc_terminal_controller make -f Makefile -j tests_run

	cd ./abc_logging_service; \
		MODULE_NAME=abc_logging_service make -f Makefile -j tests_run

	cd ./abc_brightness_service; \
		MODULE_NAME=abc_brightness_service make -f Makefile -j tests_run

	cd ./abc_power_controller; \
		MODULE_NAME=abc_power_controller make -f Makefile -j tests_run

	cd ./abc_backlight_brightness_controller; \
		MODULE_NAME=abc_backlight_brightness_controller make -f Makefile -j tests_run

	cd ./abc_io_service; \
		MODULE_NAME=abc_io_service make -f Makefile -j tests_run
