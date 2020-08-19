let bots = [
    new Bot(1, document.getElementById("nameBot1"), document.getElementById("fileBot1")),
    new Bot(2, document.getElementById("nameBot2"), document.getElementById("fileBot2")),
    new Bot(3, document.getElementById("nameBot3"), document.getElementById("fileBot3")),
    new Bot(4, document.getElementById("nameBot4"), document.getElementById("fileBot4"))
];

document.getElementById("start").addEventListener("click", function () {
    let nameGame = document.getElementById("nameGame");
    if (nameGame.value.length === 0) {
        alert.showError("Please write the name of the game");
        return;
    }
    let playerBots = []
    for (let i = 0; i < bots.length; i++) {
        let err = bots[i].error();
        if (err !== "") {
            alert.showError(err);
            return;
        }
        if (!bots[i].empty()) {
            playerBots.push({
                name: bots[i].getName(),
                code: bots[i].getData(),
            })
        }
    }
    if (playerBots.length === 0) {
        alert.showError("Please upload at least one bot");
        return;
    }
    alert.showWarning("Creating a game...")
    createGame({
        name: nameGame.value,
        bots: playerBots,
        total: playerBots.length,
    }).then(
        function (result) {
            console.log(result);
            if (result.id === undefined) {
                alert.showError(result.error);
                return;
            }
            alert.showSuccess("Success");
            window.location="/game/"+result.id;
        }
    );
})
