package net.validcat.android.watering.domain.interactor;

import net.validcat.android.watering.data.DataRepository;
import net.validcat.android.watering.data.model.DataContainer;
import net.validcat.android.watering.data.storage.RetrofitNetworkRepository;

import retrofit2.Call;


public class GetDataUseCase  {
    private final DataRepository repository;

    public GetDataUseCase() {
        repository = new DataRepository(new RetrofitNetworkRepository());
    }

    public Call<DataContainer> buildUseCaseObservable() {
        return repository.getDetectorsData();
    }
}
