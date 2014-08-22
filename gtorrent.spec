Name:           gtorrent
Version:        0.5
Release:        1%{?dist}
Summary:        A simple GTK+ torrent client built off of libtorrent.

License:        GPLv2
URL:            https://github.com/Prince781/gtorrent
Source0:        ftp://ftp.prince781.net/linux/%{name}/%{name}-%{version}.tar.gz 

#BuildRequires:  libtorrent-rasterbar
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires:  gtk3 libnotify
Requires:       libtorrent-rasterbar, gtk3, libnotify

%description
gTorrent is a torrent client and frontend to libtorrent for GNOME, written in
C. It supports basic features, including adding magnet links, configuring
torrent behavior, viewing torrent statistics, and notifying via libnotify.

%prep
%autosetup -c gtorrent-%{version}

%build
make %{?_smp_mflags}


%install
make DESTDIR=$RPM_BUILD_ROOT%{_bindir} install

# remove extraneous files
rm -rf $RPM_BUILD_ROOT%{_datadir}/*
rm -rf $RPM_BUILD_ROOT%{_includedir}/*


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,0755)
%{_bindir}/gTorrent



%changelog
* Fri Aug 22 2014 Princeton Ferro
- 
