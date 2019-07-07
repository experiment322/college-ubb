<?php
    // luam valoarea parametrului din query string (currentPage)
    $idCerut = $_GET["id"];

    $servername = "localhost";
    $username = "root";
    $password = "root";
    $dbname = "labajax"; // numele bazei de date

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT id, nume, prenume, telefon, email FROM t002";

    $stmt = $conn->prepare($sql);
    $stmt->execute();
    $stmt->bind_result($id, $nume, $prenume, $telefon, $email);

    // daca am primit -1 ca si id, ii returnam un <ul></ul> care
    // contine toate id-urile din tabel
    if ($idCerut == -1) {
        echo "<br/>Lista id-uri: <ul>";
        while($stmt->fetch()){
            echo "<a href='#'><li onclick='fillForm(this.id)' id='" . $id . "'>" . $id . "</li></a>";
        }
        echo "</ul>";
    }
    // altfel, ii dam inregistrarea cu id-ul cerut, ca si array
    // (in javascript, va fi efectiv un array obisnuit)
    else {
        while($stmt->fetch()){
            if ($id == $idCerut) {
                $valori = array($nume, $prenume, $telefon, $email);
                echo json_encode($valori);
            }
        }
    }

    $stmt->close();
    $conn->close();
?>