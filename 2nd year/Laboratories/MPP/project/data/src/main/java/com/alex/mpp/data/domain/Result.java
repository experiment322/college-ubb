package com.alex.mpp.data.domain;

import lombok.Data;
import lombok.NonNull;

import java.io.Serializable;

@Data
public class Result implements Serializable {
    private @NonNull Integer id;
    private @NonNull Integer gameId;
    private @NonNull Integer athleteId;
    private @NonNull Float value;
}
