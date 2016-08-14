package services;

import android.util.Log;

import com.tinder_app.MatchChatActivity;
import com.tinder_app.R;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;
import classes.SessionManager;
import requests.chat.GetNewMessageRequest;

/**
 * Daemon that checks for new messages
 */
public class GetNewMessageService implements Runnable {

    private static final int TIME = 5000;
    private MatchChatActivity mContext;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor for the class GetNewMessageService
     * @param context the context from where it is executed
     */
    public GetNewMessageService(MatchChatActivity context) {
        mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the new message in background every half a second
     */
    @Override
    public void run() {
        android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
        while (mContext.isAlive()) {
            if (mContext.getOtherUserId() != null) {
                GetNewMessageRequest request = new GetNewMessageRequest(mContext);
                JSONObject data = new JSONObject();
                try {
                    data.put("to_user_id", SessionManager.getUserId(mContext));
                    data.put(Constants.USER_ID, mContext.getOtherUserId());
                    request.send(data);
                } catch (JSONException e) {
                    Log.e(mContext.getString(R.string.JSON_ERROR), e.toString());
                }
            }
            try {
                Thread.sleep(TIME);
            } catch (InterruptedException e) {
                Log.e(mContext.getString(R.string.REQUEST_ERROR), e.toString());
            }
        }
    }
}
