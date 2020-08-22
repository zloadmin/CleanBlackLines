#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

bool isBlackPixel(Vec3b bgrPixel);
int getPercentOfBlackPixels(double black_pixels, double row);

const int BLACK_LIMIT = 27;
const int PERCENT_OF_BLACK = 75;

int main(int argc, char **argv) {
    if ( argc != 2 )
    {
        printf("usage: CleanBlackLines <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], 1 );
    if (!image.data) {
        printf("No image data \n");
        return -1;
    }
    int black_pixels[image.cols];
    bool changed = false;
    for (int i = 0; i < image.rows; i++) {
        black_pixels[i] = 0;
        for (int j = 0; j < image.cols; j++) {
            Vec3b bgrPixel = image.at<Vec3b>(i, j);
            if (isBlackPixel(bgrPixel)) {
                black_pixels[i]++;
            }
        }
        int p = getPercentOfBlackPixels(black_pixels[i], image.cols);
        if (p > PERCENT_OF_BLACK) {
            changed = true;
            for (int j = 0; j < image.cols; j++) {
                Vec3b bgrPixel = image.at<Vec3b>(i, j);
                bgrPixel[0] = 0;
                bgrPixel[1] = 0;
                bgrPixel[2] = 0;
                image.at<Vec3b>(i, j) = bgrPixel;
            }
        }
    }
    if(changed) {
        printf("Detected black lines, file will change\n");
        try {
            imwrite("test.jpg", image);
        }
        catch (runtime_error &ex) {
            fprintf(stderr, "Exception save image to JPG format: %s\n", ex.what());
            return 1;
        }
        fprintf(stdout, "Saved JPG file.\n");
        return 0;
    }

    waitKey(0);

    return 0;
}

bool isBlackPixel(Vec3b bgrPixel) {
    int B = bgrPixel.val[0];
    int G = bgrPixel.val[1];
    int R = bgrPixel.val[2];
    return R <= BLACK_LIMIT && G <= BLACK_LIMIT && B <= BLACK_LIMIT;
}

int getPercentOfBlackPixels(double black_pixels, double row) {
    return black_pixels > 0 ? black_pixels / row * 100 : 0;
}