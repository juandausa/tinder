package requests;

import android.util.Log;
import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.LoginActivity;
import com.tinder_app.R;

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
        Log.i("user", json.toString());
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
        } catch (JSONException e) {
            Log.e(mContext.getString(R.string.JSON_ERROR),e.getMessage());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void onError(VolleyError error) {
        Log.e(mContext.getString(R.string.REQUEST_ERROR)+"1", error.getMessage());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void launchMainActivity() {
        mContext.launchMainActivity();
    }
}
