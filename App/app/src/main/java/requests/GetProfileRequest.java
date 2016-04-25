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
 * Request that gets the profile data of the user
 */
public class GetProfileRequest extends JSONRequest {

    private MainActivity mActivity;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class GetProfileRequest
     * @param context the context from where this request is being constructed
     **/
    public GetProfileRequest(MainActivity context) {
        super(context);
        mActivity = context;
        mContext = context;
        mMethod = Request.Method.GET;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback function that has the logic for handling the response
     * @param response the response of the request in format JSONObject
     */
    @Override
    protected void onResponse(JSONObject response) {
        Log.i("PROFILE", response.toString());
        mActivity.setProfile(response);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Send a request using the data of the json passed as parameter
     * @param json this parameter has the data that has to be used in the sending of the request
     */
    @Override
    public void send(JSONObject json) {
        try {
            super.send(json, Constants.USER_DATA_PATH + json.getString(Constants.USER_ID));
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback function that has the logic for handling errors
     * @param error belonging to the request sent
     */
    @Override
    protected void onError(VolleyError error) {
        Log.e(mContext.getString(R.string.REQUEST_ERROR) + " PROFILE", error.toString());
    }
}
