#ifndef VEC3_H
#define VEC3_H

#ifdef USE_SSE
#include "vec3sse.h"
#else
#include "vec3std.h"
#endif

#endif //VEC3_H