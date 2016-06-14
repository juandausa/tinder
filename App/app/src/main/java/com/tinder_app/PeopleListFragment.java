package com.tinder_app;

import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.Fragment;
import android.support.v7.app.AlertDialog;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.daprlabs.cardstack.SwipeDeck;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Callable;

import classes.CandidateData;
import classes.Constants;
import classes.SessionManager;
import classes.SwipeDeckAdapter;
import requests.GetCandidatesRequest;
import requests.JSONRequest;
import requests.SendDislikeRequest;
import requests.SendLikeRequest;

/**
 * Fragment that holds the SwipeDeck of the people to be liked or disliked by the user.
 */
public class PeopleListFragment extends Fragment {

    private static final int SWIPE_DURATION = 4000;
    private static final String SEND_LIKE = "LIKE";
    private static final String SEND_DISLIKE = "DISLIKE";
    private JSONArray mCandidates;
    private List<CandidateData> mCardList;
    private SwipeDeckAdapter mAdapter;
    private SwipeDeck mCardStack;
    private ProgressDialog mProgress;
    private Map<String, Method> mDecisionMethods;
    MainActivity mActivity;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets up the swipe deck, and the buttons with their logic in the PeopleListFragment
     * @param inflater the inflater for inflating the layout
     * @param container the parent view
     * @param savedInstanceState the bundle for saving the state of the fragment
     * @return the view with the data setted
     */
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        CoordinatorLayout layout = (CoordinatorLayout) inflater.inflate(R.layout.swipe_deck, container, false);
        mActivity = (MainActivity) getActivity();
        setUpLikeButton(layout);
        setUpDislikeButton(layout);
        loading();
        getCandidates();
        buildMethodsMap();

        mCardStack = (SwipeDeck) layout.findViewById(R.id.swipe_deck);
        //cardStack.setHardwareAccelerationEnabled(true);
        mCardList = new ArrayList<>();
        mAdapter = new SwipeDeckAdapter(mCardList, getActivity());
        mCardStack.setAdapter(mAdapter);

        mCardStack.setEventCallback(new SwipeDeck.SwipeEventCallback() {
            @Override
            public void cardSwipedLeft(int position) {
                //Log.i("MainActivity", "card was swiped left, position in adapter: " + position);
                sendDecisionOverCandidate(SEND_DISLIKE);
            }

            @Override
            public void cardSwipedRight(int position) {
                //Log.i("MainActivity", "card was swiped right, position in adapter: " + position);
                sendDecisionOverCandidate(SEND_LIKE);
            }

            @Override
            public void cardsDepleted() {
                //Log.i("MainActivity", "no more cards");
            }

            @Override
            public void cardActionDown() {
            }

            @Override
            public void cardActionUp() {
            }
        });
        return layout;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Generates a progress dialog while the candidates cards are loading
     */
    private void loading() {
        mProgress = new ProgressDialog(getActivity());
        mProgress.setTitle(R.string.searching);
        mProgress.setMessage(getString(R.string.searching_for_close_people));
        mProgress.show();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sends a request asking for candidates of match for the user
     */
    private void getCandidates() {
        GetCandidatesRequest request = new GetCandidatesRequest(getActivity(), this);
        try {
            JSONObject json = new JSONObject();
            String userId = SessionManager.getUserId(getActivity());
            json.put(Constants.USER_ID, userId);
            request.send(json);
        } catch (JSONException e) {
            Log.e(getString(R.string.JSON_ERROR), e.toString());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets up the look and logic of the like button
     * @param layout the layout where the button is placed
     */
    private void setUpLikeButton(ViewGroup layout) {
        FloatingActionButton fab = (FloatingActionButton) layout.findViewById(R.id.main_like_fab);
        if (fab == null) {
            return;
        }
        fab.setBackgroundTintList(getResources().getColorStateList(android.R.color.white));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sendLikeDecision();
            }
        });
    }

    private void sendLikeDecision() {
        mCardStack.swipeTopCardRight(SWIPE_DURATION);
        sendDecisionOverCandidate(SEND_LIKE);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets up the look and logic of the dislike button
     * @param layout the layout where the button is placed
     */
    private void setUpDislikeButton(ViewGroup layout) {
        FloatingActionButton fab = (FloatingActionButton) layout.findViewById(R.id.main_dislike_fab);
        if (fab == null) {
            return;
        }
        fab.setBackgroundTintList(getResources().getColorStateList(android.R.color.white));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sendDislikeDecision();
            }
        });
    }

    private void sendDislikeDecision() {
        mCardStack.swipeTopCardLeft(SWIPE_DURATION);
        sendDecisionOverCandidate(SEND_DISLIKE);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void buildMethodsMap() {
        mDecisionMethods = new HashMap<>();
        try {
            mDecisionMethods.put(SEND_LIKE, mActivity.getClass().getMethod("sendLikeRequest", String.class));
            mDecisionMethods.put(SEND_DISLIKE, mActivity.getClass().getMethod("sendDislikeRequest", String.class));
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void sendDecisionOverCandidate(String decision) {
        CandidateData candidate = (CandidateData) mAdapter.getItem(0);
        try {
            (mDecisionMethods.get(decision)).invoke(mActivity, candidate.getUserId());
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void sendDecisionFromResult(String result) {
        if (result.equals(SEND_LIKE)) {
            sendLikeDecision();
        } else if (result.equals(SEND_DISLIKE)) {
            sendLikeDecision();
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Receives the candidates and place them in an array, and on the stack of cards
     * @param candidates of match for the user
     */
    public void setCandidates(final JSONArray candidates) {

        mCandidates = candidates;

        AsyncTask loadCards = new AsyncTask() {
            private List<CandidateData> mCards = new ArrayList<>();

            @Override
            protected Object doInBackground(Object[] params) {
                int length = candidates.length();
                for (int i = 0; i < length; i++) {
                    try {
                        mCards.add(new CandidateData(candidates.getJSONObject(i)));
                    } catch (JSONException e) {
                        Log.e(getString(R.string.JSON_ERROR), e.toString());
                    }
                }
                return null;
            }

            @Override
            protected void onPostExecute(Object param) {
                // To dismiss the dialog
                mAdapter.update(mCards);
                mCardStack.invalidate();
                mProgress.dismiss();
            }
        };
        loadCards.execute();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * When there is a timeout for the getCandidates request, dismiss the loading dialog and
     * show a dialog with the message of unable to connect
     */
    public void timeoutOnCandidatesRequest() {
        mProgress.dismiss();
        unableToConnectDialog();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Creates a dialog that shows the message of unable to connect
     */
    private void unableToConnectDialog() {
        new AlertDialog.Builder(getActivity())
                .setTitle(R.string.connection_error)
                .setMessage(getString(R.string.connection_error_message))
                .setCancelable(false)
                .setPositiveButton(R.string.OK, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // Whatever...
                    }
                }).create().show();
    }
}