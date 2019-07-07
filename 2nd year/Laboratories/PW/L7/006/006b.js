$(function() {
	start();
});

function start() {
	getProductTypes();
}

function categorySelected(event) {
	let categoryName = event.target.value;
	loadCategory(categoryName);
}

function addCategorySelectEvent() {
	$("#category-select").on("change", categorySelected);
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
	$("#filter-input").on("input", function() {
		let value = $(this).val();
		let filterCriteria = $("#filter-select").val();
		let productCategory = $("#category-select").val();
		if (value === "") {
			loadProducts(productCategory, "none", value);
		} else {
			loadProducts(productCategory, filterCriteria, value);
		}
		
	});
}

function createFilters(products) {
	$("#filter").html("");
	let html = "<h2>Filter products</h2>";

	let keys = Object.keys(products[0]);

	html += "<select id='filter-select'>";
	keys.forEach(function(key) {
		html += "<option>" + key + "</option>";
	});

	html += "</select><div><input id='filter-input' type='text'></div>"
	$("#filter").html(html);
	addFilterEvents();
}

function createProducts(products) {
	$("#content").html("");
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

	$("#content").html(html);
}

function loadProducts(productName, filterCriteria, filterData) {
	let url = "/LabAJAX/006/" + productName + ".php";

	$.get(
		url,
		{
			criteria: filterCriteria,
			data: filterData
		},
		function(data) {
			console.log(data);
			let resp = $.parseJSON(data);
			createProducts(resp);
			if (filterCriteria === "none") {
				createFilters(resp);
			}
		}
	);
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
	$("#categories").html(html);
	addCategorySelectEvent();
}

function getProductTypes() {
	let url = "/LabAJAX/006/getentities.php";
	$.get(
		url,
		function(data) {
			let obj = $.parseJSON(data);
			createCategorySelect(obj);
		} 
	);
}
