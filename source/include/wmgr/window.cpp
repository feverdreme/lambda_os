#include "window.hpp"

#include <graphics/fb.h>
#include <graphics/puts.h>
#include <graphics/putpixel.h>
#include <libc/fonts.h>
#include <memory/kmalloc.h>

Window::Window() {}

Window::Window(int posx, int posy, int width, int height, const char *title, pixel_color_t border_color, pixel_color_t bg_color):
    posx(posx),
    posy(posy),
    width(width),
    height(height),
    title(title),
    border_color(border_color),
    bg_color(bg_color) {
        text_buffer = (char *)kmalloc(6400 * sizeof(char));
    }

Window::~Window() {}

void Window::run() {
    this->draw();

    
}

void Window::draw() {
    this->draw_tilebar();
    this->draw_body();
    this->draw_border();
}

void Window::draw_tilebar() {
    // Tilebar Color
    putrect(posx, posy, width, 20, border_color);

    // Draw the Title
    puts(title,
        posx + xpadding,
        posy + (20 - spleen_font.fc_height) / 2, 
        GREEN);
}

void Window::draw_body() {
    // Body Background
    putrect(posx, posy + 20, width, height - 20, bg_color);
}

void Window::draw_border() {
    put_hline(posx, posy, width, border_color);
    put_hline(posx, posy + height - 1, width, border_color);
    put_vline(posx, posy, height, border_color);
    put_vline(posx + width - 1, posy, height, border_color);
}