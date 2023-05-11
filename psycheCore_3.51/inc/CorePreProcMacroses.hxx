/// HASSERT(condition) checks if the condition is met, and if not, calls
/// ABORT with an error message indicating the module and line where
/// the error occurred.


#include <stdlib.h>
#include <stdio.h>

#undef HASSERT
#undef __HASSERT

#undef DHASSERT

#define HASSERT(e)  \
    ((void) ((e) ? ((void)0) : __HASSERT (#e, __FILE__, __LINE__)))
#define __HASSERT(e, file, line) \
    ((void)printf ("%s:%u: failed assertion `%s'\n", file, line, e), abort())



/// DHASSERT(condition) is just like HASSERT, except that it only is
/// functional in DEBUG mode, but does nothing when in a non-DEBUG
/// (optimized, shipping) build.

#ifdef DEBUG
#define DHASSERT(x) HASSERT(x)
#else
#define DHASSERT(x) ((void)0)
#endif


#ifndef _COREPREPROCMACROSES_H_
#define _COREPREPROCMACROSES_H_

#endif
