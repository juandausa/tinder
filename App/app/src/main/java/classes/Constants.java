package classes;

import android.content.Context;

/**
 * Class that contains configuration constants.
 */
public final class Constants {

    /**
     * Ip of the server. Used to build paths for requests.
     * Localhost is "http://10.0.2.2:5000";;
     */
    public static final String IP_SERVER = "http://192.168.1.108:5000"; //"http://10.0.2.2:8000";

    /**
     * Route for constructing the url path for the request that checks if the user is registered in
     * the app.
     */
    public static final String LOGIN_PATH = "/login/";

    /**
     * Route for constructing the url path for the request that register a new user in the app.
     */
    public static final String REGISTER_PATH = "/register/";

    /**
     * Route for constructing the url path for the request that gets the people that match with the
     * discovery filters.
     */
    public static final String CANDIDATES_PATH = "/candidates/";

    /**
     * Route for constructing the url path for the request that gets the people that matched with
     * the user.
     */
    public static final String MATCHES_PATH = "/matches/";

    /**
     * Route for constructing the url path for the request that gets the user data
     */
    public static final String USER_DATA_PATH = "/user/";

    /**
     * Route for constructing the url path for the request that changes the filters of people
     * discovery.
     */
    public static final String FILTERS_PATH = "/filters/";

    /**
     * Route for constructing the url path for the request that updates the user data in the server
     */
    public static final String USER_UPDATE_DATA_PATH = "/user/update/";

    /**
     * Route for constructing the url path for the request that send the id of the candidate that
     * the user liked.
     */
    public static final String LIKES_PATH = "/likes/";

    /**
     * Route for constructing the url path for the request that send the id of the candidate that
     * the user disliked.
     */
    public static final String DISLIKES_PATH = "/dislikes/";


    /**********************************************************************************************/
    /**********************     FACEBOOK INTERESTS STRING CONSTANTS     ***************************/
    /**********************************************************************************************/

    /**
     * Name of the "likes" interest
     */
    public static final String LIKES = "likes";

    /**
     * Name of the "books" interest
     */
    public static final String BOOKS = "books";

    /**
     * Name of the "games" interest
     */
    public static final String MOVIES = "movies";

    /**
     * Name of the "games" interest
     */
    public static final String GAMES = "games";

    /**
     * Name of the "music" interest
     */
    public static final String MUSIC = "music";

    /**
     * Name of the "television" interest
     */
    public static final String TV = "television";

    /**
     * Count of facebook categories of interests
     */
    public static final int CATEGORIES_COUNT = 6;


    /**********************************************************************************************/
    /**********************             USER STRING CONSTANTS           ***************************/
    /**********************************************************************************************/

    /**
     * Name of the "user_id" user field
     */
    public static final String USER_ID = "user_id";

    /**
     * Name of the "alias" user field
     */
    public static final String ALIAS = "alias";

    /**
     * Name of the "name" user field
     */
    public static final String NAME = "name";

    /**
     * Name of the "age" user field
     */
    public static final String AGE = "age";

    /**
     * Name of the "birthday" user field
     */
    public static final String BIRTHDAY = "birthday";

    /**
     * Name of the "photo_profile" user field
     */
    public static final String PHOTO_PROFILE = "photo_profile";

    /**
     * Name of the "gender" user field
     */
    public static final String GENDER = "gender";

    /**
     * Name of the "email" user field
     */
    public static final String EMAIL = "email";

    /**
     * Name of the "location" user field
     */
    public static final String LOCATION = "location";

    /**
     * Name of the "latitude" user field
     */
    public static final String LATITUDE = "latitude";

    /**
     * Name of the "longitude" user field
     */
    public static final String LONGITUDE = "longitude";

    /**
     * Name of the "interests" user field
     */
    public static final String INTERESTS = "interests";


    /**********************************************************************************************/
    /**********************          SESSION STRING CONSTANTS           ***************************/
    /**********************************************************************************************/

    /**
     * Name of the "session" field
     */
    public static final String SESSION = "session";

    /**
     * Name of the "logged_in" field
     */
    public static final String LOGGED_IN = "logged_in";


    /**********************************************************************************************/
    /**********************          SETTINGS STRING CONSTANTS           ***************************/
    /**********************************************************************************************/

    /**
     * Name of the "settings" field
     */
    public static final String SETTINGS = "settings";

    /**
     * Name of the "distance" field
     */
    public static final String DISTANCE = "distance";

    /**
     * Name of the "men" field
     */
    public static final String MEN_INTEREST = "men";

    /**
     * Name of the "women" field
     */
    public static final String WOMEN_INTEREST = "women";

    /**
     * Name of field "show_gender" of the json sent in setting request
     */
    public static final String SHOW_GENDER = "show_gender";

    /**
     * Name of field "discovering_distance" of the json sent in setting request
     */
    public static final String DISCOVERING_DISTANCE = "discovering_distance";

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * String for intent for starting MatchesActivity
     */
    public static final String CONVERSATION = "conversation";

    /**
     * Application context
     */
    private static Context cONTEXT;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Private constructor of the class Constants.
     */
    private Constants() { }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the application context
     * @return the application context
     */
    public static final Context getContext() {
        return cONTEXT;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the application context
     * @param context the application context
     */
    public static void setContext(Context context) {
        cONTEXT = context;
    }
}