#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;


int main(int argc, char* argv[]) {

    Mat src,gray;
    src = imread(argv[1]);
    cvtColor(src, gray, CV_BGR2GRAY);
    const int MEDIAN_BLUR_FILTER_SIZE = 7; 
    medianBlur(gray, gray, MEDIAN_BLUR_FILTER_SIZE);
    Mat edges;
    const int LAPLACIAN_FILTER_SIZE = 5;
    Laplacian(gray, edges, CV_8U, LAPLACIAN_FILTER_SIZE);

    Mat mask;
    const int EDGES_THRESHOLD = 80;
    threshold(edges, mask, EDGES_THRESHOLD, 255, THRESH_BINARY_INV);
    imwrite(argv[2], mask);
    waitKey(0);
    
}
