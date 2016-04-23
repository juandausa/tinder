package classes;

import android.content.Context;
import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.widget.NumberPicker;
import android.widget.TextView;

import com.tinder_app.EditProfileActivity;

/**
 * Created by fabrizio on 23/04/16.
 */
public class DialogFactory {

    /**********************************************************************************************/
    /**********************************************************************************************/

    private DialogFactory() {}

    /**********************************************************************************************/
    /**********************************************************************************************/

    public static AlertDialog getNumberPickerDialog(final EditProfileActivity context, final String initValue) {
        NumberPicker picker = new NumberPicker(context);
        picker.setValue(Integer.valueOf(initValue));
        picker.setMaxValue(100);
        picker.setMinValue(18);
        picker.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
            @Override
            public void onValueChange(NumberPicker picker, int oldVal, int newVal) {
                context.updateAgeView(Integer.toString(newVal));
            }
        });

        return new AlertDialog.Builder(context)
                .setTitle("Elegir edad")
                .setView(picker)
                .setCancelable(false)
                .setPositiveButton("ok", null)
                .setNegativeButton("cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        context.updateAgeView(initValue);
                    }
                }).create();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public static AlertDialog getExitWithoutSaveDialog(final EditProfileActivity context) {
        return new AlertDialog.Builder(context)
                .setTitle("Cambios sin guardar")
                .setMessage("¿Desea salir sin guardar los cambios?")
                .setCancelable(false)
                .setPositiveButton("si", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        context.finish();
                    }
                })
                .setNegativeButton("no", null).create();
    }
}
