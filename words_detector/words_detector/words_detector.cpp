//#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv) {
	cv::Mat img = cv::imread(argv[1], -1);
	if (img.empty()) return -1;

	img.at<uchar>(5, 5) = 0;
	img.at<uchar>(6, 5) = 0;
	img.at<uchar>(7, 5) = 0;
	img.at<uchar>(8, 5) = 0;

	cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
	cv::imshow("Example1", img);
	cv::waitKey(0);
	cv::destroyWindow("Example1");
	return 0;
}