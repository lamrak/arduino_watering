package net.validcat.android.watering.data;

import net.validcat.android.watering.data.model.DataContainer;
import net.validcat.android.watering.data.storage.RetrofitNetworkRepository;

import okhttp3.ResponseBody;
import retrofit2.Call;

/**
 * Created by Oleksii on 3/22/17.
 */

public class DataRepository {

    private final RetrofitNetworkRepository networkRepository;

    public DataRepository(RetrofitNetworkRepository networkRepository) {
        this.networkRepository = networkRepository;
    }

    public Call<DataContainer> getDetectorsData() {
        return networkRepository.getDetectorsData();
    }

    public Call<ResponseBody> watering() {
        return networkRepository.makeWateringRequest();
    }
}
