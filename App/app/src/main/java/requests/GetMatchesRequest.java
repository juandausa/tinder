package requests;

import android.content.Context;
import android.util.Log;

import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.MatchesFragment;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;

/**
 * Request that gets the data and conversations of all matches of the user
 */
public class GetMatchesRequest extends JSONRequest {

    private static final String MATCHES = "matches";
    private MatchesFragment mFragment;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class GetCandidatesRequest
     *
     * @param context  the context from where this request is being constructed
     * @param fragment the fragment from where this request is being constructed
     **/
    public GetMatchesRequest(Context context, MatchesFragment fragment) {
        super(context);
        mFragment = fragment;
        mMethod = Request.Method.GET;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback function that has the logic for handling the response
     *
     * @param response the response of the request in format JSONObject
     */
    @Override
    protected void onResponse(JSONObject response) {
        try {
            Log.i(MATCHES, response.toString());
            mFragment.setMatches(response.getJSONArray(MATCHES));
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
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
            super.send(json, Constants.MATCHES_PATH + json.getString(Constants.USER_ID));
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
        Log.e(mContext.getString(R.string.REQUEST_ERROR) + MATCHES, error.toString());
        //mFragment.timeoutOnCandidatesRequest();
    }
}
