#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void isBlackPixel(Vec3s bgrPixel);

int main(int argc, char** argv )
{
//    if ( argc != 2 )
//    {
//        printf("usage: DisplayImage.out <Image_Path>\n");
//        return -1;
//    }

    Mat image;
//    image = imread( argv[1], 1 );
    image = imread( "1.jpg", 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            Vec3b bgrPixel = image.at<Vec3s>(i, j);
            isBlackPixel(bgrPixel);
//            cout << bgrPixel << "\n";
            // do something with BGR values...
        }
    }
//    namedWindow("Display Image", WINDOW_AUTOSIZE );
//    imshow("Display Image", image);

    waitKey(0);

    return 0;
}
void isBlackPixel(Vec3s bgrPixel)
{
    cout << bgrPixel[0] << " - " << bgrPixel[1]  << " - " << bgrPixel[2]  << "\n";
}