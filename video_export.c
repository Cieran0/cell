#include "automaton_2d.h"
#define FPS 5
#define SCALE 3

struct ycbcr
{
    char y;  // Luma component
    char cb; // Chroma blue component
    char cr; // Chroma red component
} typedef ycbcr;

#define white (ycbcr){ .y=235, .cb=128, .cr=128, }
#define black (ycbcr){ .y=16, .cb=128, .cr=128, }
ycbcr colours[] = {black, white}; 

char* frame_buffer = 0;

// Function to write a frame to a video file
void write_frame(FILE* file, int size) {
    int pixels_count = size * size; 

    // Only allocate if not already allocated
    if (!frame_buffer)
        frame_buffer = (char*)malloc(pixels_count * 3);

    fprintf(file, "FRAME\n");

    for (int j = 0; j < pixels_count; j++) {
        int y = j / size;
        int x = j % size;

        // Scale the pixel coordinates to get the corresponding coordinates in the board
        int original_x = x / SCALE;
        int original_y = y / SCALE;

        // Get the state of the cell from the board
        int is_alive = board[original_x][original_y];

        frame_buffer[j] = colours[is_alive].y;
        frame_buffer[j + pixels_count] = colours[is_alive].cb;
        frame_buffer[j + pixels_count * 2] = colours[is_alive].cr;
    }

    // Write the frame data to video file
    fwrite(frame_buffer, pixels_count * 3, 1, file);
}

// Export to a YUV4MPEG2 video file
void export_to_video(char* filename, int size, int number_of_gens, void (*ruleset)(void)) {
    FILE* file = fopen(filename, "w");

    int scaled_size = size * SCALE;

    // Header for the video file
    fprintf(file, "YUV4MPEG2 W%d H%d F30:1 Ip A1:1 C444\n", scaled_size, scaled_size);

    for (int frame = 0; frame < number_of_gens; frame++) {

        if (frame > 0)
            ruleset();

        // Write frames to the video file, repeating each frame for a fraction of a second (FPS)
        for (int f = 0; f < 30 / FPS; f++)
            write_frame(file, scaled_size);

        int progress = ((float)frame / number_of_gens) * 100;
        printf("Done: %d%%\r", progress);
        fflush(stdout);
    }

    fclose(file); 
    free(frame_buffer);
    frame_buffer = 0;
}