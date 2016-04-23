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

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import classes.DialogFactory;
import classes.MyUserProfileData;
import requests.UpdateProfileRequest;

public class EditProfileActivity extends AppCompatActivity {

    private int PICK_IMAGE_REQUEST = 1;
    private final static String USER = "user";
    private final static String AGE = "Edad: ";

    private MyUserProfileData mUserData;
    private String mSelectedGender;
    private String mNewAlias;
    private Bitmap mNewProfilePhoto;
    private String mNewAge;

    private TextView mAgeView;
    private EditText mText;

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

    private void initialize() {
        mNewAge = mUserData.getAge();
        mNewAlias = mUserData.getAlias();
        mSelectedGender = mUserData.getGender();
        mNewProfilePhoto = mUserData.getPhoto();
    }


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

    private void setEditableAlias(MyUserProfileData data) {
        mText = (EditText) findViewById(R.id.editable_profile_alias);
        if (mText == null) return;
        mText.setText(data.getAlias());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

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

    public void updateAgeView(String newVal) {
        String ageString = AGE + newVal;
        mNewAge = newVal;
        mAgeView.setText(ageString);
    }


    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.edit_done_actions, menu);
        return true;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public void onBackPressed() {
        exitWithoutSaveDialog();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

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
        } catch (JSONException e) {}
    }

    /**********************************************************************************************/
    /**********************************************************************************************/


    public void saveChanges() {
        Intent intent = new Intent();
        intent.putExtra(UserProfileActivity.USER, mUserData.toString());
        intent.putExtra("image_path", saveProfilePhoto());
        setResult(Activity.RESULT_OK, intent);
        finish();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private String saveProfilePhoto() {
        try{
            String filePath = Environment.getExternalStorageDirectory().getAbsolutePath() +
                    "/tinderCloneProfile";
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
