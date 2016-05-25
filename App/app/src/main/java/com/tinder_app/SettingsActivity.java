package com.tinder_app;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.SeekBar;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import classes.Constants;
import classes.DialogFactory;
import classes.SettingsManager;
import requests.ChangeSettingsRequest;

/**
 * This Activity holds the settings controls that allows the user customize some features.
 */
public class SettingsActivity extends AppCompatActivity {

    private static final int MAX_DISTANCE = 100;
    private int mDistance;
    private boolean mMenChecked;
    private boolean mWomenChecked;
    private String mMenString;
    private String mWomenString;
    private TextView mGenderLabel;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set up the look and behavior of the activity
     * @param savedInstanceState saved state of the activity
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        discoverDistanceBarSetUp();
        setUpGenderInterestCheckboxes();
        mMenChecked = SettingsManager.getInterestedInMen(SettingsActivity.this);
        mWomenChecked = SettingsManager.getInterestedInWomen(SettingsActivity.this);
        mDistance = SettingsManager.getDistance(SettingsActivity.this);
        TextView rangeDistance = (TextView) findViewById(R.id.distance_label);
        rangeDistance.setText(Integer.toString(mDistance));
        //ageBarSetUp();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets up the discover distance bar, a seek bar with max range 100.
     */
    private void discoverDistanceBarSetUp() {
        SeekBar seekBar = (SeekBar) findViewById(R.id.distance);
        if (seekBar == null) {
            return;
        }
        seekBar.setMax(MAX_DISTANCE);
        seekBar.setProgress(SettingsManager.getDistance(SettingsActivity.this));
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                TextView rangeDistance = (TextView) findViewById(R.id.distance_label);
                String selectedDistance = Integer.toString(progress) + " km";
                if (rangeDistance == null) {
                    return;
                }
                rangeDistance.setText(selectedDistance);
                mDistance = progress;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void setUpGenderInterestCheckboxes() {
        mGenderLabel = (TextView) findViewById(R.id.gender_label);
        setBehaviorToMenCheckbox();
        setBehaviorToWomenCheckbox();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void setBehaviorToMenCheckbox() {
        CheckBox men = (CheckBox) findViewById(R.id.men);
        final CheckBox women = (CheckBox) findViewById(R.id.women);
        if ((women == null) || (men == null)) {
            return;
        }
        men.setChecked(SettingsManager.getInterestedInMen(SettingsActivity.this));
        mMenString = getString(R.string.men);
        setGenderLabel(mGenderLabel, men.isChecked(), women.isChecked(), mMenString, mWomenString);
        men.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                mMenChecked = isChecked;
                if (mGenderLabel == null) {
                    return;
                }
                setGenderLabel(
                        mGenderLabel,
                        isChecked,
                        women.isChecked(),
                        mMenString,
                        mWomenString
                );
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void setBehaviorToWomenCheckbox() {
        CheckBox women = (CheckBox) findViewById(R.id.women);
        final CheckBox men = (CheckBox) findViewById(R.id.men);
        if ((women == null) || (men == null)) {
            return;
        }
        women.setChecked(SettingsManager.getInterestedInWomen(SettingsActivity.this));
        mWomenString = getString(R.string.women);
        setGenderLabel(mGenderLabel, women.isChecked(), men.isChecked(), mWomenString, mMenString);
        women.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                mWomenChecked = isChecked;
                if (mGenderLabel == null) {
                    return;
                }
                setGenderLabel(
                        mGenderLabel,
                        isChecked,
                        men.isChecked(),
                        mWomenString,
                        mMenString
                );
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void setGenderLabel(TextView genderLabel, boolean genderChecked,
                        boolean otherGenderChecked, String genderString, String otherGenderString) {
        if ((genderChecked) && (otherGenderChecked)) {
            String label = genderString + " y " + otherGenderString;
            genderLabel.setText(label);
        } else if (genderChecked) {
            genderLabel.setText(genderString);
        } else if (otherGenderChecked) {
            genderLabel.setText(otherGenderString);
        } else {
            genderLabel.setText("");
        }
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

        if ((!mMenChecked) && (!mWomenChecked)) {
            DialogFactory.exitWithoutSelectingGenderDialog(SettingsActivity.this).show();
            return;
        }

        ChangeSettingsRequest request = new ChangeSettingsRequest(SettingsActivity.this);
        JSONObject filters = new JSONObject();
        String genderString = "";
        if ((mMenChecked) && (mWomenChecked)) {
            genderString = "Male,Female";
        } else if (mWomenChecked) {
            genderString = "Female";
        } else {
            genderString = "Male";
        }
        try {
            filters.put(Constants.SHOW_GENDER, genderString);
            filters.put(Constants.DISCOVERING_DISTANCE, mDistance);
            request.send(filters);
        } catch (JSONException e) {
            Log.e(getString(R.string.JSON_ERROR), e.toString());
        }
        finish();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void saveChanges() {
        SettingsManager.changeDistance(SettingsActivity.this, mDistance);
        SettingsManager.changeInterestOnMen(SettingsActivity.this, mMenChecked);
        SettingsManager.changeInterestOnWomen(SettingsActivity.this, mWomenChecked);
    }

}
