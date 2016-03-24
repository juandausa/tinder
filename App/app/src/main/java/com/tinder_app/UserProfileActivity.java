package com.tinder_app;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.CollapsingToolbarLayout;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.View;
import android.widget.ImageView;

import com.bumptech.glide.Glide;

/**
 * Activity that shows the profile information of a determined user.
 */
public class UserProfileActivity extends AppCompatActivity {

    /**
     * Hardcoded string for getting the name of the user.
     */
    public static final String EXTRA_NAME = "cheese_name";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);

        Intent intent = getIntent();
        final String cheeseName = intent.getStringExtra(EXTRA_NAME);

        final Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        CollapsingToolbarLayout collapsingToolbar
                = (CollapsingToolbarLayout) findViewById(R.id.collapsing_toolbar);
        if (collapsingToolbar != null) {
            collapsingToolbar.setTitle(cheeseName);
        }
        loadBackdrop();
        setUpLikeButton();
        setUpDislikeButton();
    }


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

    private void loadBackdrop() {
        final ImageView imageView = (ImageView) findViewById(R.id.backdrop);
        if (imageView != null) {
            Glide.with(this).load(Cheeses.getRandomCheeseDrawable()).centerCrop().into(imageView);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.sample_actions, menu);
        return true;
    }
}
