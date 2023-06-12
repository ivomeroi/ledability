package com.example.anto.holterbluetoothinteligente;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothHeadset;
import android.bluetooth.BluetoothSocket;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.Gravity;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.app.ActivityCompat;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.fragment.app.Fragment;

import com.google.android.material.navigation.NavigationView;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {
    int main_itemnum;
    private long mMillisUntilFinish;
    CountDownTimer countdowntimer;
    CountDownTimer assist;
    SharedPreferences sharedPreferences;
    SharedPreferences.Editor editor;
    BluetoothAdapter btadapter = BluetoothAdapter.getDefaultAdapter();
    //private static final String BLUETOOTH_ADDRESS = "00:18:E4:34:C5:45"; // Replace with your HC-05's Bluetooth address
    //private static final String BLUETOOTH_URL = "btspp://" + BLUETOOTH_ADDRESS + ":1;authenticate=false;encrypt=false;master=false";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        editor = sharedPreferences.edit();

        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);


        selector fragment = new selector();
        getSupportFragmentManager().beginTransaction().add(R.id.fragment_container, fragment).commit();
        getSupportActionBar().setTitle(getString(R.string.selector));

    }


    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
            switch (main_itemnum) {
                case 1:
                    MainActivity.this.moveTaskToBack(true);
                case 2:
                    getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new selector()).commit();

                    getSupportActionBar().setTitle(getString(R.string.selector));

                    navigationView.setCheckedItem(R.id.selector);
                case 3:
                    MainActivity.this.moveTaskToBack(true);
            }
        }
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        int itemnum = item.getOrder();

        openfragment(itemnum);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    public void openfragment(int itemnum) {
        Fragment fragment = null;
        String title = "";

        switch (itemnum) {
            case 1:
                fragment = new selector();
                main_itemnum = 1;
                title = "Selector";
                break;
            case 2:
                fragment = new programa();
                title = "Programa";
                main_itemnum = 2;
                break;
            case 3:
                fragment = new ajustes();
                title = "Ajustes";
                main_itemnum = 3;
                break;
        }

        getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, fragment).commit();
        getSupportActionBar().setTitle(title);
    }

    @Override
    protected void onActivityResult(int requestcode, int resultcode, Intent data) {
        super.onActivityResult(requestcode, resultcode, data);

        if (requestcode == 1) {
            if (resultcode == RESULT_OK) {
                Toast.makeText(this, "Bluetooth habilitado", Toast.LENGTH_SHORT).show();
                //startService(new Intent(this, analisisecg.class));
            }
        }
    }
}