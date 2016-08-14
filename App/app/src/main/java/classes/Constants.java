package classes;

import android.content.Context;

/**
 * Class that contains configuration constants.
 */
public final class Constants {

    /**
     * Default string for the server ip. Used to build paths for requests.
     * Localhost is "http://10.0.2.2:5000";
     */
    public static final String DEFAULT_IP = "http://10.0.2.2:8000";

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
    public static final String USER_UPDATE_DATA_PATH = "/user/";

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

    /**
     * Route for constructing the url path for the request that gets a new message from other user
     */
    public static final String GET_MESSAGE = "/getmessage/";

    /**
     * Route for constructing the url path for the request that sends a new message to other user
     */
    public static final String SEND_MESSAGE = "/sendmessage/";

    /**********************************************************************************************/
    /**********************          CHAT STRING CONSTANTS           ***************************/
    /**********************************************************************************************/

    /**
     * Key for chat messages
     */
    public static final String MESSAGE = "message";

    /**
     * Key for old chat messages
     */
    public static final String OLD_MESSAGES = "old_messages";

    /**
     * Name of the "likes" interest
     */
    public static final String LIKES = "likes";


    /**********************************************************************************************/
    /**********************     FACEBOOK INTERESTS STRING CONSTANTS     ***************************/
    /**********************************************************************************************/

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
    /**
     * Name of the "user_id" user field
     */
    public static final String USER_ID = "user_id";


    /**********************************************************************************************/
    /**********************             USER STRING CONSTANTS           ***************************/
    /**********************************************************************************************/

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

    /**
     * Name of the "ip" field
     */
    public static final String IP = "ip";


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

    /**
     * Name of the "settings" field
     */
    public static final String SETTINGS = "settings";


    /**********************************************************************************************/
    /**********************          SETTINGS STRING CONSTANTS           ***************************/
    /**********************************************************************************************/

    /**
     * Name of the "distance" field
     */
    public static final String DISTANCE = "distance";

    /**
     * Name of the "men" field
     */
    public static final String MEN_INTEREST = "male";

    /**
     * Name of the "women" field
     */
    public static final String WOMEN_INTEREST = "female";

    /**
     * Name of field "show_gender" of the json sent in setting request
     */
    public static final String SHOW_GENDER = "show_gender";

    /**
     * Name of field "discovering_distance" of the json sent in setting request
     */
    public static final String DISCOVERING_DISTANCE = "discovering_distance";

    /**
     * Default distance for the discovering distance setting
     */
    public static final int DEFAULT_DISTANCE = 10;

    /**
     * Default gender interest for the gender interest setting
     */
    public static final String DEFAULT_GENDER_INTEREST = "male|female";

    /**
     * String for intent for starting MatchesActivity
     */
    public static final String CONVERSATION = "conversation";

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Ip of the server. Used to build paths for requests.
     * Localhost is "http://10.0.2.2:5000";;
     */
    private static String ipSERVER = "http://192.168.1.101:8000";

    /**
     * Application context
     */
    private static Context cONTEXT;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Private constructor of the class Constants.
     */
    private Constants() {
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the application context
     *
     * @return the application context
     */
    public static final Context getContext() {
        return cONTEXT;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the application context
     *
     * @param context the application context
     */
    public static void setContext(Context context) {
        cONTEXT = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the URL of the server using the ip received as parameter
     * @param ip the ip number where the server is running
     */
    public static void setIpServer(String ip) {
        ipSERVER = "http://" + ip + ":8000";
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the IP number of the server
     * @return the string that represents the server ip
     */
    public static String getIpServer() {
        return ipSERVER;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Overrides the current url of the server with a new one received as parameter
     * @param url the new url
     */
    public static void setServerURL(String url) {
        ipSERVER = url;
    }
}
