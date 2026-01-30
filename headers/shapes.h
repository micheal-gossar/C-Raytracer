#ifndef SHAPES_H
#define SHAPES_H

#include <stdbool.h>
#include <ray.h>
#include <vec3.h>
#include <math.h>

double HitSphere(point3 center, double radius, const ray* r) {
    vec3 oc = VMINUS(r->orig, center);
    double a = VLENGTH_SQ(r->dir);
    double b = 2.0 * VDOT(oc, r->dir);
    double c = VLENGTH_SQ(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1;
    } else {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}

#endif 