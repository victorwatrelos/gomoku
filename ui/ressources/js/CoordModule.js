CoordModule = (function () {
    
  	var xStart = 40;
  	var xEnd = 975;
	var step = (xEnd - xStart) / 18.0;
	var GRID_LENGTH = 19;

  return {

	getDistCoord: function(pos) {
		return {
			x: Math.round(Math.trunc((pos % 19)) * step + xStart - 4),
			y: Math.round(Math.trunc((pos / 19)) * step + xStart - 4)
		};
	},
	getLocalPos: function(coordX, coordY) {
					 coordX -= xStart;
					 coordY -= xStart;
		var x = Math.round(coordX / step);
		var y = Math.round(coordY / step);
		console.log("x: " + x + " y: " + y);
		return x + y * GRID_LENGTH;
	}
  }
})();
