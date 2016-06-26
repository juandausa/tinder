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
 * Created by fabrizio on 16/06/16.
 */
public class GetNewMessageService implements Runnable {

    private static final int TIME = 5000;
    private MatchChatActivity mContext;

    public GetNewMessageService(MatchChatActivity context) {
        mContext = context;
    }

    @Override
    public void run() {
        android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
        while (mContext.isAlive()) {
            if (mContext.mOtherUserId != null) {
                GetNewMessageRequest request = new GetNewMessageRequest(mContext);
                JSONObject data = new JSONObject();
                try {
                    data.put("to_user_id", SessionManager.getUserId(mContext));
                    data.put(Constants.USER_ID, mContext.mOtherUserId);
                    request.send(data);
                } catch (JSONException e) {
                    e.printStackTrace();
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
