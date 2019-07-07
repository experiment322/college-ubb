// obiectul folosit de ajax
let xmlhttp;

// retine daca au fost facute schimbari sau nu
let changesMade = false;

// retine ultimul id pe care am dat click
let idCurent = -1;

incarcaListaIduri();

// apelata cand se modifica valoarea unui input
function schimbareFacuta() {
    changesMade = true;
    document.getElementById("saveButton").disabled = false;
}

// apelata la click pe butonul de save
function saveChanges() {
    xmlhttp = getXmlHttpObject();
    if (xmlhttp == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
    }

    let nume = document.getElementById("inputNume").value;
    let prenume = document.getElementById("inputPrenume").value;
    let telefon = document.getElementById("inputTelefon").value;
    let email = document.getElementById("inputEmail").value;
    let url = "003Save.php";
    url += "?id=" + idCurent + "&nume=" + nume + "&prenume=" + prenume + "&telefon=" + telefon + "&email=" + email;

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
            // dupa salvare, dezactivam butonul de save, si spunem ca
            // nu avem nici o schimbare in inputuri (sunt actualizate)
            changesMade = false;
            document.getElementById("saveButton").disabled = true;
        }
    };
    xmlhttp.open("GET", url, true);
    xmlhttp.send(null);
}

// apelata la incarcarea paginii, incarca lista de id-uri
function incarcaListaIduri() {
    xmlhttp = getXmlHttpObject();
    if (xmlhttp == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
    }

    let url = "003.php";
    url += "?id=-1";

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
            document.getElementById("divLista").innerHTML = xmlhttp.responseText;
        }
    };
    xmlhttp.open("GET", url, true);
    xmlhttp.send(null);
}

// apelata la click pe un id din lista de id-uri
function fillForm(idElement) {
    // verificam daca au fost schimbari facute sau nu; daca nu au
    // fost schimbari in inputuri, schimbam contentul formului in
    // functie de id-ul pe care s-a dat click
    if (changesMade) {
        let continuare = confirm("Exista schimbari nesalvate! Doriti totusi sa continuati?");
        if (!continuare) {
            return;
        }
    }
    xmlhttp = getXmlHttpObject();
    if (xmlhttp == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
    }

    let url = "003.php";
    url += "?id=" + idElement;

    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
            document.getElementById("inputNume").value = JSON.parse(xmlhttp.responseText)[0];
            document.getElementById("inputPrenume").value = JSON.parse(xmlhttp.responseText)[1];
            document.getElementById("inputTelefon").value = JSON.parse(xmlhttp.responseText)[2];
            document.getElementById("inputEmail").value = JSON.parse(xmlhttp.responseText)[3];
        }
    };
    xmlhttp.open("GET", url, true);
    xmlhttp.send(null);

    // setam id-ul curent al elementului selectat la cel pe care am dat click
    idCurent = idElement;
}

function getXmlHttpObject() {
    if (window.XMLHttpRequest) {
        return new XMLHttpRequest();
    }
    return null;
}