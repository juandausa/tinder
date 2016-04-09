package requests;

import android.content.Context;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;

import org.json.JSONObject;

/**
 * Created by fabrizio on 03/04/16.
 */
public abstract class AbstractRequest {
    protected RequestHandler requestHandler;
    protected Context mContext;
    protected Response.Listener mResponseListener;
    protected Response.ErrorListener mErrorListener;
    protected int mMethod;
    protected Request mRequest;

    /**********************************************************************************************/
    /**********************************************************************************************/

    public AbstractRequest(Context context) {
        requestHandler = RequestHandler.getInstance(context);
        mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    //Sincronico
    protected void send(JSONObject json, String route) {
        setResponseListener();
        setErrorListener();
        String path = RequestHandler.getServerUrl() + route;
        Request request = buildRequest(path, json);
        requestHandler.addToRequestQueue(request);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    protected abstract void setResponseListener();

    protected abstract void setErrorListener();

    protected abstract Request buildRequest(String path, JSONObject json);

    public abstract void send(JSONObject json);

    protected abstract void onError(VolleyError error);

}
