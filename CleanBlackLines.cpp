#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <experimental/filesystem>
#include <regex>
#include <iterator>

using namespace cv;
using namespace std;
namespace fs = std::experimental::filesystem;

bool isBlackPixel(Vec3b bgrPixel);

int getPercentOfBlackPixels(double black_pixels, double row);

string getNewFilePath(char **argv);

string getOldFilePath(char **argv);

const int BLACK_LIMIT = 27;
const int PERCENT_OF_BLACK = 75;

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: CleanBlackLines <Image_Path>\n");
        return -1;
    }
    bool debug = false;
    if (argc == 3) debug = true;
    if (debug) cout << "Start file " << argv[1] << "\n";
    Mat image;
    image = imread(argv[1], 1);
    if (!image.data) {
        printf("No image data \n");
        return -1;
    } else {
        if (debug) cout << "Loaded file " << argv[1] << "\n";
    }


    
    if (debug) cout << "Image size  rows: " << image.rows << ", cols " << image.cols << "\n";
    int black_pixels[image.rows];
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
            for (int jk = 0; jk < image.cols; jk++) {
                Vec3b bgrPixel = image.at<Vec3b>(i, jk);
                bgrPixel[0] = 0;
                bgrPixel[1] = 0;
                bgrPixel[2] = 0;
                image.at<Vec3b>(i, jk) = bgrPixel;

            }
        }
    }
    if (debug) cout << "Cahnged  " << changed << "\n";
    string old_file_path = getOldFilePath(argv);
    string new_file_path = getNewFilePath(argv);

    if (changed) {

        bool is_copyed = false;
        if (debug) cout << "Copy file to   " << new_file_path << "\n";
        try {
            fs::copy_file(old_file_path, new_file_path);
            is_copyed = true;
        }
        catch (fs::filesystem_error &e) {
            fprintf(stderr, "Could not copy file : %s\n", e.what());
            return 1;
        }

        if (is_copyed) {
            if (debug) cout << "Save file to  " << old_file_path << "\n";
            try {
                imwrite(old_file_path, image);
            }
            catch (runtime_error &ex) {
                fprintf(stderr, "Exception save image to JPG format: %s\n", ex.what());
                printf("Try back copy file\n");
                fs::copy_file(new_file_path, old_file_path);
                return 1;
            }
            cout << old_file_path << " - DONE. COPY " << new_file_path << "\n";
        } else {
            printf("Error of copy file. File has not been cahnged\n");
        }

        return 0;
    } else {
        cout << old_file_path << " - SKIP" << "\n";
    }
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

string getNewFilePath(char **argv) {
    fs::path absolute_path = fs::absolute(argv[1]);
    string s(absolute_path);
    regex e("\\.(.*)$");
    return std::regex_replace(s, e, "_ORIGIN_.$1");
}

string getOldFilePath(char **argv) {
    return fs::absolute(argv[1]);
}