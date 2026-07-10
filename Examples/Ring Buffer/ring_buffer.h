#ifndef RING_BUFFER_H
#define RING_BUFFER_H

/* * By using 'extern', we tell other files: 
 * "These variables exist somewhere else in the project, I promise!"
 * We expose them here so main.c can print them for our visualizer.
 */
extern int Head;
extern int Tail;
extern int count;
extern int Buffer_Size;

// --- Function Prototypes (The Menu) ---
void API_WriteToBuffer(int data_element);
void API_ReadfromBuffer(int *data_element);
int Is_bufferfull(void);
int Is_bufferempty(void);

#endif // CIRCULAR_BUFFER_H