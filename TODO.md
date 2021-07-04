# Improvements

### Bugs

- none

### Features

- The brightness should also depend on the battery charge level, i.e. when the
  battery is low, the brightness should go down as well.
- Need to workout how exposure works and improve the brightness detection from
  the picture (perhaps this is the bias when looking at the histogram?)
- Add timestamps to the logs.
- Add module name appended to the log name (i.e. register each module
  with the logger).
- Allow the user to point the paths for any unavailable optional features (via
  config files).
- Add some logs files used for statistics.
- Use time stamps to minimise the number of times files are set/read.
- (almost done) Throw compile errors if #defines are not set.
- The display brightness may contribute to the overall brightness of the image,
  so take it into account.
- Maybe allow users to change the path where the pic is stored (or other paths).
- Add more options to the config file (max, min brightness, battery paths,
  speed, adjust the brightness even during charging, persistent mode, default
  mode, etc.)
- Move the limit checking for config options in the config service.
- Notify the user that only one application can control the camera at once, so
  that the sampling period is not too low.
- Once most of the configuration is available in a file, create a gtk3 app to
  allow easy control over that file, allow starting/stopping the app. Also,
  make sure the program accepts sufficient flags for the gui to use.
- Handle the case when multiple programs are started at once.
- Consider moving the wiki to github.io

### Build and releases

#### High priority

- Try different versions of autotools
- Need to also automate some sort of coverage runs with gcov for the C code to
  maintain an above 90% test coverage
- Need to sign tarball and RPM releases
- Need to sort out runtime, build and development dependencies
- Sort through which configure options requires uses vs enable

#### Medium priority

- test rpm builds as well during CI
- start looking at deb generation

#### Low priority

- add support for gmock

# Features

#### Requirement

What:
- the backlight brightness is not changed

When:
- the laptop lid is closed
- the power manager is in reduced brightness mode
- the power manager is in blank display mode

#### Requirement

What:
- the default state of the laptop lid is assumed to be open

When:
- the state of the laptop lid cannot be determined

#### Requirement

What:
- the power manager mode is assumed to be active (default)

When:
- the power manager mode cannot be determined

#### Requirement

What:
- the application issues an error and exits

When:
- the brightness could not be updated during 3\*N seconds

#### Requirement

What:
- the N value, minimum and maximum brightness thresholds are set to their
  default values and a warning is issued by the application

When:
- the configuration file does not exist
- the configuration file is corrupt or has invalid configuration

# Dependencies

- make
- g++
- gcc
- gtest
- fswebcam
- convert
- upower
- systemd

- Need to add a list of runtime vs dev time dependencies
- Need to add a guide on how to add modules (to describe the infrastructure)




# UI notes

## Config control

### Mandatory:

- Allow editing of the current config. Check the config values before writing them.
- View the default config.
- View the config limits.

### Nice to have:

- Allow to specify a custom config/default file.


## App control

- Allow starting and stopping, enabling and disabling the app (i.e. enable at startup).
- View statistics (cpu usage?).
- View current state (filter, brightness levels, ambient, etc).

## Other

- Protect the app (from the same location) from starting multiple times.
- Query the cli app about the current/default config locations.
- Dump special statistics in a file (differentiate between debug and info). Use a CLI switch to disable/enbale info/debug logs.
- Set permissions for installed files
