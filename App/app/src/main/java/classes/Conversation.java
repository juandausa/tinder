package classes;

import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Class that modelates a conversation between two users
 */
public class Conversation {

    private static final String ME = "0";
    private static final String OTHER = "1";
    private JSONArray mMessages;
    private int mMessageIndex = 0;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class Conversation
     * @param messages the messages of the conversation
     */
    public Conversation(JSONArray messages) {
        mMessages = messages;
    }

    /**
     * Constructor of the class Conversation
     * @param messages the messages of the conversation
     */
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

    /**
     * Returns true if the message is from the user
     * @return true if the message is from the user
     */
    public boolean currentMessageIsMine() {
        boolean isMine = true;
        try {
            JSONObject messageObject = (JSONObject) mMessages.get(mMessageIndex);
            String key = (messageObject.names()).getString(0);
            //boolean isMine = (!messageObject.isNull(ME));
            //return isMine;
            isMine = key.equals(ME);
        } catch (JSONException e) {
            Log.e("JSON ERROR", e.toString());
        }
        return isMine;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Get the current message, and advances to the next
     * @return the current message in the conversation
     */
    public String getCurrentMessage() {
        try {
            JSONObject messageObject = (JSONObject) mMessages.get(mMessageIndex);
            String message = null;
            if (currentMessageIsMine()) {
                message = messageObject.getString(ME);
            } else {
                message = messageObject.getString(OTHER);
            }
            mMessageIndex++;
            return message;
        } catch (JSONException e) {
            Log.e("JSON ERROR", e.toString());
            return "";
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns true if there are no more messages
     * @return true if there are no more messages in the conversation to be read
     */
    public boolean noMoreMessages() {
        return (mMessageIndex >= mMessages.length());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Converts the conversation into a string
     * @return the string of the conversation
     */
    @Override
    public String toString() {
        return mMessages.toString();
    }
}
