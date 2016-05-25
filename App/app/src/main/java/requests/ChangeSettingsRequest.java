package requests;

import android.util.Log;

import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.R;
import com.tinder_app.SettingsActivity;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;
import classes.SessionManager;

/**
 * Created by fabrizio on 24/05/16.
 */
public class ChangeSettingsRequest extends JSONRequest {

    private SettingsActivity mContext;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class UpdateProfileRequest
     * @param context the context from where this request is being constructed
     */
    public ChangeSettingsRequest(SettingsActivity context) {
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
        Log.i("user", json.toString());
        String path = Constants.FILTERS_PATH + SessionManager.getUserId(mContext);
        super.send(json, path);
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
            if (response.getInt("status_code") == 200) {
                saveChanges();
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

    /**
     * Method that wraps a call to the mehod saveChanges of EditProfileActivity
     */
    private void saveChanges() {
        mContext.saveChanges();
    }
}

