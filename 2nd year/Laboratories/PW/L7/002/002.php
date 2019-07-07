<?php
    $paginaCurenta = $_GET["currentPage"];

    $servername = "localhost";
    $username = "root";
    $password = "root";
    $dbname = "alex";


    $conn = new mysqli($servername, $username, $password, $dbname);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT id, nume, prenume, telefon, email FROM t002";

    $stmt = $conn->prepare($sql);
    $stmt->execute();
    $stmt->bind_result($id, $nume, $prenume, $telefon, $email);

    // daca am primit -1 ca si pagina curenta, inseamna ca trebuie sa
    // returnam numarul de persoane, pentru ca clientul sa stie cate
    // pagini sunt in total (si sa poata da disable la butoanele de prev/next)
    if ($paginaCurenta == -1) {
        $nrValori = 0;
        while($stmt->fetch()){
            $nrValori++;
        }
        echo $nrValori;
    }
    // altfel, ii dam pagina cu indexul cerut
    else {
        echo "<tr>";
        echo "<th>Nume</th>";
        echo "<th>Prenume</th>";
        echo "<th>Telefon</th>";
        echo "<th>Email</th>";
        echo "</tr>";
        $nrValori = 0;
        $valoriPuseInTabel = 0;
        while($stmt->fetch()){
            if (intdiv($nrValori, 3) == $paginaCurenta) {
                echo "<tr>";
                echo "<td>" . $nume . "</td>";
                echo "<td>" . $prenume . "</td>";
                echo "<td>" . $telefon . "</td>";
                echo "<td>" . $email . "</td>";
                echo "</tr>";
                $valoriPuseInTabel++;
            }
            $nrValori++;
        }
        // daca cumva e ultima pagina, si nu sunt 3 inregistrari
        // pe ultima pagina, completam cu inregistrari goale pana
        // cand tabelul are 3 inregistrari, pentru consistenta
        while ($valoriPuseInTabel < 3) {
                echo "<tr>";
                echo "<td>&nbsp;</td>";
                echo "<td>&nbsp;</td>";
                echo "<td>&nbsp;</td>";
                echo "<td>&nbsp;</td>";
                echo "</tr>";
                $valoriPuseInTabel++;
        }
    }

    $stmt->close();
    $conn->close();
?>
