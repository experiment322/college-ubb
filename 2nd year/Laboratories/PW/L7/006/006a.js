window.onload = function() {
	start();
};

function start() {
	getProductTypes();
}

function categorySelected(event) {
	let categoryName = event.target.value;
	loadCategory(categoryName);
}

function addCategorySelectEvent() {
	document.querySelector("#category-select").onchange = categorySelected;
}

function loadCategory(category) {
	switch(category) {
		case("notebook"):
			loadNotebooks("none", "");
			break;
		case("pc"):
			loadPCs("none", "");
			break;
		case("phone"):
			loadPhones("none", "");
			break;
	}
}

function addFilterEvents() {
	document.querySelector("#filter-input").oninput = function() {
		let value = this.value;
		let filterCriteria = document.getElementById("filter-select").value;
		let productCategory = document.getElementById("category-select").value;
		if (value === "") {
			loadProducts(productCategory, "none", value);
		} else {
			loadProducts(productCategory, filterCriteria, value);
		}
	};
}

function createFilters(products) {
	document.getElementById("filter").innerHTML = "";
	let html = "<h2>Filter products</h2>";

	let keys = Object.keys(products[0]);

	html += "<select id='filter-select'>";
	keys.forEach(function(key) {
		html += "<option>" + key + "</option>";
	});

	html += "</select>";
	html += "<div><input id='filter-input' type='text'></div>";
	document.getElementById("filter").innerHTML = html;
	addFilterEvents();
}

function createProducts(products) {
	document.getElementById("content").innerHTML = "";
	let html = "";

	products.forEach(function(product) {
		html += "<div class=\"product\">";
		let keys = Object.keys(product);
		html += "<ul>";
		keys.forEach(function(key) {
			html += "<li><strong>" + key + "</strong>: " + product[key] + "</li>";
		});
		html += "</ul></div>";
	});

	document.getElementById("content").innerHTML = html;
}

function loadProducts(productName, filterCriteria, filterData) {
	xmlhttp = getXmlHttpObject();
	if (xmlhttp == null) {
		alert("Your browser does not support XMLHTTP!");
		return;
	}

	let url = "/LabAJAX/006/" + productName + ".php";
	url += "?criteria=" + filterCriteria + "&data=" + filterData;
	console.log(url);
	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
			let resp = JSON.parse(this.responseText);
			
			createProducts(resp);
			if (filterCriteria === "none") {
				createFilters(resp);
			}
			
		}
	};
	xmlhttp.open("GET", url, true);
	xmlhttp.send(null);
}

function loadNotebooks(filter, data) {
	loadProducts("notebook", filter, data);
}

function loadPCs(filter, data) {
	loadProducts("pc", filter, data);
}

function loadPhones(filter, data) {
	loadProducts("phone", filter, data);
}

function createCategorySelect(obj) {
	let categories = obj.tables;
	let html = "<h2>Categories</h2><select id=\"category-select\"><option></option>";
	categories.forEach(function(category) {
		html += "<option>" + category + "</option>";
	});
	html += "</select>";
	document.getElementById("categories").innerHTML = html;
	addCategorySelectEvent();
}

function getProductTypes() {
	xmlhttp = getXmlHttpObject();
	if (xmlhttp == null) {
		alert("Your browser does not support XMLHTTP!");
		return;
	}

	let url = "/LabAJAX/006/getentities.php";
	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
			let obj = JSON.parse(this.responseText);
			createCategorySelect(obj);
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