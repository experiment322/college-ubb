<?php 

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "labajax";

$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
//select all tables from database
$sql = "SELECT table_name FROM information_schema.tables WHERE table_name='notebook' or table_name='phone' or table_name='pc';";
$statement = $conn->prepare($sql);

$statement->execute();
$statement->bind_result($table);

$tables = array();
while ($statement->fetch()) {
	array_push($tables, $table);
}
$allTables = new StdClass();
$allTables->tables = $tables;
//return a json
echo json_encode($allTables);
$statement->close();
$conn->close();


 ?>