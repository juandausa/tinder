package com.tinder_app;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.CollapsingToolbarLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.flyco.roundview.RoundTextView;
import com.ismaeltoe.FlowLayout;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import classes.UserData;

/**
 * Activity that shows the profile information of a determined user.
 */
public abstract class UserProfileActivity extends AppCompatActivity {

    /**
     * Hardcoded string for getting the name of the user.
     */
    public static final String USER = "user";
    protected UserData mUserData;
    protected TextView mTitleView;
    protected ImageView mImageView;

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);

        mUserData = getDataFromIntent();

        final Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        loadTitle();
        loadBackdropImage(mUserData);
        loadUserData(mUserData);
        loadUserInterests(mUserData);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    protected void loadBackdropImage(UserData data) {
        mImageView = (ImageView) findViewById(R.id.backdrop);
        if ((mImageView != null) && (data != null)) {
            mImageView.setImageBitmap(data.getPhoto());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    protected void loadTitle() {
        CollapsingToolbarLayout collapsingToolbar
                = (CollapsingToolbarLayout) findViewById(R.id.collapsing_toolbar);
        if ((collapsingToolbar != null) /*&& (candidateData != null)*/){
            //collapsingToolbar.setTitle(candidateData.getAlias());
            collapsingToolbar.setTitle(" ");
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    protected void loadUserData(UserData userData) {
        mTitleView = (TextView) findViewById(R.id.user_title);
        if ((userData != null) && (mTitleView != null)) {
            String aliasAndAge = userData.getAlias() + ", " + userData.getAge();
            mTitleView.setText(aliasAndAge);
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    protected void loadUserInterests(UserData userData) {
        FlowLayout interestsView = (FlowLayout) findViewById(R.id.interests_layout);
        if (interestsView == null) return;
        LayoutInflater inflater = LayoutInflater.from(this);
        JSONArray interests = userData.getInterests();
        int size = interests.length();

        try {
            for (int i = 0; i < size; i++) {
                String interest = (String) interests.get(i);
                RoundTextView view = (RoundTextView)
                        inflater.inflate(R.layout.round_text_view, interestsView, false);
                view.setText(interest);
                RelativeLayout.LayoutParams params1 = new RelativeLayout.LayoutParams(
                        RelativeLayout.LayoutParams.WRAP_CONTENT,
                        RelativeLayout.LayoutParams.WRAP_CONTENT
                );
                params1.setMargins(0, 0, 5, 5);
                interestsView.addView(view, params1);
            }
        } catch (JSONException e) {
            Log.e(getString(R.string.JSON_ERROR)+"USER", e.toString());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.sample_actions, menu);
        return true;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    protected UserData getDataFromIntent() {
        Intent intent = getIntent();
        String data = intent.getStringExtra(USER);
        try {
            return buildUserData(new JSONObject(data));
        } catch (JSONException e) {
            Log.e(getString(R.string.JSON_ERROR), e.toString());
            return null;
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    protected abstract UserData buildUserData(JSONObject data);
}
