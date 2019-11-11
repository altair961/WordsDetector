#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>

std::vector<cv::Rect> detectLetters(cv::Mat img);

int main(int argc, char** argv) {
	cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
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

	// Command line.
 //
	double fixed_threshold = 15.0; //(double)atof(argv[1]);
	int threshold_type = 1; // atoi(argv[2]) ? cv::THRESH_BINARY : cv::THRESH_BINARY_INV;
	int adaptive_method = 1; // atoi(argv[3]) ? cv::ADAPTIVE_THRESH_MEAN_C
		//: cv::ADAPTIVE_THRESH_GAUSSIAN_C;

	int block_size = 71; // atoi(argv[4]);
	double offset = 15.0; //  (double)atof(argv[5]);

	cv::Mat It, Iat;
	// Thresholds.
	//
	cv::threshold(
		img,
		It,
		fixed_threshold,
		255,
		threshold_type);
	cv::adaptiveThreshold(
		img,
		Iat,
		255,
		adaptive_method,
		threshold_type,
		block_size,
		offset
	);
	

	// create 8bit color image. IMPORTANT: initialize image otherwise it will result in 32F
	cv::Mat img_rgb(Iat.size(), CV_8UC3);

	// convert grayscale to color image
	cv::cvtColor(Iat, img_rgb, cv::COLOR_GRAY2RGB);

	Iat.at<uchar>(0, 1) = 255;
	Iat.at<uchar>(0, 2) = 255;
	Iat.at<uchar>(0, 3) = 255;
	Iat.at<uchar>(0, 4) = 255;
	Iat.at<uchar>(0, 5) = 255;
	Iat.at<uchar>(0, 6) = 255;
	Iat.at<uchar>(0, 7) = 255;
	Iat.at<uchar>(0, 8) = 255;
	Iat.at<uchar>(0, 9) = 255;

	std::vector<cv::Rect> letterBBoxes1 = detectLetters(img_rgb);
	//	std::vector<cv::Rect> letterBBoxes2 = detectLetters(img2);
		//Display
	for (int i = 0; i < letterBBoxes1.size(); i++) {
		cv::rectangle(img_rgb, letterBBoxes1[i], cv::Scalar(0, 255, 0), 3, 8, 0);
		cv::circle(img_rgb, cv::Point(letterBBoxes1[i].x + letterBBoxes1[i].width * 0.5,
			letterBBoxes1[i].y + letterBBoxes1[i].height * 0.5), 2, cv::Scalar(0, 0, 255), 5);
	}


	
	//cv::imshow("Raw", Igray);
	cv::imshow("Threshold", It);
	cv::imshow("Adaptive Threshold", img_rgb);

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

std::vector<cv::Rect> detectLetters(cv::Mat img)
{
	std::vector<cv::Rect> boundRect;
	cv::Mat img_gray, img_sobel, img_threshold, element;
	cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
	cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
	cv::threshold(img_sobel, img_threshold, 0, 255, cv::THRESH_OTSU + cv::THRESH_BINARY);
	element = getStructuringElement(cv::MORPH_RECT, cv::Size(17, 3));
	cv::morphologyEx(img_threshold, img_threshold, cv::MORPH_CLOSE, element); //Does the trick
	std::vector< std::vector< cv::Point> > contours;
	cv::findContours(img_threshold, contours, 0, 1);
	std::vector<std::vector<cv::Point> > contours_poly(contours.size());
	for (int i = 0; i < contours.size(); i++)
		if (contours[i].size() > 100)
		{
			cv::approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
			cv::Rect appRect(boundingRect(cv::Mat(contours_poly[i])));
			if (appRect.width > appRect.height)
				boundRect.push_back(appRect);
		}
	return boundRect;
}