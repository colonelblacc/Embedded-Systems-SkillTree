#include "ring_buffer.h"
#include "stdio.h"

// --- MAIN FUNCTION TO VISUALLY TEST THE PROCESS ---
int main(void) {
    int read_data;

    printf("=== CIRCULAR BUFFER VISUALIZER ===\n");
    printf("Buffer Size: %d\n\n", Buffer_Size);

    // 1. Fill the buffer completely
    printf("--- 1. FILLING THE BUFFER ---\n");
    for(int i = 1; i <= Buffer_Size; i++) {
        int value = i * 10;
        printf("Writing: %d\n", value);
        API_WriteToBuffer(value);
        printf("  [Head: %d | Tail: %d | Count: %d]\n", Head, Tail, count);
    }

    // 2. Try to write when full
    printf("\n--- 2. TRYING TO OVERFILL ---\n");
    printf("Writing: 999\n");
    API_WriteToBuffer(999);
    printf("  [Head: %d | Tail: %d | Count: %d]\n", Head, Tail, count);

    // 3. Read some data to make room
    printf("\n--- 3. READING 3 ITEMS ---\n");
    for(int i = 0; i < 3; i++) {
        API_ReadfromBuffer(&read_data);
        printf("Read out: %d\n", read_data);
        printf("  [Head: %d | Tail: %d | Count: %d]\n", Head, Tail, count);
    }

    // 4. Force the Wrap-Around!
    printf("\n--- 4. WRITING AGAIN (WATCH THE HEAD WRAP AROUND) ---\n");
    printf("Writing: 100\n");
    API_WriteToBuffer(100);
    printf("  [Head: %d | Tail: %d | Count: %d]\n", Head, Tail, count);
    
    printf("Writing: 200\n");
    API_WriteToBuffer(200);
    printf("  [Head: %d | Tail: %d | Count: %d]\n", Head, Tail, count);

    // 5. Empty the buffer completely
    printf("\n--- 5. EMPTYING THE REST OF THE BUFFER ---\n");
    while(!Is_bufferempty()) {
        API_ReadfromBuffer(&read_data);
        printf("Read out: %d\n", read_data);
        printf("  [Head: %d | Tail: %d | Count: %d]\n", Head, Tail, count);
    }

    // 6. Try to read when empty
    printf("\n--- 6. TRYING TO READ FROM EMPTY ---\n");
    API_ReadfromBuffer(&read_data);

    return 0;
}