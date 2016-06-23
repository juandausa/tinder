package requests;

import android.util.Log;

import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.EditProfileActivity;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;

/**
 * Request that sends the updated data of the user
 */
public class UpdateProfileRequest extends JSONRequest {

    private EditProfileActivity mContext;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class UpdateProfileRequest
     * @param context the context from where this request is being constructed
     */
    public UpdateProfileRequest(EditProfileActivity context) {
        super(context);
        mMethod = Request.Method.PUT;
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
        try {
            String path = Constants.USER_UPDATE_DATA_PATH + json.getString(Constants.USER_ID);
            super.send(json, path);
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR) + "_UPDATE", e.toString());
        }
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
        Log.e(mContext.getString(R.string.REQUEST_ERROR) + "1", error.toString());
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