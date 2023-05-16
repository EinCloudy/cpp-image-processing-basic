#include <string>
#include <cstdio>

using namespace std;


typedef struct {
    unsigned char r, g, b;
} Pixel;

class PPM {
private:
    char magicNum[3];
    int width, height, maxVal;
    Pixel* pixels;


public:
    PPM(const char* filename) {
        // Open the file
        FILE* file = fopen(filename, "r");
        if (file == nullptr) {
            fprintf(stderr, "Failed to open file: %s\n", filename);
            return;
        }

        // Read the file header
        if (fscanf(file, "%2s %d %d %d", magicNum, &width, &height, &maxVal) != 4) {
            fprintf(stderr, "Failed to read magic number, width, height, and maxVal\n");
            fclose(file);
            return;
        }

        // Allocate memory for the pixels
        pixels = (Pixel*)malloc(sizeof(Pixel) * width * height);

        // Read the pixels
        for (int i = 0; i < width * height; i++) {
            int r, g, b;
            if (fscanf(file, "%d %d %d", &r, &g, &b) != 3) {
                fprintf(stderr, "Failed to read pixel values\n");
                fclose(file);
                free(pixels);
                return;
            }
            pixels[i].r = r;
            pixels[i].g = g;
            pixels[i].b = b;
        }

        // Close the file
        fclose(file);

        printf("Magic Number: %s\n", magicNum);
        printf("Width: %d\n", width);
        printf("Height: %d\n", height);
    }




    Pixel* getPixels() {
        return pixels;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    int getMaxVal() {
        return maxVal;
    }

    void write(const char* filename) {
        // Open the file
        FILE* file = fopen(filename, "w");

        // Check if the file could be opened
        if (file == nullptr) {
            fprintf(stderr, "Failed to open file: %s\n", filename);
            return;
        }

        // Write the file header
        fprintf(file, "P3\n%d %d\n%d\n", width, height, maxVal);
        for (int i = 0; i < width * height; i++) {
            fprintf(file, "%d %d %d ", pixels[i].r, pixels[i].g, pixels[i].b);
        }

        // Close the file
        fclose(file);
    }


};

