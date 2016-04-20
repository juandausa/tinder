package requests;

import android.content.Context;
import android.util.Log;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.tinder_app.MainActivity;
import com.tinder_app.PeopleListFragment;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;

/**
 * Created by fabrizio on 01/04/16.
 */
public class GetCandidatesRequest extends JSONRequest {

    PeopleListFragment mFragment;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * @param context
     **/
    public GetCandidatesRequest(Context context, PeopleListFragment fragment) {
        super(context);
        mFragment = fragment;
        mMethod = Request.Method.GET;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onResponse(JSONObject response) {
        try {
            Log.i("CANDIDATES", response.toString());
            mFragment.setCandidates(response.getJSONArray("candidates"));
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void send(JSONObject json) {
        try {
            super.send(json, Constants.CANDIDATES_PATH + json.getString("user_id"));
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onError(VolleyError error) {
        Log.e(mContext.getString(R.string.REQUEST_ERROR),error.toString());
    }
}
