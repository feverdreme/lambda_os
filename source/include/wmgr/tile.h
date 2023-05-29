#ifndef TILE_H
#define TILE_H
#ifdef __cplusplus
extern "C" {
#endif

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

// var counter of windows that exist
extern int num_tiles;

// list of all window pointers
extern Tile_t *all_tiles[MAX_TILES]; 

/* -------------------------------------------------------------------------- */
/*                                Tile Methods                                */
/* -------------------------------------------------------------------------- */

Tile_t* init_genesis_tile();

/* ------------------------------ Constructors ------------------------------ */

/**
 * @brief Create a tile object
 * 
 * @param tile_type 
 * @return Tile_t* 
 */
Tile_t* create_tile(int tile_type);

/**
 * @brief Create a tile object of TILE_CHILDREN type
 * 
 * @param parent What tile this one will belong to 
 * @return Tile_t* 
 */
Tile_t* create_tile_tile(Tile_t *parent);

/**
 * @brief Create a tile object of WINDOW_CHILDREN type
 * 
 * @param child Window to be assigned its child 
 * @return Tile_t* 
 */
Tile_t* create_window_tile(Window_t *child);

/* ------------------------- Parent and Child Logic ------------------------- */

SUCCESS_STATUS_t tile_add_child_tile(Tile_t *this, Tile_t *child);
SUCCESS_STATUS_t tile_add_child_window(Tile_t *this, Window_t *child);
SUCCESS_STATUS_t tile_change_parent(Tile_t *this, Tile_t *new_parent);
SUCCESS_STATUS_t tile_remove_child(Tile_t *this, Tile_t *child);

/* -------------------------------- Rendering ------------------------------- */

/**
 * @brief Draws a tile recursively. 
 * Keeps recursing on children until it finds a WINDOW_CHILDREN element and has seperate logic to handle it.
 * Uses tile_draw_2x2 and tile_draw_rowcol methods depending on the geometry of the tile.
 * 
 * @param this 
 * @param x X position of the tile
 * @param y Y position of the tile
 * @param width Width of the tile
 * @param height Height of the tile
 */
void tile_draw(Tile_t *this, int x, int y, int width, int height);

/**
 * @brief Draws a 2x2 geometry of tile children.
 * 
 * \pre Parent has 4 children
 * \pre Aspect ratio >= 4
 * 
 * @param this 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 */
void tile_draw_2x2(Tile_t *this, int x, int y, int width, int height);

/**
 * @brief Draws children in order. Optimizes for aspect ratio.
 * Picks either in a row or col depending on which side is longer. 
 * 
 * @param this 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 */
void tile_draw_rowcol(Tile_t *this, int x, int y, int width, int height);

/* -------------------------------------------------------------------------- */
/*                              Utility Functions                             */
/* -------------------------------------------------------------------------- */
bool tile_has_child_tile(Tile_t *this, Tile_t *child);

#ifdef __cplusplus
}
#endif
#endif