#include <wmgr/window.h>

#include <envvars.h>
#include <graphics/putpixel.h>
#include <graphics/puts.h>
#include <libc/libc.h>
#include <libc/fonts.h>
#include <memory/kmalloc.h>

int num_windows = 0;
Window_t* all_windows[MAX_WINDOWS];  // maximum windows allowed

void init_genesis_window() {
    Window_t* genesis_window = create_window(
        0, 0, INTERNAL_WIDTH, INTERNAL_HEIGHT, "Window 1", 20, RED,
        "Elit ut laboris ut quis laboris dolor velit sit ea anim quis officia.");

    // window_draw_window(genesis_window);
}

Window_t* create_window(int _pos_x, int _pos_y, int _width, int _height, const char *_tilebar_title, int _th, pixel_color_t _border_color, char* _bodytext) {
    Window_t* new_window = (Window_t*)kmalloc(sizeof(Window_t));

    new_window->pos_x = _pos_x;
    new_window->pos_y = _pos_y;
    new_window->width = _width;
    new_window->height = _height;
    new_window->tilebar_title = _tilebar_title;
    new_window->tilebar_height = _th;
    new_window->border_color = _border_color;
    new_window->bodytext = _bodytext;

    all_windows[num_windows] = new_window;
    num_windows++;

    return new_window;
}

void window_destroy_window(Window_t* w) {
    kfree(w);
    num_windows--;
}

void window_draw_window(Window_t* w) {
    window_draw_tilebar(w);
    window_draw_body(w);
    window_draw_border(w);
}

void window_draw_tilebar(Window_t* w) {
    // create background
    putrect(w->pos_x, w->pos_y, w->width, w->tilebar_height, LIGHTCYAN);

    // put the title text
    const char* default_text = "STATUS MODE 11:59"; // TODO: body text should be a method or some data struct that can store a wide range of bodies. maybe a content type with a draw method?
    int default_text_len = font_strlen(default_text, &spleen_font, cursor.kerning);
    // puts("STATUS MODE 11:59", w->width - default_text_len, spleen_font.fc_width, GREEN);

    // Draw title

    int title_len = font_strlen(w->tilebar_title, &spleen_font, cursor.kerning);

    putc('[', w->pos_x, w->pos_y + 5, GREEN);
    puts(w->tilebar_title, w->pos_x + spleen_font.fc_width + cursor.kerning, w->pos_y + 5, GREEN);
    putc(']', w->pos_x + spleen_font.fc_width + title_len + cursor.kerning * 2, w->pos_y + 5, GREEN);

    puts("[X]", w->pos_x + spleen_font.fc_width * 2 + title_len + cursor.kerning * 3, w->pos_y + 5, GREEN);
}

void window_draw_body(Window_t* w) {
    // create background
    putrect(w->pos_x, w->pos_y + w->tilebar_height, w->width, w->height - w->tilebar_height, 0x00FFFFFF);

    puts(w->bodytext, w->pos_x + 1, w->pos_y + w->tilebar_height + 1, GREEN);
}

void window_draw_border(Window_t* w) {
    put_hline(w->pos_x, w->pos_y, w->width, w->border_color);
    put_hline(w->pos_x, w->pos_y + w->height, w->width, w->border_color);
    put_vline(w->pos_x, w->pos_y, w->height, w->border_color);
    put_vline(w->pos_x + w->width, w->pos_y, w->height, w->border_color);
}

void window_update_xywh(Window_t* w, int x, int y, int width, int height) {
    w->pos_x = x;
    w->pos_y = y;
    w->width = width;
    w->height = height;
}