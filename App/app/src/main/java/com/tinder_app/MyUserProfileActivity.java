package com.tinder_app;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.view.GravityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

/**
 * Created by fabrizio on 28/03/16.
 */
public class MyUserProfileActivity extends UserProfileActivity {

    @Override
    public void onCreate(Bundle savedInstance) {
        super.onCreate(savedInstance);
        findViewById(R.id.like_fab).setVisibility(View.GONE);
        findViewById(R.id.dislike_fab).setVisibility(View.GONE);
        findViewById(R.id.edit_profile_fab).setVisibility(View.VISIBLE);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.edit_profile_actions, menu);
        return true;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Executes a determined action on item's selection on the menu.
     * @param item item selected
     * @return true if action is performed, false otherwise.
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Intent intent = null;
        switch (item.getItemId()) {
            case R.id.edit_profile:
                return true;
            default:
                break;
        }
        return super.onOptionsItemSelected(item);
    }
}
