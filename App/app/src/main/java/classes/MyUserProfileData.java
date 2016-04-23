package classes;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by fabrizio on 22/04/16.
 */
public class MyUserProfileData extends UserData {

    private String mName;
    private String mEmail;

    public MyUserProfileData(JSONObject user) {
        super(user);
        try {
            mName = user.getString("name");
            mEmail = user.getString("email");
        } catch (JSONException e) {}
    }
}
