package classes.communications;

import android.os.AsyncTask;

import java.net.URL;

/**
 * Worker that loads the text from the url in background
 */
public class ServerConnectGet extends AsyncTask<String, String, String> {

    protected AsyncCallerResponse mCaller = null;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor for the class
     * @param caller the context that interacts with this
     */
    public ServerConnectGet(AsyncCallerResponse caller) {
        this.mCaller = caller;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Loads the image into a bitmap from the url in background
     * @param args arguments, the first is a string with the url
     * @return the bitmap loaded
     */
    protected String doInBackground(String... args) {
        String data = null;
        String url = args[0];
        try {
            data = (String) new URL(url).getContent();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return data;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Calls the processFinish method from the context
     * @param data the text to be passed to the context
     */

    protected void onPostExecute(String data) {
        mCaller.processFinish(data);
    }
}

