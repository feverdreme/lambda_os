#ifndef WINDOW_H
#define WINDOW_H

typedef struct Window {
    int posx;
    int posy;
    int tilebar_height;
    char* bodytext;
} Window_t;

extern const int MAXWINDOWS;
extern int num_windows;
extern Window_Entry_t **all_windows; // list of all window pointers

Window_t* create_window(int _posx, int _posy, int _th, char* _bodytext);

void draw_window(Window_t* w);
void draw_tilebar(Window_t* w);

#endif