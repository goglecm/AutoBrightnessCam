# Improvements

### High priority

- Fix readme
- add gtest as a devel library with this specific version

### Medium priority

- add some infrastructure to allow common code between tests to be shared
- start looking at rpm generation (deb as well)
- try to develop code from a new repo checkout and see how it goes
- try different compilers

### Low priority

- add timestamp for the logs
- (later) add module name appended to the log name (i.e. register each module
  with the logger)
- add support for gmock
- remove the terminal module and rather than calling system/popen properly
  implement what the command are supposed to do
- allow the user to point the paths for any unavailable optional features
- implement the power module to use #include <linux/baterry..stuff>

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
- the brightness could not be updated during 3*N seconds

#### Requirement

What:
- the N value, minimum and maximum brightness thresholds are set to their
  default values and a warning is issued by the application

When:
- the configuration file does not exist
- the configuration file is corrupt or has invalid configuration