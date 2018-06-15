package de.twometer.mycraft;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import java.io.IOException;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import de.twometer.mycraft.interop.NativeLib;
import de.twometer.mycraft.net.Listener;
import de.twometer.mycraft.net.McClient;

public class MainActivity extends AppCompatActivity {

    private GLSurfaceView glSurfaceView;
    private NativeLib nativeLib;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        nativeLib = new NativeLib();
        glSurfaceView = new GLSurfaceView(this);
        glSurfaceView.setEGLContextClientVersion(3);
        glSurfaceView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                nativeLib.onSurfaceCreated();
            }

            @Override
            public void onSurfaceChanged(GL10 gl, int width, int height) {
                nativeLib.onSurfaceChanged(width, height);
            }

            @Override
            public void onDrawFrame(GL10 gl) {
                nativeLib.onDrawFrame();
            }
        });
        setContentView(glSurfaceView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (glSurfaceView != null) glSurfaceView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_FULLSCREEN | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION);
        if (glSurfaceView != null) glSurfaceView.onResume();
    }

    private void startNetworkThread() {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                McClient client = new McClient();
                try {
                    client.login("DevClient", "192.168.2.102", 25565);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                client.setListener(new Listener() {
                    @Override
                    public void onPacket(int id, byte[] packet) {
                        nativeLib.onPacket(id, packet);
                    }

                    @Override
                    public void onLoginStatusChanged(final String status) {

                    }

                    @Override
                    public void onLoginCompleted() {
                        nativeLib.onLoginCompleted();
                    }
                });
            }
        });
        thread.start();
    }

}
