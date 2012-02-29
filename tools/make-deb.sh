#!/bin/bash

VERSION=0.2.1
ARCHITECTURE=$(dpkg-architecture -qDEB_BUILD_ARCH)

install_dependency_if_not_yet_installed()
{
  local dependency=$1
  if ! dpkg -l | grep $dependency
  then
	sudo apt-get install $dependency
  fi
}

install_all_dependencies_if_not_yet_installed()
{
  echo -en "\033[37;1;41mCheck dependencies...\033[0m\n"
  install_dependency_if_not_yet_installed md5deep
  install_dependency_if_not_yet_installed cmake
  install_dependency_if_not_yet_installed make
  install_dependency_if_not_yet_installed fakeroot
}

build_source_files()
{
  echo -en "\033[37;1;41mBuild binary...\033[0m\n"
  cmake CMakeLists.txt
  make
}

make_catalog_structure()
{
  echo -en "\033[37;1;41mCreate temporary directory for package and copy required files...\033[0m\n"
  mkdir -p ./kbe/usr/share/kbe
  mkdir -p ./kbe/usr/share/doc/kbe
  mkdir -p ./kbe/usr/lib/kbe
  mkdir -p ./kbe/usr/bin
  mkdir -p ./kbe/usr/share/applications
  mkdir -p ./kbe/usr/share/pixmaps
}

fill_catalog_structure_with_content() 
{
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

  echo -en "\033[37;1;41mMake *.deb pachage...\033[0m\n"
  cd ./kbe
  md5deep -l usr/lib/kbe/kbe > ./DEBIAN/md5sums
  md5deep -r -l usr/share >> ./DEBIAN/md5sums
  cd -
}

set_attribute_value_in_file()
{ 
  local attribute=$1
  local value=$2
  local file=$3

  sed -i '/'"$attribute"'/s|: .*$|: '"$value"'|' $file
}

make_changes_in_control_file()
{
  set_attribute_value_in_file 'Version' $VERSION DEBIAN/control
  set_attribute_value_in_file 'Architecture' $ARCHITECTURE DEBIAN/control
  # Calculate full size
  full_size=$(du -s ./kbe/usr | awk '{print $1}')
  set_attribute_value_in_file 'Installed-Size' $full_size DEBIAN/control
}

build_deb_package()
{
  fakeroot dpkg-deb --build kbe
  fakeroot dpkg-name -o kbe.deb
  echo -en "\033[37;1;41mkbe.deb package is built\033[0m\n"
}

clean()
{
  echo -en "\033[37;1;41mRemove temporary data...\033[0m\n"
  rm -r ../CMakeFiles ../sources/*/*.cxx ../sources/*.cxx ./kbe
  rm ../cmake_install.cmake ../CMakeCache.txt ../Makefile ../ui_mainwindow.h
}

make_deb_package()
{
  install_all_dependencies_if_not_yet_installed

  cd ../
  build_source_files
  # Back to that dir
  cd -

  make_catalog_structure
  fill_catalog_structure_with_content
  make_changes_in_control_file
  build_deb_package
  clean
}

# Starting point
make_deb_package