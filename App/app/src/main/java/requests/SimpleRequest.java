package requests;

import android.content.Context;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;

import org.json.JSONObject;

/**
 * Abstract class that sets the shape of a Request that sends nothing and receives a response code
 */
public abstract class SimpleRequest extends AbstractRequest {

    /**
     * Constructor of the class SimpleRequest
     *
     * @param context the context from where this request is being constructed
     **/
    protected SimpleRequest(Context context) {
        super(context);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Builds the request. Generates the path and sets the data to be sent from the json.
     *
     * @param path the path used to send the request
     * @param json the data to be sent
     * @return the generated request
     */
    @Override
    protected Request buildRequest(String path, JSONObject json) {
        return new StatusRequest(mMethod, path, mResponseListener, mErrorListener);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets a response listener on the request that will call to onResponse
     */
    @Override
    protected void setResponseListener() {
        mResponseListener = new Response.Listener<Integer>() {
            @Override
            public void onResponse(Integer response) {
                SimpleRequest.this.onResponse(response);
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
                SimpleRequest.this.onError(error);
            }
        };
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback function that has the logic for handling the response
     *
     * @param response the response of the request in format JSONObject
     */
    protected abstract void onResponse(Integer response);

}
