package classes;

import org.json.JSONException;
import org.json.JSONObject;


public class User {

    private JSONObject mInterests = null;
    private String mUserId = null;
    private int mLatitude =  -1;
    private int mLongitude = -1;
    private String mAlias = null;
    private String mUsername = null;
    private String mEmail = null;
    private String mPhoto = null;

    /**********************************************************************************************/
    /**********************************************************************************************/

    private User() {
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public static User Build() {
        return new User();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public User addUsername(String username) {
        this.mUsername = username;
        return this;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public User addUserId(String userId) {
        this.mUserId = userId;
        return this;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public User addAlias(String alias) {
        this.mAlias = alias;
        return this;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public User addEmail(String email) {
        this.mEmail = email;
        return this;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public User addLocation(int latitude, int longitude) {
        this.mLatitude = latitude;
        this.mLongitude = longitude;
        return this;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public User addInterests(JSONObject interests) {
        this.mInterests = interests;
        return this;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public User addProfilePhoto(String profile_photo) {
        this.mPhoto = profile_photo;
        return this;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/


    public JSONObject toJSON() {
        try {
            JSONObject json = new JSONObject();
            json.put("user_id", this.mUserId);
            json.put("name", this.mUsername);
            json.put("alias", this.mAlias);
            json.put("email", this.mEmail);
            json.put("interests", this.mInterests);
            json.put("photo_profile", this.mPhoto);
            JSONObject location = new JSONObject();
            location.put("latitude", this.mLatitude);
            location.put("longitude", this.mLongitude);
            json.put("location", location);
            return json;
        } catch (JSONException e) {
            return null;
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public User fromJSON(JSONObject json) {
        try {
            this.mUserId = json.getString("user_id");
            this.mUsername = json.getString("name");
            this.mAlias = json.getString("alias");
            this.mEmail = json.getString("email");
            this.mInterests = json.getJSONObject("interests");
            JSONObject location = json.getJSONObject("location");
            this.mLatitude = location.getInt("latitude");
            this.mLongitude = location.getInt("longitude");
            this.mPhoto = json.getString("photo_profile");
        } catch (JSONException e) {}
        return this;
    }
}
