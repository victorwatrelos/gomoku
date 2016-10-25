var io;
var m_client = null;
var	m_backState = false;
var	m_board = "";
var	tmp_board = {'type': null};


module.exports.init = function(server, comBack, gomokuManager) {
io = require('socket.io')(server);
io.on('connection', function(client) {  
	m_client = client;
	console.log('Front websocket client connected');
	m_client.emit('data', {'type': 'connected', 'data': {'connected': true}});
	if (!(gomokuManager.isRunning()))
		m_client.emit('data', {'type': 'ask_new_game', 'data': null});

	client.on('node-data', function(data) {
		switch (data.type) {
			case "new_game":
				gomokuManager.launchGomoku(data.data);
				m_client.emit('data', {'type': 'new_game_started', 'data': null});
				break;
			case "ask_board":
				m_client.emit('data', tmp_board);
				break;
			case "force_restart":
				gomokuManager.kill();
				m_client.emit('data', {'type': 'ask_new_game', 'data': null});
				break;
		};
	});
	client.on('data', function(data) {
		comBack.sendData(data);
	});
	client.on('error', function(err) {
		console.log(err);
	});
});
}

module.exports.sendData = function(data) {
	if (data.type == "board")
	{
		tmp_board = data;
	}
	if (m_client == null) {
		setTimeout(module.exports.sendData, 500);
	} else {
		m_client.emit('data', data);
	}
}
module.exports.setState = function(state) {
	m_backState = state;
	if (m_client !== null)
		module.exports.sendData({'type': 'connected', 'data': {'connected': state}});
}

