SocketModule = (function() {

	var socket = io.connect('http://localhost:4200');
	socket.on("disconnect", function(data) {
		DisplayModule.setBackCo(false);
	});
	socket.on("connect_failed", function(data) {
		DisplayModule.setBackCo(false);
	});
	socket.on('data', function(data) {
		console.log(data);
		switch (data.type) {
			case "new_game_started":
				DisplayModule.dispNewGame(false);
				break;
			case "get_move":
				DisplayModule.dispTurnOf(data.data);
				break;
			case "connected":
				if (data.data.connected === true)
					DisplayModule.setBackCo(true);
				else
					DisplayModule.setBackCo(false);
				break;
			case "winner":
				DisplayModule.dispWinner(data.data.player);
				break;
			case "ask_new_game":
				DisplayModule.dispNewGame(true);
				break ;
			case "board":
				for (var i = 0; i < data.data.grid.length; i++)
				{
					BoardModule.setStone(i, data.data.grid[i]);
				}
				DisplayModule.dispNbStone(data.data.blackStone, data.data.whiteStone);
				break;
		}
	});
	return {
		sendMove: function(pos, color) {
			var move = {'type': 'move', 'data': {'pos': pos, 'color': color}};
			DisplayModule.dispTurnOf(-1);
			socket.emit('data', move);
		},
		sendNewGame: function() {
			var data = {'type': 'new_game', 'data': null};
			socket.emit('node-data', data);
		}
	}
})();
