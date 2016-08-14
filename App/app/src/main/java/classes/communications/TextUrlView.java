package classes.communications;

import android.widget.TextView;


/**
 * Class that represents a proxy of a textView
 */
public class TextUrlView implements AsyncCallerResponse {

    private String mUrl;
    private TextView mTextViewToFill;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class
     * @param url the url from where the text is loaded
     * @param textViewToFill the imageView to fill with the text loaded
     */
    public TextUrlView(String url, TextView textViewToFill) {
        this.mUrl = url;
        this.mTextViewToFill = textViewToFill;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Conects to the url
     */
    public void connect() {
        new ServerConnectGet(this).execute(mUrl);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Callback that sets the text into the viewImage when the loading is finished
     * @param data the text
     */
    @Override
    public void processFinish(String data) {
        mTextViewToFill.setText(data);
    }
}
