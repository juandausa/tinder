package classes;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by fabrizio on 25/04/16.
 */
public class MatchData extends UserData {

    private static final String MESSAGES = "messages";
    private Conversation mConversation;

    /**
     * Constructor of the class MatchData
     * @param match the JSONObject containing the match data.
     */
    public MatchData(JSONObject match) {
        super(match);
        try {
            mConversation = new Conversation(match.getJSONArray(MESSAGES));

        } catch (JSONException e) {

        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public Conversation getConversation() {
        return mConversation;
    }
}