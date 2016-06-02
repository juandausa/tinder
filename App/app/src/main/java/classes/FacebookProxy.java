package classes;

import android.location.Location;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

import facebookdata.FacebookDataAsyncTask;
import facebookdata.FacebookInterestParser;
import facebookdata.FacebookProfileAsyncTask;

/**
 * Class that is an intermediator between the facebook Graph API and the rest of the app.
 * Is used as if it were an object that knows the data of the user.
 */
public class FacebookProxy {

    private String mFacebookUserId;
    private FacebookInterestParser mParser;
    private ConcurrentMap<String, JSONObject> mInterests;
    private ConcurrentMap<String, JSONObject> mProfile;
    private Location mLocation;

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
        return mInterests.size() >= Constants.CATEGORIES_COUNT;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property likes.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getLikes() {
        return mParser.parseInterests(mInterests.get(Constants.LIKES), Constants.LIKES);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest movies.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getMovies() {
        return mParser.parseInterests(mInterests.get(Constants.MOVIES), Constants.MOVIES);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest books.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getBooks() {
        return mParser.parseInterests(mInterests.get(Constants.BOOKS), Constants.BOOKS);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest television.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getTVShows() {
        return mParser.parseInterests(mInterests.get(Constants.TV), Constants.TV);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest music.
     * @return a JSON Array with the name of the interests as value
     */
    public JSONArray getMusic() {
        return mParser.parseInterests(mInterests.get(Constants.MUSIC), Constants.MUSIC);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter of the property/interest games.
     * @return a JSONArray with  the name of the interests as value
     */
    public JSONArray getGames() {
        return mParser.parseInterests(mInterests.get(Constants.GAMES), Constants.GAMES);
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
            json.put(Constants.USER_ID, this.mFacebookUserId);
            json.put(Constants.NAME, mProfile.get(Constants.NAME));
            json.put(Constants.ALIAS, mProfile.get(Constants.ALIAS));
            json.put(Constants.EMAIL, mProfile.get(Constants.EMAIL));
            json.put(Constants.BIRTHDAY, mProfile.get(Constants.BIRTHDAY));
            json.put(Constants.GENDER, mProfile.get(Constants.GENDER));
            JSONObject interests = new JSONObject();
            interests.put(Constants.LIKES, getLikes());
            interests.put(Constants.MOVIES, getMovies());
            interests.put(Constants.MUSIC, getMusic());
            interests.put(Constants.TV, getTVShows());
            interests.put(Constants.BOOKS, getBooks());
            interests.put(Constants.GAMES, getGames());
            json.put(Constants.INTERESTS, interests);
            json.put(Constants.PHOTO_PROFILE, mProfile.get(Constants.PHOTO_PROFILE));
            if (mLocation != null) {
                JSONObject location = new JSONObject();
                location.put(Constants.LATITUDE, mLocation.getLatitude());
                location.put(Constants.LONGITUDE, mLocation.getLongitude());
                json.put(Constants.LOCATION, location);
            }
            Log.e("JSON", json.toString());
            return json;
        } catch (JSONException e) {
            return null;
        }
    }
}