class Bot {
    constructor(id, name, file) {
        this.id   = id
        this.name = name;
        this.file = file;
        this.data = "";
        let upload = function(bot) {
            let r = new FileReader();
            r.readAsBinaryString(file.files[0]);
            r.onload = function(e) {
                bot.data = e.target.result;
            }
        }
        file.addEventListener("change", upload.bind(this, this));
    }

    error() {
        if (this.name.value.length > 0) {
            if (!this.file.value) {
                return "Please download the Bot #"+this.id+" source code file";
            }
        }
        if (this.file.value) {
            if (this.name.value.length === 0) {
                return "Please write the name of the Bot #"+this.id;
            }
        }
        return "";
    }

    empty() {
        return !(this.name.value.length > 0 && this.file.value);
    }

    getName() {
        return this.name.value;
    }

    getData() {
        return this.data;
    }
}

let alert = document.getElementById("alert");
alert.showError = function (text) {
    alert.setAttribute("class",  "col-12 alert alert-danger" );
    alert.innerText = text;
}
alert.showWarning = function (text) {
    alert.setAttribute("class",  "col-12 alert alert-warning" );
    alert.innerText = text;
}
alert.showSuccess = function (text) {
    alert.setAttribute("class", "col-12 alert alert-success")
    alert.innerText = text;
}

async function createGame(game) {
    let resp = await fetch('/create_game', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(game)
    });
    return await resp.json();
}
