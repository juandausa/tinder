package com.tinder_app;

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
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

import com.facebook.login.LoginManager;

import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

import classes.CustomViewPager;
import requests.GetCandidatesRequest;

/**
 * Main Activity of the App. Main screen, where the user will be the mayor part of the time.
 * This Activity has two sections. The first has the people to be liked or dis-liked. The second,
 * has the matches and links to the conversations with them.
 */
public class MainActivity extends AppCompatActivity {

    private DrawerLayout mDrawerLayout;
    private JSONObject mCandidates;
    private JSONObject mUserData;
    public String userId;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        userId = getIntent().getStringExtra("user_id");

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        final ActionBar ab = getSupportActionBar();
        ab.setHomeAsUpIndicator(R.drawable.ic_menu);
        ab.setDisplayHomeAsUpEnabled(true);

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
        tabLayout.setupWithViewPager(viewPager);
        tabLayout.getTabAt(0).setIcon(R.drawable.ic_favorite_white_24dp);
        tabLayout.getTabAt(1).setIcon(R.drawable.ic_forum_white_24dp);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Executes a determined action on item's selection on the menu.
     * @param item item selected
     * @return true if action is performed, false otherwise.
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Intent intent = null;
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
     * @param viewPager
     */
    private void setupViewPager(ViewPager viewPager) {
        Adapter adapter = new Adapter(getSupportFragmentManager());
        adapter.addFragment(new PeopleListFragment(), "Personas");
        adapter.addFragment(new MatchesFragment(), "Mensajes");
        viewPager.setAdapter(adapter);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Sets the content of the NavigationDrawer View
     * @param navigationView
     */
    private void setupDrawerContent(NavigationView navigationView) {
        View header = navigationView.getHeaderView(0);
        TextView seeProfile = (TextView) header.findViewById(R.id.see_profile);
        seeProfile.setPaintFlags(seeProfile.getPaintFlags() | Paint.UNDERLINE_TEXT_FLAG);
        header.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), MyUserProfileActivity.class);
                startActivity(intent);
            }
        });

        navigationView.setNavigationItemSelectedListener(
                new NavigationView.OnNavigationItemSelectedListener() {
                    @Override
                    public boolean onNavigationItemSelected(MenuItem menuItem) {
                        Intent intent = null;
                        switch (menuItem.getItemId()) {
                            case R.id.nav_discover_settings:
                                break;
                            case R.id.nav_settings:
                                intent = new Intent(getApplicationContext(), SettingsActivity.class);
                                break;
                            case R.id.nav_exit:
                                LoginManager.getInstance().logOut();
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

    /**
     * Adapter for the ViewPager.
     */
    static class Adapter extends FragmentPagerAdapter {
        private final List<Fragment> mFragments = new ArrayList<>();
        private final List<String> mFragmentTitles = new ArrayList<>();

        /**
         * Constructor of the class Adapter.
         * @param fm fragment manager.
         */
        public Adapter(FragmentManager fm) {
            super(fm);
        }

        /**
         * Adds a fragment to the Adapter.
         * @param fragment fragment to be added to the Adapter.
         * @param title Title to be shown of the section that represents the Fragment.
         */
        public void addFragment(Fragment fragment, String title) {
            mFragments.add(fragment);
            //mFragmentTitles.add(title);
        }

        @Override
        public Fragment getItem(int position) {
            return mFragments.get(position);
        }

        @Override
        public int getCount() {
            return mFragments.size();
        }

        @Override
        public CharSequence getPageTitle(int position) {
            //return mFragmentTitles.get(position);
            return "";
        }
    }
}
