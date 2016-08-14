package facebookdata;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;

import com.facebook.AccessToken;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * AsyncTask that gets the facebook profile information of the user
 */
public class FacebookProfileAsyncTask extends AsyncTask<Void, Void, Void> {

    private final String mName = "name";
    private final String mEmail = "email";
    private final String mGender = "gender";
    private final String mBirthday = "birthday";
    private final String mFirstName = "first_name";
    private final String mAlias = "alias";
    private final String mUser = "user_id";
    private final String mPhoto = "photo_profile";
    private String mUserId;
    private ConcurrentMap mProfile;
    private Bundle mParams;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class FacebookProfileAsyncTask
     *
     * @param userId  the user id of the user
     * @param profile the profile to be filled with info
     */
    public FacebookProfileAsyncTask(String userId, ConcurrentMap profile) {
        mUserId = userId;
        mProfile = profile;
        mParams = new Bundle();
        mParams.putString("fields", "name,email,gender,birthday,first_name,picture.type(large)");
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the profile image of the facebook user
     * @param src url of the profile image
     * @return the bitmap with the image
     */
    public static Bitmap getBitmapFromURL(String src) {
        try {
            URL url = new URL(src);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setDoInput(true);
            connection.connect();
            InputStream input = connection.getInputStream();
            Bitmap myBitmap = BitmapFactory.decodeStream(input);
            return myBitmap;
        } catch (IOException e) {
            // Log exception
            return null;
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Encode the bitmap to base64
     * @param image the bitmap with the image
     * @param compressFormat the format to be compressed
     * @param quality the final quality of the image stored as base64
     * @return the string with the base64
     */
    public static String encodeToBase64(Bitmap image, Bitmap.CompressFormat compressFormat, int quality) {
        ByteArrayOutputStream byteArrayOS = new ByteArrayOutputStream();
        image.compress(compressFormat, quality, byteArrayOS);
        return Base64.encodeToString(byteArrayOS.toByteArray(), Base64.DEFAULT);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the user data from facebook
     *
     * @param params none
     * @return null
     */
    @Override
    protected Void doInBackground(Void... params) {
        final AtomicBoolean ready = new AtomicBoolean(false);
        getUserData();
        //getProfilePhoto();
        ready.set(true);
        return null;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the user profile data from facebook using the Facebook Graph API
     */
    private void getUserData() {
        GraphRequest request = GraphRequest.newMeRequest(
                AccessToken.getCurrentAccessToken(),
                new GraphRequest.GraphJSONObjectCallback() {
                    @Override
                    public void onCompleted(JSONObject user, GraphResponse graphResponse) {
                        JSONObject response = (graphResponse.getJSONObject());
                        Log.i("Response", graphResponse.toString());
                        Log.i("Object", user.toString());
                        Log.d("check", response.toString());
                        try {
                            Bitmap bitmap = getBitmapFromURL(user.getJSONObject("picture").
                                    getJSONObject("data").getString("url"));
                            String base64Photo = encodeToBase64(bitmap, Bitmap.CompressFormat.JPEG, 100);
                            mProfile.putIfAbsent(mName, user.getString(mName));
                            mProfile.putIfAbsent(mEmail, user.getString(mEmail));
                            mProfile.putIfAbsent(mBirthday, user.getString(mBirthday));
                            mProfile.putIfAbsent(mAlias, user.getString(mFirstName));
                            if (genderIsMale(user.getString(mGender))) {
                                mProfile.putIfAbsent(mGender, "male");
                            } else {
                                mProfile.putIfAbsent(mGender, "female");
                            }
                            mProfile.putIfAbsent(mUser, mUserId);
                            mProfile.putIfAbsent(mPhoto, base64Photo);
                        } catch (JSONException e) {
                            Log.e("JSON ERROR", e.toString());
                        }
                    }
                });
        request.setParameters(mParams);
        request.executeAndWait();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private boolean genderIsMale(String gender) {
        return ((gender.equals("hombre")) || (gender.equals("male")));
    }

}