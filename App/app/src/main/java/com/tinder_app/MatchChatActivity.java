package com.tinder_app;

import android.content.Intent;
import android.graphics.CornerPathEffect;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;

import classes.ChatMessage;
import classes.ChatMessageAdapter;
import classes.Constants;
import classes.Conversation;
import me.himanshusoni.chatmessageview.ChatMessageView;

public class MatchChatActivity extends AppCompatActivity {

    private Conversation mConversation;
    private String mAlias;
    private ListView mListView;
    private ChatMessageAdapter mAdapter;
    private Button mButtonSend;
    private EditText mEditTextMessage;

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


    private void sendMessage(String message) {
        ChatMessage chatMessage = new ChatMessage(message, true, false);
        mAdapter.add(chatMessage);
        mAdapter.notifyDataSetChanged();
    }

    private void mimicOtherMessage(String message) {
        ChatMessage chatMessage = new ChatMessage(message, false, false);
        mAdapter.add(chatMessage);
        mAdapter.notifyDataSetChanged();
    }

    private void sendMessage() {
        ChatMessage chatMessage = new ChatMessage(null, true, true);
        mAdapter.add(chatMessage);
        mimicOtherMessage();
    }

    private void mimicOtherMessage() {
        ChatMessage chatMessage = new ChatMessage(null, false, true);
        mAdapter.add(chatMessage);
    }



    private void showConversation() {
        //LinearLayout layout = (LinearLayout) findViewById(R.id.chat_layout);
        int index = 0;
        boolean messageIsMine = true;
        String aux = "this is a test";
        sendMessage(aux);
        mimicOtherMessage("ok, no problem");
    }

}
