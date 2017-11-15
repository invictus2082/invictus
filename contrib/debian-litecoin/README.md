
Debian
====================
This directory contains files used to package invictusd/invictus-qt
for Debian-based Linux systems. If you compile invictusd/invictus-qt yourself, there are some useful files here.

## invictus: URI support ##


invictus-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install invictus-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your invictus-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

invictus-qt.protocol (KDE)

