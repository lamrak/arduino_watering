package net.validcat.android.watering.data.storage;

import net.validcat.android.watering.data.model.DataContainer;

import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.http.GET;

/**
 * Created by Oleksii on 3/22/17.
 */

public interface RetrofitRestApi {

    @GET("/")
    Call<DataContainer> getDetectorsData();

    @GET("/W")
    Call<ResponseBody> makeWateringRequest();
}
