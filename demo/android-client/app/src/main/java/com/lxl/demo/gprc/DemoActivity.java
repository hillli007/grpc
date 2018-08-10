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

    private Button sendButton;
    private Button serverButton;
    private EditText hostEdit;
    private EditText portEdit;
    private EditText messageEdit;
    private EditText serverPortEdit;
    private TextView resultText;
    private GrpcTask grpcTask;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_helloworld);
        sendButton = (Button) findViewById(R.id.send_button);
        serverButton = (Button) findViewById(R.id.server_button);
        hostEdit = (EditText) findViewById(R.id.host_edit_text);
        portEdit = (EditText) findViewById(R.id.port_edit_text);
        messageEdit = (EditText) findViewById(R.id.message_edit_text);
        serverPortEdit = (EditText) findViewById(R.id.server_port_edit_text);
        resultText = (TextView) findViewById(R.id.grpc_response_text);
        resultText.setMovementMethod(new ScrollingMovementMethod());
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (grpcTask != null) {
            grpcTask.cancel(true);
            grpcTask = null;
        }
    }

    public void sendMessage(View view) {
        ((InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE))
                .hideSoftInputFromWindow(hostEdit.getWindowToken(), 0);
        sendButton.setEnabled(false);
        resultText.setText("");
        grpcTask = new GrpcTask(this);
        grpcTask.executeOnExecutor(
                AsyncTask.THREAD_POOL_EXECUTOR,
                hostEdit.getText().toString(),
                messageEdit.getText().toString(),
                portEdit.getText().toString());
    }

    private static class GrpcTask extends AsyncTask<String, Void, String> {
        private final WeakReference<DemoActivity> activityReference;

        private GrpcTask(DemoActivity activity) {
            this.activityReference = new WeakReference<DemoActivity>(activity);
        }

        @Override
        protected String doInBackground(String... params) {
            String host = params[0];
            String message = params[1];
            String portStr = params[2];
            int port = TextUtils.isEmpty(portStr) ? 50051 : Integer.valueOf(portStr);
            return signin(host, port, message,message);
        }

        @Override
        protected void onPostExecute(String result) {
            DemoActivity activity = activityReference.get();
            if (activity == null || isCancelled()) {
                return;
            }
            TextView resultText = (TextView) activity.findViewById(R.id.grpc_response_text);
            Button sendButton = (Button) activity.findViewById(R.id.send_button);
            resultText.setText(result);
            sendButton.setEnabled(true);
        }
    }

    public static native String signin(String host, int port, String username, String pwd);

}
