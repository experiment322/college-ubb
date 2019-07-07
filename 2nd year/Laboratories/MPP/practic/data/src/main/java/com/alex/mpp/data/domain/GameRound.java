package com.alex.mpp.data.domain;

import lombok.Data;
import lombok.NonNull;

import java.io.Serializable;

@Data
public class GameRound implements Serializable {
    private @NonNull Integer gameId;
    private @NonNull Integer roundNumber;
    private @NonNull Integer playerSteps;
}
