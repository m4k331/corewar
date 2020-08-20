<template>
  <div id="app">
    <Game />
  </div>
</template>

<script>
import Vue from 'vue'; 
import Game from "./components/Game";

export default {
  components: {
    Game,
  },
  created: function () {
    console.log("Starting connection");
    this.connection = new WebSocket("wss://echo.websocket.org");

    this.connection.onmessage = function (event) {
      console.log(event);
    };
    this.connection.onopen = function (event) {
	  console.log(event);
      console.log("Successfully connected to the echo websocket server...");
    };
  },
};
</script>