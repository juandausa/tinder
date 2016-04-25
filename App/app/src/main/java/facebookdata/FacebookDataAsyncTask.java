package facebookdata;

import android.os.AsyncTask;
import android.util.Log;

import com.facebook.AccessToken;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.HttpMethod;

import org.json.JSONObject;

import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.atomic.AtomicBoolean;

import classes.Constants;

/**
 * AsyncTask that gets the interests of a user from facebook
 */
public class FacebookDataAsyncTask extends AsyncTask<Void, Void, Void> {

    private String mUserId;
    private ConcurrentMap mInterests;

    /**
     * Constructor of the class FacebookDataAsyncTask
     * @param userId the user id of the facebook user
     * @param interests the map that will be filled with the interests of the user
     */
    public FacebookDataAsyncTask(String userId, ConcurrentMap interests) {
        mUserId = userId;
        mInterests = interests;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets all the interests of the facebook user
     * @param params none
     * @return null
     */
    @Override
    protected Void doInBackground(Void... params) {
        getUserData(mUserId, Constants.LIKES);
        getUserData(mUserId, Constants.BOOKS);
        getUserData(mUserId, Constants.MOVIES);
        getUserData(mUserId, Constants.GAMES);
        getUserData(mUserId, Constants.MUSIC);
        getUserData(mUserId, Constants.TV);
        return null;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the interests of the user from Facebook using the Graph API, and store them in the
     * attribute mInterests, with the category of the interest as key and the data received as
     * response as value.
     * @param userId The id of the user in Facebook.
     * @param category The category of the interests.
     */
    private void getUserData(String userId, final String category) {
        final AtomicBoolean ready = new AtomicBoolean(false);
        GraphRequest request = new GraphRequest(
            AccessToken.getCurrentAccessToken(),
            userId + "/" + category + "/",
            null,
            HttpMethod.GET,
            new GraphRequest.Callback() {
                @Override
                public void onCompleted(GraphResponse graphResponse) {
                    JSONObject response = (graphResponse.getJSONObject());
                    Log.d("JSON", response.toString());
                    mInterests.putIfAbsent(category, response);
                    ready.set(true);
                }
            });
        request.executeAndWait();
    }
}
