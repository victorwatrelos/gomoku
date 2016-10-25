var express = require('express');  
var app = express();  
var server = require('http').createServer(app);  
var comFront = require('./module/ComFront.js');
var comBack = require('./module/ComBack.js');
var gomokuManager = require('./module/GomokuManager.js');

app.use(express.static(__dirname + '/bower_components'));  
app.use(express.static(__dirname + '/ressources'));  
app.get('/', function(req, res,next) {  
	    res.sendFile(__dirname + '/index.html');
});

gomokuManager.setComBack(comBack);
comBack.init(comFront);
comFront.init(server, comBack, gomokuManager);



server.listen(4200);
