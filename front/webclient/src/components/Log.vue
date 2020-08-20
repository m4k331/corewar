<template>
  <div class="logMain">
    <div class="nameLog">MESSAGES</div>
    <div class="logContainer">
      <div class="logScroller scroller">
        <div v-for="(msg, idx) in messages" :key="'msg' + idx" class="msg">{{idx}} - {{msg}}</div>
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
  updated() {
    // whenever data changes and the component re-renders, this is called.
    this.$nextTick(() => this.scrollToEnd());
  },
  mounted() {
	  this.scrollToEnd();
  },
  methods: {
    scrollToEnd: function () {
		const container = document.querySelector(".scroller")
		const scrollHeight = container.scrollHeight
		container.scrollTop = scrollHeight
    },
  },
};
</script>

<style>
.logMain {
  margin-top: 10px;
  border: 1px solid whitesmoke;
  border-radius: 5px;
  padding: 0px 10px 10px 10px;
  height: 400px;
  width: 100%;
  background-color: thistle;
}
.nameLog {
  width: 100%;
  text-align: center;
}
.logContainer {
  overflow: hidden;
  width: 100%;
  height: 95%;
  border-radius: 5px;
  background-color: #fff;
}
.logScroller {
  width: 104%;
  height: 100%;
  overflow-y: scroll;
  padding-right: 17px;
  padding-bottom: 17px;
  box-sizing: content-box;
}
.msg {
  padding-bottom: 2px;
  border-bottom: 1px solid slategrey;
}
.msg:hover {
  background-color: lightgray;
}
</style>