#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>
using namespace std;
int main()
{
	IplImage *src = cvLoadImage("horses.jpg");
	IplImage *dst;
	CvSize size; 
	size.width = 200;
	size.height = 20000;
	dst = cvCreateImage(size, src->depth, src->nChannels);
	cvResize(src, dst, CV_INTER_CUBIC);
	cout<<"dst widthStep: "<<dst->widthStep<<endl;
	cvNamedWindow("src", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("dst", CV_WINDOW_AUTOSIZE);
	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvSaveImage("dst.bmp",dst);
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow("src");
	cvDestroyWindow("dst");
	return 0;
}
