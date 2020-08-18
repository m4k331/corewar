<template>
  <div class="logMain">
    <div class="nameLog">MESSAGES</div>
    <div class="logContainer">
      <div class="logScroller">
        <div v-for="(msg, idx) in messages" :key="msg + idx">{{idx}} - {{msg}}</div>
      </div>
    </div>
  </div>
</template>

<script>
import Vue from "vue";

export default {
  name: "Log",
  props: {
    messages: Array,
  },
};
</script>

<style>
.logMain {
  margin-top: 10px;
  border: 1px solid black;
  border-radius: 5px;
  padding: 0px 10px 10px 10px;
  height: 55%;
  width: 100%;
}
.nameLog {
  width: 100%;
  text-align: center;
}
.logContainer {
  overflow: hidden;
  width: 100%;
  height: 95%;
}
.logScroller {
  width: 100%;
  height: 100%;
  overflow-y: scroll;
  padding-right: 17px;
  box-sizing: content-box;
}
</style>