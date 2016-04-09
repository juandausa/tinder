package requests;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.util.Log;

import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.RequestFuture;
import com.tinder_app.MainActivity;

import org.json.JSONObject;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeoutException;

import classes.Constants;
import classes.User;

import static com.android.volley.Request.*;


public class RegisterRequest {

    private RequestHandler requestHandler;
    private JSONObject facebookUser = null;
    private JSONObject jsonRequest;
    private String facebookId;
    private SharedPreferences preferences;
    private Context mContext;
    private static final String TAG = "UserRegisterRequest";

    /**********************************************************************************************/
    /**********************************************************************************************/

    public RegisterRequest(Context context) {
        requestHandler = RequestHandler.getInstance(context);
        this.mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    //Sincronico
    public void send(JSONObject user) throws InterruptedException, ExecutionException, TimeoutException {
        String path = RequestHandler.getServerUrl() + Constants.REGISTER_PATH;
        //RequestFuture<JSONObject> future = RequestFuture.newFuture();
        JsonObjectRequest request = new JsonObjectRequest(Method.POST, path, user, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                //preferences.edit().putString("userData", facebookUser.toString()).commit();
                Log.i("RESPONSE", response.toString());
                Intent myIntent = new Intent(mContext, MainActivity.class);
                myIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {

            }
        });
        requestHandler.addToRequestQueue(request);
        /*JSONObject response = null;
        try {
            response = future.get(10, TimeUnit.SECONDS);
        } catch (InterruptedException | ExecutionException | TimeoutException e) {
            // exception handling
            throw e;
        }*/
    }

    /**********************************************************************************************/
    /**********************************************************************************************/


    /**********************************************************************************************/
    /**********************************************************************************************/

    public void setPreferences(SharedPreferences preferences) {
        this.preferences = preferences;
    }


    /**********************************************************************************************/
    /**********************************************************************************************/
/*
    public class RegisterUserTask extends AsyncTask<Void, Void, Boolean> {

        RegisterUserTask() {}

        @Override
        protected Boolean doInBackground(Void... params) {
            //TODO: Primero verificar si existe ya ese usuario
            LoginRequest loginRequest = new LoginRequest(requestHandler.getContext());
            try {
                facebookUser = loginRequest.send(facebookId);
                if (facebookUser == null) {
                    return false;
                }
            } catch (TimeoutException | ExecutionException | InterruptedException e) {
                return false;
            }
            Log.e(TAG, "Put user preferences");
            preferences.edit().putString("userData", facebookUser.toString()).commit();
            Intent myIntent = new Intent(mContext, MainActivity.class);
            myIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            mContext.startActivity(myIntent);
            return true;
        }

        @Override
        protected void onPostExecute(final Boolean success) {
            if (!success) {
                //Lo creo y lo recupero
                CreateUserTask createUserTask = new CreateUserTask();
                createUserTask.execute();
            }
        }

        @Override
        protected void onCancelled() {
        }

    }
*/
    /**********************************************************************************************/
    /**********************************************************************************************/

    public class CreateUserTask extends AsyncTask<Void, Void, Boolean> {

        CreateUserTask() {

        }


        @Override
        protected Boolean doInBackground(Void... params) {
            /*try {
                facebookUser = createUser(jsonRequest);
                if (facebookUser == null) {
                    return false;
                }
            } catch (TimeoutException | ExecutionException | InterruptedException e) {
                return false;

            }*/
            return true;
        }

        @Override
        protected void onPostExecute(final Boolean success) {
            if (success) {

                Log.e(TAG, "Put user preferences");
//               User completeUser = new FacebookUser(facebookUser);
                /*User completeUser = new User(facebookUser);
                preferences.edit().clear().commit();
                preferences.edit().putString("userData", completeUser.toJson().toString()).commit();
                Intent myIntent = new Intent(callerActivity, MainActivity.class);
                myIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                mContext.startActivity(myIntent);*/
            }
        }

        @Override
        protected void onCancelled() {}

    }
}