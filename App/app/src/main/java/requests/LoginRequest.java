package requests;

import android.util.Log;
import com.android.volley.Request;
import com.android.volley.VolleyError;
import com.tinder_app.LoginActivity;
import org.json.JSONException;
import org.json.JSONObject;
import classes.Constants;

public class LoginRequest extends SimpleRequest {

    private static final int REGISTERED = 200;
    private static final int UNREGISTERED = 304;
    private JSONObject mUser;
    private LoginActivity mContext;

    /**********************************************************************************************/
    /**********************************************************************************************/

    public LoginRequest(LoginActivity context) {
        super(context);
        mMethod = Request.Method.GET;
        mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void send(JSONObject json) {
        mUser = json;
        try {
            String route = Constants.LOGIN_PATH + json.getString("user_id");
            super.send(json, route);
        } catch (JSONException e) {}
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onResponse(Integer response) {
        Log.i("RESPONSE", response.toString());
        switch (response.intValue()) {
            case REGISTERED:
                launchMainActivity();
                break;
            case UNREGISTERED:
                NewRegisterRequest req = new NewRegisterRequest(mContext);
                req.send(mUser);
                break;
            default:
                return;
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onError(VolleyError error) {
        Log.e("ERR", error.getMessage());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void launchMainActivity() {
        mContext.launchMainActivity();
    }
}
