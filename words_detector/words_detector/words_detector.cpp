#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv) {
	cv::Mat img = cv::imread(argv[1]);
	if (img.empty()) return -1;

	cv::Mat imgGray;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

	cv::Mat imgBlurred;
	cv::GaussianBlur(imgGray, imgBlurred, cv::Size(11, 11), 0);

	cv::Mat imgBinary;
	int block_size = 71; // atoi(argv[4]);
	double offset = 15.0; //  (double)atof(argv[5]);
	double fixed_threshold = 15.0; //(double)atof(argv[1]);
	int threshold_type = 1; // atoi(argv[2]) ? cv::THRESH_BINARY : cv::THRESH_BINARY_INV;
	int adaptive_method = 1; // atoi(argv[3]) ? cv::ADAPTIVE_THRESH_MEAN_C

//	cv::adaptiveThreshold(imgBlurred, imgBinary, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_OTSU, block_size, offset); //(imgBlurred, 200, 255, cv2.THRESH_BINARY)[1]
	cv::adaptiveThreshold(
		imgBlurred,
		imgBinary,
		255,
		adaptive_method,
		threshold_type,
		block_size,
		offset
	);

	cv::Mat imgEroded;
	int erosion_type = 1;
	int erosion_size = 1;
	cv::Mat erosion_kernel = cv::getStructuringElement(erosion_type,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	cv::erode(imgBinary, imgEroded, erosion_kernel, cv::Point(-1,-1), 1, 0);

	cv::Mat imgDilated;
	cv::dilate(imgEroded, imgDilated, erosion_kernel, cv::Point(-1,-1), 3); //4

		//thresh = cv2.dilate(thresh, None, iterations = 4)
																														//	cv::threshold(
	//		imgGray,
	//		It,
	//		fixed_threshold,
	//		255,
	//		threshold_type);
	//cv::adaptiveThreshold(
	//	imgGray,
	//	Iat,
	//	255,
	//	adaptive_method,
	//	threshold_type,
	//	block_size,
	//	offset
	//);


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

	// Command line.
 //
	//double fixed_threshold = 15.0; //(double)atof(argv[1]);
	//int threshold_type = 1; // atoi(argv[2]) ? cv::THRESH_BINARY : cv::THRESH_BINARY_INV;
	//int adaptive_method = 1; // atoi(argv[3]) ? cv::ADAPTIVE_THRESH_MEAN_C
		//: cv::ADAPTIVE_THRESH_GAUSSIAN_C;

	//int block_size = 71; // atoi(argv[4]);
	//double offset = 15.0; //  (double)atof(argv[5]);

	cv::namedWindow("imgBinary", cv::WINDOW_AUTOSIZE);
	cv::imshow("imgBinary", imgBinary);
	
	cv::namedWindow("imgEroded", cv::WINDOW_AUTOSIZE);
	cv::imshow("imgEroded", imgEroded);
	
	cv::namedWindow("imgDilated", cv::WINDOW_AUTOSIZE);
	cv::imshow("imgDilated", imgDilated);
	cv::waitKey(0);
	cv::destroyWindow("imgDilated");
	return 0;
}