package classes;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Class that contains the data of a match of the user
 */
public class MatchData extends UserData {

    private static final String MESSAGES = "messages";
    private Conversation mConversation;

    /**
     * Constructor of the class MatchData
     *
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

    /**
     * Gets the conversation of the user with this match
     *
     * @return the conversation
     */
    public Conversation getConversation() {
        return mConversation;
    }
}