// #include <wmgr/window.h>

// #include "../kernel/memory/kmalloc.h"
// #include "../kernel/graphics/putpixel.h"

// const int MAXWINDOWS = 256;

// int num_windows = 0;
// Window_Entry_t* all_windows[MAXWINDOWS];  // maximum windows allowed

// Window_t* create_window(int _posx, int _posy, int _th, char* _bodytext) {
//     Window_t* new_window = (Window_t*)kmalloc(sizeof(Window_t));

//     all_windows[num_windows] = new_window;
//     num_windows++;
// }

// void draw_window(Window_t* w){
//     draw_tilebar(w);
// }

// void draw_tilebar(Window_t* w) {
//     // create background
//     putrect(0, 0, 320, 20, LIGHTGRAY);

//     // put the title text
    
// }