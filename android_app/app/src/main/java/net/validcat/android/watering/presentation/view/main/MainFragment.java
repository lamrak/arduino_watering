package net.validcat.android.watering.presentation.view.main;

import android.os.Bundle;
import android.support.v4.widget.SwipeRefreshLayout;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import net.validcat.android.watering.R;
import net.validcat.android.watering.presentation.presenter.MainPresenter;
import net.validcat.android.watering.presentation.view.BaseFragment;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import nucleus.factory.RequiresPresenter;

/**
 * MainFragment view.
 */
@RequiresPresenter(MainPresenter.class)
public class MainFragment extends BaseFragment<MainPresenter> implements MainView {
    @BindView(R.id.swipe) SwipeRefreshLayout swipe;
    @BindView(R.id.tv_light) TextView tvLightness;
    @BindView(R.id.tv_moisture) TextView tvMoisture;
    @BindView(R.id.tv_temp) TextView tvTemp;
    @BindView(R.id.tv_w_level) TextView tvWLevel;

    public MainFragment() {
    }

    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View root = inflater.inflate(net.validcat.android.watering.R.layout.fragment_main, container, false);
        ButterKnife.bind(this, root);

        swipe.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                getPresenter().getDataFromDetectors();
            }
        });

        return root;
    }

    @Override
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
    }

    @Override public void showLoading() {}
    @Override public void hideLoading() {}

    @Override
    public void showError(String message) {
        Toast.makeText(getContext(), message, Toast.LENGTH_LONG).show();
    }

    @Override
    public void updateUI(String lightness, String moisture, String temp, String level) {
        swipe.setRefreshing(false);
        tvLightness.setText(lightness);
        tvMoisture.setText(moisture);
        tvTemp.setText(temp);
        tvWLevel.setText(level);
    }

    @Override
    public void startWatering() {
        //TODO make smart animation
        //TODO disable button
        //TODO update ui
    }

    @OnClick(R.id.btn_watering)
    public void onWateringActivated(View v) {
        getPresenter().goWatering();
    }

}
