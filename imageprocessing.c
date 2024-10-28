#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
int ***flip_horizontal(int ***image, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M / 2; j++) {
            for (int t = 0; t < 3; t++) {
                int cpy = image[i][j][t];
                image[i][j][t] = image[i][M-j-1][t];
                image[i][M-j-1][t] = cpy;
            }
        }
    }
    return image;
}
int ***rotate_left(int ***image, int N, int M) {
    int ***rotated_img = (int ***)malloc(M * sizeof(int **));
    for (int i = 0; i < M; i++) {
        rotated_img[i] = (int **)malloc(N * sizeof(int *));
        for (int j = 0; j < N; j++) {
            rotated_img[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }

       for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int t = 0; t < 3; t++) {
                rotated_img[M- 1 - j][i][t] = image[i][j][t];
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return rotated_img;
}
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***cropped_img = (int ***)malloc(h * sizeof(int **));
    for (int i = 0; i < h; i++) {
        cropped_img[i] = (int **)malloc(w * sizeof(int *));
        for (int j = 0; j < w; j++) {
            cropped_img[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    for (int i = 0, ii = y; i < h; i++, ii++) {
        for (int j = 0, ji = x; j < w; j++, ji++) {
            for (int t = 0; t < 3; t++) {
                cropped_img[i][j][t] = image[ii][ji][t];
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return cropped_img;
}
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int n_extd = 2 * rows + N;
    int m_extd = 2 * cols + M;
    int ***extended = (int ***)malloc(n_extd * sizeof(int **));
    for (int i = 0; i < n_extd; i++) {
        extended[i] = (int **)malloc(m_extd * sizeof(int *));
        for (int j = 0; j < m_extd; j++) {
            extended[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    for (int i = 0; i < n_extd; i++) {
        for (int j = 0; j< m_extd; j++) {
            if ((i >= rows && i <= rows + N - 1) && (j >= cols && j<= cols + M -1)) {
                for (int t = 0; t < 3; t++) {
                    extended[i][j][t] = image[i - rows][j - cols][t];
                }
            } else {
                extended[i][j][0] = new_R;
                extended[i][j][1] = new_G;
                extended[i][j][2] = new_B;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return extended;
}
int ***paste(int ***image_dst, int N_dst, int M_dst, int *** image_src, int N_src, int M_src, int x, int y) {
    for (int id = y, is = 0 ; id < N_dst && is < N_src; id++, is++) {
        for (int jd = x, js = 0; jd < M_dst && js < M_src; jd++, js++) {
            for (int t = 0; t < 3; t++) {
                image_dst[id][jd][t] = image_src[is][js][t];
            }
        }
    }
    return image_dst;
}
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    int ***filtered = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        filtered[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            filtered[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }
    int filter_offset = filter_size / 2;
    const float MAX_PIXEL_VALUE = 255;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            float Rs = 0, Gs = 0, Bs = 0;
            for (int t = -filter_offset; t <= filter_offset; t++) {
                for (int k = -filter_offset; k <= filter_offset; k++) {
                    if (i + t >= 0 && j + k >= 0 && i + t < N && j + k < M) {
                        Rs += (float)image[i + t][j + k][0] * filter[t + filter_offset][k + filter_offset];
                        Gs += (float)image[i + t][j + k][1] * filter[t + filter_offset][k + filter_offset];
                        Bs += (float)image[i + t][j + k][2] * filter[t + filter_offset][k + filter_offset];
                    }
                }
            }
            if (Rs < 0) {
                filtered[i][j][0] = 0;
            } else if (Rs > MAX_PIXEL_VALUE) {
                filtered[i][j][0] = (int)MAX_PIXEL_VALUE;
            } else {
                filtered[i][j][0] = (int)Rs;
            }
            if (Gs < 0) {
                filtered[i][j][1] = 0;
            } else if (Gs > MAX_PIXEL_VALUE) {
                filtered[i][j][1] = (int)MAX_PIXEL_VALUE;
            } else {
                filtered[i][j][1] = (int)Gs;
            }
            if (Bs < 0) {
                filtered[i][j][2] = 0;
            } else if (Bs > MAX_PIXEL_VALUE) {
                filtered[i][j][2] = (int)MAX_PIXEL_VALUE;
            } else {
                filtered[i][j][2] = (int)Bs;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return filtered;
}
