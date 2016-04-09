package facebook_data;

import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Class that contains the logic of how to process the data of the facebook user's interests.
 */
public class FacebookInterestParser {

    /**
     * Gets the value of the field "name" of the JSON received as parameter.
     * @param interest the JSON object to process.
     * @return a the String with the value of the field "name" of the JSON object.
     * @throws JSONException if field "name" does not exist in the JSON object.
     */
    private String getInterestName(JSONObject interest) throws JSONException {
        return interest.getString("name");
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Process the JSON object data, received as parameter to give it a new format.
     * The format of the returned JSON is the parameter category as key and a JSONArray of Strings
     * as value . These strings are the names of the interests in the data object.
     * @param data The JSON object containing the interests.
     * @param category The category of the interests contained in data.
     * @return A JSONObject with the category of the interests as key and a JSONArray of the
     * interest's names.
     */
    public JSONArray parseInterests(JSONObject data, String category) {
        JSONArray interestsArray = new JSONArray();
        try {
            Log.e("data", data.toString());
            JSONArray interests = data.getJSONArray("data");
            int length = interests.length();
            for (int i = 0; i < length; i++) {
                interestsArray.put(getInterestName(interests.getJSONObject(i)));
            }
        } catch (JSONException e) {
            Log.e("ParseErr", e.getMessage());
        }
        return interestsArray;
    }
}
