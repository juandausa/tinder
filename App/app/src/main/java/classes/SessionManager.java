package classes;

import android.content.Context;
import android.content.SharedPreferences;

/**
 * Class that contains the logic for storing and getting session information
 */
public final class SessionManager {

    /**
     * Private constructor of the class SessionManager
     */
    private SessionManager() { }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets an instance of SharedPreferences with the session data
     * @param context the context where the session manager is used
     * @return an instance of sharedPreferences with the session data
     */
    private static SharedPreferences getSessionPreferences(Context context) {
        Context c = context.getApplicationContext();
        return c.getSharedPreferences(Constants.SESSION, Context.MODE_PRIVATE);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Opens a session
     * @param context the context where the session manager is used
     * @param id the id of the user that owns the session
     */
    public static void login(Context context, String id) {
        SharedPreferences preferences = getSessionPreferences(context);
        preferences.edit().putString(Constants.USER_ID, id).apply();
        preferences.edit().putBoolean(Constants.LOGGED_IN, true).apply();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Closes a session
     * @param context the context where the session manager is used
     */
    public static void logout(Context context) {
        SharedPreferences preferences = getSessionPreferences(context);
        preferences.edit().putBoolean(Constants.LOGGED_IN, false).apply();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Checks if the session is open
     * @param context the context where the session manager is used
     * @return true if session is open, false otherwise.
     */
    public static boolean isLoggedIn(Context context) {
        SharedPreferences preferences = getSessionPreferences(context);
        return preferences.getBoolean(Constants.LOGGED_IN, false);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the user id
     * @param context the context where the session manager is used
     * @return the user id
     */
    public static String getUserId(Context context) {
        SharedPreferences preferences = getSessionPreferences(context);
        return preferences.getString(Constants.USER_ID, null);
    }
}
