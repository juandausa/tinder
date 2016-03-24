package com.tinder_app;

import android.os.Bundle;
import android.support.design.widget.CoordinatorLayout;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.daprlabs.cardstack.SwipeDeck;

import java.util.ArrayList;

import classes.SwipeDeckAdapter;

/**
 * Fragment that holds the SwipeDeck of the people to be liked or disliked by the user.
 */
public class PeopleListFragment extends Fragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        CoordinatorLayout layout = (CoordinatorLayout) inflater.inflate(R.layout.swipe_deck, container, false);
        //SwipeDeck cardStack = (SwipeDeck) layout.findViewById(R.id.swipe_deck);
        //CardView cardView = (CardView) inflater.inflate(R.layout.card, container);
        setUpLikeButton(layout);
        setUpDislikeButton(layout);

        SwipeDeck cardStack = (SwipeDeck) layout.findViewById(R.id.swipe_deck);
        //cardStack.setHardwareAccelerationEnabled(true);


        final ArrayList<String> testData = new ArrayList<>();
        testData.add("0");
        testData.add("1");
        testData.add("2");
        testData.add("3");
        testData.add("4");

        final SwipeDeckAdapter adapter = new SwipeDeckAdapter(testData, getActivity());
        cardStack.setAdapter(adapter);

        cardStack.setEventCallback(new SwipeDeck.SwipeEventCallback() {
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

}
