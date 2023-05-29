#ifndef WINDOW_H
#define WINDOW_H
#ifdef __cplusplus
extern "C" {
#endif

#include <graphics/putpixel.h>

#define MAX_WINDOWS 256

class Window {
private:
    static int num_windows;
    static Window *all_windows[MAX_WINDOWS];

    int posx;
    int posy;
    int width;
    int height;

    const char *title;
    pixel_color_t border_color;
    pixel_color_t bg_color;

    void draw_tilebar();
    void draw_body();

public:
    Window(int posx, int posy, int width, int height, const char *title, pixel_color_t border_color, pixel_color_t bg_color);

    void draw();

    ~Window();
};

#ifdef __cplusplus
}
#endif
#endif