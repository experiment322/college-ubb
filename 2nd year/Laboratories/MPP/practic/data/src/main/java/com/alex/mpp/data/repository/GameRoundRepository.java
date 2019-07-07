package com.alex.mpp.data.repository;

import com.alex.mpp.data.domain.GameRound;

import java.util.Map;

public interface GameRoundRepository extends CRUDRepository<Map.Entry<Integer, Integer>, GameRound> {
}
