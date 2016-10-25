const spawn = require('child_process').spawn;
var gomoku;
var stateGomoku = false;
var fs = require('fs');
var m_comBack;

module.exports.setComBack = function(comBack)
{
	m_comBack = comBack;
}

module.exports.isRunning = function()
{
	return stateGomoku;
}

module.exports.kill = function()
{
	if (!stateGomoku)
		return ;
	gomoku.kill('SIGINT');
}

module.exports.launchGomoku = function(config)
{
	if (stateGomoku)
	{
		return;
	}
	stateGomoku = true;
	gomoku = spawn('./gomoku', ['p1:' + config.p1, 'p2:' + config.p2]);
	m_comBack.connect();
	gomoku.on('close', (code) => {
		m_comBack.stopConnect();
		console.log('Gomoku exit with code ' + code);
		stateGomoku = false;
	});

	gomoku.on('error', (err) => {
		m_comBack.stopConnect();
		console.log('Gomoku crash:');
		console.log(err);
		stateGomoku = false;
	});

	gomoku.stdout.on('data', (data) => {
		fs.appendFile('gomoku_stdout.log', data, function(err) {
			if (err)
			{
				return console.log(err);
			}
		}); 
	});

	gomoku.stderr.on('data', (data) => {
		fs.appendFile('gomoku_stderr.log', data, function(err) {
			if (err)
			{
				return console.log(err);
			}
		}); 
	});
}
