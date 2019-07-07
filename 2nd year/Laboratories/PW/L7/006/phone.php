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

$sql = "select manufacturer, model, screen from phone";
if ($criteria != "none") {
	$sql .= " where " . $criteria . " like '" . $filterData . "%';";
}
$statement = $conn->prepare($sql);
$statement->execute();
$statement->bind_result($manufacturer, $model, $screen);

$phones = array();
while ($statement->fetch()) {
	$phone = new StdClass();
	
	//attributes
	$phone->manufacturer = $manufacturer;
	$phone->model = $model;
	$phone->screen = $screen;

	array_push($phones, $phone);
}

echo json_encode($phones);
$statement->close();
$conn->close();


 ?>