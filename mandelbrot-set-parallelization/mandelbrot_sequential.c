#include <stdio.h>
#include <time.h>

#define IMG_WIDTH 800
#define IMG_HEIGHT 800
#define MAX_ITERATIONS 1000

typedef struct {
    unsigned char r, g, b;
} Color;

void saveImage(Color image[IMG_WIDTH][IMG_HEIGHT]) {
    FILE *fp;
    fp = fopen("mandelbrot.ppm", "wb");
    fprintf(fp, "P6\n%d %d\n255\n", IMG_WIDTH, IMG_HEIGHT);
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            fwrite(&image[j][i], 1, 3, fp);
        }
    }
    fclose(fp);
}

int mandelbrot(double x, double y) {
    double real = 0.0, imag = 0.0;
    int iterations = 0;
    while (real * real + imag * imag <= 4.0 && iterations < MAX_ITERATIONS) {
        double temp = real * real - imag * imag + x;
        imag = 2.0 * real * imag + y;
        real = temp;
        iterations++;
    }
    return iterations;
}

int main() {
    Color image[IMG_WIDTH][IMG_HEIGHT];

    clock_t start_time = clock();  // Start the timer

    for (int i = 0; i < IMG_WIDTH; i++) {
        for (int j = 0; j < IMG_HEIGHT; j++) {
            double x = (i - IMG_WIDTH/2.0) * 4.0 / IMG_WIDTH;
            double y = (j - IMG_HEIGHT/2.0) * 4.0 / IMG_WIDTH;
            int iterations = mandelbrot(x, y);
            unsigned char colorValue = (unsigned char)(255 * iterations / MAX_ITERATIONS);
            Color pixelColor = {colorValue, colorValue, colorValue};
            image[i][j] = pixelColor;
        }
    }

    clock_t end_time = clock();  // End the timer

    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Sequential Time taken to generate the Mandelbrot set: %.4f seconds\n", elapsed_time);

    saveImage(image);

    return 0;
}
