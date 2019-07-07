<?php
    // luam valoarea parametrului din query string (currentPage)
    $idCerut = $_GET["id"];
    $numeCerut = $_GET["nume"];
    $prenumeCerut = $_GET["prenume"];
    $telefonCerut = $_GET["telefon"];
    $emailCerut = $_GET["email"];

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

    $sql = "UPDATE t002 SET nume = ?, prenume = ?, telefon = ?, email = ? WHERE id = ?";

    $stmt = $conn->prepare($sql);
    $stmt->bind_param("ssssi",$numeCerut, $prenumeCerut, $telefonCerut, $emailCerut, $idCerut);
    $stmt->execute();

    $stmt->close();
    $conn->close();
?>