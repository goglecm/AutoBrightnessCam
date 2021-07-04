aubrcaui_LDADD = \
	libabc_logging_service.la \
	$(GTK4_LIBS)

# Override the global flags as the gtk headers are very relaxed.
aubrcaui_CFLAGS = \
	$(GENERAL_DEFINITIONS) \
	$(GENERAL_INCLUDE_PATHS) \
	$(GTK4_CFLAGS) \
	$(C_STANDARD)

aubrcaui_SOURCES = programs/src/ui/main.c
