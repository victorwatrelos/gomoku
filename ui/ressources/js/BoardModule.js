BoardModule = (function() {
	var grid_size = 19 * 19;
	var canvas;
	board = Array(grid_size).fill({color: 2, img: null});//Init array to empty
	for (i = 0; i < grid_size; i++) {
		board[i] = {color: 2, img: null};
	}
	return {
		setCanvas: function(p_canvas) {
			canvas = p_canvas;
	    },
		setStone: function(pos, color) {
			data = board[pos];
			if (data.color != color)
			{
				board[pos].color = color;
				if (data.img !== null)
				{
					data.img.remove();
				}
				if (color != 2) {
					board[pos].img = GetStoneModule.getStone(color, CoordModule.getDistCoord(pos));
					canvas.add(board[pos].img);
				}
			}
		}
	}
})();
