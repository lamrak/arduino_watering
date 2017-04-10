package net.validcat.android.watering.presentation.view.main;

import android.content.Context;

import net.validcat.android.watering.presentation.view.LoadDataView;

public interface MainView extends LoadDataView {

    void updateUI(String lightness, String moisture, String temp, String level);
    void startWatering();

    Context getContext();
}
