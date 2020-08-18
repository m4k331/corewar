<template>
	
</template>

<script>
export default {
	name: 'WebSocket',
	beforeCreate: function() {
		console.log("create websocket")
		console.log("connect websocket")
		const ws = new WebSocket("wss://echo.websocket.org/")
		ws.onopen = function() {
			ws.send("Ya otkrylsya")
		}
	},
	mounted: function() {
		console.log("receive msgs on websocket")
	},
	beforeDestroy: function() {
		console.log("disconect websocket")
	}
	
}
</script>

<style scoped>

</style>


