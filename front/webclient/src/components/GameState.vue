<template>
  <div id="gamestate">
    <div class="nameStat">GAME STATISTICS</div>
    <div class="gameStatContainer">
      <div class="gameStatCover">
        <div v-for="(pr, name) in gameState" :key="name+pr" class="stateItem">
          <div class="name">{{name}}</div>
          <div class="value">{{pr}}</div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import Vue from "vue";

export default {
  name: "GameState",
  props: {
    gameState: Object,
  },
};
</script>

<style>
#gamestate {
  border-radius: 5px;
  border: 1px solid lavender;
  padding: 0px 10px 10px 10px;
  height: fit-content;
  width: 100%;
  background-color: lavender;
}
.gameStatContainer {
  overflow: hidden;
  border-radius: 5px;
  background-color: #fff;
}
.gameStatCover {
  border-radius: 5px;
  background-color: #fff;
  box-sizing: content-box;
}
.nameStat {
  width: 100%;
  text-align: center;
  padding-bottom: 5px;
}
.stateItem {
  display: flex;
  /* border-radius: 5px; */
}
.stateItem:hover {
  background-color: gainsboro;
}
.name {
  width: 40%;
  padding-left: 10%;
  text-align: center;
}
.value {
  width: 40%;
  padding-right: 10%;
}
</style>
