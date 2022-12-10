#include <graphics/putpixel.h>
#include <graphics/puts.h>
#include <libc/libc.h>
#include <memory/kmalloc.h>
#include <wmgr/window.h>

int num_windows = 0;
Window_t* all_windows[MAX_WINDOWS];  // maximum windows allowed

void init_genesis_window() {
    Window_t* genesis_window = create_window(
        0, 0, 20,
        "Elit ut laboris ut quis laboris dolor velit sit ea anim quis officia. \
Duis elit consectetur eu magna. Adipisicing est dolor consequat sunt velit. \
Aliquip tempor mollit ullamco quis ea. Non commodo anim aliquip consequat irure occaecat \
consectetur mollit deserunt amet duis commodo ad aute.\nSit excepteur adipisicing tempor \
laboris ea ut. Dolore aute magna dolor enim do laborum cupidatat esse reprehenderit aliqua aliqua. \
Fugiat dolore dolore anim sunt Lorem qui mollit velit nulla cillum deserunt minim exercitation. \
Quis aliquip enim nostrud aute mollit enim ex dolore est mollit ullamco. Excepteur voluptate \
velit ex proident deserunt qui dolor fugiat excepteur sit commodo voluptate. Incididunt \
nostrud ut veniam cillum do.\nEsse aute sit id in nulla culpa et aliquip ipsum. Est do \
enim reprehenderit nostrud aute anim. Sunt veniam veniam pariatur anim id anim. Tempor \
ex labore occaecat enim nulla et amet sunt id nulla. Dolore adipisicing duis minim fugiat. \
Mollit id reprehenderit cupidatat in nulla ullamco veniam exercitation tempor. Consectetur \
esse reprehenderit dolor ipsum minim voluptate laborum esse sint.\nVeniam commodo tempor \
esse nostrud consequat officia anim cupidatat laboris in mollit deserunt in. Ipsum irure \
laboris amet eiusmod ea ad laboris Lorem culpa duis. Incididunt laborum mollit et reprehenderit \
ipsum labore commodo qui sint. Quis ad eiusmod est occaecat exercitation est \
consectetur excepteur nisi nostrud ipsum.");

    window_draw_window(genesis_window);
}

Window_t* create_window(int _pos_x, int _pos_y, int _th, char* _bodytext) {
    Window_t* new_window = (Window_t*)kmalloc(sizeof(Window_t));

    new_window->pos_x = _pos_x;
    new_window->pos_y = _pos_y;
    new_window->tilebar_height = _th;
    new_window->bodytext = _bodytext;

    all_windows[num_windows] = new_window;
    num_windows++;

    return new_window;
}

void window_draw_window(Window_t* w) {
    window_draw_tilebar(w);
    window_draw_body(w);
}

void window_draw_tilebar(Window_t* w) {
    // create background
    putrect(0, 0, 320, 20, LIGHTCYAN);

    // put the title text
    const char* default_text = "STATUS MODE 11:59";
    int default_text_len =
        strlen(default_text) * 5 + cursor.kerning * strlen(default_text);
    puts("STATUS MODE 11:59", 320 - default_text_len, 5);

    puts("[WINDOW 1][X]", 0, 5);
}

void window_draw_body(Window_t* w) {
    // create background
    putrect(0, 20, 320, 200 - 20, WHITE);

    puts(w->bodytext, 0, 20 + 1);
}