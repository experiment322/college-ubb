let xmlhttp;

// declaram matricea jocului (cea din memorie)
let matriceJoc = [
    ["g","g","g"], // "g" de la "gol"
    ["g","g","g"],
    ["g","g","g"]
];

// la click pe o celula din tabel, se apeleaza onCellClick
for (let i = 0; i < 3; i++) {
    for (let j = 0; j < 3; j++) {
        document.getElementById("tablaJoc").rows[i].cells[j].onclick = function() {
            onCellClick(this, i, j);
        }
    }
}

// alegem daca da AI-ul primul sau nu, random, chiar la inceput
// random - intre 1 si 2 (inclusiv)
if (Math.floor((Math.random() * 2) + 1) === 1) {
    turaAI();
}

// se apeleaza la click pe o celula in tabel; pune X daca celula e goala
function onCellClick(tableCell, rowIndex, colIndex) {
    let tablaJoc = document.getElementById("tablaJoc");
    if (matriceJoc[rowIndex][colIndex] === "g") {
        tablaJoc.rows[rowIndex].cells[colIndex].innerHTML = "X";
        matriceJoc[rowIndex][colIndex] = "X";
        verificareFinal();
        turaAI();
    }
}

// verifica daca e gata jocul, si daca nu e gata, efectueaza tura AI-ului
function verificareFinal() {
    xmlhttp = getXmlHttpObject();
    if (xmlhttp == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
    }

    // trimitem toata matricea, de forma "matriceJoc00=X&matriceJoc01=O&..."
    let url = "004Final.php?";
    for (let i=0; i<3; i++) {
        for (let j = 0; j < 3; j++) {
            if (i === 2 && j === 2)
                url += "matriceJoc" + i + j + "=" + matriceJoc[i][j];
            else
                url += "matriceJoc" + i + j + "=" + matriceJoc[i][j] + "&";
        }
    }

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
            // 0 - jocul NU e gata
            // 1 - jocul e gata, castiga playerul
            // 2 - jocul e gata, castiga AI-ul
            // 3 - jocul e gata, egalitate
            // daca jocul nu e gata, facem tura AI-ului
            if (parseInt(xmlhttp.responseText) === 0) {
            }
            else if (parseInt(xmlhttp.responseText) === 1) {
                document.getElementById("mesajDiv").innerHTML = "Felicitari! Ati castigat.";
            }
            else if (parseInt(xmlhttp.responseText) === 2) {
                document.getElementById("mesajDiv").innerHTML = "AI-ul a castigat.";
            }
            else if (parseInt(xmlhttp.responseText) === 3) {
                document.getElementById("mesajDiv").innerHTML = "Egalitate.";
            }
        }
    };
    xmlhttp.open("GET", url, true);
    xmlhttp.send(null);
}

function turaAI() {
    xmlhttp = getXmlHttpObject();
    if (xmlhttp == null) {
        alert("Your browser does not support XMLHTTP!");
        return;
    }

    // trimitem toata matricea, de forma "matriceJoc00=X&matriceJoc01=O&..."
    let url = "004TuraAI.php?";
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (i === 2 && j === 2)
                url += "matriceJoc" + i + j + "=" + matriceJoc[i][j];
            else
                url += "matriceJoc" + i + j + "=" + matriceJoc[i][j] + "&";
        }
    }

    xmlhttp.onreadystatechange = function () {
        if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
            // primim un array care e de forma [linie,coloana], ce reprezinta
            // exact mutarea urmatoare a AI-ului
            let linie = parseInt(JSON.parse(xmlhttp.responseText)[0]);
            let coloana = parseInt(JSON.parse(xmlhttp.responseText)[1]);

            if (linie !== -1 && coloana !== -1) {
                // efectuam mutarea AI-ului
                matriceJoc[linie][coloana] = "O";
                document.getElementById("tablaJoc").rows[linie].cells[coloana].innerHTML = "O";
            }

            // verificam daca e gata jocul dupa efectuarea mutarii
            verificareFinal();
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
