package requests;

import android.content.Context;
import android.util.Log;

import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.MainActivity;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;

/**
 * Created by fabrizio on 13/06/16.
 */
public class SendDislikeRequest extends JSONRequest {

    private static final String DISLIKE_STRING = "_DISLIKE";
    private final String mStatusCode = "status_code";
    private final int mOk = 200;

    /**
     * Constructor of the class JSONRequest
     *
     * @param context the context from where this request is being constructed
     **/
    public SendDislikeRequest(MainActivity context) {
        super(context);
        mContext = context;
        mMethod = Request.Method.POST;
    }

    @Override
    protected void onResponse(JSONObject response) {
        try {
            if (response.getInt(mStatusCode) != mOk) {
                // TODO: Do something on error code received
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void send(JSONObject json) {
        try {
            super.send(json, Constants.DISLIKES_PATH + json.getString(Constants.USER_ID));
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
        }
    }

    @Override
    protected void onError(VolleyError error) {
        Log.e(mContext.getString(R.string.REQUEST_ERROR)+DISLIKE_STRING, error.getMessage());
    }

}