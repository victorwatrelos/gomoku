const spawn = require('child_process').spawn;
var gomoku;
var stateGomoku = false;
var fs = require('fs');
var m_comBack;

module.exports.setComBack = function(comBack)
{
	m_comBack = comBack;
}

module.exports.launchGomoku = function()
{
	if (stateGomoku)
	{
		return;
	}
	stateGomoku = true;
	gomoku = spawn('./gomoku');
	m_comBack.connect();
	gomoku.on('close', (code) => {
		m_comBack.stopConnect();
		console.log('Gomoku exit with code ' + code);
		stateGomoku = false;
	});

	gomoku.stdout.on('data', (data) => {
		fs.writeFile('gomoku_stdout.log', data, function(err) {
			if (err)
			{
				return console.log(err);
			}
		}); 
	});

	gomoku.stderr.on('data', (data) => {
		fs.writeFile('gomoku_stderr.log', data, function(err) {
			if (err)
			{
				return console.log(err);
			}
		}); 
	});
}
