package net.validcat.android.watering.data.model;

public class DataContainer {
    public int moistureValue;
    public int temperatureValue;
    public int lightnessValue;
    public int levelValue;

    @Override
    public String toString() {
        return "{moisture: " + moistureValue
                + ", temp: " + temperatureValue
                + ", lightness: " + lightnessValue
                + ", level: " + levelValue + "}";
    }
}
