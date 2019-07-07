<?php 

$criteria = $_GET["criteria"];
$filterData = $_GET["data"]; 

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "labajax";

$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
$sql = "select manufacturer, model, ram, hdd, videocard from notebook";
if ($criteria != "none") { //if we have criteria we also have filter data
	$sql .= " where " . $criteria . " like '" . $filterData . "%';";
	
}

$statement = $conn->prepare($sql);
$statement->execute();
$statement->bind_result($manufacturer, $model, $ram, $hdd, $videocard);

$notebooks = array();
while ($statement->fetch()) {
	$notebook = new StdClass();
	
	//attributes
	$notebook->manufacturer = $manufacturer;
	$notebook->model = $model;
	$notebook->ram = $ram;
	$notebook->hdd = $hdd;
	$notebook->videocard = $videocard;

	array_push($notebooks, $notebook);
}

echo json_encode($notebooks);
$statement->close();
$conn->close();


 ?>