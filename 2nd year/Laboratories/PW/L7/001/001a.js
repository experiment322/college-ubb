let xmlhttp;

function getXmlHttpObject() {
    if (window.XMLHttpRequest) {
        return new XMLHttpRequest();
    }
    return null;
}

function afisarePlecari() {
    xmlhttp = getXmlHttpObject();
    if (xmlhttp == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
    }

    let url = "001.php";
    let e = document.getElementById("lista1");
    let strOras = e.options[e.selectedIndex].text;
    url += "?oras=" + strOras;

    xmlhttp.onreadystatechange = stateChanged;
    xmlhttp.open("GET", url, true);
    xmlhttp.send(null);
}

function stateChanged() {
    if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
        document.getElementById("lista2").innerHTML = xmlhttp.responseText;
    }
}
