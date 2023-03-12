#include "tile.h"

#include <envvars.h>

#include <memory/kmalloc.h>

int num_tiles = 0;             // counter of windows that exist
Tile_t *all_tiles[MAX_TILES];  // list of all window pointers

Tile_t *init_genesis_tile() { create_tile(NULL, 0); }

Tile_t *create_tile(Tile_t *parent, int tile_type) {
    Tile_t *new_tile = (Tile_t *)kmalloc(sizeof(Tile_t));

    new_tile->num_children = 0;
    new_tile->tile_type = tile_type;
    new_tile->parent = parent;

    all_tiles[num_tiles] = new_tile;
    num_tiles++;

    return new_tile;
}

void tile_add_child_tile(Tile_t *this, Tile_t *child) {
    if (this->tile_type != TILE_CHILDREN) return;
    if (this->num_children >= MAX_SUBELEMENTS) return;

    tile_change_parent(child, this);

    this->sub_tiles[this->num_children] = child;
    this->num_children++;
}

void tile_add_child_window(Tile_t *this, Window_t *child) {
    if (this->tile_type != WINDOW_CHILDREN) return;
    if (this->num_children >= MAX_SUBELEMENTS) return;

    this->sub_windows[this->num_children] = child;
    this->num_children++;
}

SUCCESS_STATUS_t tile_change_parent(Tile_t *this, Tile_t *new_parent) {
    // Verify the new parent is of correct type
    if (new_parent->tile_type != TILE_CHILDREN) return FAILURE;

    // Verify the new parent has enough size
    if (new_parent->num_children == MAX_SUBELEMENTS) return FAILURE;

    // Delete child from previous parent
    tile_remove_child(this->parent, (GENERIC_PTR_ARRAY)(this->parent->sub_tiles), this);

    // Reassign new parent
    this->parent = new_parent;

    // add child to new parent
    new_parent->sub_tiles[new_parent->num_children++] = this;

    return SUCCESS;
}

SUCCESS_STATUS_t tile_remove_child(Tile_t *this, GENERIC_PTR_ARRAY child_arr, void *child) {
    for (int child_index; child_index < MAX_SUBELEMENTS; child_index++) {
        if (child_arr[child_index] == child) {
            // child is found

            // there's no replacing to be done
            if (child_index == MAX_SUBELEMENTS) return FAILURE;

            // swap the tobedeleted child with the last child
            // and decrement the parent's num_children at the same time
            child_arr[child_index] = child_arr[(this->num_children--) - 1];
        }
    }

    return SUCCESS;
}