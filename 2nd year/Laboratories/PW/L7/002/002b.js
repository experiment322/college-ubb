let currentPage = 0;
let nrPersoane = 0;
let nrPagini = 0;

incarcaNrPersoane();
reincarcareContinut();

function paginaMinus() {
    currentPage--;
    reincarcareContinut();
    if (currentPage === 0)
        $("#prevButton").prop("disabled", true);
    if (currentPage < nrPagini - 1)
        $("#nextButton").prop("disabled", false);
}

function paginaPlus() {
    currentPage++;
    reincarcareContinut();
    if (currentPage > 0)
        $("#prevButton").prop("disabled", false);
    if (currentPage === nrPagini - 1)
        $("#nextButton").prop("disabled", true);
}

function incarcaNrPersoane() {
    let url = "002.php";
    url += "?currentPage=-1";
    $.ajax({
        url: url, async: true, success: function (result) {
            nrPersoane = parseInt(result);
            nrPagini = Math.ceil(nrPersoane / 3);
        }
    });
}

function reincarcareContinut() {
    let url = "002.php";
    url += "?currentPage=" + currentPage;
    $.ajax({
        url: url, async: true, success: function (result) {
            $("#persoane").html(result);
        }
    });
}
