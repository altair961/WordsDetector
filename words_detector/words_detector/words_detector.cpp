//#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv) {
	cv::Mat img = cv::imread(argv[1], -1);
	if (img.empty()) return -1;

	//img.at<uchar>(5, 5) = 0;
	//img.at<uchar>(6, 5) = 0;
	//img.at<uchar>(7, 5) = 0;
	//img.at<uchar>(8, 5) = 0;

	//auto width{ img.size().width };
	//auto height{ img.size().height };

	int rows = img.rows;
	int cols = img.cols;

	cv::Size s = img.size();
	rows = s.height;
	cols = s.width;

	//int dims = img.dims;
	//img.size();
	
	//for (auto i : img) {

	//}
	
	//for (auto i{ 0 }; i < 2000; ++i)
	//{

	//	img.at<uchar>(8, i) = 254;
	//	img.at<uchar>(9, i) = 254;
	//	img.at<uchar>(10, i) = 254;

	//	//for (auto j{ 0 }; j < height; ++j)
	//	//{
	//		//img.at<uchar>(j, i) = 0;
	//	//}
	//}

		//img.at<uchar>(5, 987) = 0;
		//img.at<uchar>(5, 988) = 0;
		//img.at<uchar>(5, 989) = 0;
		//img.at<uchar>(5, 990) = 0;
		//img.at<uchar>(5, 991) = 0;
		//img.at<uchar>(5, 992) = 0;




	for (int row = 0; row < img.rows; ++row) {
		uchar* p = img.ptr(row);
	//	for (int col = 0; col < img.cols; ++col) {
//			*p++  //points to each pixel value in turn assuming a CV_8UC1 greyscale image 
		//}

		//or
			for (int col = 0; col < img.cols * 3; ++col) { // here we multiply by 3 - beacuse 
				// the amount of elements horizontaly is 3 times bigger than resolution 
				// since each pixel represented by red green and blue pixel,
				// when we deal with gray images we do not multiply 
				*p++;  //points to each pixel B,G,R value in turn assuming a CV_8UC3 color image 
				//img.at<uchar>(row, col) = 200;
				
			}
			// use pointers instead of "img.at<uchar>(row, col) = 200;" pointers are faster and are ok for traversing even for video
	}

	cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
	cv::imshow("Example1", img);
	cv::waitKey(0);
	cv::destroyWindow("Example1");
	return 0;
}

/*

#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv) {
	cv::Mat img = cv::imread(argv[1], -1);
	if (img.empty()) return -1;

	img.at<uchar>(5, 5) = 0;
	img.at<uchar>(6, 5) = 0;
	img.at<uchar>(7, 5) = 0;
	img.at<uchar>(8, 5) = 0;

	cv::Mat img2 = cv::imread(argv[1], -1);

	//cv::blur(img, (5, 5));
	cv::blur(img, img2, cv::Size(10, 10));

	cv::Mat img3 = cv::imread(argv[1], -1);

	img2.convertTo(img3, -3, 1, 0);

	cv::Mat img_higher_brightness;
	img3.convertTo(img_higher_brightness, -1, 1, -20); //increase the brightness by 20 for each pixel

	cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
	cv::imshow("Example1", img_higher_brightness);
	cv::waitKey(0);
	cv::destroyWindow("Example1");
	return 0;
}
*/