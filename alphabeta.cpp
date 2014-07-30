#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>


double alpha;
int beta;

int main(int argc, char *argv[]) {

    if (argc != 5){
        printf("usage: %s image_name alpha beta 1/0(save/not_save) \n", argv[0]);
        return 1;
    }

    cv::Mat image = cv::imread(argv[1]);
    cv::Mat new_image = cv::Mat::zeros(image.size(), image.type());
    alpha = atof(argv[2]);
    beta = atoi(argv[3]);
    printf("%f %d\n", alpha, beta);

    for(int y = 0; y < image.rows; y++) {
        for(int x = 0; x < image.cols; x++) {
            for(int c = 0; c < 3; c++) {
                new_image.at<cv::Vec3b>(y, x)[c] = 
                    cv::saturate_cast<uchar>(alpha * (image.at<cv::Vec3b>(y, x)[c]) + beta);
            }
        }
    }

#if 0
    image.convertTo(new_image, -1, alpha, beta);
#endif

    if(atoi(argv[4]) == 1) {
        char *tmp = strstr(argv[1], ".");
        *tmp = 0;

        cv::imwrite(strcat(argv[1], "_new.jpg"), new_image);
        printf("[INFO] Generate complete.");
    }

    else {

    cv::namedWindow("Original Image", 1);
    cv::namedWindow("New Image", 1);

    cv::imshow("Original Image", image);
    cv::imshow("New Image", new_image);
    cv::waitKey();
    }
    

    return 0;

}
