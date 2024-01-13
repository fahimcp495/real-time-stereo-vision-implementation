#ifndef IMAGE_STRUCT_H
#define IMAGE_STRUCT_H

typedef struct {
    int imagesize_x, imagesize_y;
    int **pixel;
} image_t;

#endif // IMAGE_STRUCT_H
