package com.tinder_app;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.CollapsingToolbarLayout;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.text.Layout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.flyco.roundview.RoundTextView;
import com.ismaeltoe.FlowLayout;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

import classes.CandidateData;

/**
 * Activity that shows the profile information of a determined user.
 */
public class UserProfileActivity extends AppCompatActivity {

    /**
     * Hardcoded string for getting the name of the user.
     */
    public static final String USER = "user";

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);

        final CandidateData candidateData = getDataFromIntent();

        final Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        loadTitle();
        loadBackdropImage(candidateData);
        loadUserData(candidateData);
        loadUserInterests(candidateData);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void loadBackdropImage(CandidateData data) {
        final ImageView imageView = (ImageView) findViewById(R.id.backdrop);
        if ((imageView != null) && (data != null)) {
            imageView.setImageBitmap(data.getPhoto());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void loadTitle() {
        CollapsingToolbarLayout collapsingToolbar
                = (CollapsingToolbarLayout) findViewById(R.id.collapsing_toolbar);
        if ((collapsingToolbar != null) /*&& (candidateData != null)*/){
            //collapsingToolbar.setTitle(candidateData.getAlias());
            collapsingToolbar.setTitle(" ");
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void loadUserData(CandidateData candidateData) {
        TextView titleView = (TextView) findViewById(R.id.user_title);
        titleView.setText(candidateData.getAlias() + ", " + candidateData.getAge());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void loadUserInterests(CandidateData candidateData) {
        FlowLayout interestsView = (FlowLayout) findViewById(R.id.interests_layout);
        LayoutInflater inflater = LayoutInflater.from(this);
        JSONArray interests = candidateData.getInterests();
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
        } catch (JSONException e) {}
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

    protected CandidateData getDataFromIntent() {
        Intent intent = getIntent();
        String data = intent.getStringExtra(USER);
        try {
            return new CandidateData(new JSONObject(data));
        } catch (JSONException e) {
            Log.e(getString(R.string.JSON_ERROR), e.toString());
            return null;
        }
    }
}
