#include <MiniFB.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <color.h>
#include <ray.h>
#include <shapes.h>
#include <vec3.h>




#define ASPECT_RATIO (16.0 / 9.0)
#define WIDTH 1000
#define HEIGHT ((int)(WIDTH / ASPECT_RATIO))
#define VIEWPORT_HEIGHT 2.0
#define VIEWPORT_WIDTH (VIEWPORT_HEIGHT * (double)(WIDTH)/HEIGHT)
#define FOCAL_LENGTH 1.0

color RayColor(const ray* r) {
    double t = HitSphere((point3){0,0,-1}, 0.5, r);
    if (t > 0.0) {
        vec3 N = UNITVECTOR(VMINUS(RayAt(r,t), ((vec3){0,0,-1})));
        return VSCALE(((color){N.x+1, N.y+1, N.z+1}), 0.5);
    }
    vec3 unit_direction = UNITVECTOR(r->dir);
    float a = 0.5*(unit_direction.y + 1.0f);
    
    color white = {1.0, 1.0, 1.0};
    color blue = {0.5, 0.7, 1.0};
    color c1 = VSCALE(white, 1.0 - a);
    color c2 = VSCALE(blue, a);
    
    return VADD(c1, c2);
}

int main(void) {
    point3 cameraCenter = (point3){0,0,0};
    vec3 viewportU = (vec3){VIEWPORT_WIDTH, 0,0};
    vec3 viewportV = (vec3){0, -VIEWPORT_HEIGHT, 0};
    
    vec3 deltaU = VDIVIDE(viewportU, WIDTH);
    vec3 deltaV = VDIVIDE(viewportV, HEIGHT);

    vec3 focalVec = (vec3){0, 0, FOCAL_LENGTH};
    vec3 viewUHalf = VDIVIDE(viewportU, 2.0);
    vec3 viewVHalf = VDIVIDE(viewportV, 2.0);

    vec3 upperLeft = VMINUS(cameraCenter, focalVec);
    upperLeft = VMINUS(upperLeft, viewUHalf);
    upperLeft = VMINUS(upperLeft, viewVHalf);

    vec3 pixel00Loc = VADD(upperLeft, MULTIPLY(VADD(deltaU, deltaV), 0.5));


    struct mfb_window *window = mfb_open_ex("Raytracer", WIDTH, HEIGHT, WF_RESIZABLE);
    if (window == NULL) {
        printf("Window Init Failed");
        return 0;
    }
    uint32_t *buffer = (uint32_t*)malloc(WIDTH*HEIGHT*4);


    mfb_update_state state;
    do {
        for (int i = 0; i < WIDTH * HEIGHT; ++i) {
            if (i % WIDTH == 0) {
                float Percent = (float)i / (WIDTH * HEIGHT);
                fprintf(stderr, "\r[");
                int BarWidth = 20;
                int Pos = BarWidth * Percent;
                for (int j = 0; j < BarWidth; ++j) fprintf(stderr, j <= Pos ? "=" : " ");
                fprintf(stderr, "] %.1f%%", Percent * 100.0f);
            }
            int x = i % WIDTH;
            int y = i / WIDTH;

            vec3 PixelCenter = VADD(pixel00Loc, VADD(MULTIPLY(deltaU, x), MULTIPLY(deltaV, y)));
            vec3 RayDirection = VMINUS(PixelCenter, cameraCenter);

            ray R = { .orig = cameraCenter, .dir = RayDirection };
            
            color PixelColor = RayColor(&R);
            WriteColor(buffer, i, &PixelColor);
        }

        state = mfb_update_ex(window, buffer, WIDTH, HEIGHT);

        if (state < 0) {
            window = NULL;
            break;
        }
    } while (mfb_wait_sync(window));

    free(buffer);
    buffer = NULL;
    window = NULL;

    return 0;
}
