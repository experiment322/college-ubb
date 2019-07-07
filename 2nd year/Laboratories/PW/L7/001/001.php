<?php
    $orasPlecare = ($_GET["oras"]);

    $servername = "localhost";
    $username = "root";
    $password = "root";
    $dbname = "alex";

    $conn = new mysqli($servername, $username, $password, $dbname);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT * FROM t001 WHERE plecare = ?";

    $stmt = $conn->prepare($sql);
    $stmt->bind_param("s", $orasPlecare);
    $stmt->execute();
    $stmt->bind_result($plecare, $sosire);

    while($stmt->fetch()){
        if ($plecare === $orasPlecare)
            echo "<option>" . $sosire . "</option>";
    }

    $stmt->close();
    $conn->close();
?>
