#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <time.h>
#include "facial.hpp"
#include <queue>
#include <cmath>
using namespace std;
using namespace cv;
using namespace cv::face;

queue<bool> qMouth;
queue<bool> qEyes;


int main(int argc,char** argv)
{
	int mouth=0;
	int eyes=0;
    // 加载人脸检测器（Face Detector）
	// [1]Haar Face Detector
    CascadeClassifier faceDetector("/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml");
	// [2]LBP Face Detector
//	CascadeClassifier faceDetector("/usr/share/OpenCV/lbpcascades/lbpcascade_frontalface_improved.xml");

    // 创建Facemark类的对象
    Ptr<Facemark> facemark = FacemarkLBF::create();

    // 加载人脸检测器模型
   // facemark->loadModel("/home/openailab/FatigueDectection/lbfmodel.yaml");
    facemark->loadModel("lbfmodel.yaml");
    // 设置网络摄像头用来捕获视频
    VideoCapture cam;
    cam.open(0);
    if(!cam.isOpened()){
    	cout<<"Failed to open the video!"<<endl;
	return 1;
    }
   cout<<cam.get(CV_CAP_PROP_FPS)<<endl; 
    // 存储视频帧和灰度图的变量
    Mat frame, gray;
    clock_t start,finish;
    // 读取帧
    while(cam.read(frame))
    {

      start=clock();

      // 存储人脸矩形框的容器
      vector<Rect> faces;
	  // 将视频帧转换至灰度图, 因为Face Detector的输入是灰度图
      cvtColor(frame, gray, COLOR_BGR2GRAY);

      // 人脸检测
      faceDetector.detectMultiScale(gray, faces);

      int a=0,b=0,maxI=0;
      for(int i=0;i<faces.size();i++){
      	int tA=faces[i].width;
	int tB=faces[i].height;
	if(tA>a&&tB>b){
		a=tA;
		b=tB;
		maxI=i;
	}
      	     // rectangle(frame,faces[i],Scalar(0,0,255),2,8,0);
      }
      if(faces.size()!=0) {
	rectangle(frame,faces[maxI],Scalar(0,0,255),2,8,0);
	  // 人脸关键点的容器
      vector< vector<Point2f> > landmarks;
      Rect tmp;
      tmp=faces[maxI];
      faces.clear();
      faces.push_back(tmp);
	  // 运行人脸关键点检测器（landmark detector）
      bool success = facemark->fit(frame,faces,landmarks);
      if(success)
      {
        // 如果成功, 在视频帧上绘制关键点
        for(int i = 0; i < landmarks.size(); i++)
        {
			// 自定义绘制人脸特征点函数, 可绘制人脸特征点形状/轮廓
		//	drawLandmarks(frame, landmarks[i]);
			// OpenCV自带绘制人脸关键点函数: drawFacemarks
		//	drawFacemarks(frame, landmarks[i], Scalar(0, 0, 255));
			printFacePoint(frame,landmarks[i]);
        }
	bool tMouth=mouthOpen(landmarks[0]);
	if(qMouth.size()==13){
		mouth-=qMouth.front();
		mouth+=tMouth;
		qMouth.pop();
		qMouth.push(tMouth);
		if(mouth>5)
			cout<<"MOUTH FATIGUE!!!"<<endl;
		else cout<<"MOUTH alive.^-^"<<endl;
	}
	else {
		qMouth.push(tMouth);
		mouth+=tMouth;
	}

	bool tEyes=!eyesOpen(landmarks[0]);
	if(qEyes.size()==20){
		eyes-=qEyes.front();
		eyes+=tEyes;
		qEyes.pop();
		qEyes.push(tEyes);
		if(eyes>10)
			cout<<"EYES FATIGUE!!!"<<endl;
		else cout<<"EYES blink.^-^"<<endl;
	}
	else {
		qEyes.push(tEyes);
		eyes+=tEyes;
	}
      }
      }
      finish=clock();
      double totalTime=(double)(finish-start)/CLOCKS_PER_SEC;
     // cout<<"it cost "<<totalTime*1000<<"ms."<<endl;
      // 显示结果
      imshow("Facial Landmark Detection", frame);
      // 如果按下ESC键, 则退出程序
      if (waitKey(1) == 27) break;
      
   	
    }
    return 0;
}
