package com.example.anto.holterbluetoothinteligente;

import android.Manifest;
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

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.UUID;

public class inicio2 extends AppCompatActivity {
    BluetoothAdapter btadapter = BluetoothAdapter.getDefaultAdapter();
    SharedPreferences.Editor editor;
    Handler handler = new Handler();
    static BluetoothSocket btsocket;
    static InputStream instream;
    static boolean servicioactivo = false;
    SharedPreferences sharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        editor = PreferenceManager.getDefaultSharedPreferences(this).edit();
        setContentView(R.layout.activity_inicio2);
    }


    public class conectar implements Runnable {
        public conectar(BluetoothDevice device) {
            UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

            try {
                if (ActivityCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                    // TODO: Consider calling
                    //    ActivityCompat#requestPermissions
                    // here to request the missing permissions, and then overriding
                    //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                    //                                          int[] grantResults)
                    // to handle the case where the user grants the permission. See the documentation
                    // for ActivityCompat#requestPermissions for more details.
                    return;
                }
                if (btsocket == null)
                    btsocket = device.createRfcommSocketToServiceRecord(uuid);
            } catch (IOException e) {
                btsocket = null;

            }
        }


        public void run() {
            try {
                if (ActivityCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                    // TODO: Consider calling
                    //    ActivityCompat#requestPermissions
                    // here to request the missing permissions, and then overriding
                    //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                    //                                          int[] grantResults)
                    // to handle the case where the user grants the permission. See the documentation
                    // for ActivityCompat#requestPermissions for more details.
                    return;
                }
                btsocket.connect();
            } catch (IOException connectException) {
//                try {
//                    handler.post(() -> Toast.makeText(getApplicationContext(), "Falló la conexión", Toast.LENGTH_SHORT).show());
//
//                    btsocket.close();
//                } catch (IOException closeException) {
//                }

                return;
            }

            handler.post(() -> {
                Toast.makeText(getApplicationContext(), "Dispositivo conectado", Toast.LENGTH_SHORT).show();

                if (sharedPreferences.getBoolean("mostrarinicio", true)) {
                    Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                    intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
                    startActivity(intent);
                    setContentView(R.layout.activity_main);
                }
            });
            String BLUETOOTH_ADDRESS = "00:18:E4:34:C5:45";
            BluetoothDevice device = btadapter.getRemoteDevice(BLUETOOTH_ADDRESS);
            Method m = null;
            try {
                m = device.getClass().getMethod("isConnected", (Class[]) null);
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
            boolean boo = false;
            try {
                boo = (boolean) m.invoke(device, (Object[]) null);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            }
            if(boo){
                new Thread(new analisisecg.recibir()).start();
            }

        }


    }
    public void comenzar(View view) {
        /*
        if (!btadapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                // TODO: Consider calling
                //    ActivityCompat#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for ActivityCompat#requestPermissions for more details.
                return;
            }
            startActivityForResult(enableBtIntent, 1);
        }
        else {
        */


        Intent intent = new Intent(this, MainActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
            startActivity(intent);
        setContentView(R.layout.activity_main);
            //startService(new Intent(this, analisisecg.class));
        //}
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