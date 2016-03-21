package com.tinder_app;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.support.annotation.Nullable;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import classes.SimpleStringRecyclerViewAdapter;

/**
 * Fragment that holds the Matches for the user in form of list.
 */
public class MatchesFragment extends Fragment {

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstState) {
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
        recyclerView.setAdapter(new SimpleStringRecyclerViewAdapter(getActivity(),
                getRandomSublist(Cheeses.CHEESE_STRINGS, 30)));
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
}
