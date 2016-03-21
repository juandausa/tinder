package classes;

import android.content.Context;
import android.support.v4.view.ViewPager;
import android.util.AttributeSet;
import android.view.MotionEvent;

/**
 * ViewPager with disabled responses to touch and drag.
 */
public class CustomViewPager extends ViewPager {

    /**
     * Constructor for the CustomViewPager class.
     * @param context Contex of the CustomViewPager.
     */
    public CustomViewPager(Context context) {
        super(context);
    }

    /**
     * Constructor for the CustomViewPager class.
     * @param context Contex of the CustomViewPager.
     * @param attrs Other attributes.
     */
    public CustomViewPager(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent arg0) {
        // Never allow swiping to switch between pages
        return false;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        // Never allow swiping to switch between pages
        return false;
    }

}
