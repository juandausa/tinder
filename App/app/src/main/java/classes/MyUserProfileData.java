package classes;

import android.graphics.Bitmap;
import android.util.Base64;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;

/**
 * Class that contains the data of the current user
 */
public class MyUserProfileData extends UserData {

    private String mName;
    private String mEmail;
    private String mGender;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class MyUserProfileData
     *
     * @param user the JSONObject containing the data of the user
     */
    public MyUserProfileData(JSONObject user) {
        super(user);
        try {
            mName = user.getString("name");
            mEmail = user.getString("email");
            mGender = user.getString("gender");
        } catch (JSONException e) {
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the name of the user
     *
     * @return the name of the user
     */
    public String getName() {
        return mName;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the email of the user
     *
     * @return the email of the user
     */
    public String getEmail() {
        return mEmail;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the gender of the user
     *
     * @return the gender of the user
     */
    public String getGender() {
        return mGender;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets a new gender to the user
     *
     * @param gender the new gender of the user
     */
    public void setGender(String gender) {
        mGender = gender;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets a new alias to the user
     *
     * @param alias the new alias of the user
     */
    public void setAlias(String alias) {
        mAlias = alias;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets a new photo to the user
     *
     * @param photo the new photo of the user
     */
    public void setPhoto(Bitmap photo) {
        if (photo == null) {
            mPhoto = null;
            if (mJson.has(Constants.PHOTO_PROFILE)) {
                mJson.remove(Constants.PHOTO_PROFILE);
            }
            return;
        }
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        photo.compress(Bitmap.CompressFormat.PNG, 100, byteArrayOutputStream);
        byte[] byteArray = byteArrayOutputStream.toByteArray();
        mPhoto = Base64.encodeToString(byteArray, Base64.DEFAULT);
        try {
            mJson.put(Constants.PHOTO_PROFILE, mPhoto);
        } catch (JSONException e) {
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets a new age to the user
     *
     * @param age the new age of the user
     */
    public void setAge(String age) {
        mAge = age;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Converts the instance of MyUserProfileData to a string
     *
     * @return a string with the data of the user
     */
    @Override
    public String toString() {
        this.toJSON();
        return super.toString();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Converts the instance of MyUserProfileData to a string
     *
     * @return a string with the data of the user
     */
    @Override
    public JSONObject toJSON() {
        try {
            mJson.put(Constants.GENDER, mGender);
            int value = Integer.parseInt(mAge);
            mJson.put(Constants.AGE, value);
            mJson.put(Constants.ALIAS, mAlias);
            mJson.put(Constants.PHOTO_PROFILE, mPhoto);
        } catch (JSONException e) {
        }
        return mJson;
    }
}
