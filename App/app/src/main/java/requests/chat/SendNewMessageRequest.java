package requests.chat;

import android.util.Log;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.MatchChatActivity;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;
import requests.JSONRequest;

/**
 * Created by fabrizio on 16/06/16.
 */
public class SendNewMessageRequest extends JSONRequest {


    private MatchChatActivity mContext;
    private String mMessage;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class SendNewMessageRequest
     *
     * @param context the context from where this request is being constructed
     **/
    public SendNewMessageRequest(MatchChatActivity context) {
        super(context);
        mContext = context;
        mMethod = Request.Method.POST;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onResponse(final JSONObject response) {
        mContext.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mContext.sendMessage(mMessage);
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void send(JSONObject json) {
        try {
            mMessage = json.getString(Constants.MESSAGE);
            super.send(json, Constants.SEND_MESSAGE + json.getString(Constants.USER_ID));
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR), e.getMessage());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onError(VolleyError error) {
        Toast.makeText(mContext, R.string.message_not_sent, Toast.LENGTH_LONG).show();
        Log.e(mContext.getString(R.string.REQUEST_ERROR), error.getMessage());
    }
}