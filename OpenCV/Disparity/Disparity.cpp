#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/calib3d.hpp>

#include <iostream>
#include <string>

void findMatchings(cv::Mat& iA, cv::Mat& iB, std::vector<cv::Point2f>& pA, std::vector<cv::Point2f>& pB) {
	//cv::Mat copyA, copyB;
	std::vector<cv::Point2f> tmpA;
	std::vector<cv::Point2f> tmpB;
	std::vector<uchar> status;
	std::vector<float> err;

	//cv::cvtColor(*iA, copyA, cv::COLOR_BGR2GRAY);
	//cv::cvtColor(*iB, copyB, cv::COLOR_BGR2GRAY);

	int maxCorners = 23;
	double qualityLevel = 0.01;
	double minDistance = 10;

	cv::goodFeaturesToTrack(iA, tmpA, maxCorners, qualityLevel, minDistance);
	cv::calcOpticalFlowPyrLK(iA, iB, tmpA, tmpB, status, err);

	for (int i = 0; i < tmpA.size(); i++) {
		if (status.at(i) == 1) {
			pA.push_back(tmpA.at(i));
			pB.push_back(tmpB.at(i));
		}
	}
}

void displayMatchings(cv::Mat& iA, cv::Mat& iB, std::vector<cv::Point2f>& pA, std::vector<cv::Point2f>& pB) {
	for (int i = 0; i < pA.size(); i++) {
		cv::line(iA, pA.at(i), pB.at(i), (255, 0, 0));
		cv::line(iB, pA.at(i), pB.at(i), (255, 0, 0));
	}

	cv::imshow("Disparity1", iA);
	cv::imshow("Disparity2", iB);

}

int main(int argc, char** argv)
{
	std::string fileiA = "D:/ESGI/5eme Annee/visions/dataTPdisparity/image1.jpg";
	std::string fileiB = "D:/ESGI/5eme Annee/visions/dataTPdisparity/image2.jpg";

	cv::Mat image1 = cv::imread(fileiA, cv::IMREAD_GRAYSCALE);
	cv::Mat image2 = cv::imread(fileiB, cv::IMREAD_GRAYSCALE);
	if (image1.empty()) // Check for failure
	{
		std::cout << "Could not open or find the image" << std::endl;
		system("pause"); //wait for any key press
		return -1;
	}

	std::vector<cv::Point2f> points1, points2;

	findMatchings(image1, image2, points1, points2);
	displayMatchings(image1, image2, points1, points2);
	//cv::Mat rectified1(image1.size(), image1.type());
	//cv::Mat rectified2(image2.size(), image2.type());
	//rectify(image1, image2, points1, points2, rectified1, rectified2);
	//cv::imshow("rectified L", rectified1);
	//cv::imshow("rectified R", rectified2);
	//cv::waitKey();
	//cv::Mat disparity = computeDisparity(rectified1, rectified2);
	//cv::imshow("disparity", disparity);
	cv::waitKey(0);
	return 0;
}