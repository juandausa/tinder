package com.tinder_app;

import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
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

    private void discoverDistanceBarSetUp() {
        SeekBar seekBar = (SeekBar) findViewById(R.id.distance);
        seekBar.setMax(100);
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                TextView rangeDistance = (TextView) findViewById(R.id.distance_label);
                rangeDistance.setText(Integer.toString(progress) + " km");
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void ageBarSetUp() {
        // https://github.com/edmodo/range-bar/wiki
        // Documentation of RangeBar
        RangeBar rangebar = (RangeBar) findViewById(R.id.age_rangebar);
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
                distance.setText(ageRangeLabel);
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

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

    private void womenSwitchSetUp() {

    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void genderSwitchesSetUp(final GenderObject gender, final GenderObject oppositeGender) {

        gender.getSwitch().setTextOn("");
        gender.getSwitch().setTextOff("");
        gender.getSwitch().setOnDragListener(new View.OnDragListener() {
            @Override
            public boolean onDrag(View v, DragEvent event) {
                TextView genderLabel = (TextView) findViewById(R.id.gender_label);
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

    private class GenderObject {

        private String genderLabel;
        private Switch genderSwitch;

        public GenderObject(String genderLabel, Switch genderSwitch) {
            this.genderLabel = genderLabel;
            this.genderSwitch = genderSwitch;
        }

        public String getLabel() {
            return this.genderLabel;
        }

        public Switch getSwitch() {
            return this.genderSwitch;
        }
    }

}
