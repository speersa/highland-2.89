#ifndef ANATOOLS_FILE_VERSION
#define ANATOOLS_FILE_VERSION v12r19
#define ANATOOLS_FILE_MAJOR_VERSION 12
#define ANATOOLS_FILE_MINOR_VERSION 19
#define ANATOOLS_FILE_PATCH_VERSION 0
#define BEFORE_ANATOOLS_FILE(v,r,p) ((ANATOOLS_FILE_MAJOR_VERSION==(v)&&ANATOOLS_FILE_MINOR_VERSION==(r)&&ANATOOLS_FILE_PATCH_VERSION<(p))||(ANATOOLS_FILE_MAJOR_VERSION==(v)&&ANATOOLS_FILE_MINOR_VERSION<(r))||(ANATOOLS_FILE_MAJOR_VERSION<(v)))
#define EQUALS_ANATOOLS_FILE(v,r,p) (ANATOOLS_FILE_MAJOR_VERSION==(v)&&ANATOOLS_FILE_MINOR_VERSION==(r)&&ANATOOLS_FILE_PATCH_VERSION==(p))
#endif
