package com.alex.mpp.common.service;

import com.alex.mpp.data.domain.Athlete;

import java.util.Collection;
import java.util.Map;

public interface AthleteService {
    Collection<Athlete> getAthletes();

    Map<String, Float> getAthletesTotalPoints();
}
