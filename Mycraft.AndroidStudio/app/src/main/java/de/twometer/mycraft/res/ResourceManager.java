package de.twometer.mycraft.res;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.os.Build;
import android.os.Environment;
import android.support.v4.content.ContextCompat;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import de.twometer.mycraft.MainActivity;

public class ResourceManager {

    private Context context;
    private File assetsDir;

    public ResourceManager(Context context) {
        this.context = context;
        this.assetsDir = new File(Environment.getExternalStorageDirectory(), "Mycraft");
    }

    public void prepareFirstRun() throws IOException {
        if (hasPermission()) {
            AssetManager manager = context.getAssets();
            for (String str : manager.list("gamedata")) {
                copyFolder(manager, "gamedata", str);
            }
        } else {
            requestFilePermissions();
        }
        this.assetsDir = new File(assetsDir, "gamedata");
    }

    private void copyFolder(AssetManager manager, String folder, String file) throws IOException {
        String currentDir = folder + "/" + file;
        for (String str : manager.list(currentDir)) {
            String currentFile = currentDir + "/" + str;
            InputStream inputStream = null;
            try {
                inputStream = manager.open(currentFile);
            } catch (IOException e) {
                e.printStackTrace();
            }
            if (inputStream == null) { // It's a folder
                copyFolder(manager, currentDir, str);
            } else {
                File f = new File(assetsDir, currentFile);
                if (!f.getParentFile().exists()) f.getParentFile().mkdirs();
                writeToFile(inputStream, f);
                inputStream.close();
            }
        }
    }

    private void writeToFile(InputStream inputStream, File file) throws IOException {
        if (file.exists()) file.delete();
        file.createNewFile();
        FileOutputStream outputStream = new FileOutputStream(file);
        byte[] buf = new byte[4096];
        while (true) {
            int read = inputStream.read(buf);
            if (read <= 0) break;
            outputStream.write(buf, 0, read);
        }
        outputStream.close();
    }

    private void requestFilePermissions() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            ((MainActivity) context).requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE}, 123);
        }
    }

    private boolean hasPermission() {
        return ContextCompat.checkSelfPermission(context, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED;
    }


    public File getAssetsDir() {
        return assetsDir;
    }
}
