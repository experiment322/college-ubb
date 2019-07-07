// retine daca au fost facute schimbari sau nu
let changesMade = false;

// retine ultimul id pe care am dat click
let idCurent = -1;

incarcaListaIduri();

// apelata cand se modifica valoarea unui input
function schimbareFacuta() {
    changesMade = true;
    $("#saveButton").prop("disabled",false);
}

// apelata la click pe butonul de save
function saveChanges() {
    let nume = $("#inputNume").val();
    let prenume = $("#inputPrenume").val();
    let telefon = $("#inputTelefon").val();
    let email = $("#inputEmail").val();
    let url = "003Save.php";
    url += "?id=" + idCurent + "&nume=" + nume + "&prenume=" + prenume + "&telefon=" + telefon + "&email=" + email;

    $.ajax({
        url: url, async: true, success: function (result) {
            // dupa salvare, dezactivam butonul de save, si spunem ca
            // nu avem nici o schimbare in inputuri (sunt actualizate)
            changesMade = false;
            $("#saveButton").prop("disabled",true);
        }
    });
}

// apelata la incarcarea paginii, incarca lista de id-uri
function incarcaListaIduri() {
    let url = "003.php";
    url += "?id=-1";

    $.ajax({
        url: url, async: true, success: function (result) {
            $("#divLista").html(result);
        }
    });
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

    let url = "003.php";
    url += "?id=" + idElement;

    $.ajax({
        url: url, async: true, success: function (result) {
            $("#inputNume").val(JSON.parse(result)[0]);
            $("#inputPrenume").val(JSON.parse(result)[1]);
            $("#inputTelefon").val(JSON.parse(result)[2]);
            $("#inputEmail").val(JSON.parse(result)[3]);
        }
    });

    // setam id-ul curent al elementului selectat la cel pe care am dat click
    idCurent = idElement;
}