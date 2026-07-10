#include <stdio.h>
#include "ring_buffer.h"



// These live OUTSIDE the functions so they remember their values
int Head = 0;
int Tail = 0;
int count = 0;
int Buffer_Size = 10; // Example size
int Buffer[10];       // Example array

void API_WriteToBuffer(int data_element){
    // 1. Check if full using our count variable
    if(count == Buffer_Size){
        printf("\nBuffer is Full! Dropping data.");
    }else{
        // 2. Write data
        Buffer[Head] = data_element;
        
        // 3. Move Head forward (and wrap around)
        Head = (Head + 1) % Buffer_Size;
        
        // 4. Increase the count
        count++; 
    }
}

// FIXED: Notice the '*' so we can modify the variable passed to us
void API_ReadfromBuffer(int *data_element){
    if(count == 0){
        printf("\nBuffer is Empty");
    }else{
        // FIXED: Typo corrected and pointer dereferenced
        *data_element = Buffer[Tail];
        
        Tail = (Tail + 1) % Buffer_Size;
        count--;
    }
}


int Is_bufferfull(void){
    if (count == Buffer_Size) {
        return 1; // True
    }
    return 0; // False
}

int Is_bufferempty(void){
    if (count == 0) {
        return 1; // True
    }
    return 0; // False
}