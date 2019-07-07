let xmlhttp1, xmlhttp2;
let currentPage = 0;
let nrPersoane = 0;
let nrPagini = 0;

incarcaNrPersoane();
reincarcareContinut();

// apelata la click pe butonul de previous
function paginaMinus() {
    currentPage--;
    reincarcareContinut();
    if (currentPage === 0)
        document.getElementById("prevButton").disabled = true;
    if (currentPage < nrPagini - 1)
        document.getElementById("nextButton").disabled = false;
}

// apelata la click pe butonul de next
function paginaPlus() {
    currentPage++;
    reincarcareContinut();
    if (currentPage > 0)
        document.getElementById("prevButton").disabled = false;
    if (currentPage === nrPagini - 1)
        document.getElementById("nextButton").disabled = true;
}

// apelata la incarcarea paginii, determina cate persoane sunt
// si cate pagini sunt
function incarcaNrPersoane() {
    xmlhttp1 = getXmlHttpObject();
    if (xmlhttp1 == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
    }

    let url = "002.php";
    url += "?currentPage=-1";

    xmlhttp1.onreadystatechange = setNrPersoane;
    xmlhttp1.open("GET", url, true);
    xmlhttp1.send(null);
}
function setNrPersoane() {
    if (xmlhttp1.readyState === 4 && xmlhttp1.status === 200) {
        nrPersoane = parseInt(xmlhttp1.responseText);
        nrPagini = ((nrPersoane - 1) / 3) + 1;
    }
}

// apelata cand se schimba pagina (si la incarcarea paginii),
// incarca continutul tabelului
function reincarcareContinut() {
    xmlhttp2 = getXmlHttpObject();
    if (xmlhttp2 == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
    }

    let url = "002.php";
    url += "?currentPage=" + currentPage;

    xmlhttp2.onreadystatechange = stateChanged;
    xmlhttp2.open("GET", url, true);
    xmlhttp2.send(null);
}
function stateChanged() {
    if (xmlhttp2.readyState === 4 && xmlhttp2.status === 200) {
        document.getElementById("persoane").innerHTML = xmlhttp2.responseText;
    }
}

function getXmlHttpObject() {
    if (window.XMLHttpRequest) {
        return new XMLHttpRequest();
    }
    return null;
}