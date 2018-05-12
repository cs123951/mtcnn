//
// Created by Admin on 2018/4/9.
//
#include <jni.h>
#ifndef ANDROID_ORG_OPENCV_SAMPLES_MTCNN_TUTORIAL2ACTIVITY_H
#define ANDROID_ORG_OPENCV_SAMPLES_MTCNN_TUTORIAL2ACTIVITY_H

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_opencv_samples_mtcnn_Tutorial2Activity
 * Method:    mtcnnDetect
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_opencv_samples_mtcnn_Tutorial2Activity_mtcnnDetect
        (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif

#endif //ANDROID_ORG_OPENCV_SAMPLES_MTCNN_TUTORIAL2ACTIVITY_H
