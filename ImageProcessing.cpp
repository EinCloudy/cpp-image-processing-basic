#include "PPM.cpp"

using namespace std;


class ImageProcessing {
private:
    PPM *image;
    double doubleFilter[3][3] = {{-1, -1, -1},
                                 {-1, 8, -1},
                                 {-1, -1, -1}};
public:
    ImageProcessing(char* filename) {
        image = new PPM(filename);
        printf("Image loaded\n");
    }

    PPM getImage() {
        return *image;
    }

    void convertToGray() {
        printf("Converting to gray\n");
        Pixel *pixels = image->getPixels();
        for(int i=0; i<image->getWidth()*image->getHeight(); i++) {
            int gray = (pixels[i].r + pixels[i].g + pixels[i].b) / 3;
            pixels[i].r = gray;
            pixels[i].g = gray;
            pixels[i].b = gray;
        }
        printf("Converted to gray\n");
    }

    void edgeDetection() {
        printf("Applying edge detection\n");

        // Create a new array to store the filtered pixels
        Pixel *pixels = image->getPixels();
        Pixel *newPixels = (Pixel*)malloc(sizeof(Pixel) * image->getWidth() * image->getHeight());

        // Apply the filter to each pixel
        for(int i = 0; i < image->getWidth() * image->getHeight(); i++) {

            // The x coordinate is the remainder of i divided by the width
            int x = i % image->getWidth();

            // The y coordinate is the integer division of i by the width
            int y = i / image->getWidth();

            int sumR = 0;
            int sumG = 0;
            int sumB = 0;

            // Apply the filter to the pixels around the current pixel
            for(int j = -1; j <= 1; j++) {
                for(int k = -1; k <= 1; k++) {
                    // The value of the filter at the current position
                    int filterValue = doubleFilter[k + 1][j + 1];

                    // The x and y coordinates of the pixel to apply the filter to
                    int x2 = x + j;
                    int y2 = y + k;

                    // Only apply the filter to pixels within the image
                    if(x2 >= 0 && x2 < image->getWidth() && y2 >= 0 && y2 < image->getHeight()) {
                        sumR += pixels[y2 * image->getWidth() + x2].r * filterValue;
                        sumG += pixels[y2 * image->getWidth() + x2].g * filterValue;
                        sumB += pixels[y2 * image->getWidth() + x2].b * filterValue;
                    }
                }
            }

            // Clamp the values to the range [0, 255]
            newPixels[i].r = max(0, min(255, sumR));
            newPixels[i].g = max(0, min(255, sumG));
            newPixels[i].b = max(0, min(255, sumB));
        }

        // Update the original image with the filtered pixels
        for(int i = 0; i < image->getWidth() * image->getHeight(); i++) {
            pixels[i].r = newPixels[i].r;
            pixels[i].g = newPixels[i].g;
            pixels[i].b = newPixels[i].b;
        }

        // Free the memory allocated for the new pixels
        free(newPixels);
        printf("Applied edge detection\n");
    }
};
