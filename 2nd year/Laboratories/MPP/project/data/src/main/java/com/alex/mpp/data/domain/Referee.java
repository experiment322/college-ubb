package com.alex.mpp.data.domain;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

import java.io.Serializable;

@Data
@NoArgsConstructor
@RequiredArgsConstructor
public class Referee implements Serializable {
    private @NonNull Integer id;
    private @NonNull Integer gameId;
    private @NonNull String name;
    private @NonNull String username;
    private @NonNull String password;
}
