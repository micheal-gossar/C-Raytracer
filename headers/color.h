#ifndef COLOR_H
#define COLOR_H
#include <MiniFB.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <vec3.h>

void WriteColor(uint32_t *buffer, int index, const color* pxCl) {
    double r = pxCl->x;
    double g = pxCl->y;
    double b = pxCl->z;

    int ir = (int)(255.999 * r);
    int ig = (int)(255.999 * g);
    int ib = (int)(255.999 * b);

    buffer[index] = MFB_RGB(ir, ig, ib);
}
#endif