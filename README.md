# AutoBrightnessCam

Service to automatically adjust the display brightness using the webcam as an
ambient luminosity sensor. Generally useful for laptops without an ambient light
sensor (ALS).

## Installation

### TL;DR:

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

It is recommended to do the building in a separate directory as to not interfere
with the source files (though it shouldn't be a problem).

It is also recommended to install the app with root privileges as it will
attempt to load the app as a systemd service.

Installing the app in a local directory `../configure
--prefix=/home/john/my_local_dir` is supported, however systemd won't find the
service file (which will be in
/home/john/my\_local\_dir/lib/systemd/system/\*.service and so you need to copy
it in the correct location where systemd expects it (i.e. /etc/systemd/system or
/usr/local/lib/systemd/system).

After that don't forget to enable and start the service with:
```
sudo systemctl enable autobrightnesscam.service
sudo systemctl start autobrightnesscam.service
```

### Dependencies

Required:

- fswebcam - used to take pictures

- convert - from ImageMagick, used to extract the brightness from the picture

Optional:

- upower - used to get the charging state of the laptop, though the app can also
  manually look for the battery state

## Usage

If the installation succeeds and systemd is happy, it should all work.

The app will kick in and take pictures and adjust the brightness when the
battery is discharging. When charging, the app will try to keep the brightness
at 100%.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

Please make sure to update tests as appropriate.