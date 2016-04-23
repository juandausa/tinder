package com.tinder_app;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.view.GravityCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;

import classes.MyUserProfileData;
import classes.UserData;

/**
 * Created by fabrizio on 28/03/16.
 */
public class MyUserProfileActivity extends UserProfileActivity {

    @Override
    public void onCreate(Bundle savedInstance) {
        super.onCreate(savedInstance);
        findViewById(R.id.like_fab).setVisibility(View.GONE);
        findViewById(R.id.dislike_fab).setVisibility(View.GONE);
        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.edit_profile_fab);
        fab.setVisibility(View.VISIBLE);
        fab.setBackgroundTintList(getResources().getColorStateList(R.color.com_facebook_blue));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                launchEditProfileActivity();
            }
        });
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
                launchEditProfileActivity();
                return true;
            default:
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void launchEditProfileActivity() {
        Intent intent = new Intent(getApplicationContext(), EditProfileActivity.class);
        intent.putExtra("user", mUserData.toString());
        startActivityForResult(intent, 1);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode == Activity.RESULT_OK) {
            try {
                JSONObject jsonObject = new JSONObject(data.getStringExtra(USER));
                mUserData = new MyUserProfileData(jsonObject);
                Bitmap image = getImage(data.getStringExtra("image_path"));
                ((MyUserProfileData) mUserData).setPhoto(image);
                loadBackdropImage(mUserData);
                loadUserData(mUserData);
                mTitleView.invalidate();
                mImageView.invalidate();
            } catch (JSONException e) {}
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private Bitmap getImage(String filePath) {
        //File sd = Environment.getExternalStorageDirectory();
        File image = new File(filePath);
        BitmapFactory.Options bmOptions = new BitmapFactory.Options();
        return BitmapFactory.decodeFile(image.getAbsolutePath(),bmOptions);
    }

    @Override
    protected UserData buildUserData(JSONObject data) {
        return new MyUserProfileData(data);
    }
}
