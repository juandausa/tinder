package classes;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;

/**
 * Created by fabrizio on 22/04/16.
 */
public class UserData {

    protected String mUserId;
    protected String mAlias;
    protected String mPhoto;
    protected JSONArray mInterests;
    protected String mAge;
    protected JSONObject json;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class CandidateData, that represents a user that can be a candidadate to
     * match with the current user.
     * @param user data of the candidate to be builded.
     */
    public UserData(JSONObject user) {
        json = user;
        try {
            mUserId = user.getString("user_id");
            mAlias = user.getString("alias");
            mPhoto = user.getString("photo_profile");
            mInterests = user.getJSONArray("interests");
            mAge = Integer.toString(user.getInt("age"));
        } catch (JSONException e) {
            try {
                mInterests = new JSONArray(user.getString("interests"));
                mAge = user.getString("age");
            } catch (JSONException ex) {}
        }
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

    /**********************************************************************************************/
    /**********************************************************************************************/

    public JSONObject toJSON() {
        return json;
    }
}
