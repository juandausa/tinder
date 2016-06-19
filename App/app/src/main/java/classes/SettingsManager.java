package classes;

import android.content.Context;
import android.content.SharedPreferences;

/**
 * Class that contains the logic for storing and getting settings information
 */
public final class SettingsManager {



    /**
     * Private constructor of the class SettingsManager
     */
    private SettingsManager() {
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets an instance of SharedPreferences with the session data
     *
     * @param context the context where the session manager is used
     * @return an instance of sharedPreferences with the session data
     */
    private static SharedPreferences getSettingsPreferences(Context context) {
        Context c = context.getApplicationContext();
        return c.getSharedPreferences(Constants.SETTINGS, Context.MODE_PRIVATE);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the distance for discovering new candidates
     *
     * @param context the context where the settings manager is used
     * @return an instance the distance for discovering new candidates
     */
    public static int getDistance(Context context) {
        SharedPreferences pref = getSettingsPreferences(context);
        return pref.getInt(Constants.DISTANCE, Constants.DEFAULT_DISTANCE);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns true if the user is interested in men
     *
     * @param context the context where the session manager is used
     * @return true if the user is interested in men
     */
    public static boolean getInterestedInMen(Context context) {
        SharedPreferences pref = getSettingsPreferences(context);
        return pref.getBoolean(Constants.MEN_INTEREST, true);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns true if the user is interested in women
     * @param context the context where the session manager is used
     * @return true if the user is interested in women
     */
    public static boolean getInterestedInWomen(Context context) {
        SharedPreferences pref = getSettingsPreferences(context);
        return pref.getBoolean(Constants.WOMEN_INTEREST, true);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the default values for the settings
     * @param context the context where the session manager is used
     */
    public static void setDefaultValues(Context context) {
        SharedPreferences preferences = getSettingsPreferences(context);
        preferences.edit().putInt(Constants.DISTANCE, Constants.DEFAULT_DISTANCE).apply();
        preferences.edit().putBoolean(Constants.MEN_INTEREST, true).apply();
        preferences.edit().putBoolean(Constants.WOMEN_INTEREST, true).apply();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Changes the distance setting saved
     * @param distance the distance in wich range the user wants to search for people
     * @param context the context where the session manager is used
     */
    public static void changeDistance(Context context, int distance) {
        SharedPreferences preferences = getSettingsPreferences(context);
        preferences.edit().putInt(Constants.DISTANCE, distance).apply();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Change the interest on men
     * @param men true if the user is interested in men
     * @param context the context where the session manager is used
     */
    public static void changeInterestOnMen(Context context, boolean men) {
        SharedPreferences preferences = getSettingsPreferences(context);
        preferences.edit().putBoolean(Constants.MEN_INTEREST, men).apply();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Change the interest on men
     * @param women true if the user is interested in women
     * @param context the context where the session manager is used
     */
    public static void changeInterestOnWomen(Context context, boolean women) {
        SharedPreferences preferences = getSettingsPreferences(context);
        preferences.edit().putBoolean(Constants.WOMEN_INTEREST, women).apply();
    }
}