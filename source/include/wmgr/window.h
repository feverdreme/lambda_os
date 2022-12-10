#ifndef WINDOW_H
#define WINDOW_H

/* -------------------------------------------------------------------------- */
/*                                  CONSTANTS                                 */
/* -------------------------------------------------------------------------- */

#define MAX_WINDOWS 256

/* -------------------------------------------------------------------------- */
/*                                   Structs                                  */
/* -------------------------------------------------------------------------- */

typedef struct Window {
    int pos_x;
    int pos_y;
    int tilebar_height;
    const char* bodytext;
} Window_t;

/* -------------------------------------------------------------------------- */
/*                              Global Variables                              */
/* -------------------------------------------------------------------------- */

extern int num_windows; // counter of windows that exist
extern Window_t *all_windows[MAX_WINDOWS]; // list of all window pointers

/* -------------------------------------------------------------------------- */
/*                           Window Member Functions                          */
/* -------------------------------------------------------------------------- */

// Special init function
void init_genesis_window();

Window_t* create_window(int _pos_x, int _pos_y, int _th, char* _bodytext);

void window_draw_window(Window_t* w);
void window_draw_tilebar(Window_t* w);
void window_draw_body(Window_t* w);

#endif