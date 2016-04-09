package facebook_data;

import android.os.AsyncTask;
import android.util.Log;

import com.facebook.AccessToken;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.HttpMethod;

import org.json.JSONObject;

import java.util.concurrent.ConcurrentMap;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Created by fabrizio on 28/03/16.
 */
public class FacebookDataAsyncTask extends AsyncTask<Void,Void,Void> {

    private String mUserId;
    private ConcurrentMap mInterests;
    private static final String LIKES = "likes";
    private static final String BOOKS = "books";
    private static final String MOVIES = "movies";
    private static final String GAMES = "games";
    private static final String MUSIC = "music";
    private static final String TV = "television";

    public FacebookDataAsyncTask(String userId, ConcurrentMap interests) {
        mUserId = userId;
        mInterests = interests;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected Void doInBackground(Void... params) {
        getUserData(mUserId, LIKES);
        getUserData(mUserId, BOOKS);
        getUserData(mUserId, MOVIES);
        getUserData(mUserId, GAMES);
        getUserData(mUserId, MUSIC);
        getUserData(mUserId, TV);
        return null;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the interests of the user from Facebook using the Graph API, and store them in the
     * attribute mInterests, with the category of the interest as key and the data received as
     * response as value.
     * @param user_id The id of the user in Facebook.
     * @param category The category of the interests.
     */
    private void getUserData(String user_id, final String category) {
        final AtomicBoolean ready = new AtomicBoolean(false);
        GraphRequest request = new GraphRequest(
            AccessToken.getCurrentAccessToken(),
            user_id + "/" + category + "/",
            null,
            HttpMethod.GET,
            new GraphRequest.Callback() {
                @Override
                public void onCompleted(GraphResponse graphResponse) {
                    JSONObject response = (graphResponse.getJSONObject());
                    Log.d("check", response.toString());
                    mInterests.putIfAbsent(category, response);
                    ready.set(true);
                }
            });
        request.executeAndWait();
    }
}
