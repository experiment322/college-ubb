package com.alex.mpp.data.domain;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

import javax.persistence.Entity;
import javax.persistence.Id;
import java.io.Serializable;

@Data
@Entity
@NoArgsConstructor
@RequiredArgsConstructor
public class Game implements Serializable {
    @Id
    private @NonNull Integer id;
    private @NonNull String name;
}
