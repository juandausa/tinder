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
 * Request that asks if a user is registered or not. If not, the user is registered.
 */
public class LoginRequest extends SimpleRequest {

    private static final int REGISTERED = 200;
    private static final int UNREGISTERED = 304;
    private JSONObject mUser;
    private LoginActivity mContext;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class LoginRequest
     *
     * @param context the context from where this request is being constructed
     */
    public LoginRequest(LoginActivity context) {
        super(context);
        mMethod = Request.Method.GET;
        mContext = context;
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
        mUser = json;
        JSONObject empty = new JSONObject();
        try {
            empty.put(Constants.USER_ID, json.getString(Constants.USER_ID));
            Log.i(Constants.USER_ID, empty.getString(Constants.USER_ID));
            String route = Constants.LOGIN_PATH + empty.getString(Constants.USER_ID);
            super.send(empty, route);
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback function that has the logic for handling the response
     *
     * @param response the response of the request in format JSONObject
     */
    @Override
    protected void onResponse(Integer response) {
        Log.i("RESPONSE", response.toString());
        switch (response) {
            case REGISTERED:
                launchMainActivity();
                break;
            case UNREGISTERED:
                NewRegisterRequest req = new NewRegisterRequest(mContext);
                req.send(mUser);
                break;
            default:
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
        Log.e(mContext.getString(R.string.REQUEST_ERROR) + "2", error.toString());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Method that wraps a call to launchMainActivity of the activity LoginActivity and is called
     * from onResponse
     */
    private void launchMainActivity() {
        mContext.launchMainActivity();
    }
}
