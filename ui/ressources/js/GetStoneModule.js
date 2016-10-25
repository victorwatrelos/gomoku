GetStoneModule = (function () {
  	var xStart = 40;
  	var xEnd = 975;
	var step = (xEnd - xStart) / 18.0;
	var stoneSize = step - 15;
	var margin = stoneSize / 2;

	return {
		getStone: function(color, coord) {
			if (color == 0) {
				imgEl = document.getElementById("black_stone");
			} else {
				imgEl = document.getElementById("white_stone");
			}
			console.log(coord);
			return new fabric.Image(imgEl, {
				width: stoneSize,
				height: stoneSize,
				left: coord.x - margin - 3,
				top: coord.y - margin - 3,
				lockMovementX: true,
				lockMovementY: true,
				lockScalingX: true,
				lockScalingY: true,
				lockRotation: true,
				selectable: false
			});
		}
	}
})();
