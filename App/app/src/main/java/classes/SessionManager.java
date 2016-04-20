package classes;

import android.content.Context;
import android.content.SharedPreferences;

/**
 * Created by fabrizio on 20/04/16.
 */
public class SessionManager {

    private SessionManager() {}

    private static SharedPreferences getSessionPreferences(Context context) {
        Context c = context.getApplicationContext();
        return c.getSharedPreferences("session", c.MODE_PRIVATE);
    }

    public static void login(Context context, String id) {
        SharedPreferences preferences = getSessionPreferences(context);
        preferences.edit().putString("user_id", id).commit();
        preferences.edit().putBoolean("logged_in", true).commit();
    }

    public static void logout(Context context) {
        SharedPreferences preferences = getSessionPreferences(context);
        preferences.edit().putBoolean("logged_in", false).commit();
    }

    public static boolean isLoggedIn(Context context) {
        SharedPreferences preferences = getSessionPreferences(context);
        return preferences.getBoolean("logged_in", false);
    }

    public static String getUserId(Context context) {
        SharedPreferences preferences = getSessionPreferences(context);
        return preferences.getString("user_id", null);
    }
}
