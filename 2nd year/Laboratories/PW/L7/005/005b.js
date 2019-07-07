let currentFiles = [];

$(function() {
	start();
});

function start() {
	currentFiles = [];
	getTree("../");
}

function addClickEvents() {
	$(".fa-sort-down").on("click", displayTree);

	$(".fa-file").on("click", function() {
		openFile(this.getAttribute("value"));
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
	$.get(
		"/LabAJAX/005/openfile.php",
		{file: fileUrl},
		function(data) {
			$("#container").html(data);
			addClickEvents();	
		}
	);
}

function displayTree() {
	console.log(this);
	let content = this.getAttribute("value");
	console.log(content);
	if (currentFiles.includes(content)) {
		currentFiles = currentFiles.filter(function(el) {return el !== content;})
	} else {
		currentFiles.push(content);
	}
	getTree();
}


function getTree() {
	$.get(
		"/LabAJAX/005/tree.php",
		{visible: getVisibleFoldersUrl()},
		function(data) {
			$("#container").html(data);
			addClickEvents();	
		}
	);
}