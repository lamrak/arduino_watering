package net.validcat.android.watering.domain.interactor;

import net.validcat.android.watering.data.DataRepository;
import net.validcat.android.watering.data.storage.RetrofitNetworkRepository;

import okhttp3.ResponseBody;
import retrofit2.Call;


public class WateringUseCase {
    private final DataRepository repository;

    public WateringUseCase() {
        repository = new DataRepository(new RetrofitNetworkRepository());
    }

    public Call<ResponseBody> buildUseCaseObservable() {
        return repository.watering();
    }
}
