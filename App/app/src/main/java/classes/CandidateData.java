package classes;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Parcel;
import android.os.Parcelable;
import android.util.Base64;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.Serializable;

/**
 * Class that represents a candidate to be a match with the current user.
 */
public class CandidateData extends UserData {

    public CandidateData(JSONObject candidate) {
        super(candidate);
    }
}
