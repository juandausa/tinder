package com.tinder_app;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
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
 * Activity that shows the data of the user
 */
public class MyUserProfileActivity extends UserProfileActivity {

    /**
     * Sets up the activity data and look
     *
     * @param savedInstance the saved state of the activity
     */
    @Override
    public void onCreate(Bundle savedInstance) {
        super.onCreate(savedInstance);
        setButtonInvisible(R.id.like_fab);
        setButtonInvisible(R.id.dislike_fab);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.edit_profile_fab);
        if (fab == null) {
            return;
        }
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

    /**
     * Set visibility of the button with id "resourceId" invisible
     *
     * @param resourceId the id of the button
     */
    private void setButtonInvisible(int resourceId) {
        FloatingActionButton fab = (FloatingActionButton) findViewById(resourceId);
        if (fab != null) {
            fab.setVisibility(View.GONE);
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Inflates the menu that contains the options available for this activity
     *
     * @param menu the menu for this activity
     * @return true
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.edit_profile_actions, menu);
        return true;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Executes a determined action on item's selection on the menu.
     *
     * @param item item selected
     * @return true if action is performed, false otherwise.
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
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

    /**
     * Launch the EditProfileActivity for editing the profile data
     */
    private void launchEditProfileActivity() {
        Intent intent = new Intent(getApplicationContext(), EditProfileActivity.class);
        intent.putExtra(USER, mUserData.toString());
        startActivityForResult(intent, 1);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * On result from the EditProfileActivity updates the user data.
     *
     * @param requestCode the request code sent in the startActivityForResult
     * @param resultCode  the result code sent by the finished activity
     * @param data        the data result of the finished activity
     */
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
            } catch (JSONException e) {
                Log.e(getString(R.string.JSON_ERROR), e.toString());
            }
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Reads and returns image stored in the path indicated by the filePath
     *
     * @param filePath the path of the stored image
     * @return a Bitmap with the image wanted
     */
    private Bitmap getImage(String filePath) {
        //File sd = Environment.getExternalStorageDirectory();
        File image = new File(filePath);
        BitmapFactory.Options bmOptions = new BitmapFactory.Options();
        return BitmapFactory.decodeFile(image.getAbsolutePath(), bmOptions);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the user data
     *
     * @param data the data of the user in a JSONObject
     * @return the user data in an instance of MyUserProfileData
     */
    @Override
    protected UserData buildUserData(JSONObject data) {
        return new MyUserProfileData(data);
    }
}
