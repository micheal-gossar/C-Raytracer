#include <MiniFB.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define WIDTH 256
#define HEIGHT 256

int main(void) {
    struct mfb_window *window = mfb_open_ex("Raytracer", WIDTH, HEIGHT, WF_RESIZABLE);
    if (window == NULL) {
        printf("Window Init Failed");
        return 0;
    }
    uint32_t *buffer = malloc(WIDTH*HEIGHT*4);


    mfb_update_state state;
    do {
        for (int i = 0; i < WIDTH * HEIGHT; ++i) {
            if (i % WIDTH == 0) {
                float percent = (float)i / (WIDTH * HEIGHT);
                fprintf(stderr, "\r[");
                int bar_width = 20;
                int pos = bar_width * percent;
                for (int j = 0; j < bar_width; ++j) fprintf(stderr, j <= pos ? "=" : " ");
                fprintf(stderr, "] %.1f%%", percent * 100.0f);
            }
            // Note: This logic seems to be trying to calculate UVs, but 'i' is linear.
            // Using a simple placeholder color to ensure it works first.
            int x = i % WIDTH;
            int y = i / WIDTH;
            
            float r = (float)x / (WIDTH - 1);
            float g = (float)y / (HEIGHT - 1);
            float b = 0.25f;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);

            buffer[i] = MFB_RGB(ir, ig, ib);
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
