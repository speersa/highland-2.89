#ifndef ANATOOLS_FILE_VERSION
#define ANATOOLS_FILE_VERSION v10r11p21
#define ANATOOLS_FILE_MAJOR_VERSION 10
#define ANATOOLS_FILE_MINOR_VERSION 11
#define ANATOOLS_FILE_PATCH_VERSION 21
#define BEFORE_ANATOOLS_FILE(v,r,p) ((ANATOOLS_FILE_MAJOR_VERSION==(v)&&ANATOOLS_FILE_MINOR_VERSION==(r)&&ANATOOLS_FILE_PATCH_VERSION<(p))||(ANATOOLS_FILE_MAJOR_VERSION==(v)&&ANATOOLS_FILE_MINOR_VERSION<(r))||(ANATOOLS_FILE_MAJOR_VERSION<(v)))
#define EQUALS_ANATOOLS_FILE(v,r,p) (ANATOOLS_FILE_MAJOR_VERSION==(v)&&ANATOOLS_FILE_MINOR_VERSION==(r)&&ANATOOLS_FILE_PATCH_VERSION==(p))
#define ANATOOLS_FILE_PROD5 BEFORE_ANATOOLS_FILE(11,0,0)
#define ANATOOLS_FILE_AFTERPROD5 !BEFORE_ANATOOLS_FILE(11,0,0)
#endif