#ifndef KDMSG_H
#define KDMSG_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Kernel Debug MeSsaGe. Wrapper for putting a debug message to the screen.
 * 
 */
void kdmsg(const char* msg);

#ifdef __cplusplus
}
#endif
#endif