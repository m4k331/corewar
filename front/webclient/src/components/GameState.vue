<template>
  <div id="gamestate">
	  <div class="nameStat">GAME STATISTICS</div>
    <div v-for="(pr, name) in gameState" :key="name+pr" class="stateItem">
      <div class="name">{{name}}</div>
      <div class="value">{{pr}}</div>
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
  border: 1px solid #f1f;
  padding: 0px 10px 10px 10px;
  height: 30%;
  width: 100%;
  margin-top: 10px;
}
.nameStat {
	width: 100%;
	text-align: center;
	padding-bottom: 5px;
}
.stateItem {
  display: flex;
}
.name {
  width: 65%;
}
.value {
  width: 20%;
}
</style>
