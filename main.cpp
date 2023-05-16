#include "ImageProcessing.cpp"

int main() {
    // Read the image
    char* filename = "input.ppm";
    char* outputName = "output.ppm";
    ImageProcessing imageProcessing(filename);

    // Convert the image to gray
    imageProcessing.convertToGray();

    // Apply edge detection
    imageProcessing.edgeDetection();

    // Write the image
    imageProcessing.getImage().write(outputName);
}
