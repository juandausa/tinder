package requests;

import android.content.Context;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;

import org.json.JSONObject;

/**
 * Created by fabrizio on 03/04/16.
 */
public abstract class SimpleRequest extends AbstractRequest {

    /**
     * @param context
    **/
    public SimpleRequest(Context context) {
        super(context);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected Request buildRequest(String path, JSONObject json) {
        return new StatusRequest(mMethod, path, mResponseListener, mErrorListener);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

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

    protected abstract void onResponse(Integer response);

}
