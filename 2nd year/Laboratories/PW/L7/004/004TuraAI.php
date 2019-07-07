<?php
    $matriceJoc = array(
        array($_GET["matriceJoc00"],$_GET["matriceJoc01"],$_GET["matriceJoc02"]),
        array($_GET["matriceJoc10"],$_GET["matriceJoc11"],$_GET["matriceJoc12"]),
        array($_GET["matriceJoc20"],$_GET["matriceJoc21"],$_GET["matriceJoc22"]));

    // free pos in array
    $pozitiiLibere = array();
    for ($i = 0; $i < 3; $i++) {
        for ($j = 0; $j < 3; $j++) {
            if ($matriceJoc[$i][$j] === "g")
                $pozitiiLibere[] = array($i, $j);
        }
    }

    // random pos from fr array
    if (count($pozitiiLibere) > 0) {
        echo json_encode($pozitiiLibere[rand(0, count($pozitiiLibere) - 1)]);
    }
    else {
        echo "[-1,-1]";
    }
?>