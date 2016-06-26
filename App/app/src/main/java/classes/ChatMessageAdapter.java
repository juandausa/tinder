package classes;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.tinder_app.R;

import java.util.List;

/**
 * Adapter for the Chat view
 */
public class ChatMessageAdapter extends ArrayAdapter<ChatMessage> {

    private static final int MY_MESSAGE = 0;
    private static final int OTHER_MESSAGE = 1;
    private static final int MY_IMAGE = 2;
    private static final int OTHER_IMAGE = 3;

    /**
     * Constructor for the ChatMessageAdapter
     *
     * @param context the context where it is used
     * @param data    the data to be stored
     */
    public ChatMessageAdapter(Context context, List<ChatMessage> data) {
        super(context, R.layout.item_mine_message, data);
    }

    /**
     * Returns the count of data types in the adapter
     *
     * @return the count of data types in the adapter
     */
    @Override
    public int getViewTypeCount() {
        // my message, other message, my image, other image
        return 4;
    }

    /**
     * Returns the type of the data at position 'position'
     *
     * @param position the position of the data selected
     * @return the type of the data at position 'position'
     */
    @Override
    public int getItemViewType(int position) {
        ChatMessage item = getItem(position);

        if (item.isMine() && !item.ismIsImage()) {
            return MY_MESSAGE;
        } else if (!item.isMine() && !item.ismIsImage()) {
            return OTHER_MESSAGE;
        } else if (item.isMine() && item.ismIsImage()) {
            return MY_IMAGE;
        } else {
            return OTHER_IMAGE;
        }
    }

    /**
     * Gets the view whit all the messages generated from the data stored in the adapter
     *
     * @param position  position of the data that will be procesed to generate it's view
     * @param otherView the view
     * @param parent    the parent view
     * @return the generated view
     */
    @Override
    public View getView(int position, View otherView, ViewGroup parent) {
        View convertView = otherView;
        int viewType = getItemViewType(position);
        if (viewType == MY_MESSAGE) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.item_mine_message, parent, false);

            TextView textView = (TextView) convertView.findViewById(R.id.text);
            textView.setText(getItem(position).getContent());

        } else if (viewType == OTHER_MESSAGE) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.item_other_message, parent, false);

            TextView textView = (TextView) convertView.findViewById(R.id.text);
            textView.setText(getItem(position).getContent());
        } else if (viewType == MY_IMAGE) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.item_mine_image, parent, false);
        } else {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.item_other_image, parent, false);
        }

        convertView.findViewById(R.id.chatMessageView).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getContext(), "onClick", Toast.LENGTH_LONG).show();
            }
        });


        return convertView;
    }
}
