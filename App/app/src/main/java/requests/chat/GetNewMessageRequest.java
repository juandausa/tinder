package requests.chat;

import android.util.Log;

import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.MatchChatActivity;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;
import requests.JSONRequest;

/**
 * Request that gets a new message from the other user
 */
public class GetNewMessageRequest extends JSONRequest {


    private MatchChatActivity mContext;
    //private String TO_USER_ID = "to_user_id";


    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class GetNewMessageRequest
     *
     * @param context the context from where this request is being constructed
     **/
    public GetNewMessageRequest(MatchChatActivity context) {
        super(context);
        mContext = context;
        mMethod = Request.Method.POST;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * On response, send the message received to the context
     * @param response the response of the request in format JSONObject
     */
    @Override
    protected void onResponse(final JSONObject response) {
        try {
            final String message = response.getString(Constants.MESSAGE);
            if (message.equals("")) return;
            mContext.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    mContext.mimicOtherMessage(message);

                }
            });
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Method that sends the request
     * @param json this parameter has the data that has to be used in the sending of the request
     */
    @Override
    public void send(JSONObject json) {
        try {
            super.send(json, Constants.GET_MESSAGE + json.getString(Constants.USER_ID));
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback executed on error
     * @param error belonging to the request sent
     */
    @Override
    protected void onError(VolleyError error) {
        Log.e(mContext.getString(R.string.REQUEST_ERROR), error.getMessage());
    }
}
