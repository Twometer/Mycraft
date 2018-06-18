package de.twometer.mycraft;

import android.annotation.SuppressLint;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;

import java.io.IOException;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import de.twometer.mycraft.interop.NativeLib;
import de.twometer.mycraft.net.Listener;
import de.twometer.mycraft.net.McClient;
import de.twometer.mycraft.res.ResourceManager;

public class MainActivity extends AppCompatActivity {

    private static final float CONTROL_PADDING = 0.05f / 2;
    private static final float CONTROL_SIZE = 0.15f / 2;

    private GLSurfaceView glSurfaceView;
    private NativeLib nativeLib;
    private ResourceManager resourceManager;

    private float previousX0;
    private float previousY0;

    private float previousX1;
    private float previousY1;

    private int viewportWidth;
    private int viewportHeight;

    private int[] controlPadBorder;


    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        resourceManager = new ResourceManager(this);
        try {
            resourceManager.prepareFirstRun();
        } catch (IOException e) {
            e.printStackTrace();
        }
        nativeLib = new NativeLib();
        nativeLib.setAssetsFolder(resourceManager.getAssetsDir().getAbsolutePath());
        glSurfaceView = new GLSurfaceView(this);
        glSurfaceView.setEGLContextClientVersion(3);
        glSurfaceView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                nativeLib.onSurfaceCreated();
            }

            @Override
            public void onSurfaceChanged(GL10 gl, int width, int height) {
                viewportWidth = width;
                viewportHeight = height;
                controlPadBorder = new int[]{
                        (int) (viewportWidth * (CONTROL_PADDING * 4 + CONTROL_SIZE * 3)),
                        viewportHeight - (int) (viewportWidth * (CONTROL_PADDING * 4 + CONTROL_SIZE * 3)) // Yes, viewportWidth. Because opengl
                };
                nativeLib.onSurfaceChanged(width, height);
            }

            @Override
            public void onDrawFrame(GL10 gl) {
                nativeLib.onDrawFrame();
            }
        });

        glSurfaceView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                int action = event.getActionMasked();
                int index = event.getActionIndex();

                boolean isMultitouch = event.getPointerCount() > 1;

                float x = event.getX(index);
                float y = event.getY(index);

                float x0 = event.getX(0);
                float y0 = event.getY(0);

                float x1 = isMultitouch ? event.getX(1) : previousX1;
                float y1 = isMultitouch ? event.getY(1) : previousY1;

                boolean isInPad = x <= controlPadBorder[0] && y > controlPadBorder[1];
                boolean isInPad0 = x0 <= controlPadBorder[0] && y0 > controlPadBorder[1];
                boolean isInPad1 = x1 <= controlPadBorder[0] && y1 > controlPadBorder[1];

                if (isInPad && (action == MotionEvent.ACTION_DOWN || action == MotionEvent.ACTION_POINTER_DOWN)) {
                    nativeLib.onPadTouch(true, x, y);
                }

                if (isInPad && (action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_POINTER_UP)) {
                    nativeLib.onPadTouch(false, x, y);
                }

                if (action == MotionEvent.ACTION_MOVE) {
                    if (!isInPad0) {
                        nativeLib.onRotate(x0 - previousX0, y0 - previousY0);
                    } else if (!isInPad1) {
                        nativeLib.onRotate(x1 - previousX1, y1 - previousY1);
                    }
                }

                previousX0 = x0;
                previousY0 = y0;
                previousX1 = x1;
                previousY1 = y1;

                return true;
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
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
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
