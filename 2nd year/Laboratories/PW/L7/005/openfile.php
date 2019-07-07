<?php 
	$file = $_GET["file"];
	echo "<div id=\"file\"";
	echo file_get_contents($file);
	echo "</div>";
 ?>