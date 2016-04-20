package classes;

import android.location.Location;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

import facebook_data.FacebookDataAsyncTask;
import facebook_data.FacebookInterestParser;
import facebook_data.FacebookProfileAsyncTask;

/**
 * Class that is an intermediator between the facebook Graph API and the rest of the app.
 * Is used as if it were an object that knows the data of the user.
 */
public class FacebookProxy {

    private String mFacebookUserId;
    private FacebookInterestParser mParser;
    private ConcurrentMap<String,JSONObject> mInterests;
    private ConcurrentMap<String,JSONObject> mProfile;
    private Location mLocation;

    private static final String LIKES = "likes";
    private static final String BOOKS = "books";
    private static final String MOVIES = "movies";
    private static final String GAMES = "games";
    private static final String MUSIC = "music";
    private static final String TV = "television";
    private static final int CATEGORIES_COUNT = 6;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class FacebookProxy.
     * @param userId The id of the user in Facebook.
     */
    public FacebookProxy(String userId) {
        mFacebookUserId = userId;
        mParser = new FacebookInterestParser();
        initialize();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Initialize the instance of FacebookProxy. Gets the user data from Facebook and stores it in
     * the current instance.
     */
    public void initialize() {
        mInterests = new ConcurrentHashMap<>();
        mProfile = new ConcurrentHashMap<>();
        (new FacebookDataAsyncTask(mFacebookUserId, mInterests)).execute();
        (new FacebookProfileAsyncTask(mFacebookUserId, mProfile)).execute();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Indicates if the FacebookProxy instace is syncronized with the Facebook profile.
     * @return True if it is initialized, false otherwise.
     */
    public boolean isInitialized() {
        return mInterests.size() >= CATEGORIES_COUNT;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property likes.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getLikes() {
        return mParser.parseInterests(mInterests.get(LIKES), LIKES);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest movies.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getMovies() {
        return mParser.parseInterests(mInterests.get(MOVIES), MOVIES);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest books.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getBooks() {
        return mParser.parseInterests(mInterests.get(BOOKS), BOOKS);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest television.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getTVShows() {
        return mParser.parseInterests(mInterests.get(TV), TV);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest music.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getMusic() {
        return mParser.parseInterests(mInterests.get(MUSIC), MUSIC);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest games.
     * @return a JSONArray with  the name of the interests as value
     */
    public JSONArray getGames() {
        return mParser.parseInterests(mInterests.get(GAMES), GAMES);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Setter of the attribute location.
     * @param location the location of the user, to be stored.
     */
    public void addLocation(Location location) {
        mLocation = location;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Parse the instance of FacebookProxy into a JSONObject.
     * @return the JSONObject with the data of the FacebookProxy instance.
     */
    public JSONObject toJSON() {
        try {
            JSONObject json = new JSONObject();
            json.put("user_id", this.mFacebookUserId);
            json.put("name", mProfile.get("name"));
            json.put("alias", mProfile.get("alias"));
            json.put("email", mProfile.get("email"));
            json.put("birthday", mProfile.get("birthday"));
            JSONObject interests = new JSONObject();
            interests.put(LIKES, getLikes());
            interests.put(MOVIES, getMovies());
            interests.put(MUSIC, getMusic());
            interests.put(TV, getTVShows());
            interests.put(BOOKS, getBooks());
            interests.put(GAMES, getGames());
            json.put("interests", interests);
            json.put("photo_profile", mProfile.get("photo_profile"));
            if (mLocation != null) {
                JSONObject location = new JSONObject();
                location.put("latitude", mLocation.getLatitude());
                location.put("longitude", mLocation.getLongitude());
                json.put("location", location);
            }
            Log.e("JSON", json.toString());
            return json;
        } catch (JSONException e) {
            return null;
        }
    }
}