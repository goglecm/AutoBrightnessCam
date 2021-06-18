Name:           autobrightnesscam
Version:        2.0
Release:        1%{?dist}
Summary:        Adjusts the brightness based on the luminosity from the webcam.

License:        GPLv3+
URL:            https://github.com/goglecm/AutoBrightnessCam/releases/download/v2.0/autobrightnesscam-2.0.tar.gz
Source0:        autobrightnesscam-2.0.tar.gz

BuildRequires:  gcc make libconfig-devel
Requires:       fswebcam ImageMagick systemd upower sed grep

%description
App to periodically adjust the display brightness based on the luminosity of the
webcam.

%prep
%setup -q


%build
%configure --disable-debug --disable-systemdbanner
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
%make_install

%post
systemctl daemon-reexec
systemctl enable /usr/lib64/systemd/system/autobrightnesscam.service
systemctl start autobrightnesscam.service


%preun
systemctl stop autobrightnesscam.service
systemctl disable autobrightnesscam.service

%files
/usr/bin/aubrca
/usr/lib64/systemd/system/autobrightnesscam.service
/etc/aubrca.conf
/var/aubrca/debug.log
/usr/share/aubrca/defaults.conf
