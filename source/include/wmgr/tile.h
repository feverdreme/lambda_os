#ifndef TILE_H
#define TILE_H

#include <envvars.h>

#include <stdbool.h>

#include <wmgr/window.h>

/* -------------------------------------------------------------------------- */
/*                                  Constants                                 */
/* -------------------------------------------------------------------------- */

#define MAX_TILES 16
#define MAX_SUBELEMENTS 4

/* -------------------------------------------------------------------------- */
/*                                   Structs                                  */
/* -------------------------------------------------------------------------- */

enum Tile_Type {
    TILE_CHILDREN,
    WINDOW_CHILDREN
};

/**
 * @struct Tile
 * @brief Tile struct for the tiliing system. Its children can either be tiles or windows but cannot be both.
 */
typedef struct Tile {
    int num_children;

    /// @brief What type of children the instance has
    enum Tile_Type tile_type;
    
    struct Tile* sub_tiles[MAX_SUBELEMENTS];
    Window_t* child_window;

    struct Tile* parent;
} Tile_t;

/* -------------------------------------------------------------------------- */
/*                              Global Variables                              */
/* -------------------------------------------------------------------------- */

extern int num_tiles; // counter of windows that exist
extern Tile_t *all_tiles[MAX_TILES]; // list of all window pointers

/* -------------------------------------------------------------------------- */
/*                                Tile Methods                                */
/* -------------------------------------------------------------------------- */

Tile_t* init_genesis_tile();

Tile_t* create_tile(int tile_type);
SUCCESS_STATUS_t tile_add_child_tile(Tile_t *this, Tile_t *child);
SUCCESS_STATUS_t tile_add_child_window(Tile_t *this, Window_t *child);
SUCCESS_STATUS_t tile_change_parent(Tile_t *this, Tile_t *new_parent);
SUCCESS_STATUS_t tile_remove_child(Tile_t *this, Tile_t *child);

/**
 * @brief Draws a tile recursively.
 * 
 * @param this 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 * @return * void 
 */
void tile_draw(Tile_t *this, int x, int y, int width, int height);

void tile_draw_2x2(Tile_t *this, int x, int y, int width, int height);

void tile_draw_rowcol(Tile_t *this, int x, int y, int width, int height);

/* -------------------------------------------------------------------------- */
/*                              Utility Functions                             */
/* -------------------------------------------------------------------------- */
bool tile_has_child_tile(Tile_t *this, Tile_t *child);

#endif