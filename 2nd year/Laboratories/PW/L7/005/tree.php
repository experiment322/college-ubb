<?php 
	$dir = $_GET["visible"];
	$visibleContent = explode("<<", $dir);

	function generateDirectoryTree($dir) {
		global $visibleContent;
		echo "<ul>";
		foreach (new DirectoryIterator($dir) as $file) {
			if (!$file->isDot()) {
				if ($file->isDir()) {
					echo "<li><i class=\"fa fa-sort-down\" value=\"" . $file->getPathname() . "\">" . basename($file->getPathname()) . "</i>";
					if (in_array($file->getPathname(), $visibleContent)) {
						generateDirectoryTree($file->getPathname());
					}
				} else {
					echo "<li><i class=\"fa fa-file\" value=\"" . $file->getPathname() . "\">" . 
						basename($file->getPathname()) . "</i>";
				}
				
				echo "</li>";
				
			}
			
		}
		echo "</ul>";
	}
	generateDirectoryTree("../");
 ?>