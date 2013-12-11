/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef PLATFORM_H
#define PLATFORM_H

#define KBE_PLATFORM_WIN32 1
#define KBE_PLATFORM_LINUX 2
#define KBE_PLATFORM_APPLE 3

#define KBE_ARCHITECTURE_32 1
#define KBE_ARCHITECTURE_64 2

// Get OS
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define KBE_PLATFORM KBE_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
#   define KBE_PLATFORM KBE_PLATFORM_APPLE
#else
#   define KBE_PLATFORM KBE_PLATFORM_LINUX
#endif

// Get architecture type
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define KBE_ARCH_TYPE KBE_ARCHITECTURE_64
#else
#   define KBE_ARCH_TYPE KBE_ARCHITECTURE_32
#endif

#if defined(_DEBUG) || defined(DEBUG)
#   define KBE_DEBUG_MODE 1
#else
#   define KBE_DEBUG_MODE 0
#endif


#endif // PLATFORM_H
