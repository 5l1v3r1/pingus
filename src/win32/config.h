#ifndef PINGUS_CONFIG_H
#define PINGUS_CONFIG_H

#include <assert.h>

#define PACKAGE "Pingus"
#define VERSION  "0.7.0"
#define PACKAGE_STRING "Pingus 0.7.0"
#define MAJOR_VERSION 0
#define MINOR_VERSION 7
#define PATCH_VERSION 0
#define VERSION_STRING "0.7.0"
#define PINGUS_DATADIR "data"
#define ENABLE_NLS 1

/* 'real' config values */
#define HAVE_STDDEF_H 1
#define HAVE_STRING_H 1
#define HAVE_STDLIB_H 1
#define HAVE_ALLOCA 1
#define HAVE_GETCWD 1
#define HAVE_SETLOCALE 1
#define HAVE_STRDUP 1
#define HAVE_GETTEXT 1
#define HAVE_LIBCLANVORBIS 1
#define HAVE_LIBCLANMIKMOD 1
#define ICONV_CONST const

/* MSVC specifics */
#if defined(_MSC_VER) && !defined(__cplusplus)
#define inline __inline
#endif

#define alloca _alloca
// ????
#define LOCALEDIR "."
#define LOCALE_ALIAS_PATH "."

typedef unsigned __int64 uintmax_t;

#endif
