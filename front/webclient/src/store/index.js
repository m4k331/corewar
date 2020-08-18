import Vue from "vue";
import Vuex from "vuex";

Vue.use(Vuex);


export default new Vuex.Store({
	state: {
		codes: new Array(4096).fill(0),
		set: new Array(4096).fill(0),
		CTD: 10000,
		CyclesDone: 10000,
		NumLive: 10000,
		NumCheck: 10000,
		LLP: 10000,
		message: ['initial state of msg','first msg', 'second msg','3','4','5','6','7','8','8','8','8','8','8','8','8','8','8','8'],
		connected: false,
		error: '',
	},
	mutations: {
		WS_CONNECT(state) {
			state.connected = true
		},
		WS_DISCONNECT(state) {
			state.connected = false
		},
		WS_MESSAGE(state, message) {
			state.message = state.message.push(message)
		},
		WS_HELLO_WORLD(state, message) {
			state.message = state.message.push(message)
		},
		WS_ERROR(state, message) {
			state.error = message.error
		},
	},
})