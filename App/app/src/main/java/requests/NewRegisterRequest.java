package requests;

import android.util.Log;
import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.LoginActivity;

import org.json.JSONException;
import org.json.JSONObject;
import classes.Constants;

/**
 * Created by fabrizio on 03/04/16.
 */
public class NewRegisterRequest extends JSONRequest {

    private LoginActivity mContext;

    /**********************************************************************************************/
    /**********************************************************************************************/

    public NewRegisterRequest(LoginActivity context) {
        super(context);
        mMethod = Request.Method.POST;
        mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void send(JSONObject json) {
        super.send(json, Constants.REGISTER_PATH);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void onResponse(JSONObject response) {
        Log.i("RESPONSE2", response.toString());
        try {
            if (response.getInt("status_code") == 200) {
                launchMainActivity();
            }
        } catch (JSONException e) {}
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void onError(VolleyError error) {
        Log.e("ERR", error.getMessage());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void launchMainActivity() {
        mContext.launchMainActivity();
    }
}
