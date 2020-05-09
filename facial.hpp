// Summary: 绘制人脸关键点和多边形线
// Author:  Amusi
// Date:    2018-03-20

#ifndef _renderFace_H_
#define _renderFace_H_


#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
using namespace cv; 
using namespace std; 

#define COLOR Scalar(255, 200,0)

// drawPolyline通过连接开始和结束索引之间的连续点来绘制多边形线。
void drawPolyline(
 Mat &im,
 const vector<Point2f> &landmarks,
 const int start,
 const int end,
 bool isClosed = false
 ){
	// 收集开始和结束索引之间的所有点
	vector <Point> points;
	for (int i = start; i <= end; i++)
	{
		points.push_back(cv::Point(landmarks[i].x, landmarks[i].y));
	}

	// 绘制多边形曲线
	polylines(im, points, isClosed, COLOR, 2, 16);

}

// 绘制人脸关键点
void drawLandmarks(Mat &im, vector<Point2f> &landmarks){
	bool op=false;
	// 在脸上绘制68点及轮廓（点的顺序是特定的，有属性的）
	if (op&&landmarks.size() == 68){
		drawPolyline(im, landmarks, 0, 16);           // Jaw line
		drawPolyline(im, landmarks, 17, 21);          // Left eyebrow
		drawPolyline(im, landmarks, 22, 26);          // Right eyebrow
		drawPolyline(im, landmarks, 27, 30);          // Nose bridge
		drawPolyline(im, landmarks, 30, 35, true);    // Lower nose
		drawPolyline(im, landmarks, 36, 41, true);    // Left eye
		drawPolyline(im, landmarks, 42, 47, true);    // Right Eye
		drawPolyline(im, landmarks, 48, 59, true);    // Outer lip
		drawPolyline(im, landmarks, 60, 67, true);    // Inner lip
	}
	else 
	{ 
		// 如果人脸关键点数不是68，则我们不知道哪些点对应于哪些面部特征。所以，我们为每个landamrk画一个圆圈。
		for(int i = 0; i < landmarks.size(); i++)
		{
			circle(im,landmarks[i],3, COLOR, FILLED);
		}
	}

}

void printPoint(Mat &img,string text,Point origin){
	putText(img,text,origin,FONT_HERSHEY_COMPLEX,1,Scalar(0,255,255),2,8,0);
}

void printFacePoint(Mat &img,vector<Point2f> &landmarks){	
	float H=abs(landmarks[51].y-landmarks[57].y);
	float L=abs(landmarks[48].x-landmarks[54].x);
	float h=abs(landmarks[62].y-landmarks[66].y);
	float l=abs(landmarks[60].x-landmarks[64].x);
	
	float hEyeLeftInner=abs(landmarks[38].y-landmarks[40].y);
	float hEyeLeftOuter=abs(landmarks[37].y-landmarks[41].y);
	float lLeft=abs(landmarks[36].x-landmarks[39].x);
	float lRight=abs(landmarks[42].x-landmarks[45].x);
	float hEyeRightInner=abs(landmarks[43].y-landmarks[47].y);
	float hEyeRightOuter=abs(landmarks[44].y-landmarks[46].y);
	
	float leftEAR=(hEyeLeftInner+hEyeLeftOuter)/(2*lLeft);
	float rightEAR=(hEyeRightInner+hEyeRightOuter)/(2*lRight);
	
	printPoint(img,"left:"+to_string(leftEAR),Point(100,100));
	printPoint(img,"right"+to_string(rightEAR),Point(100,200));
}

bool mouthOpen(vector<Point2f> &landmarks){
	float H=abs(landmarks[51].y-landmarks[57].y);
        float L=abs(landmarks[48].x-landmarks[54].x);
	float MAR=H/(2*L);
	return MAR>0.28;
}

bool eyesOpen(vector<Point2f> &landmarks){	
	float hEyeRightInner=abs(landmarks[43].y-landmarks[47].y);
	float hEyeRightOuter=abs(landmarks[44].y-landmarks[46].y);
	float lRight=abs(landmarks[42].x-landmarks[45].x);
	float hEyeLeftInner=abs(landmarks[38].y-landmarks[40].y);
	float hEyeLeftOuter=abs(landmarks[37].y-landmarks[41].y);
	float lLeft=abs(landmarks[36].x-landmarks[39].x);

	float leftEAR=(hEyeLeftInner+hEyeLeftOuter)/(2*lLeft);
	float rightEAR=(hEyeRightInner+hEyeRightOuter)/(2*lRight);

	return (leftEAR+rightEAR)/2>=0.25;
}
#endif // _renderFace_H_
