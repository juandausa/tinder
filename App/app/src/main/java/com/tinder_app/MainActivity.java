package com.tinder_app;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Paint;
import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.GravityCompat;
import android.support.v4.view.ViewPager;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

import com.facebook.login.LoginManager;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

import classes.Constants;
import classes.CustomViewPager;
import classes.MyUserProfileData;
import classes.SessionManager;
import requests.GetProfileRequest;
import requests.JSONRequest;
import requests.SendDislikeRequest;
import requests.SendLikeRequest;

/**
 * Main Activity of the App. Main screen, where the user will be the mayor part of the time.
 * This Activity has two sections. The first has the people to be liked or dis-liked. The second,
 * has the matches and links to the conversations with them.
 */
public class MainActivity extends AppCompatActivity {

    private DrawerLayout mDrawerLayout;
    private MyUserProfileData mUserData;
    private String mUserId;
    private PeopleListFragment mPeopleFragment;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set up the mainAcivity
     *
     * @param savedInstanceState the saved state of the acivity
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        SessionManager.loadServerIp(MainActivity.this);

        //userId = getIntent().getStringExtra(Constants.USER_ID);
        getProfile();

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        final ActionBar ab = getSupportActionBar();
        if (ab != null) {
            ab.setHomeAsUpIndicator(R.drawable.ic_menu);
            ab.setDisplayHomeAsUpEnabled(true);
        }

        mDrawerLayout = (DrawerLayout) findViewById(R.id.drawer_layout);
        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        if (navigationView != null) {
            setupDrawerContent(navigationView);
        }

        CustomViewPager viewPager = (CustomViewPager) findViewById(R.id.viewpager);
        if (viewPager != null) {
            setupViewPager(viewPager);
        }

        TabLayout tabLayout = (TabLayout) findViewById(R.id.tabs);
        setTabLayout(tabLayout, viewPager);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set up the Tab Layout, sets the content of each tab
     *
     * @param tabLayout the layout to be setted
     * @param viewPager the view pager containig the fragments that will be en each tab
     */
    private void setTabLayout(TabLayout tabLayout, CustomViewPager viewPager) {
        if (tabLayout == null) {
            return;
        }
        tabLayout.setupWithViewPager(viewPager);
        TabLayout.Tab tab1 = tabLayout.getTabAt(0);
        TabLayout.Tab tab2 = tabLayout.getTabAt(1);
        if (tab1 != null) {
            tab1.setIcon(R.drawable.ic_favorite_white_24dp);
        }
        if (tab2 != null) {
            tab2.setIcon(R.drawable.ic_forum_white_24dp);
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Executes a determined action on item's selection on the menu.
     *
     * @param item item selected
     * @return true if action is performed, false otherwise.
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                mDrawerLayout.openDrawer(GravityCompat.START);
                return true;
            default:
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the content of the ViewPager.
     *
     * @param viewPager the view pager that will have the fragments to be shown in each tab
     */
    private void setupViewPager(ViewPager viewPager) {
        Adapter adapter = new Adapter(getSupportFragmentManager());
        mPeopleFragment = new PeopleListFragment();
        adapter.addFragment(mPeopleFragment);
        adapter.addFragment(new MatchesFragment());
        viewPager.setAdapter(adapter);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the content of the NavigationDrawer View
     *
     * @param navigationView the view that contains the sliding menu that will hold options
     */
    private void setupDrawerContent(NavigationView navigationView) {
        View header = navigationView.getHeaderView(0);
        TextView seeProfile = (TextView) header.findViewById(R.id.see_profile);
        seeProfile.setPaintFlags(seeProfile.getPaintFlags() | Paint.UNDERLINE_TEXT_FLAG);
        header.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), MyUserProfileActivity.class);
                intent.putExtra("user", mUserData.toString());
                startActivity(intent);
            }
        });

        navigationView.setNavigationItemSelectedListener(
                new NavigationView.OnNavigationItemSelectedListener() {
                    @Override
                    public boolean onNavigationItemSelected(MenuItem menuItem) {
                        Intent intent = null;
                        switch (menuItem.getItemId()) {
                            case R.id.nav_settings:
                                intent = new Intent(getApplicationContext(), SettingsActivity.class);
                                break;
                            case R.id.nav_exit:
                                LoginManager.getInstance().logOut();
                                SessionManager.logout(MainActivity.this);
                                finish();
                                return true;
                            default:
                                mDrawerLayout.closeDrawers();
                                return true;
                        }
                        // menuItem.setChecked(true);
                        mDrawerLayout.closeDrawers();
                        if (intent != null) {
                            startActivity(intent);
                        }
                        return true;
                    }
                });
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    private void getProfile() {
        GetProfileRequest request = new GetProfileRequest(this);
        try {
            JSONObject json = new JSONObject();
            mUserId = SessionManager.getUserId(this);
            json.put(Constants.USER_ID, mUserId);
            request.send(json);
        } catch (JSONException e) {
            Log.e(getString(R.string.JSON_ERROR), e.toString());
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Set the profile data of the user
     *
     * @param user a JSONObject with the profile data of the user
     */
    public void setProfile(final JSONObject user) {
        mUserData = new MyUserProfileData(user);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    public void sendLikeRequest(String candidateId) {
        SendLikeRequest request = new SendLikeRequest(this);
        sendDecisionOverCandidate(candidateId, request);
    }

    public void sendDislikeRequest(String candidateId) {
        SendDislikeRequest request = new SendDislikeRequest(this);
        sendDecisionOverCandidate(candidateId, request);
    }


    private void sendDecisionOverCandidate(String candidateId, JSONRequest request) {

        JSONObject data = new JSONObject();
        try {
            data.put("to_user_id", candidateId);
            data.put(Constants.USER_ID, mUserId);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        request.send(data);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        if (requestCode == 1) {
            if (resultCode == Activity.RESULT_OK) {
                String result = data.getStringExtra(OtherUsersProfileActivity.DECISION);
                mPeopleFragment.sendDecisionFromResult(result);
            }
            if (resultCode == Activity.RESULT_CANCELED) {
                //Write your code if there's no result
            }
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Adapter for the ViewPager.
     */
    static class Adapter extends FragmentPagerAdapter {
        private final List<Fragment> mFragments = new ArrayList<>();
        //private final List<String> mFragmentTitles = new ArrayList<>();

        /**
         * Constructor of the class Adapter.
         *
         * @param fm fragment manager.
         */
        public Adapter(FragmentManager fm) {
            super(fm);
        }

        /**
         * Adds a fragment to the Adapter.
         *
         * @param fragment fragment to be added to the Adapter.
         */
        public void addFragment(Fragment fragment) {
            mFragments.add(fragment);
            //mFragmentTitles.add(title);
        }

        /**
         * Returns the item at the position "position"
         *
         * @param position of the element to the returned
         * @return the item at the position "position"
         */
        @Override
        public Fragment getItem(int position) {
            return mFragments.get(position);
        }

        /**
         * Returns the count of items in the adapter
         *
         * @return the count of items in the adapter
         */
        @Override
        public int getCount() {
            return mFragments.size();
        }

        /**
         * Returns the page title to show on the Tab that is related with the fragment on the
         * Pager Adapter
         *
         * @param position of the item in the adapter
         * @return the title of the item
         */
        @Override
        public CharSequence getPageTitle(int position) {
            //return mFragmentTitles.get(position);
            return "";
        }
    }
}
