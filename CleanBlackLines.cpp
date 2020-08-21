#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

bool isBlackPixel(Vec3b bgrPixel);

int getPercentOfBlackPixels(double black_pixels, double row);
vector<bool> getBlackLines(Mat image);
vector<Vec3b> getNewImage(Mat image, vector<bool> black_lines);

const int BLACK_LIMIT = 27;
const int PERCENT_OF_BLACK = 75;

int main(int argc, char **argv) {
//    if ( argc != 2 )
//    {
//        printf("usage: DisplayImage.out <Image_Path>\n");
//        return -1;
//    }

    Mat image;
//    image = imread( argv[1], 1 );
    image = imread("1.jpg", 1);

    if (!image.data) {
        printf("No image data \n");
        return -1;
    }
    vector<bool> black_lines = getBlackLines(image);
    vector<Vec3b> new_image = getNewImage(image, black_lines);

//    for(int i=0; i<black_lines.size(); ++i)
//        cout << black_lines[i] << "\n";

//    namedWindow("Display Image", WINDOW_AUTOSIZE );
//    imshow("Display Image", image);

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


vector<bool> getBlackLines(Mat image) {
    int black_pixels[image.cols];
    vector<bool> black_lines(image.cols, false);
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
            black_lines[i] = true;
        }
    }
    return black_lines;
}
vector<Vec3b> getNewImage(Mat image, vector<bool> black_lines)
{
    vector<Vec3b> new_image;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            new_image[i][j] = image.at<Vec3b>(i, j);
        }
    }
    return new_image;
}