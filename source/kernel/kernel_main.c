#include <stdint.h>
#include <stdbool.h>
#include <limine.h>

#include <envvars.h>

#include <arch/gdt/gdt.h>
#include <arch/idt/idt.h>
#include <arch/paging/paging.h>

#include <memory/kmalloc.h>
#include <memory/mem.h>
#include <graphics/fb.h>
#include <graphics/putpixel.h>
#include <graphics/puts.h>
#include <arch/debug/kpanic.h>
#include <wmgr/window.h>
#include <wmgr/tile.h>

// TODO: make libc and fonts shared static libraries to be linked last

void main() {
    initialize_fb();
    // gdt_install();
    // idt_init();
    init_mem_model();
    init_genesis_window();
    Tile_t *genesis_tile = init_genesis_tile();
    // // putrect(0, 0, FB_WIDTH, FB_HEIGHT, WHITE);

    Window_t* test_window = create_window(0, 0, FB_WIDTH / 2, FB_HEIGHT, "Window 1", 20, BLACK, "Hello! test window!");
    Window_t* test_window2 = create_window(FB_WIDTH / 2, 0, FB_WIDTH / 2, FB_HEIGHT / 2, "Window 2", 20, BLACK, "Pog Pog");
    Window_t* test_window3 = create_window(FB_WIDTH / 2, FB_HEIGHT / 2, FB_WIDTH / 2, FB_HEIGHT / 2, "Patricie Viewer", 20, GREEN, "Ancilla est in foro");
    Window_t* test_window4 = create_window(FB_WIDTH / 2, 0, FB_WIDTH / 2, FB_HEIGHT / 2, "Window 4", 20, BLACK, "Pog Pog 2");
    
    // // window_draw_window(test_window);
    // // window_draw_window(test_window2);
    // // window_draw_window(test_window3);

    Tile_t* t1 = create_tile(WINDOW_CHILDREN);
    Tile_t* t2 = create_tile(WINDOW_CHILDREN);
    Tile_t* t3 = create_tile(WINDOW_CHILDREN);
    // Tile_t* t4 = create_tile(WINDOW_CHILDREN);
    Tile_t *t4 = create_window_tile(test_window4);

    tile_add_child_window(t1, test_window);
    tile_add_child_window(t2, test_window2);
    tile_add_child_window(t3, test_window3);
    // tile_add_child_window(t4, test_window4);

    tile_add_child_tile(genesis_tile, t1);
    tile_add_child_tile(genesis_tile, t2);
    // tile_add_child_tile(genesis_tile, t3);
    tile_change_parent(t3, genesis_tile);
    tile_add_child_tile(genesis_tile, t4);

    // if (sizeof(Page_Entry_t) == 8)
    tile_draw(genesis_tile, 0, 0, 640, 400);
    printd(get_MAXPHYADDR());

    return;
}