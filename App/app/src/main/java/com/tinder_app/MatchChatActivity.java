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

import java.util.ArrayList;

import classes.ChatMessage;
import classes.ChatMessageAdapter;
import classes.Constants;
import classes.Conversation;

/**
 * Chat Activity of the user with other
 */
public class MatchChatActivity extends AppCompatActivity {

    private Conversation mConversation;
    private String mAlias;
    private ListView mListView;
    private ChatMessageAdapter mAdapter;
    private Button mButtonSend;
    private EditText mEditTextMessage;

    /**
     * Sets the activity data and views
     * @param savedInstanceState the saved state of the activity to be restored
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_match_chat);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        mListView = (ListView) findViewById(R.id.listView);
        mButtonSend = (Button) findViewById(R.id.btn_send);
        mEditTextMessage = (EditText) findViewById(R.id.et_message);


        Intent intent = getIntent();
        mAlias = intent.getStringExtra(Constants.ALIAS);
        mConversation = new Conversation(intent.getStringExtra(Constants.CONVERSATION));
        toolbar.setTitle(mAlias);
        toolbar.bringToFront();

        mAdapter = new ChatMessageAdapter(this, new ArrayList<ChatMessage>());
        mListView.setAdapter(mAdapter);

        mButtonSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = mEditTextMessage.getText().toString();
                if (TextUtils.isEmpty(message)) {
                    return;
                }
                sendMessage(message);
                mEditTextMessage.setText("");
            }
        });
        showConversation();
    }


    /**
     * The user sends a message
     * @param message the message to be sent
     */
    private void sendMessage(String message) {
        ChatMessage chatMessage = new ChatMessage(message, true, false);
        mAdapter.add(chatMessage);
        mAdapter.notifyDataSetChanged();
    }

    /**
     * The other user sends a message
     * @param message the message to be sent
     */
    private void mimicOtherMessage(String message) {
        ChatMessage chatMessage = new ChatMessage(message, false, false);
        mAdapter.add(chatMessage);
        mAdapter.notifyDataSetChanged();
    }

    /**
     * Send a message from both of the users
     */
    private void sendMessage() {
        ChatMessage chatMessage = new ChatMessage(null, true, true);
        mAdapter.add(chatMessage);
        mimicOtherMessage();
    }

    /**
     * Send a message from the other user
     */
    private void mimicOtherMessage() {
        ChatMessage chatMessage = new ChatMessage(null, false, true);
        mAdapter.add(chatMessage);
    }


    /**
     * Show a conversation
     */
    private void showConversation() {
        //LinearLayout layout = (LinearLayout) findViewById(R.id.chat_layout);
        int index = 0;
        boolean messageIsMine = true;
        String aux = "this is a test";
        sendMessage(aux);
        mimicOtherMessage("ok, no problem");
    }

}
