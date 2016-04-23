package requests;

import android.util.Log;

import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.EditProfileActivity;
import com.tinder_app.LoginActivity;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;

/**
 * Created by fabrizio on 23/04/16.
 */
public class UpdateProfileRequest extends JSONRequest {

    private EditProfileActivity mContext;

    /**********************************************************************************************/
    /**********************************************************************************************/

    public UpdateProfileRequest(EditProfileActivity context) {
        super(context);
        mMethod = Request.Method.POST;
        mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void send(JSONObject json) {
        Log.i("user", json.toString());
        try {
            String path = Constants.USER_UPDATE_DATA_PATH + json.getString("user_id");
            super.send(json, path);
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR)+"_UPDATE", e.toString());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

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

    @Override
    public void onError(VolleyError error) {
        Log.e(mContext.getString(R.string.REQUEST_ERROR) + "1", error.getMessage());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void saveChanges() {
        mContext.saveChanges();
    }
}