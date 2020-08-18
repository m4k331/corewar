<template>
  <div class="game">
    <div class="gameName">{{ msg }}</div>
    <Arena :code="codes" />
    <div class="info">
      <GameState :gameState="GState" />
      <Log :messages="log" />
    </div>
  </div>
</template>

<script>
import Vue from "vue";
import Arena from "./Arena";
import Log from "./Log";
import GameState from "./GameState";

export default {
  name: "game",
  components: {
    GameState: GameState,
    Log: Log,
    Arena: Arena,
  },
  data() {
    return {
      msg: "Name of The Game",
      response: "Server keeps silence...",
    };
  },
  computed: {
    codes() {
      return this.$store.state.codes.map((mapItem, index) => ({
        map: mapItem,
        set: this.$store.state.set[index],
      }));
    },
    GState() {
      return {
        CTD: this.$store.state.CTD,
        CyclesDone: this.$store.state.CyclesDone,
        NumLive: this.$store.state.NumLive,
        NumCheck: this.$store.state.NumCheck,
        LLP: this.$store.state.LLP,
      };
    },
    log() {
      return this.$store.state.message;
    },
  },
  methods: {},
  created() {
    console.log(this.$options);
  },
};
</script>

<style scoped>
.game {
  display: flex;
  flex-wrap: wrap;
  justify-content: space-evenly;
}
.gameName {
  width: 100%;
  align-content: center;
  text-align: center;
  background-color: bisque;
}
.info {
  display: flex;
  flex-wrap: wrap;
  flex-direction: column;
}
</style>