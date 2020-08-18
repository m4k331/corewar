import VueSocketio from "vue-socket.io";
import Vue from "vue";

import App from "./App.vue";
import store from "./store";

Vue.use(new VueSocketio({
	debug: true,
	connection: `//${window.location.host}`,
	vuex: {
		store,
		actionPrefix: 'WS_',
		mutationPrefix: 'WS_',
	}
}),);

new Vue({
  store,
  render: (h) => h(App),
}).$mount("#app");
