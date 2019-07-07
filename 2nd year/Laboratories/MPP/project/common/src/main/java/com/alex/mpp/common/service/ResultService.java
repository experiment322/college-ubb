package com.alex.mpp.common.service;

import com.alex.mpp.data.domain.Result;

import java.util.Collection;

public interface ResultService {
    Collection<Result> getResultsForGame(Integer gameId);

    void setResult(Integer athleteId, Integer gameId, Float value);
}
