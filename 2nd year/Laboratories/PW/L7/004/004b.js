// declaram matricea jocului (cea din memorie)
let matriceJoc = [
    ["g","g","g"], // "g" de la "gol"
    ["g","g","g"],
    ["g","g","g"]
];

// la click pe o celula din tabel, se apeleaza onCellClick
for (let i = 0; i < 3; i++) {
    for (let j = 0; j < 3; j++) {
        $("#tablaJoc tr:nth-child(" + (i + 1) + ") td:nth-child(" + (j + 1) + ")").click(function() {
            onCellClick(this, i, j);
        });
    }
}

// alegem daca da AI-ul primul sau nu, random, chiar la inceput
// random - intre 1 si 2 (inclusiv)
if (Math.floor((Math.random() * 2) + 1) === 1) {
    turaAI();
}

// se apeleaza la click pe o celula in tabel; pune X daca celula e goala
function onCellClick(tableCell, rowIndex, colIndex) {
    if (matriceJoc[rowIndex][colIndex] === "g") {
        $("#tablaJoc tr:nth-child(" + (rowIndex + 1) + ") td:nth-child(" + (colIndex + 1) + ")").html("X");
        matriceJoc[rowIndex][colIndex] = "X";
        verificareFinal();
        turaAI();
    }
}

// verifica daca e gata jocul, si daca nu e gata, efectueaza tura AI-ului
function verificareFinal() {
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

    $.ajax({
        url: url, async: true, success: function (result) {
            // 0 - jocul NU e gata
            // 1 - jocul e gata, castiga playerul
            // 2 - jocul e gata, castiga AI-ul
            // 3 - jocul e gata, egalitate
            // daca jocul nu e gata, facem tura AI-ului
            if (parseInt(result) === 0) {
            }
            else if (parseInt(result) === 1) {
                $("#mesajDiv").html("Felicitari! Ati castigat.");
            }
            else if (parseInt(result) === 2) {
                $("#mesajDiv").html("AI-ul a castigat.");
            }
            else if (parseInt(result) === 3) {
                $("#mesajDiv").html("Egalitate.");
            }
        }
    });
}

function turaAI() {
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

    $.ajax({
        url: url, async: true, success: function (result) {
            // primim un array care e de forma [linie,coloana], ce reprezinta
            // exact mutarea urmatoare a AI-ului
            let linie = parseInt(JSON.parse(result)[0]);
            let coloana = parseInt(JSON.parse(result)[1]);

            if (linie !== -1 && coloana !== -1) {
                // efectuam mutarea AI-ului
                matriceJoc[linie][coloana] = "O";
                $("#tablaJoc tr:nth-child(" + (linie + 1) + ") td:nth-child(" + (coloana + 1) + ")").html("O");
            }

            // verificam daca e gata jocul dupa efectuarea mutarii
            verificareFinal();
        }
    });
}
