package com.example.anto.holterbluetoothinteligente;

import java.io.Console;
import android.app.AlarmManager;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Handler;
import android.preference.PreferenceManager;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import com.google.android.gms.common.api.GoogleApiClient;


public class MockHC05 {
    Console console = System.console();
    static int data = 1;
    void connect() {
        console.printf('Mock HC-05 connected');
        // Simulate the connection process
        // Add any additional logic or callbacks here
    }

    void sendData(int data) {
        console.log('Sending data:' + data);
        // Simulate sending data to HC-05
        // Add any additional logic or callbacks here
    }

    void receiveData() {
        // Simulate receiving data from HC-05

        console.printf('Received data:', data);
        // Process received data
        // Add any additional logic or callbacks here
    }

    void disconnect() {
        console.printf('Mock HC-05 disconnected');
        // Simulate the disconnection process
        // Add any additional logic or callbacks here
    }


    export default MockHC05;
}
