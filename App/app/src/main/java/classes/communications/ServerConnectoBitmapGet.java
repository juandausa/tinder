package classes.communications;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;

import java.io.InputStream;
import java.net.URL;

/**
 * Worker that loads the image from the url in background
 */
public class ServerConnectoBitmapGet extends AsyncTask<String, String, Bitmap> {

    protected AsyncCallerBitmapResponse mCaller = null;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor for the class
     * @param caller the context that interacts with this
     */
    public ServerConnectoBitmapGet(AsyncCallerBitmapResponse caller) {
        this.mCaller = caller;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Loads the image into a bitmap from the url in background
     * @param args arguments, the first is a string with the url
     * @return the bitmap loaded
     */
    protected Bitmap doInBackground(String... args) {
        Bitmap bitmap = null;
        String imageUrl = args[0];
        try {
            bitmap = BitmapFactory.decodeStream((InputStream) new URL(imageUrl).getContent());
        } catch (Exception e) {
            e.printStackTrace();
        }
        return bitmap;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Calls the processFinish method from the context
     * @param image the image to be passed to the context
     */
    protected void onPostExecute(Bitmap image) {
        mCaller.processFinish(image);
    }
}

