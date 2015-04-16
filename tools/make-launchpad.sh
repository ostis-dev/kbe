#!/bin/bash

VERSION=0.3.2
ARCHITECTURE=any
PROJECT_ROOT=..
PROJECT_SOURCES_ROOT=sources
BZR_REPO=kbe

usage()
{
  echo "Before using $0 check your launchpad access:"
  echo "  bzr lp-login LOGIN"
  echo "  bzr info lp:kbe"
  echo ""
  echo "If you understand information above then:"
  echo "  Usage: $0 YES"
  exit 1
}

install_dependency_if_not_yet_installed()
{
  local dependency=$1
  if ! dpkg -l | cut -d" " -f3 | grep $dependency
  then
        sudo apt-get install $dependency
  fi
}

install_all_dependencies_if_not_yet_installed()
{
  echo -en "\033[37;1;41mCheck dependencies...\033[0m\n"
  install_dependency_if_not_yet_installed bzr
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
  echo -en "\033[37;1;41mMake changes in control file...\033[0m\n"
  set_attribute_value_in_file 'Architecture' $ARCHITECTURE launchpad/control
}

prepare_project_structure()
{
  echo -en "\033[37;1;41mPrepare project structure...\033[0m\n"
  ln -s sources/all.pro all.pro
  ln -s sources/kbe kbe
  ln -s sources/plugins plugins
  cp -r tools/launchpad debian
  cp tools/DEBIAN/{changelog,copyright} debian
}

prepare_sources()
{
  echo -en "\033[37;1;41mPrepare sources...\033[0m\n"
  cp kbe/kbe.pro kbe/kbe.pro.backup
  echo "" >> kbe/kbe.pro
  echo "target.path = /usr/bin" >> kbe/kbe.pro
  echo "lib.path = /usr/lib/kbe" >> kbe/kbe.pro
  echo "lib.files = ../bin/plugins/*" >> kbe/kbe.pro
  echo "desktop.path = /usr/share/applications" >> kbe/kbe.pro
  echo "desktop.files = ../../tools/files/kbe.desktop" >> kbe/kbe.pro
  echo "xpm.path = /usr/share/pixmaps" >> kbe/kbe.pro
  echo "xpm.files = ../../tools/files/kbe.xpm" >> kbe/kbe.pro
  echo "INSTALLS += target lib desktop xpm" >> kbe/kbe.pro
  sed -i 's/Config::pathPlugins = root_dir;/Config::pathPlugins = "\/usr\/lib\/kbe";/' kbe/main.cpp
  sed -i 's/Config::pathPlugins.cd("plugins");/\/\/Config::pathPlugins.cd("plugins");/' kbe/main.cpp
}

push_bzr_repo()
{
  echo -en "\033[37;1;41mPush Bazaar repository...\033[0m\n"
  if [ -d ".bzr" ]; then
    rm -r .bzr
  fi
  bzr branch lp:kbe kbe_bzr
  if [ -d "kbe_bzr" ]; then
    REVNO=`bzr revno lp:kbe`
    let REVNO+=1
    mv kbe_bzr/.bzr .bzr
    rm -r kbe_bzr
  else
    REVNO=1
    bzr init
  fi
  bzr add .
  bzr rm --keep .git
  bzr commit -m "Release $VERSION-r$REVNO" --unchanged
  bzr push --overwrite lp:$BZR_REPO
}

clean()
{
  echo -en "\033[37;1;41mRemove temporary data...\033[0m\n"
  rm all.pro
  rm kbe
  rm plugins
  rm -r .bzr
  rm -r debian
  mv -f $PROJECT_SOURCES_ROOT/kbe/kbe.pro.backup $PROJECT_SOURCES_ROOT/kbe/kbe.pro
  sed -i 's/Config::pathPlugins = "\/usr\/lib\/kbe";/Config::pathPlugins = root_dir;/' $PROJECT_SOURCES_ROOT/kbe/main.cpp
  sed -i 's/\/\/Config::pathPlugins.cd("plugins");/Config::pathPlugins.cd("plugins");/' $PROJECT_SOURCES_ROOT/kbe/main.cpp
}

make_launchpad_packages()
{
  install_all_dependencies_if_not_yet_installed

  make_changes_in_control_file

  cd $PROJECT_ROOT
  prepare_project_structure

  cd $PROJECT_SOURCES_ROOT
  prepare_sources

  cd $PROJECT_ROOT
  push_bzr_repo

  clean
}

# Starting point
[[ $1 != "YES" ]] && usage
make_launchpad_packages
