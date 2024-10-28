#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageprocessing.h"
#include "bmp.h"
void free3D(int ***matrix, int d1, int d2) {
    for (int i = 0; i < d1; i++) {
        for (int j = 0; j < d2; j++) {
        free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}
int main() {
    const int MAX_COMD = 5;
    char comd[MAX_COMD];
    int no_pict = 0, ind = 0, N = 0, M = 0, no_filters = 0;
    const int MAX_PATH = 100;
    char path[MAX_PATH];
    int ****image = NULL;
    float ***filter = NULL;
    int *lines = NULL;
    int *cols = NULL;
    int *filter_size = NULL;
    while (scanf("%s ", comd)) {
        if (strcmp(comd, "e") == 0) {
            break;
        }
        if (strcmp(comd, "l") == 0) {
            scanf("%d %d %s ", &N, &M, path);
            no_pict++;
            image = (int ****)realloc(image, no_pict * sizeof(int ***));
            image[no_pict - 1] = (int ***)malloc(N * sizeof(int **));
            for (int i = 0; i < N; i++) {
                    image[no_pict - 1][i] = (int **)malloc(M * sizeof(int *));
                    for (int j = 0; j < M; j++) {
                    image[no_pict - 1][i][j] = (int *)malloc(3 * sizeof(int));
                    }
            }
            read_from_bmp(image[no_pict - 1], N, M, path);
            lines = (int*)realloc(lines, no_pict * sizeof(int));
            cols = (int*)realloc(cols, no_pict * sizeof(int));
            lines[no_pict - 1] = N;
            cols[no_pict - 1] = M;
        }
        if (strcmp(comd, "s") == 0) {
            scanf("%d %s ", &ind, path);
            write_to_bmp(image[ind], lines[ind], cols[ind], path);
        }
        if (strcmp(comd, "ah") == 0) {
            scanf("%d ", &ind);
            flip_horizontal(image[ind], lines[ind], cols[ind]);
        }
        if (strcmp(comd, "ar") == 0) {
            scanf("%d ", &ind);
            int ***rot = NULL;
            rot = rotate_left(image[ind], lines[ind], cols[ind]);
            image[ind] = (int ***)malloc(cols[ind] * sizeof(int**));
            for (int i = 0; i < cols[ind]; i++) {
                    image[ind][i] = (int **)malloc(lines[ind] * sizeof(int *));
                    for (int j = 0; j < lines[ind]; j++) {
                    image[ind][i][j] = (int *)malloc(3 * sizeof(int));
                    }
            }
            for (int i = 0; i < cols[ind]; i++) {
                for (int j = 0; j < lines[ind]; j++) {
                    for (int k = 0; k < 3; k++) {
                        image[ind][i][j][k] = rot[i][j][k];
                    }
                }
            }
            free3D(rot, cols[ind], lines[ind]);
            int aux = cols[ind];
            cols[ind] = lines[ind];
            lines[ind] = aux;
        }
        if (strcmp(comd, "ac") == 0) {
            int x = 0, y = 0, w = 0, h = 0;
            scanf("%d %d %d %d %d ",  &ind, &x, &y, &w, &h);
            int ***cr = NULL;
            cr = crop(image[ind], lines[ind], cols[ind], x, y, h, w);
            image[ind] = (int ***)malloc(h * sizeof(int**));
            for (int i = 0; i < h; i++) {
                    image[ind][i] = (int **)malloc(w * sizeof(int *));
                    for (int j = 0; j < w; j++) {
                    image[ind][i][j] = (int *)malloc(3 * sizeof(int));
                    }
            }
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    for (int k = 0; k < 3; k++) {
                        image[ind][i][j][k] = cr[i][j][k];
                    }
                }
            }
            free3D(cr, h, w);
            lines[ind] = h;
            cols[ind] = w;
        }
        if (strcmp(comd, "ae") == 0) {
            int ro = 0, co = 0, R = 0, G = 0, B = 0;
            scanf("%d %d %d %d %d %d ",  &ind, &ro, &co, &R, &G, &B);
            int new_lines = 2 * ro + lines[ind];
            int new_cols = 2 * co + cols[ind];
            int ***ex = NULL;
            ex = extend(image[ind], lines[ind], cols[ind], ro, co, R, G, B);
            image[ind] = (int ***)malloc(new_lines * sizeof(int**));
            for (int i = 0; i < new_lines; i++) {
                    image[ind][i] = (int **)malloc(new_cols * sizeof(int *));
                    for (int j = 0; j < new_cols; j++) {
                    image[ind][i][j] = (int *)malloc(3 * sizeof(int));
                    }
            }
            for (int i = 0; i < new_lines; i++) {
                for (int j = 0; j < new_cols; j++) {
                    for (int k = 0; k < 3; k++) {
                        image[ind][i][j][k] = ex[i][j][k];
                    }
                }
            }
            free3D(ex, new_lines, new_cols);
            lines[ind] = new_lines;
            cols[ind] = new_cols;
        }
        if (strcmp(comd, "ap") == 0) {
            int im_d = 0, im_s = 0, x = 0, y = 0;
            scanf("%d %d %d %d ", &im_d, &im_s, &x, &y);
            paste(image[im_d], lines[im_d], cols[im_d], image[im_s], lines[im_s], cols[im_s], x, y);
        }
        if (strcmp(comd, "cf") == 0) {
            int size = 0;
            scanf("%d ", &size);
            no_filters++;
            filter = (float***)realloc(filter, no_filters * sizeof(float **));
            filter[no_filters - 1] = (float **)malloc(size * sizeof(float *));
            for (int i = 0; i < size; i++) {
                filter[no_filters - 1][i] = (float *)malloc(size * sizeof(float));
            }
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    scanf("%f ", &filter[no_filters - 1][i][j]);
                }
            }
            filter_size = (int*)realloc(filter_size, no_filters * sizeof(int));
            filter_size[no_filters -1] = size;
        }
        if (strcmp(comd, "af") == 0) {
            int i_im = 0, i_fil = 0;
            scanf("%d %d ", &i_im, &i_fil);
            int ***filt_img = NULL;
            filt_img = apply_filter(image[i_im], lines[i_im], cols[i_im], filter[i_fil], filter_size[i_fil]);
            image[i_im] = (int ***)malloc(lines[i_im] * sizeof(int**));
            for (int i = 0; i < lines[i_im]; i++) {
                    image[i_im][i] = (int **)malloc(cols[i_im] * sizeof(int *));
                    for (int j = 0; j < cols[i_im]; j++) {
                    image[i_im][i][j] = (int *)malloc(3 * sizeof(int));
                    }
            }
            for (int i = 0; i < lines[i_im]; i++) {
                for (int j = 0; j < cols[i_im]; j++) {
                    for (int k = 0; k < 3; k++) {
                        image[i_im][i][j][k] = filt_img[i][j][k];
                    }
                }
            }
            free3D(filt_img, lines[i_im], cols[i_im]);
        }
        if (strcmp(comd, "df") == 0) {
            int i_fil = 0;
            scanf("%d ", &i_fil);
            for (int i = 0; i < filter_size[i_fil]; i++) {
                free(filter[i_fil][i]);
            }
            free(filter[i_fil]);
            for (int i = i_fil; i < no_filters - 1; i++) {
                filter[i] = filter[i + 1];
                filter_size[i] = filter_size[i + 1];
            }
            no_filters--;
            filter = (float ***)realloc(filter, no_filters * sizeof(float **));
            filter_size = (int *)realloc(filter_size, no_filters * sizeof(int));
        }
        if (strcmp(comd, "di") == 0) {
            int index_imag = 0;
            scanf("%d ", &index_imag);
            for (int i = 0; i < lines[index_imag]; i++) {
                for (int j = 0; j < cols[index_imag]; j++) {
                    free(image[index_imag][i][j]);
                }
                free(image[index_imag][i]);
            }
            free(image[index_imag]);
            for (int i = index_imag; i < no_pict - 1; i++) {
                image[i] = image[i + 1];
                lines[i] = lines[i + 1];
                cols[i] = cols[i + 1];
            }
            no_pict--;
            image = (int ****)realloc(image, no_pict * sizeof(int ***));
            lines = (int *)realloc(lines, no_pict * sizeof(int));
            cols = (int *)realloc(cols, no_pict * sizeof(int));
        }
    }
    for (int i = 0; i < no_filters; i++) {
        int no_lines = filter_size[i];
        float **current_filter = filter[i];
        for (int j = 0; j < no_lines; j++) {
            free(current_filter[j]);
        }
        free(current_filter);
    }
    free(filter);
    for (int i =0; i < no_pict; i++) {
        int ***current_img = image[i];
        int no_lines = lines[i];
        int no_cols = cols[i];
        if (current_img != NULL) {
            for (int lin = 0; lin < no_lines; lin++) {
                if (current_img[lin] != NULL) {
                    for (int col = 0; col < no_cols; col++) {
                        if (current_img[lin][col] != NULL) {
                            free(current_img[lin][col]);
                        }
                    }
                    free(current_img[lin]);
                }
            }
            free(current_img);
        }
    }
    free(image);
    free(lines);
    free(cols);
    free(filter_size);
    return 0;
}
