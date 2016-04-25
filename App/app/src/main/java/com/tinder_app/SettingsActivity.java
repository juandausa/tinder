package com.tinder_app;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.DragEvent;
import android.view.View;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import com.edmodo.rangebar.RangeBar;

/**
 * This Activity holds the settings controls that allows the user customize some features.
 */
public class SettingsActivity extends AppCompatActivity {

    private static final int MAX_DISTANCE = 100;

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
        ageBarSetUp();
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
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                TextView rangeDistance = (TextView) findViewById(R.id.distance_label);
                String selectedDistance = Integer.toString(progress) + " km";
                if (rangeDistance == null) {
                    return;
                }
                rangeDistance.setText(selectedDistance);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                //TODO
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                //TODO
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets up the view that allows the user to select the age range
     * For docs of RangeBar go to https://github.com/edmodo/range-bar/wiki
     */
    private void ageBarSetUp() {
        RangeBar rangebar = (RangeBar) findViewById(R.id.age_rangebar);
        if (rangebar == null) {
            return;
        }
        rangebar.setTickCount(100);
        rangebar.setTickHeight(25);
        rangebar.setBarWeight(6);
        rangebar.setBarColor(android.R.color.holo_red_light);
        rangebar.setOnRangeBarChangeListener(new RangeBar.OnRangeBarChangeListener() {
            @Override
            public void onIndexChangeListener(RangeBar rangeBar, int leftThumbIndex, int rightThumbIndex) {
                //Code using the leftThumbIndex and rightThumbIndex to update the index values.
                TextView distance = (TextView) findViewById(R.id.age_label);
                String ageRangeLabel = Integer.toString(leftThumbIndex) + " - "
                        + Integer.toString(rightThumbIndex);
                if (distance == null) {
                    return;
                }
                distance.setText(ageRangeLabel);
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets up the switch that indicates that the user is interested in men
     */
    private void menSwitchSetUp() {
        Switch men = (Switch) findViewById(R.id.men);
        Switch women = (Switch) findViewById(R.id.women);
        GenderObject menObject = new GenderObject("Hombres", men);
        GenderObject womenObject = new GenderObject("mujeres", women);
        genderSwitchesSetUp(menObject, womenObject);
        genderSwitchesSetUp(womenObject, menObject);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets up the switch that indicates that the user is interested in women
     */
    private void womenSwitchSetUp() {

    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets up the switches that indicates in wich gender is the user interested
     */
    private void genderSwitchesSetUp(final GenderObject gender, final GenderObject oppositeGender) {
        if (gender == null) {
            return;
        }
        gender.getSwitch().setTextOn("");
        gender.getSwitch().setTextOff("");
        gender.getSwitch().setOnDragListener(new View.OnDragListener() {
            @Override
            public boolean onDrag(View v, DragEvent event) {
                TextView genderLabel = (TextView) findViewById(R.id.gender_label);
                if (genderLabel == null) {
                    return false;
                }
                if (gender.getSwitch().isChecked()) {
                    if (oppositeGender.getSwitch().isChecked()) {
                        genderLabel.setText("Hombres y mujeres");

                    } else {
                        genderLabel.setText(gender.getLabel());
                    }
                }
                else if (oppositeGender.getSwitch().isChecked()) {
                    genderLabel.setText(oppositeGender.getLabel());

                }
                genderLabel.invalidate();
                return true;
            }
        });
    }

    /**********************************************************************************************/
    /*********************                  AUXILIAR CLASS              ***************************/
    /**********************************************************************************************/

    /**
     * Class that models a gender with its corresponding switch
     */
    private class GenderObject {

        private String mGenderLabel;
        private Switch mGenderSwitch;

        public GenderObject(String genderLabel, Switch genderSwitch) {
            this.mGenderLabel = genderLabel;
            this.mGenderSwitch = genderSwitch;
        }

        public String getLabel() {
            return this.mGenderLabel;
        }

        public Switch getSwitch() {
            return this.mGenderSwitch;
        }
    }

}
