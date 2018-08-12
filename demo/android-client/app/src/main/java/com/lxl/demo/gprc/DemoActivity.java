package com.lxl.demo.gprc;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


public class DemoActivity extends AppCompatActivity {

    static {
        System.loadLibrary("grpc-demo");
    }

    private TextView mStatusTv;
    private Button signInButton;
    private Button signUpButton;
    private Button logoutButton;

    private EditText hostEdit;
    private EditText portEdit;
    private EditText userEdit;
    private EditText pwdEdit;

    private String mHost;
    private int mPort;
    private String mUser;
    private String mPwd;

    private boolean mIsOnline = true;

    private HandlerThread mWorker;
    private Handler mWorkerHandler;

    // 心跳,保持登录状态
    private Runnable mHeartBeat = new Runnable() {
        @Override
        public void run() {
            if(mIsOnline) {
                String result = heartbeat(mHost, mPort, mUser, mPwd);
                Log.d("lxl","Heartbeat From Server: "+result);

                String[] res = result.split(":");
                if(res.length >= 2) {
                    if(!"android".equals(res[1])) {
                        mIsOnline = false;
                        if(!"offline".equals(res[1])) {
                            mStatusTv.setText(mUser + " 已在 "+res[1]+" 登录! 请重新登录.");
                        } else {
                            mStatusTv.setText(mUser + " 已登出.");
                        }
                        signInButton.setEnabled(true);
                        logoutButton.setEnabled(false);
                    } else {
                        mIsOnline = true;
                        mStatusTv.setText(mUser + " 在线!");
                        signInButton.setEnabled(false);
                        logoutButton.setEnabled(true);
                        mWorkerHandler.post(mHeartBeat);
                    }
                } else {
                    Toast.makeText(DemoActivity.this,"",Toast.LENGTH_SHORT).show();
                    mIsOnline = false;
                    mStatusTv.setText(mUser + " 服务器异常");
                    signInButton.setEnabled(true);
                    logoutButton.setEnabled(false);
                }

                // 每3秒检查一次
                mWorkerHandler.postDelayed(this,3000);
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mStatusTv = findViewById(R.id.status_tv);
        signInButton = findViewById(R.id.signin_button);
        signUpButton = findViewById(R.id.signup_button);
        logoutButton = findViewById(R.id.logout_button);

        hostEdit = findViewById(R.id.host_edit_text);
        portEdit = findViewById(R.id.port_edit_text);
        userEdit = findViewById(R.id.user_edit_text);
        pwdEdit = findViewById(R.id.pwd_edit_text);

        mWorker = new HandlerThread("worker");
        mWorker.start();
        mWorkerHandler = new Handler(mWorker.getLooper());
    }

    public void signInClick(View view) {
        ((InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE))
                .hideSoftInputFromWindow(hostEdit.getWindowToken(), 0);
        signInButton.setEnabled(false);
        mWorkerHandler.post(new Runnable() {
            @Override
            public void run() {
                mHost = hostEdit.getText().toString();
                String portStr = portEdit.getText().toString();
                mUser  = userEdit.getText().toString();
                mPwd  = pwdEdit.getText().toString();
                mPort = TextUtils.isEmpty(portStr) ? 50051 : Integer.valueOf(portStr);
                String result = signin(mHost, mPort, mUser, mPwd);
                Toast.makeText(DemoActivity.this,"From Server: "+result,Toast.LENGTH_LONG).show();
                String[] res = result.split(":");
                if(res.length >= 2 && "success".equals(res[0])) {
                    mIsOnline = true;
                    mWorkerHandler.post(mHeartBeat);
                    mStatusTv.setText(mUser + " 登录成功!");
                    signInButton.setEnabled(false);
                    logoutButton.setEnabled(true);
                } else {
                    mStatusTv.setText(mUser + " 登录失败!");
                    signInButton.setEnabled(true);
                    logoutButton.setEnabled(false);
                }
            }
        });
    }

    public void signUpClick(View view) {
        ((InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE))
                .hideSoftInputFromWindow(hostEdit.getWindowToken(), 0);
        signUpButton.setEnabled(false);
        mWorkerHandler.post(new Runnable() {
            @Override
            public void run() {
                mHost = hostEdit.getText().toString();
                String portStr = portEdit.getText().toString();
                mUser  = userEdit.getText().toString();
                mPwd  = pwdEdit.getText().toString();
                mPort = TextUtils.isEmpty(portStr) ? 50051 : Integer.valueOf(portStr);
                String result = signup(mHost, mPort, mUser, mPwd);
                Toast.makeText(DemoActivity.this,"From Server: "+result,Toast.LENGTH_LONG).show();
                if("success".equals(result)) {
                    mStatusTv.setText(mUser + " 注册成功!");
                }
                signUpButton.setEnabled(true);
            }
        });
    }

    public void logoutClick(View view) {
        ((InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE))
                .hideSoftInputFromWindow(hostEdit.getWindowToken(), 0);
        logoutButton.setEnabled(false);
        mWorkerHandler.post(new Runnable() {
            @Override
            public void run() {
                mIsOnline = false;
                mWorkerHandler.removeCallbacks(mHeartBeat);
                mHost = hostEdit.getText().toString();
                String portStr = portEdit.getText().toString();
                mUser  = userEdit.getText().toString();
                mPwd  = pwdEdit.getText().toString();
                mPort = TextUtils.isEmpty(portStr) ? 50051 : Integer.valueOf(portStr);
                String result = logout(mHost, mPort, mUser, mPwd);;
                Toast.makeText(DemoActivity.this,"From Server: "+result,Toast.LENGTH_LONG).show();
                String[] res = result.split(":");
                if(res.length >= 2 && "success".equals(res[0])) {
                    mIsOnline = true;
                    mWorkerHandler.post(mHeartBeat);
                    mStatusTv.setText(mUser + " 登出成功!");
                    signInButton.setEnabled(true);
                    logoutButton.setEnabled(false);
                } else {
                    mStatusTv.setText(mUser + " 登出失败!");
                    signInButton.setEnabled(true);
                    logoutButton.setEnabled(false);
                }
            }
        });
    }

    public static native String signin(String host, int port, String username, String pwd);
    public static native String heartbeat(String host, int port, String username, String pwd);
    public static native String logout(String host, int port, String username, String pwd);
    public static native String signup(String host, int port, String username, String pwd);

}
