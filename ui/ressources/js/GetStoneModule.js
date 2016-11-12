GetStoneModule = (function () {
  	var xStart = 40;
  	var xEnd = 975;
	var step = (xEnd - xStart) / 18.0;
	var stoneSize = step - 15;
	var margin = stoneSize / 2;

	function	getStoneById(id, coord, op = 1) {
		imgEl = document.getElementById(id);
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
			selectable: false,
			opacity: op
		});
	}
	return {
		getStoneById: getStoneById,
		getStone: function(color, coord, last = false, op = 1) {
			if (color == 0 && !last) {
				imgEl = "black_stone";
			} else if (color == 1 && !last) {
				imgEl = "white_stone";
			} else if (color == 0 && last) {
				imgEl = "black_stone_last";
			} else if (color == 1 && last) {
				imgEl = "white_stone_last";
			}
			return getStoneById(imgEl, coord, op);
		}
	}
})();
