package com.lxl.demo.gprc;

import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.ref.WeakReference;

import io.grpc.helloworldexample.cpp.R;

public class DemoActivity extends AppCompatActivity {

    static {
        System.loadLibrary("grpc-demo");
    }

    private Button signInButton;
    private Button signUpButton;
    private EditText hostEdit;
    private EditText portEdit;
    private EditText userEdit;
    private EditText pwdEdit;

    private SignInTask signinTask;
    private SignUpTask signupTask;

    private boolean mLoginSuccess = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        signInButton = findViewById(R.id.signin_button);
        signUpButton = findViewById(R.id.signup_button);
        hostEdit = findViewById(R.id.host_edit_text);
        portEdit = findViewById(R.id.port_edit_text);
        userEdit = findViewById(R.id.user_edit_text);
        pwdEdit = findViewById(R.id.pwd_edit_text);
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (signinTask != null) {
            signinTask.cancel(true);
            signinTask = null;
        }
        if (signupTask != null) {
            signupTask.cancel(true);
            signupTask = null;
        }
    }

    public void signInClick(View view) {
        ((InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE))
                .hideSoftInputFromWindow(hostEdit.getWindowToken(), 0);
        signInButton.setEnabled(false);
        signinTask = new SignInTask(this);
        signinTask.executeOnExecutor(
                AsyncTask.THREAD_POOL_EXECUTOR,
                hostEdit.getText().toString(),
                portEdit.getText().toString(),
                userEdit.getText().toString(),
                pwdEdit.getText().toString());
    }

    public void signUpClick(View view) {
        ((InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE))
                .hideSoftInputFromWindow(hostEdit.getWindowToken(), 0);
        signUpButton.setEnabled(false);
        signupTask = new SignUpTask(this);
        signupTask.executeOnExecutor(
                AsyncTask.THREAD_POOL_EXECUTOR,
                hostEdit.getText().toString(),
                portEdit.getText().toString(),
                userEdit.getText().toString(),
                pwdEdit.getText().toString());
    }

    private static class SignInTask extends AsyncTask<String, Void, String> {
        private final WeakReference<DemoActivity> activityReference;

        private SignInTask(DemoActivity activity) {
            this.activityReference = new WeakReference<DemoActivity>(activity);
        }

        @Override
        protected String doInBackground(String... params) {
            String host = params[0];
            String portStr = params[1];
            String user = params[2];
            String pwd = params[3];
            int port = TextUtils.isEmpty(portStr) ? 50051 : Integer.valueOf(portStr);
            return signin(host, port, user,pwd);
        }

        @Override
        protected void onPostExecute(String result) {
            DemoActivity activity = activityReference.get();
            if (activity == null || isCancelled()) {
                return;
            }
            Button signInButton = activity.findViewById(R.id.signin_button);
            signInButton.setEnabled(true);
        }
    }

    private static class SignUpTask extends AsyncTask<String, Void, String> {
        private final WeakReference<DemoActivity> activityReference;

        private SignUpTask(DemoActivity activity) {
            this.activityReference = new WeakReference<DemoActivity>(activity);
        }

        @Override
        protected String doInBackground(String... params) {
            String host = params[0];
            String portStr = params[1];
            String user = params[2];
            String pwd = params[3];
            int port = TextUtils.isEmpty(portStr) ? 50051 : Integer.valueOf(portStr);
            return signup(host, port, user,pwd);
        }

        @Override
        protected void onPostExecute(String result) {
            DemoActivity activity = activityReference.get();
            if (activity == null || isCancelled()) {
                return;
            }
            Toast.makeText(activityReference.get(),"From Server: "+result,Toast.LENGTH_LONG).show();
            Button button = activity.findViewById(R.id.signup_button);
            button.setEnabled(true);
        }
    }

    public static native String signin(String host, int port, String username, String pwd);
    public static native String signup(String host, int port, String username, String pwd);

}
