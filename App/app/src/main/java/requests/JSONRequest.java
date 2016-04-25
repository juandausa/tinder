package requests;

import android.content.Context;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;

import org.json.JSONObject;


/**
 * Abstract class that sets the shape of a Request that sends and receives a JSONObject
 */
public abstract class JSONRequest extends AbstractRequest {

    /**
     * Constructor of the class JSONRequest
     * @param context the context from where this request is being constructed
     **/
    protected JSONRequest(Context context) {
        super(context);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Builds the request. Generates the path and sets the data to be sent from the json.
     * @param path the path used to send the request
     * @param json the data to be sent
     * @return the generated request
     */
    @Override
    protected Request buildRequest(String path, JSONObject json) {
        return new JsonObjectRequest(mMethod, path, json, mResponseListener, mErrorListener);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets a response listener on the request that will call to onResponse
     */
    @Override
    protected void setResponseListener() {
        mResponseListener = new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                JSONRequest.this.onResponse(response);
            }
        };
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets an error listener on the request that will call to OnError.
     */
    @Override
    protected void setErrorListener() {
        mErrorListener = new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                JSONRequest.this.onError(error);
            }
        };
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback function that has the logic for handling the response
     * @param response the response of the request in format JSONObject
     */
    protected abstract void onResponse(JSONObject response);

}
