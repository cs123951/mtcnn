#include <jni.h>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <android/log.h>
#include "mtcnn/FaceInfo.h"
#include "mtcnn/mtcnn.h"
#include "mtcnn/network.h"
#include "mtcnn/openblas_config.h"
#include "mtcnn/org_opencv_samples_mtcnn_Tutorial2Activity.h"
#include "mtcnn/org_opencv_samples_tutorial2_Tutorial2Activity.h"
#include "mtcnn/pBox.h"
#define  LOG_TAG    "JNI_PART"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, __VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG, __VA_ARGS__)
using namespace cv;
using namespace std;
extern "C"{
jstring Java_com_example_admin_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


void Java_com_example_admin_myapplication_MainActivity_nativeProcessFrame(JNIEnv*, jobject, jlong addrGray, jlong addrRgba) {
    Mat &mGr = *(Mat *) addrGray;
    Mat &mRgb = *(Mat *) addrRgba;
    vector<KeyPoint> v;

/*    LOGD("%d image size %d",mGr.rows,mGr.cols);
    resize(mGr,mGr,Size(mGr.cols*480/mGr.rows,480));
    LOGD("%d image new-size %d",mGr.rows,mGr.cols);*/

    Ptr<FeatureDetector> detector = FastFeatureDetector::create(50);
    detector->detect(mGr, v);
    for (unsigned int i = 0; i < v.size(); i++) {
        const KeyPoint &kp = v[i];
        circle(mRgb, Point(kp.pt.x, kp.pt.y), 10, Scalar(0, 255, 255, 255));
    }


}
}
ofstream faceROI(modeldir + "/FaceRect.txt",ios::out|ios::app);
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_admin_myapplication_HomeActivity_testblas(JNIEnv *env, jobject instance) {

    // TODO
    std::string returnValue = "  hi ";

    return env->NewStringUTF(returnValue.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_admin_myapplication_HomeActivity_stringFromJNI(JNIEnv *env, jobject instance) {

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_admin_myapplication_HomeActivity_mtcnnDetect(JNIEnv *env, jobject instance, jlong matAddr) {

    long mat = (long)matAddr;
    //__android_log_print(ANDROID_LOG_INFO,"MTCNN","THE ADDRESS: %ld",mat);
    Mat &img = *(Mat *) mat;

    //cv::flip(img,img,1);
    //Mat img = origin.clone();
    //rotate image
    cv::transpose(img,img);
    cv::flip(img,img,0);

    //__android_log_print(ANDROID_LOG_INFO,RUN,"START PROCESSING");
    int row = img.rows;
    int col = img.cols;
    __android_log_print(ANDROID_LOG_INFO,RUN,"rows: %d cols: %d",row,col);
    //cv::resize(img,img,cv::Size(640,480),0,0);
    //img.convertTo(img,16);
    cv::cvtColor(img,img,cv::COLOR_RGBA2RGB);
    //__android_log_print(ANDROID_LOG_INFO,RUN,"CVTYPE: %d",img.type());
    if (!img.data) {
        __android_log_print(ANDROID_LOG_INFO,RUN,"NO DATA");
        String a="dfddf";
    }
    static mtcnn find(row,col);
    //__android_log_print(ANDROID_LOG_INFO,RUN,"CREATE FINDOBJECT");
    std::vector<FaceInfo> fds;
    //__android_log_print(ANDROID_LOG_INFO,RUN,"CREATE FACEINFO");
    find.Detect(img, fds);
    //rotate back
    cv::transpose(img,img);


    faceROI << "::";

    __android_log_print(ANDROID_LOG_INFO,RUN,"PROCESS DONE");


}