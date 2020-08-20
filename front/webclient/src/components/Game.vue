<template>
  <div class="game">
    <div class="gameName">{{ msg }}</div>
    <Arena :code="codes" class="arena"/>
    <div class="info">
      <GameState :gameState="GState" />
      <Log :messages="log" />
    </div>
    <div class="players">
      <Players />
    </div>
  </div>
</template>

<script>
import Vue from "vue";
import Arena from "./Arena";
import Log from "./Log";
import GameState from "./GameState";
import Players from "./Players";
import store from "../store";

export default {
  name: "game",
  components: {
    GameState: GameState,
    Log: Log,
	Arena: Arena,
	Players,
  },
  data() {
    return {
      msg: "Name of The Game",
      response: "Server keeps silence...",
    };
  },
  computed: {
    codes() {
      return store.state.codes.map((mapItem, index) => ({
        map: mapItem,
        set: store.state.set[index],
      }));
    },
    GState() {
      return {
        CTD: store.state.CTD,
        CyclesDone: store.state.CyclesDone,
        NumLive: store.state.NumLive,
        NumCheck: store.state.NumCheck,
        LLP: store.state.LLP,
      };
    },
    log() {
      return store.state.message;
    },
  },
  methods: {
    // Disconnects from websocket server
    disconnect: function () {
      this.connected && ws.close();
      console.error(this.connections);
    },

    // Connects to websocket server
    connect: function () {
      var app = this;

      let ws = new WebSocket("ws://localhost:9090/ws");

      ws.onmessage = function (evt) {
        console.log(evt);
        store.commit("WS_MESSAGE", evt.data);
      };
      ws.onopen = function () {
        console.log("socket opened");
        //   ws.send("cat server.go");

        app.connected = true;
      };

      ws.onclose = function () {
        app.connected = false;
      };
    },
  },
  created() {
    this.connect();
  },
};
</script>

<style scoped>
.game {
  display: flex;
  flex-wrap: wrap;
  justify-content: space-evenly;
  flex-direction: row;
}
.gameName {
  width: 100%;
  align-content: center;
  text-align: center;
  background-color: bisque;
  margin-bottom: 5px;
}
.arena{
	z-index: 2;
	width: 60%;
}
.info {
  display: flex;
  flex-wrap: wrap;
  flex-direction: column;
  justify-content: space-evenly;
  width: 35%;
}
.players{
	width: 100%;
	justify-content: space-evenly;
	display: flex;
	flex-wrap: wrap;
	flex-direction: row;
}
</style>