package requests;

import android.content.Context;
import android.util.Log;

import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.MainActivity;
import com.tinder_app.PeopleListFragment;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;

/**
 * Created by fabrizio on 22/04/16.
 */
public class GetProfileRequest extends JSONRequest {

    MainActivity mActivity;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * @param context
     **/
    public GetProfileRequest(MainActivity context) {
        super(context);
        mActivity = context;
        mContext = context;
        mMethod = Request.Method.GET;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onResponse(JSONObject response) {
        Log.i("PROFILE", response.toString());
        mActivity.setProfile(response);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void send(JSONObject json) {
        try {
            super.send(json, Constants.USER_DATA_PATH + json.getString("user_id"));
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onError(VolleyError error) {
        Log.e(mContext.getString(R.string.REQUEST_ERROR)+" PROFILE",error.toString());
    }
}
