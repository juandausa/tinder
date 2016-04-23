package classes;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Parcel;
import android.os.Parcelable;
import android.util.Base64;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.Serializable;

/**
 * Class that represents a candidate to be a match with the current user.
 */
public class CandidateData {

    private String mUserId;
    private String mAlias;
    private String mPhoto;
    private JSONArray mInterests;
    private String mAge;
    private JSONObject json;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class CandidateData, that represents a user that can be a candidadate to
     * match with the current user.
     * @param candidate data of the candidate to be builded.
     */
    public CandidateData(JSONObject candidate) {
        json = candidate;
        try {
            mUserId = candidate.getString("user_id");
            mAlias = candidate.getString("alias");
            mPhoto = candidate.getString("photo_profile");
            mInterests = candidate.getJSONArray("interests");
            mAge = Integer.toString(candidate.getInt("age"));
        } catch (JSONException e) { }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the user id
     * @return the user id
     */
    public String getUserId() {
        return mUserId;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the alias of the user
     * @return the alias of the user
     */
    public String getAlias() {
        return mAlias;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the photo of the user in bitmap format
     * @return the photo of the user
     */
    public Bitmap getPhoto() {
        byte[] decodedString = Base64.decode(mPhoto, Base64.DEFAULT);
        return BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns a JSON Array with the interests of the user
     * @return a JSON Array with the interests of the user
     */
    public JSONArray getInterests() {
        return mInterests;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the age of the user
     * @return the age of the user
     */
    public String getAge() {
        return mAge;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public String toString() {
        return json.toString();
    }
}
