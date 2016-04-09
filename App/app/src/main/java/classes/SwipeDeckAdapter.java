package classes;


import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.tinder_app.R;
import java.util.List;

/**
 * Adapter for the SwipeDeck View.
 */
public class SwipeDeckAdapter extends BaseAdapter {

    private List<CandidateData> mData;
    private Context mContext;

    /**
     * Constructor for the SwipeDeckAdapter class.
     * @param data List of objects that will appear in each of the cards of the SwipeDeck view.
     * @param context Context where this adapter is used.
     */
    public SwipeDeckAdapter(List data, Context context) {
        this.mData = data;
        this.mContext = context;
    }

    @Override
    public int getCount() {
        return mData.size();
    }

    @Override
    public Object getItem(int position) {
        return mData.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {

        View v = convertView;
        if (v == null) {
            LayoutInflater inflater = ((Activity) mContext).getLayoutInflater();
            // normally use a viewholder
            v = inflater.inflate(R.layout.card, parent, false);

        }
        ((TextView) v.findViewById(R.id.candidate_alias)).setText(mData.get(position).getAlias() + ", ");
        ((TextView) v.findViewById(R.id.candidate_age)).setText(mData.get(position).getAge());
        ((ImageView) v.findViewById(R.id.candidate_image)).setImageBitmap(mData.get(position).getPhoto());

        v.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String item = ((CandidateData) getItem(position)).getAlias();
                Log.i("MainActivity", item);
            }
        });

        return v;
    }

    public void update(List newValues) {
        mData = newValues;
        notifyDataSetChanged();
    }

}