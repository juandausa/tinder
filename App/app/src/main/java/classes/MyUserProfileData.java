package classes;

import android.graphics.Bitmap;
import android.util.Base64;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;

/**
 * Created by fabrizio on 22/04/16.
 */
public class MyUserProfileData extends UserData {

    private String mName;
    private String mEmail;
    private String mGender;

    /**********************************************************************************************/
    /**********************************************************************************************/

    public MyUserProfileData(JSONObject user) {
        super(user);
        try {
            mName = user.getString("name");
            mEmail = user.getString("email");
            mGender = user.getString("gender");
        } catch (JSONException e) {}
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public String getName() {
        return mName;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public String getEmail() {
        return mEmail;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public String getGender() {
        return mGender;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void setAlias(String alias) {
        mAlias = alias;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void setPhoto(Bitmap photo) {
        if (photo == null) {
            mPhoto = null;
            if (json.has("photo_profile")) json.remove("photo_profile");
            return;
        }
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        photo.compress(Bitmap.CompressFormat.PNG, 100, byteArrayOutputStream);
        byte[] byteArray = byteArrayOutputStream .toByteArray();
        mPhoto = Base64.encodeToString(byteArray, Base64.DEFAULT);
        try {
            json.put("photo_profile", mPhoto);
        } catch (JSONException e) {}
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void setAge(String age) {
        mAge = age;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void setGender(String gender) {
        mGender = gender;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public String toString() {
        this.toJSON();
        return super.toString();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public JSONObject toJSON() {
        try {
            json.put("gender", mGender);
            json.put("age", (int) Integer.valueOf(mAge));
            json.put("alias", mAlias);
            json.put("photo_profile", mPhoto);
        } catch (JSONException e) {}
        return json;
    }
}
