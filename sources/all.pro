
QT       += core
QT += widgets

TEMPLATE = subdirs

CONFIG += ordered

DESTDIR = ./bin

SUBDIRS = plugins/m4scp \
          plugins/scg \
          #plugins/scn \
          plugins/scs \
          kbe

#win32: SUBDIRS += updater
