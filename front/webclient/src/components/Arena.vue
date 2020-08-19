<template>
  <div class="arena">
    <div v-for="(pointerChunk, idxCh) in pointerChunks" :key="idxCh + 'Chunk'" class="pointersChunk">
      <div class="startIdx">{{ '0x' + ('00' +  generalIdx(0, idxCh).toString(16).toUpperCase()).slice(-2) }} </div>
      <div
        v-for="(n, idx) in pointerChunk"
        :key="generalIdx(idx, idxCh) + 'point'"
        class="pointer"
        :id="changeID(n.set)"
      >
        {{ n.map }}
        <div
          class="pos"
        >{{"0x" + generalIdx(idx, idxCh).toString(16).toUpperCase() + '\n' + n.map }}</div>
      </div>
    </div>
  </div>
</template>

<script>
import Vue from "vue";
import _ from "lodash";

export default Vue.extend({
  name: "Arena",
  data() {
    return {
      rowNum: 64,
    };
  },
  props: {
    code: Array,
  },
  computed: {
    pointerChunks: function () {
      return _.chunk(Object.values(this.code), this.rowNum);
    },
  },
  methods: {
    generalIdx: function (id, rowId) {
      return id + rowId * this.rowNum;
    },
    changeID(set) {
      if (set > 5) {
        set -= 8;
        switch (set) {
          case 1:
            return "car_pl1";
          case 2:
            return "car_pl2";
          case 3:
            return "car_pl3";
          case 4:
            return "car_pl4";
          default:
            return "car_pl0";
        }
      } else {
        switch (set) {
          case 1:
            return "pl1";
          case 2:
            return "pl2";
          case 3:
            return "pl3";
          case 4:
            return "pl4";
          default:
            return "pl0";
        }
      }
    },
  },
});
</script>

<style scoped>
.arena {
  display: flex;
  flex-wrap: wrap;
  flex-direction: column;
  justify-content: space-evenly;
  font-size: 8px;
}
.pointersChunk {
  display: flex;
  flex-wrap: wrap;
  flex-direction: row;
  justify-content: space-evenly;
}
.pointersChunk:hover{
	background-color: rgba(255, 100, 100, 0.5);;
}
.pointer {
  cursor: zoom-in;
  width: 10px;
  height: 10px;
  background-color: rgba(0, 0, 0, 0.1);
  border-radius: 1px;
  margin: 0.05px;
  text-align: center;
}
.startIdx {
	width: 17px;
}

.pos {
  visibility: hidden;
  background-color: teal;
  width: fit-content;
  height: 3rem;
  color: white;
  opacity: 1;
}

.pointer:hover > .pos {
  visibility: visible;
  line-height: 120%;
  font-size: 20px;
  border-radius: 10px;
}

#car_pl0 {
  background-color: black;
  color: white;
}
#pl0 {
  color: black;
}

#car_pl1 {
  background-color: darkred;
  color: white;
}
#pl1 {
  color: red;
}

#car_pl2 {
  background-color: blue;
  color: white;
}
#pl2 {
  color: blue;
}

#car_pl3 {
  background-color: darkorange;
  color: white;
}
#pl3 {
  color: darkorange;
}

#car_pl4 {
  background-color: green;
  color: white;
}
#pl4 {
  color: green;
}
</style>