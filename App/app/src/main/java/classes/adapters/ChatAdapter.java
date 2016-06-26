package classes.adapters;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.tinder_app.R;

import java.util.List;

import classes.ChatMessage;
import classes.ViewHolder;

/**
 * ViewHolder for the RecyclerView that holds String elements.
 */
public class ChatAdapter extends RecyclerView.Adapter<ViewHolder> {

    private static final int MY_MESSAGE = 0;
    private static final int OTHER_MESSAGE = 1;
    private static final int MY_IMAGE = 2;
    private static final int OTHER_IMAGE = 3;

    private final TypedValue mTypedValue = new TypedValue();
    private int mBackground;
    private List<ChatMessage> mValues;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class MatchesViewAdapter.
     *
     * @param context Context where this object is instanced.
     * @param items   List of elements that will be added to the ViewAdapter
     */
    public ChatAdapter(Context context, List<ChatMessage> items) {
        context.getTheme().resolveAttribute(R.attr.selectableItemBackground, mTypedValue, true);
        mBackground = mTypedValue.resourceId;
        mValues = items;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the value stored in the list passed to the adapter at position 'position'.
     *
     * @param position position of the value.
     * @return the value of the element queried.
     */
    public String getValueAt(int position) {
        return mValues.get(position).getContent();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Method that inflates the view, and adds it to the ViewHolder.
     *
     * @param parent   parent view of the view to be inflated
     * @param viewType type of view.
     * @return the ViewHolder with the view created.
     */
    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.list_item, parent, false);
        view.setBackgroundResource(mBackground);
        return new ViewHolder(view);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * On view holder binded, this method sets the content of the holder and its behavior.
     *
     * @param holder   Holder to be setted.
     * @param position Position of the element of the mValues to be setted to the text's holder.
     */
    @Override
    public void onBindViewHolder(final ViewHolder holder, int position) {
        final ChatMessage message = mValues.get(position);
        holder.setBoundString(message.getContent());
        holder.getTextView().setText(message.getContent());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the count of values stored in the adapter.
     *
     * @return the count of values stored in the adapter.
     */
    @Override
    public int getItemCount() {
        return mValues.size();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Update the values stored in the Adapter and notify the view so it also will update it's
     * data.
     *
     * @param newValues a List with the new values to be added to the adapter.
     */
    public void update(List<ChatMessage> newValues) {
        mValues = newValues;
        notifyDataSetChanged();
    }
}