#include<iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    Mat m_frame,smallImg,tmp,bigImg,gray,edges,masks,dst;
    int repetitions = 7; // Repetitions for strong cartoon effect.
    const int MEDIAN_BLUR_FILTER_SIZE = 7;
    const int LAPLACIAN_FILTER_SIZE = 5;
    const int EDGES_THRESHOLD = 80;

    m_frame = imread(argv[1]);
    //m_capture>>m_frame;
    Size size = m_frame.size();
    Size smallSize;
    smallSize.width = size.width/2;
    smallSize.height = size.height/2;
    smallImg = Mat(smallSize, CV_8UC3);
    tmp = Mat(smallSize, CV_8UC3);
    dst= Mat(size,CV_8UC3);


    cvtColor(m_frame,gray,CV_BGR2GRAY);

    medianBlur(gray,gray,MEDIAN_BLUR_FILTER_SIZE);

    Laplacian(gray, edges, CV_8U, LAPLACIAN_FILTER_SIZE);

    threshold(edges, masks, EDGES_THRESHOLD, 255, THRESH_BINARY_INV);

    resize(m_frame, smallImg, smallSize, 0,0, INTER_LINEAR);

    for (int i=0; i<repetitions; i++) {
        int ksize = 9; // Filter size. Has a large effect on speed.
        double sigmaColor = 9; // Filter color strength.
        double sigmaSpace = 7; // Spatial strength. Affects speed.
        bilateralFilter(smallImg, tmp, ksize, sigmaColor, sigmaSpace);
        bilateralFilter(tmp, smallImg, ksize, sigmaColor, sigmaSpace);
    }

    resize(smallImg, bigImg, size, 0,0, INTER_LINEAR);

    dst.setTo(0);

    //! copies those matrix elements to "m" that are marked with non-zero mask elements.
    bigImg.copyTo(dst,masks);

    imwrite(argv[2], dst);
    return 0;
}

