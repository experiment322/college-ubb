<?php
    $matriceJoc = array(
        array($_GET["matriceJoc00"],$_GET["matriceJoc01"],$_GET["matriceJoc02"]),
        array($_GET["matriceJoc10"],$_GET["matriceJoc11"],$_GET["matriceJoc12"]),
        array($_GET["matriceJoc20"],$_GET["matriceJoc21"],$_GET["matriceJoc22"]));

    // 0 - jocul NU e gata
    // 1 - jocul e gata, castiga playerul
    // 2 - jocul e gata, castiga AI-ul
    // 3 - jocul e gata, egalitate

    // verificam liniile
    for ($i = 0; $i < 3; $i++) {
        // verificam daca a terminat playerul (X-uri)
        $eGataLinia = 1;
        for ($j = 0; $j < 3; $j++) {
            if ($matriceJoc[$i][$j] !== "X")
                $eGataLinia = 0;
        }
        // daca linia are doar X-uri, a castigat playerul
        if ($eGataLinia === 1) {
            echo 1;
            exit;
        }
        // verificam daca a terminat AI-ul (O-uri)
        $eGataLinia = 1;
        for ($j = 0; $j < 3; $j++) {
            if ($matriceJoc[$i][$j] !== "O")
                $eGataLinia = 0;
        }

        // daca linia are doar O-uri, a castigat playerul
        if ($eGataLinia === 1) {
            echo 2;
            exit;
        }
    }

    // verificam coloanele
    for ($i = 0; $i < 3; $i++) {
        // verificam daca a terminat playerul (X-uri)
        $eGataLinia = 1;
        for ($j = 0; $j < 3; $j++) {
            if ($matriceJoc[$j][$i] !== "X")
                $eGataLinia = 0;
        }
        // daca linia are doar X-uri, a castigat playerul
        if ($eGataLinia === 1) {
            echo 1;
            exit;
        }
        // verificam daca a terminat AI-ul (O-uri)
        $eGataLinia = 1;
        for ($j = 0; $j < 3; $j++) {
            if ($matriceJoc[$j][$i] !== "O")
                $eGataLinia = 0;
        }
        // daca linia are doar O-uri, a castigat playerul
        if ($eGataLinia === 1) {
            echo 2;
            exit;
        }
    }

    // verificam diagonalele
    // verificam daca a castigat player-ul
    if ($matriceJoc[0][0] === "X" && $matriceJoc[1][1] === "X" && $matriceJoc[2][2] === "X") {
        echo 1;
        exit;
    }
    if ($matriceJoc[0][2] === "X" && $matriceJoc[1][1] === "X" && $matriceJoc[2][0] === "X") {
        echo 1;
        exit;
    }
    // verificam daca a castigat AI-ul
    if ($matriceJoc[0][0] === "O" && $matriceJoc[1][1] === "O" && $matriceJoc[2][2] === "O") {
        echo 2;
        exit;
    }
    if ($matriceJoc[0][2] === "O" && $matriceJoc[1][1] === "O" && $matriceJoc[2][0] === "O") {
        echo 2;
        exit;
    }

    // verificam daca toata tabla e plina (daca s-a ajuns pana aici,
    // nu a castigat nimeni, dar inca poate fi egal daca e tabla plina)
    $tablaPlina = 1;
    for ($i = 0; $i < 3; $i++) {
        for ($j = 0; $j < 3; $j++) {
            if ($matriceJoc[$i][$j] === "g")
                $tablaPlina = 0;
        }
    }
    if ($tablaPlina === 1)
        echo 3;
    else
        echo 0;
?>