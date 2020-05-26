package de.twometer.mycraft;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;

import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import de.twometer.mycraft.interop.JavaCallback;
import de.twometer.mycraft.interop.NativeLib;
import de.twometer.mycraft.net.Listener;
import de.twometer.mycraft.net.McClient;
import de.twometer.mycraft.net.packet.C04PlayerPosition;
import de.twometer.mycraft.net.packet.C05PlayerLook;
import de.twometer.mycraft.net.packet.C06PlayerPosLook;
import de.twometer.mycraft.res.FontProcessor;
import de.twometer.mycraft.res.ResourceManager;

public class GameActivity extends AppCompatActivity {

    public static final String EXTRA_SERVER = "mycraft.extra.server";
    public static final String EXTRA_USERNAME = "mycraft.extra.username";

    private static final float CONTROL_PADDING = 0.05f / 2;
    private static final float CONTROL_SIZE = 0.15f / 2;

    private GLSurfaceView glSurfaceView;
    private NativeLib nativeLib;
    private ResourceManager resourceManager;
    private McClient mcClient;

    private float previousX0;
    private float previousY0;

    private float previousX1;
    private float previousY1;

    private boolean previousMultitouch;

    private int viewportWidth;
    private int viewportHeight;

    private int[] controlPadBorder;

    private boolean isConnected;

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
        nativeLib.uploadFontWidths(FontProcessor.measureFont(BitmapFactory.decodeFile(resourceManager.getAssetFile("textures/ascii.png"))));
        nativeLib.register(new JavaCallback() {
            @Override
            public void setPosition(double x, double y, double z) {
                if (mcClient.isLoginMode())
                    return;
                try {
                    mcClient.sendPacket(new C04PlayerPosition(x, y, z, true));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void setRotation(float yaw, float pitch) {
                if (mcClient.isLoginMode())
                    return;
                try {
                    mcClient.sendPacket(new C05PlayerLook(yaw, pitch, true));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void setPosAndRot(double x, double y, double z, float yaw, float pitch) {
                if (mcClient.isLoginMode())
                    return;
                try {
                    mcClient.sendPacket(new C06PlayerPosLook(x, y, z, yaw, pitch, true));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        glSurfaceView = new GLSurfaceView(this);
        glSurfaceView.setEGLContextClientVersion(3);
        glSurfaceView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                nativeLib.onSurfaceCreated();
                startNetworkThread();
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

                if (!isMultitouch && previousMultitouch) {
                    previousX0 = x0;
                    previousY0 = y0;
                }

                if ((action == MotionEvent.ACTION_DOWN || action == MotionEvent.ACTION_POINTER_DOWN) && !isInPad)
                    nativeLib.onTouch(true, x, y);
                else if ((action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_POINTER_UP) && !isInPad)
                    nativeLib.onTouch(false, x, y);

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
                previousMultitouch = isMultitouch;
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
        if (!isConnected) {
            isConnected = true;

            Intent intent = getIntent();
            final String username = intent.getStringExtra(EXTRA_USERNAME);
            final String server = intent.getStringExtra(EXTRA_SERVER);

            Thread thread = new Thread(new Runnable() {
                @Override
                public void run() {
                    mcClient = new McClient();
                    try {
                        mcClient.login(username, server, 25565);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    mcClient.setListener(new Listener() {
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

}
