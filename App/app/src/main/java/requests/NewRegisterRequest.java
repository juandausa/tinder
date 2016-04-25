package requests;

import android.util.Log;
import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.LoginActivity;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;
import classes.Constants;

/**
 * Request that registers a user in the app
 */
public class NewRegisterRequest extends JSONRequest {

    private static final String USER = "user";
    private static final String STATUS_CODE = "status_code";
    private static final int OK = 200;
    private LoginActivity mContext;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class NewRegisterRequest
     * @param context the context from where this request is being constructed
     */
    public NewRegisterRequest(LoginActivity context) {
        super(context);
        mMethod = Request.Method.POST;
        mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Send a request using the data of the json passed as parameter
     * @param json this parameter has the data that has to be used in the sending of the request
     */
    @Override
    public void send(JSONObject json) {
        Log.i(USER, json.toString());
        super.send(json, Constants.REGISTER_PATH);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback function that has the logic for handling the response
     * @param response the response of the request in format JSONObject
     */
    @Override
    public void onResponse(JSONObject response) {
        Log.i("RESPONSE2", response.toString());
        try {
            if (response.getInt(STATUS_CODE) == OK) {
                launchMainActivity();
            }
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
    public void onError(VolleyError error) {
        Log.e(mContext.getString(R.string.REQUEST_ERROR) + "1", error.getMessage());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void launchMainActivity() {
        mContext.launchMainActivity();
    }
}
