package com.tinder_app;

import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
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

import java.util.ArrayList;
import java.util.List;

import classes.CandidateData;
import classes.SessionManager;
import classes.SwipeDeckAdapter;
import requests.GetCandidatesRequest;

/**
 * Fragment that holds the SwipeDeck of the people to be liked or disliked by the user.
 */
public class PeopleListFragment extends Fragment {

    private JSONArray mCandidates;
    private List<String> cardList;
    private SwipeDeckAdapter mAdapter;
    private SwipeDeck mCardStack;
    private ProgressDialog progress;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        CoordinatorLayout layout = (CoordinatorLayout) inflater.inflate(R.layout.swipe_deck, container, false);
        //SwipeDeck cardStack = (SwipeDeck) layout.findViewById(R.id.swipe_deck);
        //CardView cardView = (CardView) inflater.inflate(R.layout.card, container);
        setUpLikeButton(layout);
        setUpDislikeButton(layout);
        loading();
        getCandidates();


        mCardStack = (SwipeDeck) layout.findViewById(R.id.swipe_deck);
        //cardStack.setHardwareAccelerationEnabled(true);


        cardList = new ArrayList<String>();
        /*testData.add("0");
        testData.add("1");
        testData.add("2");
        testData.add("3");
        testData.add("4");*/

        mAdapter = new SwipeDeckAdapter(cardList, getActivity());
        mCardStack.setAdapter(mAdapter);

        mCardStack.setEventCallback(new SwipeDeck.SwipeEventCallback() {
            @Override
            public void cardSwipedLeft(int position) {
                Log.i("MainActivity", "card was swiped left, position in adapter: " + position);
            }

            @Override
            public void cardSwipedRight(int position) {
                Log.i("MainActivity", "card was swiped right, position in adapter: " + position);
            }

            @Override
            public void cardsDepleted() {
                Log.i("MainActivity", "no more cards");
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

    private void loading() {
        progress = new ProgressDialog(getActivity());
        progress.setTitle("Loading");
        progress.setMessage("Wait while loading...");
        progress.show();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void getCandidates() {
        GetCandidatesRequest request = new GetCandidatesRequest(getActivity(),this);
        try {
            JSONObject json = new JSONObject();
            String userId = SessionManager.getUserId(getActivity());
            json.put("user_id", userId);
            request.send(json);
        } catch (JSONException e) {}

    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void setUpLikeButton(ViewGroup layout) {
        FloatingActionButton fab = (FloatingActionButton) layout.findViewById(R.id.main_like_fab);
        if (fab == null) {
            return;
        }
        fab.setBackgroundTintList(getResources().getColorStateList(R.color.light_green));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Here's a Snackbar", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void setUpDislikeButton(ViewGroup layout) {
        FloatingActionButton fab = (FloatingActionButton) layout.findViewById(R.id.main_dislike_fab);
        if (fab == null) {
            return;
        }
        fab.setBackgroundTintList(getResources().getColorStateList(android.R.color.holo_red_light));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Here's a Snackbar", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void setCandidates(final JSONArray candidates) {

        mCandidates = candidates;

        AsyncTask loadCards = new AsyncTask() {
            List<CandidateData> cards = new ArrayList<>();

            @Override
            protected Object doInBackground(Object[] params) {
                int length = candidates.length();
                for(int i = 0; i < length; i++) {
                    try {
                        cards.add(new CandidateData(candidates.getJSONObject(i)));
                    } catch (JSONException e) {}
                }
                return null;
            }

            @Override
            protected void onPostExecute(Object param) {
                // To dismiss the dialog
                mAdapter.update(cards);
                mCardStack.invalidate();
                progress.dismiss();
            }
        };
        loadCards.execute();
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void timeoutOnCandidatesRequest() {
        progress.dismiss();
        unableToConnectDialog();
    }

    private void unableToConnectDialog() {
        new AlertDialog.Builder(getActivity())
                .setTitle("Error de conexión")
                .setMessage("Debido a algun problema de la red, los datos los datos " +
                        "estan tardando demasiado en llegar. ")
                .setCancelable(false)
                .setPositiveButton("ok", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // Whatever...
                    }
                }).create().show();
    }
}
