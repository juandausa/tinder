package requests;

import android.content.Context;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.Volley;

import classes.Constants;


public final class RequestHandler {

    private static RequestHandler singleton;
    private static String serverUrl = Constants.IP_SERVER;
    private RequestQueue requestQueue;
    private static Context context;

    /**********************************************************************************************/
    /**********************************************************************************************/

    private RequestHandler(Context context) {
        RequestHandler.context = context;
        requestQueue = getRequestQueue();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public static synchronized RequestHandler getInstance(Context context) {
        if (singleton == null) {
            singleton = new RequestHandler(context);
        }
        return singleton;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public static String getServerUrl() {
        return RequestHandler.serverUrl;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public Context getContext() {
        return context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public RequestQueue getRequestQueue() {
        if (requestQueue == null) {
            requestQueue = Volley.newRequestQueue(context.getApplicationContext());
        }
        return requestQueue;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void setContext(Context context) {
        RequestHandler.context= context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void addToRequestQueue(Request req) {
        getRequestQueue().add(req);
    }
}