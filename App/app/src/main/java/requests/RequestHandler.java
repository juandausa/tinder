package requests;

import android.content.Context;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.Volley;

import classes.Constants;

/**
 * Class that wraps the logic and use of the Volley Library for sending Request.
 */
public final class RequestHandler {

    private static RequestHandler singleton;
    private static String serverUrl = Constants.IP_SERVER;
    private Context mContext;
    private RequestQueue mRequestQueue;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class RequestHandler
     *
     * @param context the context from where the request is being constructed
     */
    private RequestHandler(Context context) {
        mContext = context;
        mRequestQueue = getRequestQueue();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * @param context the context from where the instance is being required
     * @return an instance of RequestHandler
     */
    public static synchronized RequestHandler getInstance(Context context) {
        if (singleton == null) {
            singleton = new RequestHandler(context);
        }
        return singleton;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the server url
     *
     * @return the server url
     */
    public static String getServerUrl() {
        return RequestHandler.serverUrl;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the context from where this handler is being used
     *
     * @return the context from where this handler is being used
     */
    public Context getContext() {
        return mContext;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the context from where this handler is being used
     *
     * @param context the context to be setted
     */
    public void setContext(Context context) {
        mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the request queue, where the requests are queued for sending
     *
     * @return the request queue
     */
    public RequestQueue getRequestQueue() {
        if (mRequestQueue == null) {
            mRequestQueue = Volley.newRequestQueue(mContext.getApplicationContext());
        }
        return mRequestQueue;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Adds a new request to the request's queue
     *
     * @param req the new request to be added to the queue
     */
    public void addToRequestQueue(Request req) {
        getRequestQueue().add(req);
    }
}