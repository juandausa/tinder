package facebook_data;

import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;

import com.facebook.AccessToken;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.HttpMethod;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Created by fabrizio on 02/04/16.
 */
public class FacebookProfileAsyncTask extends AsyncTask<Void,Void,Void> {

    private String mUserId;
    private ConcurrentMap mProfile;
    private final String mName = "name";
    private final String mEmail = "email";
    private final String mGender = "gender";
    private final String mBirthday = "birthday";
    private final String mFirstName = "first_name";
    private final String mAlias = "alias";
    private final String mUser = "user_id";
    private final String mPhoto = "photo_profile";
    private Bundle mParams;

    public FacebookProfileAsyncTask(String userId, ConcurrentMap profile) {
        mUserId = userId;
        mProfile = profile;
        mParams = new Bundle();
        mParams.putString("fields", "name,email,gender,birthday,first_name,picture.type(large)");
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

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
                            mProfile.putIfAbsent(mName, user.getString(mName));
                            mProfile.putIfAbsent(mEmail, user.getString(mEmail));
                            mProfile.putIfAbsent(mBirthday, user.getString(mBirthday));
                            mProfile.putIfAbsent(mAlias, user.getString(mFirstName));
                            mProfile.putIfAbsent(mGender, user.getString(mGender));
                            mProfile.putIfAbsent(mUser, mUserId);
                            mProfile.putIfAbsent(mPhoto, user.getJSONObject("picture").getJSONObject("data").getString("url"));
                        } catch (JSONException e) {}
                    }
                });
        request.setParameters(mParams);
        request.executeAndWait();
    }
}