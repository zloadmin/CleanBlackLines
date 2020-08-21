#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

bool isBlackPixel(Vec3b bgrPixel);
int getPercentOfBlackPixels(double black_pixels, double row);
void showColorRGB(Vec3b bgrPixel);

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
    int black_pixels[image.cols];
    for (int i = 0; i < image.rows; i++) {
        black_pixels[i] = 0;
        for (int j = 0; j < image.cols; j++) {
            Vec3b bgrPixel = image.at<Vec3b>(i, j);

            if (isBlackPixel(bgrPixel)) {
                black_pixels[i]++;
            }
//            cout << bgrPixel << "\n";
            // do something with BGR values...
        }

//        if(i > 1800 && i < 2000) {
//                cout << "Number of line " << i << ", percent of black pixels - " << black_pixels[i] << "\n";
//        }

        int p = getPercentOfBlackPixels(black_pixels[i], image.cols);

        if(p > PERCENT_OF_BLACK ) cout << "Number of line " << i << ", percent of black pixels - " << p << "%" << "\n";
    }
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
    return  black_pixels > 0 ? black_pixels / row * 100 : 0;
}
void showColorRGB(Vec3b bgrPixel)
{
    int B = bgrPixel.val[0];
    int G = bgrPixel.val[1];
    int R = bgrPixel.val[2];
    cout << "[" << R << ", " << G << ", " << B << "]" << "\n";
//    cout << "R " << R << " G " << G << " B " << B << "\n";
}