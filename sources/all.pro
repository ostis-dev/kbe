
QT       += core

TEMPLATE = subdirs

CONFIG += ordered

DESTDIR = ./bin

SUBDIRS = plugins/scg \
          kbe

          #plugins/scn \
          #plugins/scs \


#win32: SUBDIRS += updater
