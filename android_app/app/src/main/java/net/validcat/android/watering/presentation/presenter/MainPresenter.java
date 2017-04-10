package net.validcat.android.watering.presentation.presenter;

import android.os.Bundle;
import android.util.Log;

import net.validcat.android.watering.data.model.DataContainer;
import net.validcat.android.watering.domain.interactor.GetDataUseCase;
import net.validcat.android.watering.domain.interactor.WateringUseCase;
import net.validcat.android.watering.presentation.ValueConverter;
import net.validcat.android.watering.presentation.view.main.MainView;

import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class MainPresenter extends BasePresenter<MainView> {

    @Override
    protected void onCreate(Bundle savedState) {
        super.onCreate(savedState);
    }

    @Override
    protected void onTakeView(MainView view) {
        super.onTakeView(view);

        getDataFromDetectors();
    }

    public void getDataFromDetectors() {
        getView().showLoading();

        GetDataUseCase useCase = new GetDataUseCase();
        Call<DataContainer> call = useCase.buildUseCaseObservable();
        call.enqueue(new Callback<DataContainer>() {
            @Override
            public void onResponse(Call<DataContainer> call, Response<DataContainer> response) {
                DataContainer container = response.body();
                if (MainPresenter.this.getView() != null)
                    MainPresenter.this.getView().updateUI(
                            ValueConverter.getLightnessAsString(getView().getContext(), container.lightnessValue),
                            ValueConverter.getStringForMoistureValue(getView().getContext(), container.moistureValue),
                            ValueConverter.getStringForTempValue(getView().getContext(), container.temperatureValue),
                            ValueConverter.getWaterLevelAsString(getView().getContext(), container.levelValue));
            }

            @Override
            public void onFailure(Call<DataContainer> call, Throwable t) {
                Log.d("", "");
            }
        });
    }

    public void goWatering() {
        WateringUseCase useCase = new WateringUseCase();
        Call<ResponseBody> call = useCase.buildUseCaseObservable();
        call.enqueue(new Callback<ResponseBody>() {
            @Override
            public void onResponse(Call<ResponseBody> call, Response<ResponseBody> response) {
                Log.d("", "");
            }

            @Override
            public void onFailure(Call<ResponseBody> call, Throwable t) {
                Log.d("", "");
            }
        });
    }
}
