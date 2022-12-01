#ifndef WINDOW_H
#define WINDOW_H

typedef struct Window {
    int posx;
    int posy;
    int tilebar_height;
    char* bodytext;
} Window_t;

int num_windows = 0;
Window_t* total_windows[256]; // maximum windows allowed

void create_window(int _posx, int _posy, int _th, char* _bodytext) {
    if (num_windows >= 256) return; // this should give an error but ok

    return;
}

#endif