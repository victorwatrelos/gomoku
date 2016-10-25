var net = require('net');
var socket = new net.Socket();

var playersTurn = -1;
var	comFront;
var connected = false;

var isRetrying = false;
var stopConnect = true;

function connect() {
	if (connected)
		return ;
	isRetrying = false;
	socket.connect(4202, '127.0.0.1', function() {
		if (!connected)
		{
			console.log("Connected to back");
			socket.write(JSON.stringify({"ACCEPTCO": "OK"}));
		}
		connected = true;
		isRetrying = false;
		comFront.setState(true);
	});
}



function retry() {
	comFront.setState(false);
	if (!isRetrying && !stopConnect) {
		isRetrying = true;
		setTimeout(connect, 3000);
	}
}

module.exports.sendData = function(data) {
	socket.write(JSON.stringify(data));
};

module.exports.stopConnect = function () {
	stopConnect = true;
};

module.exports.connect = function () {
	stopConnect = false;
	connect();
};

module.exports.init = function(p_comFront) {
	comFront = p_comFront;
	var tmp_data = '';
	socket.on('error', function(error) {
		console.log("Socket error: " + error);
		console.log("Trying to connect");
		connected = false;
		retry();
	});
	socket.on('close', function() {
		connected = false;
		retry();
		console.log("Connection closed");
	});
	socket.on('data', function(data) {
		data = data.toString('utf8');
		tmp_data += data;
		function parseData() {
			var finalObj = {};
			var failure = false;
			try {
				var finalStr = '';
				var nb_bracket = 0;
				var	has_one = false;
				var	success = false;
				for (var i = 0; i < tmp_data.length && success === false; i++)
				{
					if (tmp_data[i] == '{')
					{
						nb_bracket++;
						has_one = true;
					}
					else if (tmp_data[i] == '}')
						nb_bracket--;
					if (has_one && nb_bracket === 0)
					{
						finalStr = tmp_data.slice(0, i + 1);
						tmp_data = tmp_data.slice(i + 1);
						success = true;
					}
				}
				if (success)
					finalObj = JSON.parse(finalStr);
				else
					failure = true;
			} catch (e) {
				failure = true;
			}
			if (!failure)
			{

				comFront.sendData(finalObj);
				parseData();
			}
		}
		parseData();
	});
}
