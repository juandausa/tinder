package classes;

import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by fabrizio on 25/04/16.
 */
public class Conversation {

    private JSONArray mMessages;
    private int mMessage_index = 0;
    private static final String ME = "0";
    private static final String OTHER = "1";

    /**********************************************************************************************/
    /**********************************************************************************************/

    public Conversation(JSONArray messages) {
        mMessages = messages;
    }

    public Conversation(String messages) {
        try {
            JSONArray array = new JSONArray(messages);
            mMessages = array;
        } catch (JSONException e) {
            Log.e("JSON ERROR", e.toString());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public boolean currentMessageIsMine() {
        boolean isMine = true;
        try {
            JSONObject messageObject = (JSONObject)mMessages.get(mMessage_index);
            String key = (messageObject.names()).getString(0);
            //boolean isMine = (!messageObject.isNull(ME));
            //return isMine;
            isMine = key.equals(ME);
        } catch (JSONException e) {
            Log.e("JSON ERROR", e.toString());
            e.printStackTrace();
        }
        return isMine;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public String getCurrentMessage() {
        try {
            JSONObject messageObject = (JSONObject) mMessages.get(mMessage_index);
            String message = null;
            if (currentMessageIsMine()) {
                message = messageObject.getString(ME);
            } else {
                message = messageObject.getString(OTHER);
            }
            mMessage_index++;
            return message;
        } catch (JSONException e) {
            Log.e("JSON ERROR", e.toString());
            return "";
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public boolean noMoreMessages() {
        return (mMessage_index >= mMessages.length());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public String toString() {
        return mMessages.toString();
    }
}
