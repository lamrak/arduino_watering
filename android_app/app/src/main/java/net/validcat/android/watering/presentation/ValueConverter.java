package net.validcat.android.watering.presentation;

import android.content.Context;

import net.validcat.android.watering.R;

/**
 * Created by Oleksii on 3/30/17.
 */

public class ValueConverter {


    /* *
     * Soggy soil -  moisture between 0 and 500;
     * Wet soil   - moisture between 500 and 800;
     * Dry soil   - moisture between 800-1023;
    */
    public static String getStringForMoistureValue(Context context, int value) {
        if (value > 950)
            return value + " critical dry soil";
        if (value > 850)
            return value + " dry soil";
        if (value > 800)
            return value + " partially dry soil";
        if (value > 700)
            return value + " partially wet soil";
        if (value > 600)
            return value + " wet soil";
        if (value > 500)
            return value + " strong wet soil";
        if (value > 400)
            return value + " soggy soil";
        if (value > 200)
            return value + " swamp in the pot";
        if (value > 0)
            return value + " ocean in the pot";

        return context.getString(R.string.not_specified);
    }

    public static String getLightnessAsString(Context context, int value) {
        if (value > 900)
            return value + " night";
        if (value > 800)
            return value + " cloudy";
        if (value > 600)
            return value + " day";
        if (value > 0)
            return value + " sunshine day";

        return context.getString(R.string.not_specified);
    }

    public static String getWaterLevelAsString(Context context, int value) {
        if (value > 400)
            return value + " full tank";
        if (value > 200)
            return value + " half tank";
        if (value > 0)
            return value + " empty tank";

        return context.getString(R.string.not_specified);
    }

    public static String getStringForTempValue(Context context, int temperatureValue) {
        return temperatureValue + " C°";
    }
}
