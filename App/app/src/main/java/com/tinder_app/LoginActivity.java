package com.tinder_app;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookSdk;
import com.facebook.login.LoginResult;
import com.facebook.login.widget.LoginButton;

/**
 * Activity that contains the Login with Facebook API to access the App.
 */
public class LoginActivity extends AppCompatActivity {

    private LoginButton mLoginButton;
    private CallbackManager mCallbackManager;

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
            mLoginButton.setReadPermissions("user_friends");
            mLoginButton.setReadPermissions("public_profile");
        }
        mLoginButton.registerCallback(mCallbackManager, new FacebookCallback<LoginResult>() {
            @Override
            public void onSuccess(LoginResult loginResult) {
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(intent);
                finish();
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
}
