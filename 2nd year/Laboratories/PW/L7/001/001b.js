function afisarePlecari() {
    let url = "001.php?oras=" + $("#lista1 option:selected").text();

    $.ajax({
        url: url, async: true, dataType: 'text', success: function (result) {
            $("#lista2").html(result);
        }
    });
}
