package com.tinder_app;

import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.support.annotation.Nullable;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import classes.Constants;
import classes.MatchData;
import classes.MatchesViewAdapter;
import classes.SessionManager;
import requests.GetMatchesRequest;

/**
 * Fragment that holds the Matches for the user in form of list.
 */
public class MatchesFragment extends Fragment {

    private List<MatchData> mMatches;
    private MatchesViewAdapter mAdapter;
    private RecyclerView mView;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstState) {
        mMatches = new ArrayList<>();
        getMatches();
        RecyclerView rv = (RecyclerView) inflater.inflate(
                R.layout.fragment_people_list, container, false);
        setupRecyclerView(rv);
        return rv;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set up content of the recycler view (list) of the fragment.
     * @param recyclerView view that show elements in form of list.
     */
    private void setupRecyclerView(RecyclerView recyclerView) {
        recyclerView.setLayoutManager(new LinearLayoutManager(recyclerView.getContext()));
        mAdapter = new MatchesViewAdapter(getActivity(), mMatches);
        recyclerView.setAdapter(mAdapter);
        mView = recyclerView;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Function that gets a random list of the elements available in the array received as param.
     * @param array elements from wich 'amount' will be chosen randomly.
     * @param amount amount of elements that will have the list returned.
     * @return list of the elements chosen randomly.
     */
    private List<String> getRandomSublist(String[] array, int amount) {
        ArrayList<String> list = new ArrayList<>(amount);
        Random random = new Random();
        while (list.size() < amount) {
            list.add(array[random.nextInt(array.length)]);
        }
        return list;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void getMatches() {
        GetMatchesRequest request = new GetMatchesRequest(getActivity(), this);
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
     * Receives the candidates and place them in an array, and on the stack of cards
     * @param matches of match for the user
     */
    public void setMatches(final JSONArray matches) {

        AsyncTask loadCards = new AsyncTask() {

            @Override
            protected Object doInBackground(Object[] params) {
                int length = matches.length();
                for (int i = 0; i < length; i++) {
                    try {
                        mMatches.add(new MatchData(matches.getJSONObject(i)));
                    } catch (JSONException e) {
                        Log.e(getString(R.string.JSON_ERROR), e.toString());
                    }
                }
                return null;
            }

            @Override
            protected void onPostExecute(Object param) {
                // To dismiss the dialog
                mAdapter.update(mMatches);
                mView.invalidate();
            }
        };
        loadCards.execute();
    }
}
