let total = 1;

document.getElementById("b1").addEventListener("click", function (){
    total = 1
});
document.getElementById("b2").addEventListener("click", function (){
    total = 2
});
document.getElementById("b3").addEventListener("click", function (){
    total = 3
});
document.getElementById("b4").addEventListener("click", function (){
    total = 4
});

document.getElementById("start").addEventListener("click", function () {
    let bot = new Bot(1, document.getElementById("nameBot"), document.getElementById("fileBot"));
    let nameGame = document.getElementById("nameGame");
    if (nameGame.value.length === 0) {
        alert.showError("Please write the name of the game");
        return;
    }
    let err = bot.error()
    if (err !== "") {
        alert.showError(err);
        return;
    }
   if (bot.empty()) {
       alert.showError("Please upload at least one bot");
       return;
   }
   alert.showWarning("Creating a game...")
   createGame({
       name: nameGame.value,
       bots: [{
           name: bot.getName(),
           code: bot.getData(),
       }],
       total: total,
    }).then(
        function (result) {
            if (result.id === undefined) {
                alert.showError(result.error);
                return;
            }
            alert.showSuccess("Success");
            window.location="/game/"+result.id;
        }
    );
})
