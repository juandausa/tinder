package classes;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Class that represents a candidate to be a match with the current user.
 */
public class CandidateData {

    private String mUserId;
    private String mAlias;
    private Bitmap mPhoto;
    private JSONArray mInterests;
    private String mAge;

    /**
     * Constructor of the class CandidateData, that represents a user that can be a candidadate to
     * match with the current user.
     * @param candidate data of the candidate to be builded.
     */
    public CandidateData(JSONObject candidate) {
        try {
            mUserId = candidate.getString("user_id");
            mAlias = candidate.getString("alias");
            byte[] decodedString = Base64.decode(candidate.getString("photo_profile"), Base64.DEFAULT);
            mPhoto = BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
            mInterests = null;
            mAge = Integer.toString(candidate.getInt("age"));
        } catch (JSONException e) { }
    }

    public String getUserId() {
        return mUserId;
    }

    public String getAlias() {
        return mAlias;
    }

    public Bitmap getPhoto() {
        return mPhoto;
    }

    public JSONArray getInterests() {
        return mInterests;
    }

    public String getAge() {
        return mAge;
    }
}
