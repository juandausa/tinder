package com.tinder_app;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

import classes.ChatMessage;
import classes.ChatMessageAdapter;
import classes.Constants;
import classes.Conversation;
import classes.SessionManager;
import requests.chat.SendNewMessageRequest;
import services.GetNewMessageService;

/**
 * Chat Activity of the user with other
 */
public class MatchChatActivity extends AppCompatActivity {

    private String mOtherUserId = null;
    private Conversation mConversation;
    private String mAlias;
    private String mUserId;
    private ListView mListView;
    private ChatMessageAdapter mAdapter;
    private Button mButtonSend;
    private EditText mEditTextMessage;
    private boolean mIsAlive;
    private Thread mListenMessagesThread;
    private JSONArray mOldMessages;


    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the activity data and views
     *
     * @param savedInstanceState the saved state of the activity to be restored
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_match_chat);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        mListenMessagesThread = new Thread(new GetNewMessageService(this));

        mListView = (ListView) findViewById(R.id.listMessageView);
        mButtonSend = (Button) findViewById(R.id.btn_send);
        mEditTextMessage = (EditText) findViewById(R.id.et_message);

        Intent intent = getIntent();
        mAlias = intent.getStringExtra(Constants.ALIAS);
        mOtherUserId = intent.getStringExtra(Constants.USER_ID);

        mUserId = SessionManager.getUserId(this);
        mConversation = new Conversation(intent.getStringExtra(Constants.CONVERSATION));
        //toolbar.setTitle(mAlias);
        toolbar.bringToFront();
        getSupportActionBar().setTitle(mAlias);

        mAdapter = new ChatMessageAdapter(this, new ArrayList<ChatMessage>());
        mListView.setAdapter(mAdapter);
        mListView.setSelection(mAdapter.getCount() - 1);


        mButtonSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = mEditTextMessage.getText().toString();
                if (TextUtils.isEmpty(message)) {
                    return;
                }
                JSONObject data = new JSONObject();
                try {
                    data.put(Constants.USER_ID, mUserId);
                    data.put(Constants.MESSAGE, message);
                    data.put("to_user_id", mOtherUserId);
                    (new SendNewMessageRequest(MatchChatActivity.this)).send(data);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                mEditTextMessage.setText("");
            }
        });
        showConversation();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onResume() {
        super.onResume();
        mIsAlive = true;
        mListenMessagesThread.setDaemon(true);
        mListenMessagesThread.start();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Getter for the mOtherUserId attribute
     * @return the user id of the other user
     */
    public String getOtherUserId() {
        return mOtherUserId;
    }

    /**
     * Setter for the mOtherUserId attribute
     * @param userId of the other user
     */
    public void setOtherUserId(String userId) {
        mOtherUserId = userId;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * The user sends a message
     *
     * @param message the message to be sent
     */
    public void sendMessage(String message) {
        ChatMessage chatMessage = new ChatMessage(message, true, false);
        mAdapter.add(chatMessage);
        mAdapter.notifyDataSetChanged();
        mListView.setSelection(mAdapter.getCount() - 1);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * The other user sends a message
     *
     * @param message the message to be sent
     */
    public void mimicOtherMessage(String message) {
        ChatMessage chatMessage = new ChatMessage(message, false, false);
        mAdapter.add(chatMessage);
        mAdapter.notifyDataSetChanged();
        mListView.setSelection(mAdapter.getCount() - 1);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Send a message from both of the users
     */
    private void sendMessage() {
        ChatMessage chatMessage = new ChatMessage(null, true, true);
        mAdapter.add(chatMessage);
        mimicOtherMessage();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Send a message from the other user
     */
    private void mimicOtherMessage() {
        ChatMessage chatMessage = new ChatMessage(null, false, true);
        mAdapter.add(chatMessage);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Show a conversation
     */
    private void showConversation() {
        while (!mConversation.noMoreMessages()) {
            String message = mConversation.getCurrentMessage();
            if (mConversation.currentMessageIsMine()) {
                sendMessage(message);
            } else {
                mimicOtherMessage(message);
            }
            mConversation.advanceToNextMessage();
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * When the user exits this activity, the isAlive flag becomes false
     */
    @Override
    protected void onStop() {
        mIsAlive = false;
        super.onStop();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Returns true if the user is in the match chat activity
     * @return true if the user is in the match chat activity
     */
    public boolean isAlive() {
        return mIsAlive;
    }
}
