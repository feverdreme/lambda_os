#include "tile.h"

#include <envvars.h>
#include <memory/kmalloc.h>

int num_tiles = 0;             // counter of windows that exist
Tile_t *all_tiles[MAX_TILES];  // list of all window pointers

Tile_t *init_genesis_tile() { return create_tile(TILE_CHILDREN); }

Tile_t *create_tile(int tile_type) {
    Tile_t *new_tile = (Tile_t *)kmalloc(sizeof(Tile_t));

    new_tile->num_children = 0;
    new_tile->tile_type = tile_type;
    new_tile->child_window = NULL;

    all_tiles[num_tiles] = new_tile;
    num_tiles++;

    return new_tile;
}

SUCCESS_STATUS_t tile_add_child_tile(Tile_t *this, Tile_t *child) {
    if (this->tile_type != TILE_CHILDREN) return FAILURE;
    if (this->num_children >= MAX_SUBELEMENTS) return FAILURE;
    
    if (child->parent != this) {
        // make it so tile_change_parent doesn't do this wrong
        child->parent = this;
    };

    this->sub_tiles[this->num_children] = child;
    this->num_children++;

    return SUCCESS;
}

void tile_add_child_window(Tile_t *this, Window_t *child) {
    if (this->tile_type != WINDOW_CHILDREN) return;

    if (this->child_window != NULL) {
        // we must prevent the memory leaks
        window_destroy_window(this->child_window);
    }

    this->child_window = child;
}

SUCCESS_STATUS_t tile_change_parent(Tile_t *this, Tile_t *new_parent) {
    // Verify the new parent is a tile_children tile
    if (new_parent->tile_type != TILE_CHILDREN) return FAILURE;

    // Verify the new parent has enough size
    if (new_parent->num_children == MAX_SUBELEMENTS) return FAILURE;

    if (this->parent == new_parent) return SUCCESS;

    // Delete child from previous parent
    if (this->parent != NULL) {
        tile_remove_child(this->parent, this);
    }

    // Reassign new parent
    this->parent = new_parent;

    // add child to new parent
    tile_add_child_tile(this->parent, this);

    return SUCCESS;
}

SUCCESS_STATUS_t tile_remove_child(Tile_t *this, Tile_t *child) {
    for (int child_index; child_index < MAX_SUBELEMENTS; child_index++) {
        if (this->sub_tiles[child_index] == child) {
            // child is found
            if (child_index == this->num_children) {
                // there's no replacing to be done
                this->num_children--;
            } else {
                // swap the tobedeleted child with the last child
                // and decrement the parent's num_children at the same time
                this->sub_tiles[child_index] = this->sub_tiles[(this->num_children--) - 1];
            }

            return SUCCESS;
        }
    }

    return FAILURE;
}

void tile_draw(Tile_t *this, int x, int y, int width, int height) {
    if (this->tile_type == WINDOW_CHILDREN) {
        window_update_xywh(this->child_window, x, y, width, height);
        window_draw_window(this->child_window);
        return;
    }

    if (this->num_children == 0) return;

    if (width >= 4 * height || height >= 4 * width)
        tile_draw_2x2(this, x, y, width, height);
    else
        tile_draw_rowcol(this, x, y, width, height);        
}

void tile_draw_rowcol(Tile_t *this, int x, int y, int width, int height) {
    int child_width = width;
    int child_width_offset = 0;
    int child_height = height;
    int child_height_offset = 0;
    
    if (width > height) {
        child_width /= this->num_children;
        child_width_offset = child_width;
    } else {
        child_height /= this->num_children;
        child_height_offset = child_height;
    }

    for (int child_index = 0; child_index < this->num_children; child_index++) {
        tile_draw(
            this->sub_tiles[child_index],
            x + child_index * child_width_offset,
            y + child_index * child_height_offset,
            child_width,
            child_height
        );
    }
}

void tile_draw_2x2(Tile_t *this, int x, int y, int width, int height) {
    int child_xs[2] = {x, x + width / 2};
    int child_ys[2] = {y, y + height / 2};
    int child_ws[2] = {width / 2, width - width / 2};
    int child_hs[2] = {height / 2, height - height / 2};

    for (int x_ind = 0; x_ind < 2; x_ind++) {
        for (int y_ind = 0; y_ind < 2; y_ind++) {
            tile_draw(this->sub_tiles[x_ind * 2 + y_ind],
                        child_xs[x_ind],
                        child_ys[y_ind],
                        child_ws[x_ind],
                        child_hs[y_ind]
            );
        }
    }
}