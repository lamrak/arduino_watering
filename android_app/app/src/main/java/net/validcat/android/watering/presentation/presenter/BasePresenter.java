package net.validcat.android.watering.presentation.presenter;

import android.os.Bundle;

import nucleus.presenter.Presenter;

import static android.util.Log.v;

/**
 * BasePresenter.
 */

public class BasePresenter<ViewType> extends Presenter<ViewType> {
    private final String TAG = getClass().getSimpleName();

    public BasePresenter() {
        v(TAG, "constructor");
    }

        @Override
    protected void onCreate(Bundle savedState) {
        super.onCreate(savedState);
        v(TAG, "onCreate");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        v(TAG, "onDestroy");
    }

    @Override
    protected void onSave(Bundle state) {
        super.onSave(state);
        v(TAG, "onSave");
    }

    @Override
    protected void onTakeView(ViewType view) {
        super.onTakeView(view);
        v(TAG, "onTakeView");
    }

    @Override
    protected void onDropView() {
        super.onDropView();
        v(TAG, "onDropView");
    }
}
