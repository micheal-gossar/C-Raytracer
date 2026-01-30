#ifndef RAY_H
#define RAY_H

#include <vec3.h>

typedef struct {
    point3 orig;
    vec3 dir;
} ray;

static inline point3 RayAt(const ray* r, double t) {
    return VADD(r->orig, VSCALE(r->dir, t));
}

#endif
