package com.alex.mpp.client.model;

import com.alex.mpp.data.domain.Athlete;
import com.alex.mpp.data.domain.Result;

public class AthleteGameResult {
    private final Result result;
    private final Athlete athlete;

    public AthleteGameResult(Result result, Athlete athlete) {
        this.result = result;
        this.athlete = athlete;
    }

    @SuppressWarnings("unused")
    public String getAthleteName() {
        return athlete.getName();
    }

    @SuppressWarnings("unused")
    public Float getResultPoints() {
        return result.getValue();
    }
}
