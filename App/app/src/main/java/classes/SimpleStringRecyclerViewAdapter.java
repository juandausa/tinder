package classes;

import android.content.Context;
import android.content.Intent;
import android.support.v7.widget.RecyclerView;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.bumptech.glide.Glide;
import com.tinder_app.Cheeses;
import com.tinder_app.OtherUsersProfileActivity;
import com.tinder_app.R;

import java.util.List;

/**
 * ViewHolder for the RecyclerView that holds String elements.
 */
public class SimpleStringRecyclerViewAdapter extends RecyclerView.Adapter<ViewHolder> {

    private final TypedValue mTypedValue = new TypedValue();
    private int mBackground;
    private List<String> mValues;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class SimpleStringRecyclerViewAdapter.
     * @param context Context where this object is instanced.
     * @param items List of elements that will be added to the ViewAdapter
     */
    public SimpleStringRecyclerViewAdapter(Context context, List<String> items) {
        context.getTheme().resolveAttribute(R.attr.selectableItemBackground, mTypedValue, true);
        mBackground = mTypedValue.resourceId;
        mValues = items;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Gets the value stored in the list passed to the adapter at position 'position'.
     * @param position position of the value.
     * @return the value of the element queried.
     */
    public String getValueAt(int position) {
        return mValues.get(position);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Method that inflates the view, and adds it to the ViewHolder.
     * @param parent parent view of the view to be inflated
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
     * @param holder Holder to be setted.
     * @param position Position of the element of the mValues to be setted to the text's holder.
     */
    @Override
    public void onBindViewHolder(final ViewHolder holder, int position) {
        holder.setBoundString(mValues.get(position));
        holder.getTextView().setText(mValues.get(position));

        holder.getView().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Context context = v.getContext();
                Intent intent = new Intent(context, OtherUsersProfileActivity.class);
                intent.putExtra(OtherUsersProfileActivity.EXTRA_NAME, holder.getBoundString());

                context.startActivity(intent);
            }
        });

        Glide.with(holder.getImageView().getContext())
                .load(Cheeses.getRandomCheeseDrawable())
                .fitCenter()
                .into(holder.getImageView());
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the count of values stored in the adapter.
     * @return the count of values stored in the adapter.
     */
    @Override
    public int getItemCount() {
        return mValues.size();
    }
}