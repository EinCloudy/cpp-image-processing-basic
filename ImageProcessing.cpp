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

        // Get the image dimensions
        int width = image->getWidth();
        int height = image->getHeight();

        // Create a new array to store the filtered pixels
        Pixel *pixels = image->getPixels();
        Pixel *newPixels = new Pixel[width * height];

        // Iterate over the pixels in the image
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;

                // Apply the filter to the pixel in the 3x3 grid
                for(int j = -1; j <= 1; j++) {
                    for(int i = -1; i <= 1; i++) {
                        // The value of the filter at the current position
                        int filterValue = doubleFilter[j + 1][i + 1];

                        // The x and y coordinates of the pixel to apply the filter to
                        int x2 = x + i;
                        int y2 = y + j;

                        // Only apply the filter to pixels within the image
                        if(x2 >= 0 && x2 < width && y2 >= 0 && y2 < height) {
                            Pixel pixel = pixels[y2 * width + x2];
                            sumR += pixel.r * filterValue;
                            sumG += pixel.g * filterValue;
                            sumB += pixel.b * filterValue;
                        }
                    }
                }

                // Clamp the values to the range [0, 255]
                newPixels[y * width + x].r = max(0, min(255, sumR));
                newPixels[y * width + x].g = max(0, min(255, sumG));
                newPixels[y * width + x].b = max(0, min(255, sumB));
            }
        }

        // Update the original image with the filtered pixels
        for(int i = 0; i < width * height; i++) {
            pixels[i] = newPixels[i];
        }

        // Free the memory allocated for the new pixels
        delete[] newPixels;

        printf("Applied edge detection\n");
    }
};
