package com.tinder_app;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.view.View;

import org.json.JSONObject;

import classes.CandidateData;
import classes.UserData;

/**
 * Activity that contains and shows the data of other users
 */
public class OtherUsersProfileActivity extends UserProfileActivity {

    /**
     * Sets up the activity data and look
     * @param savedInstance the saved state of the activity
     */
    @Override
    public void onCreate(Bundle savedInstance) {
        super.onCreate(savedInstance);
        setButtonVisibility(R.id.like_fab, View.VISIBLE);
        setButtonVisibility(R.id.dislike_fab, View.VISIBLE);
        setButtonVisibility(R.id.edit_profile_fab, View.GONE);
        setUpLikeButton();
        setUpDislikeButton();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set the visibility of the button with id "resourceId"
     * @param resourceId the id of the button
     * @param visibility the visibility wanted for the button
     */
    private void setButtonVisibility(int resourceId, int visibility) {
        View view = findViewById(resourceId);
        if (view != null) {
            view.setVisibility(visibility);
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set up the look and the behavior of the like button
     */
    private void setUpLikeButton() {
        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.like_fab);
        if (fab == null) return;
        fab.setBackgroundTintList(getResources().getColorStateList(R.color.light_green));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Here's a Snackbar", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set up the look and the behavior of the dislike button
     */
    private void setUpDislikeButton() {
        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.dislike_fab);
        if (fab == null) return;
        fab.setBackgroundTintList(getResources().getColorStateList(android.R.color.holo_red_light));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Here's a Snackbar", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the user data
     * @param data the data of the user in a JSONObject
     * @return the user data in an instance of CandidateData
     */
    @Override
    protected UserData buildUserData(JSONObject data) {
        return new CandidateData(data);
    }
}
