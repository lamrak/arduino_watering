package net.validcat.android.watering.data.storage;

import net.validcat.android.watering.data.model.DataContainer;

import okhttp3.OkHttpClient;
import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

/**
 * Created by Oleksii on 3/22/17.
 */

public class RetrofitNetworkRepository {

    private RetrofitRestApi client;

    public RetrofitNetworkRepository() {
        String API_BASE_URL = "http://192.168.1.103:81/";

        OkHttpClient.Builder httpClient = new OkHttpClient.Builder();
        Retrofit.Builder builder =
                new Retrofit.Builder()
                        .baseUrl(API_BASE_URL)
                        .addConverterFactory(GsonConverterFactory.create());
        Retrofit retrofit = builder.client(httpClient.build()).build();
        client = retrofit.create(RetrofitRestApi.class);
    }

    public Call<DataContainer> getDetectorsData() {
        return client.getDetectorsData();
    }

    public Call<ResponseBody> makeWateringRequest() {
        return client.makeWateringRequest();
    }
}
