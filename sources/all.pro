
QT       += core

TEMPLATE = subdirs

CONFIG += ordered

DESTDIR = ./bin

SUBDIRS = plugins/scg \
          plugins/scs \
          #plugins/scn \
          kbe

#win32: SUBDIRS += updater
