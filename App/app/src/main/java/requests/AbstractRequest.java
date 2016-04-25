package requests;

import android.content.Context;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.RetryPolicy;
import com.android.volley.VolleyError;

import org.json.JSONObject;

/**
 * Abstract class that sets the interfaces and common logic for request subclasses
 */
public abstract class AbstractRequest {

    private static final int TIMEOUT = 50000;
    protected RequestHandler mRequestHandler;
    protected Context mContext;
    protected Response.Listener mResponseListener;
    protected Response.ErrorListener mErrorListener;
    protected int mMethod;
    protected Request mRequest;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class AbstractRequest
     * @param context the context from where this request is being constructed
     */
    protected AbstractRequest(Context context) {
        mRequestHandler = RequestHandler.getInstance(context);
        mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Send a request using the data of the json passed as parameter. Sets the listeners and sets
     * the retry policy.
     * @param json this parameter has the data that has to be used in the sending of the request
     * @param route the route to construct the path of the request
     */
    protected void send(JSONObject json, String route) {
        setResponseListener();
        setErrorListener();
        String path = RequestHandler.getServerUrl() + route;
        Request request = buildRequest(path, json);
        setRetryPolicy(request);
        mRequestHandler.addToRequestQueue(request);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the retry polciy for retrying to send the request if an error ocurred
     * @param request the request to be sent
     */
    private void setRetryPolicy(Request request) {
        request.setRetryPolicy(new RetryPolicy() {
            @Override
            public int getCurrentTimeout() {
                return TIMEOUT;
            }

            @Override
            public int getCurrentRetryCount() {
                return TIMEOUT;
            }

            @Override
            public void retry(VolleyError error) throws VolleyError {

            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets a response listener on the request that will call to onResponse
     */
    protected abstract void setResponseListener();

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets an error listener on the request that will call to OnError.
     */
    protected abstract void setErrorListener();

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Builds the request. Generates the path and sets the data to be sent from the json.
     * @param path the path used to send the request
     * @param json the data to be sent
     * @return the generated request
     */
    protected abstract Request buildRequest(String path, JSONObject json);

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Send a request using the data of the json passed as parameter
     * @param json this parameter has the data that has to be used in the sending of the request
     */
    public abstract void send(JSONObject json);

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback function that has the logic for handling errors
     * @param error belonging to the request sent
     */
    protected abstract void onError(VolleyError error);

}
