package com.example.admin.myapplication;

/**
 * Created by Admin on 2018/4/9.
 */

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.widget.Button;
import android.widget.Toast;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Mat;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;


public class HomeActivity extends Activity implements CvCameraViewListener2 {
    private static final int REQUEST_PERMISSION = 233;
    private static final String    RUN = "Program run process";
    private static final String    TAG = "OCVSample::Activity";
    private CameraBridgeViewBase   mOpenCvCameraView;
    private Mat                    mRgba;
    private Mat                    image;
    private Button button;
    static {
        System.loadLibrary("opencv_java3");
        //System.loadLibrary("opencv_java");
        System.loadLibrary("native-lib");

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        AssetManager assetManager = getAssets();

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.tutorial2_activity_surface_view);
        mOpenCvCameraView.setVisibility(CameraBridgeViewBase.VISIBLE);
        mOpenCvCameraView.enableFpsMeter();
        mOpenCvCameraView.setCvCameraViewListener(this);
        mOpenCvCameraView.setCameraIndex(CameraBridgeViewBase.CAMERA_ID_FRONT);//front camera

//        if(checkPermission(Manifest.permission.CAMERA,REQUEST_PERMISSION))
//            init();
    }



    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    Log.i(TAG, "OpenCV loaded successfully");

                    // Load native library after(!) OpenCV initialization
                    //System.loadLibrary("mixed_sample");

                    mOpenCvCameraView.enableView();
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
    };

    @Override
    public void onResume()
    {
        Log.i("socket","onResume");
        super.onResume();
        if (!OpenCVLoader.initDebug()) {
            Log.d(TAG, "Internal OpenCV library not found. Using OpenCV Manager for initialization");
            //OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_0_0, this, mLoaderCallback);
        } else {
            Log.d(TAG, "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
    }

    public void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    public void onCameraViewStarted(int width, int height) {
        mRgba = new Mat();
        //Log.i(RUN,mRgba.type()+"");
        //mRgba = new Mat(height, width, CvType.CV_8UC4);
        //mIntermediateMat = new Mat(height, width, CvType.CV_8UC4);
    }

    public void onCameraViewStopped() {
        mRgba.release();
        //mIntermediateMat.release();
    }



    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
        mRgba = inputFrame.rgba();
        mtcnnDetect(mRgba.getNativeObjAddr());//调用新写的native方法
        Log.i(RUN,"Excute done.");
        return mRgba;
    }

    private void init(){
        startActivity(new Intent(this,MainActivity.class));
        finish();
    }

    public native void mtcnnDetect(long matAddr);

    private boolean checkPermission(String permission,int requestCode){
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (ContextCompat.checkSelfPermission(this, permission)
                    != PackageManager.PERMISSION_GRANTED) {
                if (ActivityCompat.shouldShowRequestPermissionRationale(this, permission)) {
                    showHint("Camera and SDCard access is required, please grant the permission in settings.");
                    finish();
                } else {
                    ActivityCompat.requestPermissions(this,
                            new String[]{
                                    permission,
                                    Manifest.permission.WRITE_EXTERNAL_STORAGE
                            },
                            requestCode);
                }
                return false;
            }else return true;
        }
        return true;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        switch (requestCode) {
            case REQUEST_PERMISSION:
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    init();
                }else {
                    showHint("Camera and SDCard access is required, please grant the permission in settings.");
                    finish();
                }
                break;
            default:
                finish();
                break;
        }
    }

    private void showHint(String hint){
        Toast.makeText(this,hint , Toast.LENGTH_LONG).show();
    }

    public void copyFilesFassets(Context context, String oldPath, String newPath) {
        try {
            String fileNames[] = context.getAssets().list(oldPath);//获取assets目录下的所有文件及目录名
            if (fileNames.length > 0) {//如果是目录
                File file = new File(newPath);
                file.mkdirs();//如果文件夹不存在，则递归
                for (String fileName : fileNames) {
                    copyFilesFassets(context,oldPath + "/" + fileName,newPath+"/"+fileName);
                }
            } else {//如果是文件
                InputStream is = context.getAssets().open(oldPath);
                FileOutputStream fos = new FileOutputStream(new File(newPath));
                byte[] buffer = new byte[1024];
                int byteCount=0;
                while((byteCount=is.read(buffer))!=-1) {//循环从输入流读取 buffer字节
                    fos.write(buffer, 0, byteCount);//将读取的输入流写入到输出流
                }
                fos.flush();//刷新缓冲区
                is.close();
                fos.close();
            }
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();

        }
    }

}