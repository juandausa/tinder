package requests;

import android.util.Log;

import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.MainActivity;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;

/**
 * Request that sends a decision of give a "dislike" to other user
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

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Do nothing on response
     * @param response the response of the request in format JSONObject
     */
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

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Send a request using the data of the json passed as parameter
     *
     * @param json this parameter has the data that has to be used in the sending of the request
     */
    @Override
    public void send(JSONObject json) {
        try {
            super.send(json, Constants.DISLIKES_PATH + json.getString(Constants.USER_ID));
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback function that has the logic for handling errors
     *
     * @param error belonging to the request sent
     */
    @Override
    protected void onError(VolleyError error) {
        Log.e(mContext.getString(R.string.REQUEST_ERROR) + DISLIKE_STRING, error.getMessage());
    }

}
