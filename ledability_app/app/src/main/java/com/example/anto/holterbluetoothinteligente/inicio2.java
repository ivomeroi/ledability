package com.example.anto.holterbluetoothinteligente;

import android.Manifest;
import android.app.AlarmManager;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
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
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.common.api.GoogleApiClient;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.charset.Charset;
import java.util.UUID;

public class inicio2 extends AppCompatActivity {
    BluetoothAdapter btadapter = BluetoothAdapter.getDefaultAdapter();
    SharedPreferences.Editor editor;
    Handler handler = new Handler();
    static BluetoothSocket btsocket;
    static InputStream instream;
    static boolean servicioactivo = false;
    SharedPreferences sharedPreferences;
    public static BluetoothConnection bluetoothConnection;
    private static TextView receivedDataTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        bluetoothConnection = new BluetoothConnection(getApplicationContext());

        editor = PreferenceManager.getDefaultSharedPreferences(this).edit();
        setContentView(R.layout.activity_inicio2);
    }

    public void conectar(View view) {
        String BLUETOOTH_ADDRESS = "00:18:E4:34:C5:45";
        BluetoothDevice device = btadapter.getRemoteDevice(BLUETOOTH_ADDRESS);
        bluetoothConnection.connectToDevice(device);
    }

    public static void updateTextView(String text) {
        if (receivedDataTextView != null) {
            receivedDataTextView.post(() -> receivedDataTextView.setText(text));
        }
    }

    public void onButtonClick(View view) {
        // Call the sendDataToPairedDevice() function with the desired message and context
        String message = "f";
        inicio2.sendDataToPairedDevice(message, getApplicationContext());
    }

    public static void sendDataToPairedDevice(String message, Context context) {
        byte[] toSend = message.getBytes(Charset.defaultCharset());
        try {
            UUID applicationUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
            if (ActivityCompat.checkSelfPermission(context, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                // TODO: Consider calling
                //    ActivityCompat#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for ActivityCompat#requestPermissions for more details.
                return;
            }

            OutputStream mmOutStream = bluetoothConnection.btSocket.getOutputStream();
            mmOutStream.write(toSend);
            // Your Data is sent to  BT connected paired device ENJOY.
        } catch (Exception e) {
            Toast.makeText(context, "Fallooo en la comunicación", Toast.LENGTH_SHORT).show();
        }
    }

    public class BluetoothConnection {
        private Context context;
        private BluetoothSocket btSocket;

        public BluetoothConnection(Context context) {
            this.context = context;
        }

        public BluetoothSocket getBtSocket() {
            return btSocket;
        }

        public void connectToDevice(BluetoothDevice device) {
            UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

            try {
                if (ActivityCompat.checkSelfPermission(context, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                    // TODO: Request Bluetooth permission if needed
                    return;
                }
                if (btSocket == null) {
                    btSocket = device.createRfcommSocketToServiceRecord(uuid);
                    Toast.makeText(getApplicationContext(), String.valueOf(btSocket), Toast.LENGTH_SHORT).show();

                }
            } catch (IOException e) {
                //btSocket = null;
                return;
            }

            try {
                if (ActivityCompat.checkSelfPermission(context, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                    // TODO: Request Bluetooth permission if needed
                    return;
                }
                btSocket.connect();
            } catch (IOException connectException) {
                try {
                    handler.post(() -> Toast.makeText(context, "Falló la conexión", Toast.LENGTH_SHORT).show());
                    btSocket.close();
                } catch (IOException closeException) {
                }
                return;
            }

            handler.post(() -> {
                Toast.makeText(getApplicationContext(), "Dispositivo conectado", Toast.LENGTH_SHORT).show();

                // Perform any other actions after successful connection
            });
            receivedDataTextView = findViewById(R.id.receivedDataTextView);
            Intent intent = new Intent(getApplicationContext(), analisisecg.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
            startService(intent);
            setContentView(R.layout.fragment_selector);

        }
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        overridePendingTransition(0, 0);
    }

    @Override
    protected void onActivityResult(int requestcode, int resultcode, Intent data) {
        super.onActivityResult(requestcode, resultcode, data);

        if (requestcode == 1) {
            if (resultcode == RESULT_OK) {
                Toast.makeText(this, "Bluetooth habilitado", Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(this, analisisecg.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
                startActivity(intent);
            } else {
            }
        }
    }
}