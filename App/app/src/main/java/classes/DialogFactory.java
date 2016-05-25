package classes;

import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.widget.NumberPicker;

import com.tinder_app.EditProfileActivity;
import com.tinder_app.R;
import com.tinder_app.SettingsActivity;

/**
 * Factory class that builds different types of dialogs
 */
public final class DialogFactory {

    private static final int MAX_AGE = 100;
    private static final int MIN_AGE = 18;
    /**
     * Private constructor of the DialogFactory class
     */
    private DialogFactory() {
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Builds a dialog with a number picker.
     * @param context The context where the dialog is used
     * @param initValue initial value of the number picker
     * @return an AlertDialog with a number picker
     */
    public static AlertDialog getNumberPickerDialog(final EditProfileActivity context,
                                                    final String initValue) {
        NumberPicker picker = new NumberPicker(context);
        int value = Integer.parseInt(initValue);
        picker.setValue(value);
        picker.setMaxValue(MAX_AGE);
        picker.setMinValue(MIN_AGE);
        picker.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
            @Override
            public void onValueChange(NumberPicker picker, int oldVal, int newVal) {
                context.updateAgeView(Integer.toString(newVal));
            }
        });

        return new AlertDialog.Builder(context)
                .setTitle(R.string.select_age)
                .setView(picker)
                .setCancelable(false)
                .setPositiveButton(R.string.OK, null)
                .setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        context.updateAgeView(initValue);
                    }
                }).create();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Builds a dialog with a message that asks to exit without save.
     * @param context The context where the dialog is used
     * @return an AlertDialog with a meessage that asks to exit without save
     */
    public static AlertDialog getExitWithoutSaveDialog(final EditProfileActivity context) {
        return new AlertDialog.Builder(context)
                .setTitle(R.string.changes_not_saved)
                .setMessage(R.string.save_changes)
                .setCancelable(false)
                .setPositiveButton(R.string.yes, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        context.finish();
                    }
                })
                .setNegativeButton(R.string.no, null).create();
    }


    /**
     * Builds a dialog with a message that informs that the user can leave the activity without
     * selecting one or more genders.
     * @param context The context where the dialog is used
     * @return an AlertDialog with a meessage that informs the situation
     */
    public static AlertDialog exitWithoutSelectingGenderDialog(final SettingsActivity context) {
        return new AlertDialog.Builder(context)
                .setTitle(R.string.gender_not_selected)
                .setMessage(R.string.select_one_or_more_genders)
                .setCancelable(false)
                .setPositiveButton(R.string.OK, null).create();
    }
}
