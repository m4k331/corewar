<template>
  <div class="arena">
    <div v-for="(n, idx) in code" :key="idx + n.map" class="pointer" :id="changeID(n.set)">
		{{ n.map }}
	</div>
  </div>
</template>

<script>
import Vue from "vue";

export default Vue.extend({
  name: "Arena",
  props: {
    code: Array,
  },
  methods: {
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
  font-size: 8px; 
  width: 76.3%; 
}
.pointer {
	width: 10px;
	height: 10px;
	background-color: rgba(0,0,0,0.1);
	border-radius: 2px;
	margin: 0.5px;
	text-align: center;
}

#car_pl0 {
	background-color: black;
	color:white;
}
#pl0 {
	color: 	black;
}


#car_pl1 {
	background-color: darkred;
	color: white
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