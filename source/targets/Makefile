run_all_tests:

	# Build main (with logs)
	cd ./main; \
		MODULE_NAME=main ABC_LOGGING_ON=1 make -f Makefile -j exe_build

	# Build main (no logs)
	cd ./main; \
		MODULE_NAME=main ABC_LOGGING_ON=0 make -f Makefile -j exe_build

	# Run tests
	cd ./abc_logging_service; \
		MODULE_NAME=abc_logging_service make -f Makefile -j tests_run

	cd ./abc_brightness_service; \
		MODULE_NAME=abc_brightness_service make -f Makefile -j tests_run

	cd ./abc_power_controller; \
		MODULE_NAME=abc_power_controller make -f Makefile -j tests_run

	cd ./abc_backlight_brightness_controller; \
		MODULE_NAME=abc_backlight_brightness_controller make -f Makefile -j tests_run
