#include "automaton_2d.h"
#define FPS 5
#define SCALE 3

struct ycbcr
{
    char y;
    char cb;
    char cr;
} typedef ycbcr;

#define white (ycbcr){ .y=235, .cb=128, .cr=128, }
#define black (ycbcr){ .y=16, .cb=128, .cr=128, }
ycbcr colours[] = {black,white};

char* fbuff = 0;
void write_frame(FILE* file, int size) {
    int pixels_count=size*size;
    if(!fbuff)
        fbuff = (char*)malloc(pixels_count*3);
    fprintf(file, "FRAME\n");
    for (int j = 0; j < pixels_count; j++) {
        int y=j/size;
        int x=j%size;
        int original_x = x / SCALE;
        int original_y = y / SCALE;
        fbuff[j]=colours[two_d_map[original_x][original_y]].y;
        fbuff[j+pixels_count]=colours[two_d_map[original_x][original_y]].cb;
        fbuff[j+pixels_count*2]=colours[two_d_map[original_x][original_y]].cr;
    }
    fwrite(fbuff, pixels_count*3, 1, file);
}

void export_to_video(char* filename, int size, int number_of_gens, void (*ruleset)(void)) {
    FILE *file = fopen(filename, "w");
    int scaled_size=size*SCALE;
    fprintf(file, "YUV4MPEG2 W%d H%d F30:1 Ip A1:1 C444\n", scaled_size,scaled_size);
    for (int frame = 0; frame < number_of_gens; frame++) {
        if(frame>0)
            ruleset();
        for(int f = 0; f < 30/FPS; f++)
            write_frame(file,scaled_size);
        int progess = ((float)frame / number_of_gens) * 100;
        printf("Done: %d%%\r", progess);
        fflush(stdout);
    }
    fclose(file);
    free(fbuff);
    fbuff=0;
}