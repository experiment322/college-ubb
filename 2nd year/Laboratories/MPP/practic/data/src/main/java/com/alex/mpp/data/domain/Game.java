package com.alex.mpp.data.domain;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;

@Data
@Entity
@NoArgsConstructor
@RequiredArgsConstructor
public class Game implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private @NonNull Integer id;
    @Column(name = "path")
    private @NonNull String path;
    @Column(name = "player1_id")
    private @NonNull Integer player1Id;
    @Column(name = "player2_id")
    private @NonNull Integer player2Id;
}
