package com.tinder_app;

import android.content.Intent;
import android.content.SharedPreferences;
import android.location.Location;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;

import com.facebook.AccessToken;
import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookSdk;
import com.facebook.login.LoginResult;
import com.facebook.login.widget.LoginButton;
import com.github.akashandroid90.googlesupport.location.AppLocationActivity;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Arrays;
import java.util.concurrent.ExecutionException;

import classes.Constants;
import classes.FacebookProxy;
import classes.SessionManager;
import requests.LoginRequest;
import requests.NewRegisterRequest;
import requests.RegisterRequest;

/**
 * Activity that contains the Login with Facebook API to access the App.
 */
public class LoginActivity extends AppLocationActivity {

    private LoginButton mLoginButton;
    private CallbackManager mCallbackManager;
    private String mFacebookUserId;
    private Location mCurrentLocation;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Method that is invocated when the Activity is created to set up the view and controllers.
     * This set up the background, texts and the Facebook Login Button with its behaviour.
     * @param savedInstanceState Data saved from this activity to be restored when is destroyed and
     * re-reated.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FacebookSdk.sdkInitialize(getApplicationContext());
        setContentView(R.layout.activity_login);
        mCallbackManager = CallbackManager.Factory.create();
        mLoginButton = (LoginButton) findViewById(R.id.login_button);
        if (mLoginButton != null) {
            mLoginButton.setReadPermissions(Arrays.asList(
                    "public_profile", "email", "user_likes", "user_birthday", "user_friends"));
        }

        launchIfLoggedIn();

        mLoginButton.registerCallback(mCallbackManager, new FacebookCallback<LoginResult>() {
            @Override
            public void onSuccess(LoginResult loginResult) {
                registerUser(loginResult);
            }

            @Override
            public void onCancel() {
            }

            @Override
            public void onError(FacebookException e) {

            }
        });

    }


    /**********************************************************************************************/
    /**********************************************************************************************/


    private void launchIfLoggedIn() {
        if (isLoggedIn()) {
            launchMainActivity();
        }
    }


    /**********************************************************************************************/
    /**********************************************************************************************/

    private boolean isLoggedIn() {
        //AccessToken accessToken = AccessToken.getCurrentAccessToken();
        //return accessToken != null;
        return SessionManager.isLoggedIn(LoginActivity.this);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void launchMainActivity() {
        Intent intent = new Intent(getApplicationContext(), MainActivity.class);
        intent.putExtra("user_id", mFacebookUserId);
        startActivity(intent);
        finish();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Method that gets the result from the Facebook handler activity.
     * @param requestCode request code sent by this Activity.
     * @param resultCode result code from the Facebook activity.
     * @param data data sent by the Facebook Activity
     */
    @Override
    protected void onActivityResult(final int requestCode, final int resultCode, final Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        mCallbackManager.onActivityResult(requestCode, resultCode, data);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void registerUser(LoginResult loginResult) {
        mFacebookUserId = loginResult.getAccessToken().getUserId();
        final FacebookProxy proxy = new FacebookProxy(mFacebookUserId);
        AsyncTask task = new AsyncTask() {
            @Override
            protected Object doInBackground(Object[] params) {
                while (!proxy.isInitialized()) {
                    try {
                        Thread.sleep(500);
                    } catch (InterruptedException e) {}
                }
                proxy.addLocation(mCurrentLocation);
                JSONObject data = proxy.toJSON();
                LoginRequest request = new LoginRequest(LoginActivity.this);
                //NewRegisterRequest request = new NewRegisterRequest(LoginActivity.this);
                request.send(data);
                SessionManager.login(LoginActivity.this, mFacebookUserId);
                return null;
            }
        };
        task.execute();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void newLocation(Location location) {}

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void myCurrentLocation(Location currentLocation) {
        mCurrentLocation = currentLocation;
    }
}
