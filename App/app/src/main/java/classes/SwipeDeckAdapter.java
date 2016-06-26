package classes;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.tinder_app.MainActivity;
import com.tinder_app.OtherUsersProfileActivity;
import com.tinder_app.R;

import java.util.List;

/**
 * Adapter for the SwipeDeck View.
 */
public class SwipeDeckAdapter extends BaseAdapter {

    private List<CandidateData> mData;
    private Context mContext;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor for the SwipeDeckAdapter class.
     *
     * @param data    List of objects that will appear in each of the cards of the SwipeDeck view.
     * @param context Context where this adapter is used.
     */
    public SwipeDeckAdapter(List<CandidateData> data, Context context) {
        this.mData = data;
        this.mContext = context;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the count of the items stored in the adapter.
     *
     * @return the count of the items stored in the adapter.
     */
    @Override
    public int getCount() {
        return mData.size();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns the item at position 'position' in the adapter.
     *
     * @param position the position of the item wanted.
     * @return the item wanted.
     */
    @Override
    public Object getItem(int position) {
        return mData.get(position);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Get the id of the item at position 'position'.
     *
     * @param position the position of the item from who we want to know it's id.
     * @return the id of the item.
     */
    @Override
    public long getItemId(int position) {
        return position;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Get a View that displays the data at the specified position in the data set.
     *
     * @param position    The position of the item within the adapter's data set of the item whose view
     *                    we want.
     * @param convertView The old view to reuse, if possible.
     * @param parent      The parent that this view will eventually be attached to.
     * @return A View corresponding to the data at the specified position.
     */
    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        View view = convertView;
        if (view == null) {
            LayoutInflater inflater = ((Activity) mContext).getLayoutInflater();
            view = inflater.inflate(R.layout.card, parent, false);
        }
        String candidateAliasText = mData.get(position).getAlias() + ", ";
        ((TextView) view.findViewById(R.id.candidate_alias)).setText(candidateAliasText);
        ((TextView) view.findViewById(R.id.candidate_age)).setText(mData.get(position).getAge());
        ((ImageView) view.findViewById(R.id.candidate_image)).setImageBitmap(mData.get(position).getPhoto());
        setViewListener(view, position);
        return view;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets a OnClickListener to the view passed as parameter.
     *
     * @param v        the view to be listened for clicks.
     * @param position the position of the item wanted in the Adapter to get it's data.
     */
    private void setViewListener(View v, final int position) {
        v.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                CandidateData item = ((CandidateData) getItem(position));
                Toast.makeText(mContext, item.getAlias(), Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(mContext, OtherUsersProfileActivity.class);
                intent.putExtra(OtherUsersProfileActivity.USER, item.toString());
                //mContext.startActivity(intent);
                ((MainActivity) mContext).startActivityForResult(intent, 1);
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Update the values stored in the Adapter and notify the view so it also will update it's
     * data.
     *
     * @param newValues a List with the new values to be added to the adapter.
     */
    public void update(List<CandidateData> newValues) {
        mData = newValues;
        notifyDataSetChanged();
    }
}