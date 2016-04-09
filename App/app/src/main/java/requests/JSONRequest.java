package requests;

import android.content.Context;
import android.content.Intent;
import android.telecom.Call;
import android.util.Log;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.StringRequest;
import com.tinder_app.MainActivity;

import org.json.JSONObject;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeoutException;

import classes.Constants;

/**
 * Created by fabrizio on 03/04/16.
 */
public abstract class JSONRequest extends AbstractRequest {


    /**
     * @param context
     **/
    public JSONRequest(Context context) {
        super(context);
    }

    @Override
    protected Request buildRequest(String path, JSONObject json) {
        return new JsonObjectRequest(mMethod, path, json, mResponseListener, mErrorListener);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

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

    protected abstract void onResponse(JSONObject response);

}
