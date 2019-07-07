package com.alex.mpp.data.domain;

import lombok.Data;
import lombok.NonNull;

import java.io.Serializable;

@Data
public class Player implements Serializable {
    private @NonNull Integer id;
    private @NonNull String username;
    private @NonNull String password;
}
