# AutoBrightnessCam

[![Build Status](https://travis-ci.com/goglecm/AutoBrightnessCam.svg?branch=master)](https://travis-ci.com/goglecm/AutoBrightnessCam)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/goglecm/AutoBrightnessCam.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/goglecm/AutoBrightnessCam/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/goglecm/AutoBrightnessCam.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/goglecm/AutoBrightnessCam/alerts/)

Service to automatically adjust the display brightness using the webcam as an
ambient luminosity sensor. Generally useful for laptops without an ambient light
sensor (ALS).

The command line app is called `aubrca`. You can start it manually or you can tell systemd to start it automatically (a service file is provided, see the tail of the `./configure` output log for the full path).

Here are the relevant systemd commands:

#### Install:
```
sudo systemctl daemon-reexec
sudo systemctl enable /usr/lib64/systemd/system/autobrightnesscam.service # May be different on your system.
sudo systemctl start autobrightnesscam.service
```
#### Uninstall:
```
sudo systemctl stop autobrightnesscam.service
sudo systemctl disable autobrightnesscam.service
```

## Alternatives

This app uses autotools and is easily installable on any \*nix like system. Some alternatives are:

 - https://github.com/FedeDP/Clight
 - http://calise.sourceforge.net/wordpress
 - https://launchpad.net/brightness
 - https://github.com/billyboar/autobrightness

## Installation

### TL;DR

```
mkdir build
cd build
../configure
make
sudo make install
```

Optionally for the app `aubrca` to automatically at startup via systemd, run the
`systemctl` commands to `enable` and `start` the service. The name of the
service is printed at the end of the log trail from the install target.


To uninstall:


```
sudo make uninstall
```

Note: `make install-strip` also works. It will exclude debugging symbols.

### Notable configure options

- **--enable-debug** - Enable assertions and allow the app to crash gracefully.
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

See the GitHub Wiki for tons of notes.

If the installation succeeds and systemd is happy, it should all work.

The app will kick in and take pictures and adjust the brightness when the
battery is discharging. When charging, the app sets the brightness to 100% after
which the user may change the brightness as per their needs.

## Contributing

See the GitHub Wiki for tons of notes.

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

Please make sure to update tests as appropriate.
