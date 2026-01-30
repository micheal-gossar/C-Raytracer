#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct {
    double x;
    double y;
    double z;
} vec3;

typedef vec3 point3;
typedef vec3 color;
//Vec3 and Vec3
#define VADD(u, v)       ((vec3){(u).x + (v).x, (u).y + (v).y, (u).z + (v).z})
#define VMINUS(u, v)     ((vec3){(u).x - (v).x, (u).y - (v).y, (u).z - (v).z})
#define VMULTIPLY(u, v)  ((vec3){(u).x * (v).x, (u).y * (v).y, (u).z * (v).z})
#define VCROSS(u, v)     ((vec3){(u).y * (v).z - (u).z * (v).y, (u).z * (v).x - (u).x * (v).z, (u).x * (v).y - (u).y * (v).x})

#define VSCALE(v, t)     ((vec3){(v).x * (t), (v).y * (t), (v).z * (t)})
#define VDIVIDE(v, t)    ((vec3){(v).x / (t), (v).y / (t), (v).z / (t)})

#define VDOT(u, v)       ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
#define VLENGTH_SQ(v)    (VDOT(v, v))
#define VLENGTH(v)       (sqrt(VLENGTH_SQ(v)))
#define UNITVECTOR(v)    (VDIVIDE(v, VLENGTH(v)))
//Vec3 and Int
#define PLUS(v, t)       ((vec3){(v).x + (t), (v).y + (t), (v).z + (t)})
#define MINUS(v, t)      ((vec3){(v).x - (t), (v).y - (t), (v).z - (t)})
#define MULTIPLY(v, t)   VSCALE(v, t)


#endif
