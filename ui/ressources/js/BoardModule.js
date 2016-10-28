BoardModule = (function() {
	var grid_size = 19 * 19;
	var canvas;
	var	overlayStone = null;
	var turnOf = null;
	var dispOverlay = false;
	board = Array(grid_size).fill({color: 2, img: null, isLast: false});//Init array to empty
	for (i = 0; i < grid_size; i++) {
		board[i] = {color: 2, img: null};
	}
	return {
		setTurnOf: function(p_turnOf) {
			if (p_turnOf === null)
			{
				if (overlayStone !== null)
				{
					overlayStone.remove();
					overlayStone = null;
				}
			}
			turnOf = p_turnOf;
		},
		setCanvas: function(p_canvas) {
			canvas = p_canvas;
	    },
		setDispOverlay: function(state) {
			dispOverlay = state;
			if (dispOverlay || overlayStone === null)
				return;
			overlayStone.remove();
			overlayStone = null;
		},
		setOverlayStone: function(pos) {
			if (turnOf === null)
				return;
			dispOverlay = true;
			if (overlayStone !== null)
			{
				overlayStone.remove();
				overlayStone = null;
			}
			dispOverlay = true;
			if (board[pos].color !== 2)
				return;
			overlayStone = GetStoneModule.getStone(turnOf, CoordModule.getDistCoord(pos), false, 0.5);
			canvas.add(overlayStone);
		},
		setStone: function(pos, color) {
			data = board[pos];
			if (data.color != color || data.isLast)
			{
				board[pos].color = color;
				board[pos].isLast = !(board[pos].isLast);
				if (data.img !== null)
				{
					data.img.remove();
				}
				if (color != 2) {
					board[pos].img = GetStoneModule.getStone(color, CoordModule.getDistCoord(pos), board[pos].isLast);
					canvas.add(board[pos].img);
				}
			}
		}
	}
})();
