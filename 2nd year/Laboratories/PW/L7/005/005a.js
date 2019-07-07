let currentFiles = [];

window.onload = function() {
    start();
};

function start() {
	currentFiles = [];
	getTree("../");
}

function addClickEvents() {
	document.querySelectorAll(".fa-sort-down").forEach((item) => {
		item.onclick = displayTree;
	});

	document.querySelectorAll(".fa-file").forEach((item) => {
		item.onclick = function() {
			openFile(this.getAttribute("value"));
		}
	});
}


function getVisibleFoldersUrl() {
	let visible = "";
	currentFiles.forEach(function(file) {
		visible += file + "<<";
	});
	return visible;
}

function openFile(fileUrl) {
	xmlhttp = getXmlHttpObject();

	if (xmlhttp == null) {
	    alert("Your browser does not support XMLHTTP!");
	    return;
	}

	let url = "/LabAJAX/005/openfile.php?file=" + fileUrl;
	console.log(url);
	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
			document.getElementById("container").innerHTML = this.responseText;
			addClickEvents();	
		}
	};

	xmlhttp.open("GET", url, true);
	xmlhttp.send(null);
}

function displayTree() {
	let content = this.getAttribute("value");
	if (currentFiles.includes(content)) {
		currentFiles = currentFiles.filter(function(el) {return el !== content;})
	} else {
		currentFiles.push(content);
	}
	getTree();
}


function getTree() {
	xmlhttp = getXmlHttpObject();
	if (xmlhttp == null) {
	    alert("Your browser does not support XMLHTTP!");
	    return;
	}

	let url = "LabAJAX/005/tree.php?visible=" + getVisibleFoldersUrl();
	console.log(url);
	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
            document.getElementById("container").innerHTML = this.responseText;
			addClickEvents();	
		}
	};

	xmlhttp.open("GET", url, true);
	xmlhttp.send(null);
}

function getXmlHttpObject() {
  if (window.XMLHttpRequest) {
    return new XMLHttpRequest();
  }
  return null;
}