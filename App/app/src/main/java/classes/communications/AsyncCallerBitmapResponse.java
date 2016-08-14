package classes.communications;

import android.graphics.Bitmap;

/**
 * Interface that exports the method to finish the process of load a bitmap
 */
@Deprecated
public interface AsyncCallerBitmapResponse {

    /**
     * Logic that execute when finishes the process of load a bitmap
     * @param image the bitmap
     */
    public void processFinish(Bitmap image);
}
