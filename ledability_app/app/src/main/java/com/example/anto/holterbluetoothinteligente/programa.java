package com.example.anto.holterbluetoothinteligente;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.fragment.app.Fragment;

public class programa extends Fragment {
    SharedPreferences sharedPreferences;
    SharedPreferences.Editor editor;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(getContext());
        editor = PreferenceManager.getDefaultSharedPreferences(getContext()).edit();
        View v = inflater.inflate(R.layout.fragment_programa, container, false);

        Button boton1 = (Button) v.findViewById(R.id.finalizar);
        Button boton2 = (Button) v.findViewById(R.id.iniciarPausar);

        boton1.setVisibility(View.VISIBLE);
        boton2.setVisibility(View.VISIBLE);
        return v;
    }

    @Override
    public void onDestroyView(){
        super.onDestroyView();
    }
}
