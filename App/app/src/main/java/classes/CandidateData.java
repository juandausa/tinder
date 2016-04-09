package classes;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by fabrizio on 04/04/16.
 */
public class CandidateData {

    private String userId;
    private String alias;
    private Bitmap photo;
    private JSONArray interests;
    private String age;

    public CandidateData(JSONObject candidate) {
        try {
            userId = candidate.getString("user_id");
            alias = candidate.getString("alias");
            byte[] decodedString = Base64.decode(candidate.getString("photo_profile"), Base64.DEFAULT);
            photo = BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
            interests = null;
            age = Integer.toString(candidate.getInt("age"));
        } catch (JSONException e) {}
    }

    public String getUserId() {
        return userId;
    }

    public String getAlias() {
        return alias;
    }

    public Bitmap getPhoto() {
        return photo;
    }

    public JSONArray getInterests() {
        return interests;
    }

    public String getAge() {
        return age;
    }
}
