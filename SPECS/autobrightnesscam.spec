Name:           autobrightnesscam
Version:        1.0
Release:        1%{?dist}
Summary:        Adjusts the brightness based on the luminosity from the webcam.

License:        GPLv3+
URL:            https://github.com/goglecm/AutoBrightnessCam/releases/download/v1.0/autobrightnesscam-1.0.tar.gz
Source0:        autobrightnesscam-1.0.tar.gz

BuildRequires:  gcc make
Requires:       fswebcam ImageMagick systemd upower

%description
App to periodically adjust the display brightness based on the luminosity of the
webcam.

%prep
%setup -q


%build
%configure --with-upower --enable-skipsystemctlcalls --disable-debug
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
%make_install

%post
systemctl enable /usr/lib64/systemd/system/autobrightnesscam.service
systemctl start autobrightnesscam.service


%preun
systemctl stop autobrightnesscam.service
systemctl disable autobrightnesscam.service

%files
/usr/bin/aubrca
/usr/lib64/systemd/system/autobrightnesscam.service

