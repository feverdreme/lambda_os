#ifndef VIRTM_H
#define VIRTM_H

/**
 * @brief Translates a virtual address into the physical one
 * 
 * @param vaddr Virtual address
 * @return void* 
 */
void *translate_virtaddr(void *vaddr);

#endif