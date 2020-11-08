# AutoBrightnessCam

[![Build Status](https://travis-ci.com/goglecm/AutoBrightnessCam.svg?branch=master)](https://travis-ci.com/goglecm/AutoBrightnessCam)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/goglecm/AutoBrightnessCam.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/goglecm/AutoBrightnessCam/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/goglecm/AutoBrightnessCam.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/goglecm/AutoBrightnessCam/alerts/)

Service to automatically adjust the display brightness using the webcam as an
ambient luminosity sensor. Generally useful for laptops without an ambient light
sensor (ALS).

The command line app is called `aubrca`. You can start it manually or you can tell systemd to start it automatically (a service file is provided, see the tail of the `./configure` output log for the full path or after `make install`).

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

Here are the relevant `systemd` commands:

#### Serivce install:
```
sudo systemctl daemon-reexec
sudo systemctl enable /usr/lib64/systemd/system/autobrightnesscam.service # May be different on your system.
sudo systemctl start autobrightnesscam.service
```
#### Service uninstall:
```
sudo systemctl stop autobrightnesscam.service
sudo systemctl disable autobrightnesscam.service
```


### Notable configure options

- **--enable-debug** - Enable assertions and allow the app to crash gracefully.
- **--disable-depscheck** - Do not check for runtime dependencies. Useful for VM
  builds.

### Notable configure features

- **--without-upower** - Do not use `upower` for the battery state.

### Build

It is recommended to do the building in a separate directory as to not interfere
with the source files (though it shouldn't be a problem).

Installing the app in a local directory `../configure
--prefix=/home/john/my_local_dir` is supported as well as the other `configure`
flags. See `../configure -h`.

### Dependencies

Required:

- **fswebcam** - used to take pictures
- **convert** - from ImageMagick, used to extract the brightness from the
  picture

Optional:

- **upower** - used to get the charging state of the laptop, though the app can
  also manually look for the battery state


## Configuration

There is a config file under `/etc/aubrca.conf` or `/usr/local/etc/aubrca.conf`,
depending on the `--prefix` you chose during `./configure`. There you can control
the behaviour of the application.

Options include setting the brightness adjustment smoothness, min, max, whether
to depend on battery, etc.

Note that once the config has changed, don't forget to restart the application,
either via `systemd` using `sudo systemd restart autobrightnesscam.service` or
just manually killing the app and starting it again.

Some rules on the config formatting:
- Use `#` for comments. They can be before/after the config options, or inline
  with a config option
- Use the `key = value` formatting to specify an option.
- The value may only be numerical (negative values allowed).
- No spaces before an option are allowed, but they are allowed around the `=`.


## Troubleshooting

- The brightness won't change.

If you've started the app manually, make sure to give it root permissions
(via `sudo`) as it needs root permissions to change the brightness.

Also, due to the internal filtering used, one won't notice the brightness change
immediately. You can decrease the sampling rate from the config file to take
more pics and adjust the brightness faster.

- The app crashes startup.

Check the last reported message from stderr (see `sudo systemd status
autobrightnesscam.service`). Most of the time it's a config issue.

- My config isn't being picked up.

If you have some bad config values, the app will attempt to read that option
from the default config file instead, which lives in `/share/aubrca/defaults.conf`
or `/usr/local/share/aubrca/defaults.conf` (depending on the `--prefix`).

- The app crashes sometime after startup.

Please create an issue in GitHub, this may be a bug. If you could append the
error message, or upload a core dump, that would be great.


## RPM generation

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

If the installation succeeds and `systemd` is happy, it should all work. Make
sure to start the `systemd` service or manually launch it.

The app will kick in, take pictures and adjust the brightness when the
battery is discharging. When charging, the app sets the brightness to 100% and
then stops adjusting the brightness until the next discharge cycle, unless told
otherwise via the config file.

## Contributing

See the GitHub Wiki for tons of notes.

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

Please make sure to update/add the tests as appropriate.
