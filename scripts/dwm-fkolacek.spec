Name:		dwm-fkolacek
Version:	1.0
Release:	4%{?dist}
Summary:	Customized DWM packed to RPM
Packager:	Frantisek Kolacek <fkolacek@redhat.com>
Group:		User Interface/Desktops
License:	MIT
URL:		http://github.com/fkolacek/dwm
Source0:	dwm-fkolacek-1.0.tgz

BuildRequires:	gcc libX11-devel libXinerama-devel make
Requires:	terminus-fonts xorg-x11-xinit

%description
Custom DWM configuration packed to RPM package.

%prep
%setup -q

%clean
#make clean
rm -rf %{buildroot}

%build
make


%install
#make install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/local/bin
mkdir -p %{buildroot}/usr/local/share/man/man1
mkdir -p %{buildroot}/usr/share/xsessions

install dwm %{buildroot}/usr/local/bin/dwm
chmod 755 %{buildroot}/usr/local/bin/dwm	
install	dwm.1 %{buildroot}/usr/local/share/man/man1/dwm.1
chmod 644 %{buildroot}/usr/local/share/man/man1/dwm.1

install scripts/dwm.desktop %{buildroot}/usr/share/xsessions/dwm.desktop
install scripts/dwm-personalized %{buildroot}/usr/local/bin/dwm-personalized
chmod 755 %{buildroot}/usr/local/bin/dwm-personalized

install dwm-panel/dwm-panel %{buildroot}/usr/local/bin/dwm-panel
chmod 755 %{buildroot}/usr/local/bin/dwm-panel
install dwm-panel/dwm-panel-cycle %{buildroot}/usr/local/bin/dwm-panel-cycle
chmod 755 %{buildroot}/usr/local/bin/dwm-panel-cycle

# Helpers
install scripts/dwm-menu %{buildroot}/usr/local/bin/dwm-menu
install scripts/dwm-switch-keyboard %{buildroot}/usr/local/bin/dwm-switch-keyboard
install scripts/dwm-open-browser %{buildroot}/usr/local/bin/dwm-open-browser

chmod 755 %{buildroot}/usr/local/bin/dwm-{menu,switch-keyboard,open-browser}

%files
%doc /usr/local/share/man/man1/dwm.1
%config /usr/local/bin/dwm-personalized
/usr/share/xsessions/dwm.desktop
/usr/local/bin/dwm
/usr/local/bin/dwm-panel
/usr/local/bin/dwm-panel-cycle

/usr/local/bin/dwm-menu
/usr/local/bin/dwm-switch-keyboard
/usr/local/bin/dwm-open-browser

%changelog
* Sun Nov 02 2014	Frantisek Kolacek <fkolacek@redhat.com> 1.0-1
--Initial build

* Sun Nov 02 2014	Frantisek Kolacek <fkolacek@redhat.com> 1.0-4
--Naming and placing unification, resynced to repository
