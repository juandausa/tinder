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
import android.widget.Toast;

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
    private static int SWIPE_DURATION = 4000;

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        CoordinatorLayout layout = (CoordinatorLayout) inflater.inflate(R.layout.swipe_deck, container, false);
        setUpLikeButton(layout);
        setUpDislikeButton(layout);
        loading();
        getCandidates();

        mCardStack = (SwipeDeck) layout.findViewById(R.id.swipe_deck);
        //cardStack.setHardwareAccelerationEnabled(true);
        cardList = new ArrayList<>();
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
        progress.setTitle("Buscando");
        progress.setMessage("Buscando gente cercana...");
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
        fab.setBackgroundTintList(getResources().getColorStateList(android.R.color.white));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mCardStack.swipeTopCardRight(SWIPE_DURATION);
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
        fab.setBackgroundTintList(getResources().getColorStateList(android.R.color.white));
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mCardStack.swipeTopCardLeft(SWIPE_DURATION);
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

    /**********************************************************************************************/
    /**********************************************************************************************/

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
