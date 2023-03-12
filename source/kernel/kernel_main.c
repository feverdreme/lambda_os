#include <stdint.h>
#include <stdbool.h>
#include <bootboot.h>

#include <envvars.h>

#include <memory/kmalloc.h>
#include <graphics/puts.h>
#include <arch/debug/kpanic.h>
#include <wmgr/window.h>
#include <wmgr/tile.h>

// TODO: make libc and fonts shared static libraries to be linked last

void main() {
    // gdt_install();
    // idt_init();
    init_mem_model();
    // init_genesis_window();
    Tile_t *genesis_tile = init_genesis_tile();
    // putrect(0, 0, INTERNAL_WIDTH, INTERNAL_HEIGHT, WHITE);

    Window_t* test_window = create_window(0, 0, INTERNAL_WIDTH / 2, INTERNAL_HEIGHT, "Window 1", 20, BLACK, "Hello! test window!");
    Window_t* test_window2 = create_window(INTERNAL_WIDTH / 2, 0, INTERNAL_WIDTH / 2, INTERNAL_HEIGHT / 2, "Window 2", 20, BLACK, "Pog Pog");
    Window_t* test_window3 = create_window(INTERNAL_WIDTH / 2, INTERNAL_HEIGHT / 2, INTERNAL_WIDTH / 2, INTERNAL_HEIGHT / 2, "Patricie Viewer", 20, GREEN, "Ancilla est in foro");

    // window_draw_window(test_window);
    // window_draw_window(test_window2);
    // window_draw_window(test_window3);

    Tile_t* t1 = create_tile(WINDOW_CHILDREN);
    Tile_t* t2 = create_tile(WINDOW_CHILDREN);
    Tile_t* t3 = create_tile(WINDOW_CHILDREN);

    tile_add_child_window(t1, test_window);
    tile_add_child_window(t2, test_window2);
    tile_add_child_window(t3, test_window3);

    tile_add_child_tile(genesis_tile, t1);
    tile_add_child_tile(genesis_tile, t2);
    tile_add_child_tile(genesis_tile, t3);

    tile_draw(genesis_tile, 0, 0, 640, 400);

    return;
}