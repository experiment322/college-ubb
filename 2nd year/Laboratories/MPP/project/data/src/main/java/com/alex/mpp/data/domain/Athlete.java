package com.alex.mpp.data.domain;

import lombok.Data;
import lombok.NonNull;

import java.io.Serializable;

@Data
public class Athlete implements Serializable {
    private @NonNull Integer id;
    private @NonNull String name;
}
