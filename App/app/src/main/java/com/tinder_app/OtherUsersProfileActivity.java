package com.tinder_app;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

/**
 * Created by fabrizio on 28/03/16.
 */
public class OtherUsersProfileActivity extends UserProfileActivity {

    @Override
    public void onCreate(Bundle savedInstance) {
        super.onCreate(savedInstance);
        findViewById(R.id.like_fab).setVisibility(View.VISIBLE);
        findViewById(R.id.dislike_fab).setVisibility(View.VISIBLE);
        setUpLikeButton();
        setUpDislikeButton();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void setUpLikeButton() {
        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.like_fab);
        if (fab == null) {
            return;
        }
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

    private void setUpDislikeButton() {
        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.dislike_fab);
        if (fab == null) {
            return;
        }
        fab.setBackgroundTintList(getResources().getColorStateList(android.R.color.holo_red_light));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Here's a Snackbar", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
    }
}
