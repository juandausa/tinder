package com.tinder_app;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RadioGroup;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import classes.DialogFactory;
import classes.MyUserProfileData;
import requests.UpdateProfileRequest;

/**
 * Activity that allows to edit the profile data of the user
 */
public class EditProfileActivity extends AppCompatActivity {

    private static final String USER = "user";
    private static final String AGE = "Edad: ";
    private static final int PICK_IMAGE_REQUEST = 1;

    private MyUserProfileData mUserData;
    private String mSelectedGender;
    private String mNewAlias;
    private Bitmap mNewProfilePhoto;
    private String mNewAge;

    private TextView mAgeView;
    private EditText mText;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set up the activity for edit user profile
     * @param savedInstanceState object for saving the state of the activity
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_profile);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        if (toolbar != null) {
            toolbar.setTitle("Editar perfil");
        }
        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        mUserData = getDataFromIntent();
        initialize();
        setEditablePhoto(mUserData);
        setEditableAlias(mUserData);
        setEditableGender(mUserData);
        setEditableAge(mUserData);
        //setEditableLocation();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Initialize the state of the activity
     */
    private void initialize() {
        mNewAge = mUserData.getAge();
        mNewAlias = mUserData.getAlias();
        mSelectedGender = mUserData.getGender();
        mNewProfilePhoto = mUserData.getPhoto();
    }


    /**
     * Get data from the intent that started this activity
     * @return the profile data of the user sent by the father activity
     */
    protected MyUserProfileData getDataFromIntent() {
        Intent intent = getIntent();
        String data = intent.getStringExtra(USER);
        try {
            return new MyUserProfileData(new JSONObject(data));
        } catch (JSONException e) {
            Log.e(getString(R.string.JSON_ERROR), e.toString());
            return null;
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set the profile photo and the behaviour of it, so it can be edited. Starts an activity that
     * allows the user to choose an image from the gallery
     * @param data the profile data of the user
     */
    private void setEditablePhoto(MyUserProfileData data) {
        final ImageView imageView = (ImageView) findViewById(R.id.editable_profile_picture);
        if ((imageView != null) && (data != null)) {
            imageView.setImageBitmap(data.getPhoto());
        }
        Button editPhoto = (Button) findViewById(R.id.edit_photo_button);
        if (editPhoto == null) return;
        editPhoto.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setType("image/*");
                intent.setAction(Intent.ACTION_GET_CONTENT);
                startActivityForResult(Intent.createChooser(intent, "Select Picture"), PICK_IMAGE_REQUEST);
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * On result from the activity that gets an image from the gallery, stores that image in an
     * attribute of the activity
     * @param requestCode the request code of the started activity
     * @param resultCode the resulting code from the activity
     * @param data the data sent as result of the activity
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == PICK_IMAGE_REQUEST && resultCode == RESULT_OK && data != null && data.getData() != null) {
            Uri uri = data.getData();

            try {
                mNewProfilePhoto = MediaStore.Images.Media.getBitmap(getContentResolver(), uri);
                // Log.d(TAG, String.valueOf(bitmap));
                ImageView imageView = (ImageView) findViewById(R.id.editable_profile_picture);
                if (imageView == null) return;
                imageView.setImageBitmap(mNewProfilePhoto);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the edit text that holds the alias
     * @param data the user profile data
     */
    private void setEditableAlias(MyUserProfileData data) {
        mText = (EditText) findViewById(R.id.editable_profile_alias);
        if (mText == null) return;
        mText.setText(data.getAlias());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the radio buttons that shows the gender of the user
     * @param data the user profile data
     */
    private void setEditableGender(MyUserProfileData data) {
        RadioGroup gender = (RadioGroup) findViewById(R.id.editable_profile_gender);
        if ((data == null) || (gender == null)) return;

        Log.i("GENDER", data.getGender());
        if (data.getGender().equals("Hombre")) {
            gender.check(R.id.radio_male);
        } else {
            gender.check(R.id.radio_female);
        }
        gender.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if (checkedId == R.id.radio_male) {
                    mSelectedGender = "Hombre";
                } else {
                    mSelectedGender = "Mujer";
                }
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the button and the dialog that contains a number picker for the user age
     * @param userData the user profile data
     */
    private void setEditableAge(MyUserProfileData userData) {
        Button button = (Button) findViewById(R.id.editable_profile_age_button);
        mAgeView = (TextView) findViewById(R.id.editable_profile_age_view);
        if ((userData == null) || (button == null) || (mAgeView == null)) return;
        String ageString = AGE + userData.getAge();
        mAgeView.setText(ageString);
        final AlertDialog ageDialog = DialogFactory.getNumberPickerDialog(this, userData.getAge());

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ageDialog.show();
            }
        });
    }

    /**
     * Update the view that shows the age of the user
     * @param newVal the new value of the user age
     */
    public void updateAgeView(String newVal) {
        String ageString = AGE + newVal;
        mNewAge = newVal;
        mAgeView.setText(ageString);
    }


    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Inflates the option menu of the activity
     * @param menu the menu of the activity
     * @return true
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.edit_done_actions, menu);
        return true;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * When back is pressed, it shows a dialog asking if the user is sure to exit without saving.
     * If he selects "yes", the user finishes this activity and returns to the father activity. If
     * he selects "no" the user remains in this activity.
     */
    @Override
    public void onBackPressed() {
        exitWithoutSaveDialog();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Generates a dialog that asks to the user if he is sure to exit without saving.
     * If he selects "yes", the user finishes this activity and returns to the father activity. If
     * he selects "no" the user remains in this activity.
     */
    private void exitWithoutSaveDialog() {
        DialogFactory.getExitWithoutSaveDialog(this).show();
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
        switch (item.getItemId()) {
            case R.id.edit_done:
                updateUserData();
                return true;
            case android.R.id.home:
                exitWithoutSaveDialog();
                return true;
            default:
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Updates the user data and sends this updated data to a server
     */
    public void updateUserData() {
        mNewAlias = mText.getText().toString();
        mUserData.setAlias(mNewAlias);
        mUserData.setPhoto(mNewProfilePhoto);
        mUserData.setAge(mNewAge);
        mUserData.setGender(mSelectedGender);
        try {
            JSONObject updatedData = new JSONObject(mUserData.toString());
            mUserData.setPhoto(null);   // Avoid sending large amount of data in an intent
            UpdateProfileRequest request = new UpdateProfileRequest(this);
            request.send(updatedData);
        } catch (JSONException e) {
            Log.e(getString(R.string.JSON_ERROR), e.toString());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Saves the result of this activity (the updated user data) and returns to the father activity
     * with this result.
     */
    public void saveChanges() {
        Intent intent = new Intent();
        intent.putExtra(UserProfileActivity.USER, mUserData.toString());
        intent.putExtra("image_path", saveProfilePhoto());
        setResult(Activity.RESULT_OK, intent);
        finish();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Stores in the external storage the profile photo of the user
     * @return the path where the photo was saved
     */
    private String saveProfilePhoto() {
        try {
            String filePath = Environment.getExternalStorageDirectory().getAbsolutePath()
                    + "/tinderCloneProfile";
            File file = new File(filePath);
            FileOutputStream fOut = new FileOutputStream(file);
            mNewProfilePhoto.compress(Bitmap.CompressFormat.JPEG, 85, fOut);
            fOut.flush();
            fOut.close();
            return filePath;
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(null, "Save file error!");
            return null;
        }
    }
}
