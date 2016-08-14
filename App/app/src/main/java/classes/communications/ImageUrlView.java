package classes.communications;

import android.graphics.Bitmap;
import android.widget.ImageView;

/**
 * Proxy of a image from a url
 */
public class ImageUrlView implements AsyncCallerBitmapResponse {

    private String mUrl;
    private ImageView mImageViewToFill;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor for the instance
     * @param url the url from where the image will be loaded
     * @param imageViewToFill imageView to be filled with the bitmap of the image
     */
    public ImageUrlView(String url, ImageView imageViewToFill) {
        this.mUrl = url;
        this.mImageViewToFill = imageViewToFill;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Connect and load the image from the url
     */
    public void connect() {
        new ServerConnectoBitmapGet(this).execute(mUrl);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Finish the process of loading the image and set the image bitmap to the imageView
     * @param image the bitmap
     */
    @Override
    public void processFinish(Bitmap image) {
        mImageViewToFill.setImageBitmap(image);
    }
}
