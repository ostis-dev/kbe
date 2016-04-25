/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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


