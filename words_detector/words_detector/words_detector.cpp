#include <opencv2/opencv.hpp>

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

	int rows = img.rows;
	int cols = img.cols;

	cv::Size s = img.size();
	rows = s.height;
	cols = s.width;

	int threshval = 100;

	//cv::Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);
	cv::Mat labelImage(img.size(), CV_32S);
	int nLabels = connectedComponents(imgDilated, labelImage, 8);
	std::vector<cv::Vec3b> colors(nLabels);
	colors[0] = cv::Vec3b(0, 0, 0);//background
	for (int label = 1; label < nLabels; ++label) {
		colors[label] = cv::Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
	}

	cv::Mat connectedComponent(img.size(), CV_8UC3);
	for (int r = 0; r < connectedComponent.rows; ++r) {
		for (int c = 0; c < connectedComponent.cols; ++c) {
			int label = labelImage.at<int>(r, c);
			cv::Vec3b& pixel = connectedComponent.at<cv::Vec3b>(r, c);
			pixel = colors[label];
		}
	}


	cv::namedWindow("connectedComponent", cv::WINDOW_AUTOSIZE);
	cv::imshow("connectedComponent", connectedComponent);
	
	cv::namedWindow("imgEroded", cv::WINDOW_AUTOSIZE);
	cv::imshow("imgEroded", imgEroded);
	
	cv::namedWindow("imgDilated", cv::WINDOW_AUTOSIZE);
	cv::imshow("imgDilated", imgDilated);
	cv::waitKey(0);
	cv::destroyWindow("imgDilated");
	return 0;
}