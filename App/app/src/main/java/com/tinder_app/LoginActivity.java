package com.tinder_app;

import android.content.Intent;
import android.location.Location;
import android.os.AsyncTask;
import android.os.Bundle;
import android.text.Editable;
import android.util.Log;
import android.widget.EditText;

import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookSdk;
import com.facebook.login.LoginResult;
import com.facebook.login.widget.LoginButton;
import com.github.akashandroid90.googlesupport.location.AppLocationActivity;

import org.json.JSONObject;

import java.util.Arrays;

import classes.Constants;
import classes.FacebookProxy;
import classes.SessionManager;
import classes.SettingsManager;
import requests.LoginRequest;


/**
 * Activity that contains the Login with Facebook API to access the App.
 */
public class LoginActivity extends AppLocationActivity {

    private LoginButton mLoginButton;
    private CallbackManager mCallbackManager;
    private String mFacebookUserId;
    private Location mCurrentLocation;
    private EditText mIpTextBox;

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
        Constants.setContext(getApplicationContext());
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
                Editable content = mIpTextBox.getText();
                String ip = content.toString();
                SessionManager.setServerIp(LoginActivity.this, ip);
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

    @Override
    protected void onStart() {
        super.onStart();
        mIpTextBox = (EditText) findViewById(R.id.ip_data);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Launch main activity if the user is loged in
     */
    private void launchIfLoggedIn() {
        if (isLoggedIn()) {
            launchMainActivity();
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Checks if the user is loged in
     * @return true if the user is loged in, false otherwise
     */
    private boolean isLoggedIn() {
        //AccessToken accessToken = AccessToken.getCurrentAccessToken();
        //return accessToken != null;
        return SessionManager.isLoggedIn(LoginActivity.this);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Launch main activity
     */
    public void launchMainActivity() {
        Intent intent = new Intent(getApplicationContext(), MainActivity.class);
        intent.putExtra(Constants.USER_ID, mFacebookUserId);
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

    /**
     * Sends request for checking if the user is registered, if not sends a request to register and
     * login the user
     * @param loginResult the result from the login
     */
    private void registerUser(LoginResult loginResult) {
        mFacebookUserId = loginResult.getAccessToken().getUserId();
        final FacebookProxy proxy = new FacebookProxy(mFacebookUserId);
        AsyncTask task = new AsyncTask() {
            @Override
            protected Object doInBackground(Object[] params) {
                while (!proxy.isInitialized()) {
                    try {
                        Thread.sleep(500);
                    } catch (InterruptedException e) {
                        Log.e(getString(R.string.REQUEST_ERROR), e.toString());
                    }
                }
                proxy.addLocation(mCurrentLocation);
                JSONObject data = proxy.toJSON();
                LoginRequest request = new LoginRequest(LoginActivity.this);
                //NewRegisterRequest request = new NewRegisterRequest(LoginActivity.this);
                request.send(data);
                SessionManager.login(LoginActivity.this, mFacebookUserId);
                SettingsManager.setDefaultValues(LoginActivity.this);
                return null;
            }
        };
        task.execute();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * On change of location executes the code in this function
     * @param location the new location
     */
    @Override
    public void newLocation(Location location) { }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Get the current location of the user
     * @param currentLocation the current location of the user
     */
    @Override
    public void myCurrentLocation(Location currentLocation) {
        mCurrentLocation = currentLocation;
    }
}
