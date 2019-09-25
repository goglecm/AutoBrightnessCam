# AutoBrightnessCam

[![Build Status](https://travis-ci.org/goglecm/AutoBrightnessCam.svg?branch=master)](https://travis-ci.org/goglecm/AutoBrightnessCam)

Service to automatically adjust the display brightness using the webcam as an
ambient luminosity sensor. Generally useful for laptops without an ambient light
sensor (ALS).

## Installation

### TL;DR

```
mkdir build
cd build
../configure
make
sudo make install
```

To uninstall:

```
sudo make uninstall
```

Note: `make install-strip` also works. It will exclude debugging symbols.

### Notable configure options

- **--enable-debug** - Enable assertions and allow the app to crash gracefully.
- **--enable-skipsystemctlcalls** - Skip the systemd setup. The app won't start
  automatically.
- **--disable-depscheck** - Do not check for runtime dependencies. Useful for VM
  builds.

### Notable configure features

- **--without-upower** - Do not use upower for the battery state.

### Build

It is recommended to do the building in a separate directory as to not interfere
with the source files (though it shouldn't be a problem).

It is also recommended to install the app with root privileges as it will
attempt to load the app as a systemd service.

Installing the app in a local directory `../configure
--prefix=/home/john/my_local_dir` is supported.

### Dependencies

Required:

- **fswebcam** - used to take pictures
- **convert** - from ImageMagick, used to extract the brightness from the
  picture

Optional:

- **upower** - used to get the charging state of the laptop, though the app can
  also manually look for the battery state

### RPM generation

The SPECS directory contains the spec needed to generate an RPM package. Simply
run:
```
cd ~
rpmdev-setuptree
rpmbuild -ba rpmbuild/SPECS/autobrightnesscam.spec
```

The rpm will be located in ~/rpmbuild/RPMS/\*.rpm

## Usage

If the installation succeeds and systemd is happy, it should all work.

The app will kick in and take pictures and adjust the brightness when the
battery is discharging. When charging, the app will try to keep the brightness
at 100%.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

Please make sure to update tests as appropriate.
