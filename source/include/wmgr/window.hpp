#ifndef WINDOW_H
#define WINDOW_H
#ifdef __cplusplus
extern "C" {
#endif

#include <graphics/fb.h>
#include <graphics/putpixel.h>

#define MAX_WINDOWS 256

class Window {
private:
    static int num_windows;
    static const int xpadding = 2;
    static const int ypadding = 3;
    static Window *all_windows[MAX_WINDOWS];

    int posx;
    int posy;
    int width;
    int height;

    const char *title;
    pixel_color_t border_color;
    pixel_color_t bg_color;

    char *text_buffer;

public:
    Window();
    Window(int posx, int posy, int width, int height, const char *title, pixel_color_t border_color, pixel_color_t bg_color);

    ~Window();

    void run();
private:
    void draw();
    void draw_tilebar();
    void draw_body();
    void draw_border();

    void prompt();
};

#ifdef __cplusplus
}
#endif
#endif