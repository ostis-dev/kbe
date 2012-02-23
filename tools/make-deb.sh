#!/bin/bash

VERSION=0.2.1
ARCHITECTURE=$(dpkg-architecture -qDEB_BUILD_ARCH)

sed -i '/Version/s|: .*$|: '"$VERSION"'|' DEBIAN/control
sed -i '/Architecture/s|: .*$|: '"$ARCHITECTURE"'|' DEBIAN/control

echo -en "\033[37;1;41mCheck dependencies...\033[0m\n"
if ! dpkg -l | grep md5deep
then
	sudo apt-get install md5deep
fi
if ! dpkg -l | grep debhelper
then
	sudo apt-get install debhelper
fi
if ! dpkg -l | grep cmake
then
	sudo apt-get install cmake
fi
if ! dpkg -l | grep make
then
	sudo apt-get install make
fi
if ! dpkg -l | grep fakeroot
then
	sudo apt-get install fakeroot
fi

echo -en "\033[37;1;41mBuild binary...\033[0m\n"
cd ../
cmake CMakeLists.txt
make

echo -en "\033[37;1;41mCreate temporary directory for package and copy required files...\033[0m\n"
# Back to that dir
cd -

# Making catalog structure 
mkdir -p ./kbe/usr/share/kbe
mkdir -p ./kbe/usr/share/doc/kbe
mkdir -p ./kbe/usr/lib/kbe
mkdir -p ./kbe/usr/bin
mkdir -p ./kbe/usr/share/applications
mkdir -p ./kbe/usr/share/pixmaps

# Copying needed files into catalog structure
cp -r ./DEBIAN ./kbe/
mv -f ../media ./kbe/usr/share/kbe/
mv -f ../kbe ./kbe/usr/lib/kbe/
cp ./files/kbe.desktop ./kbe/usr/share/applications/
cp ./files/kbe.xpm ./kbe/usr/share/pixmaps/

# Making symbolic links
ln -s ../lib/kbe/kbe ./kbe/usr/bin/kbe
ln -s ../share/kbe/media ./kbe/usr/lib/kbe/media

# Remove debug and other unneeded info
strip ./kbe/usr/lib/kbe/kbe

cp changelog ./kbe/usr/share/doc/kbe/
gzip -9 ./kbe/usr/share/doc/kbe/changelog

cp copyright ./kbe/usr/share/doc/kbe/

# Calculate full size
full_size=$(du -s ./kbe/usr | awk '{print $1}')
sed -i '/Installed-Size/s|: .*$|: '"$full_size"'|' DEBIAN/control

echo -en "\033[37;1;41mMake *.deb pachage...\033[0m\n"
cd ./kbe
md5deep -l usr/lib/kbe/kbe > ./DEBIAN/md5sums
md5deep -r -l usr/share >> ./DEBIAN/md5sums
cd -

fakeroot dpkg-deb --build kbe
fakeroot dpkg-name -o kbe.deb

echo -en "\033[37;1;41mRemove temporary data...\033[0m\n"
rm -r ../CMakeFiles ../sources/*/*.cxx ../sources/*.cxx ./kbe
rm ../cmake_install.cmake ../CMakeCache.txt ../Makefile ../ui_mainwindow.h

echo -en "\033[37;1;41mkbe.deb package is built\033[0m\n"
