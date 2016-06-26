package classes;

import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.tinder_app.R;

/**
 * View holder for the RecyclerView.
 */
public class ViewHolder extends RecyclerView.ViewHolder {

    private final View mView;
    private final ImageView mImageView;
    private final TextView mTextView;
    private String mBoundString;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor for the ViewHolder class.
     *
     * @param view The view to be holded by the view holder.
     */
    public ViewHolder(View view) {
        super(view);
        mView = view;
        mImageView = (ImageView) view.findViewById(R.id.avatar);
        mTextView = (TextView) view.findViewById(android.R.id.text1);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter for the mTextView attribute.
     *
     * @return the mTextView attribute.
     */
    public final TextView getTextView() {
        return mTextView;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter for the mView attribute.
     *
     * @return the mView attribute.
     */
    public final View getView() {
        return mView;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter for the mImageView attribute.
     *
     * @return the mImageView attribute.
     */
    public final ImageView getImageView() {
        return mImageView;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter for the mBoundString attribute.
     *
     * @return the mBoundString attribute.
     */
    public String getBoundString() {
        return mBoundString;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Setter for the mBoundString attribute.
     *
     * @param mBoundString the new value for the mBoundString attribute.
     */
    public void setBoundString(String mBoundString) {
        this.mBoundString = mBoundString;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Stringify the ViewHolder.
     *
     * @return a string that represents the ViewHolder.
     */
    @Override
    public String toString() {
        return super.toString() + " '" + mTextView.getText();
    }
}