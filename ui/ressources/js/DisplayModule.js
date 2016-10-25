DisplayModule = (function() {
	var loader = $('.hide-board');
	var backCo = false;	
	var	disp = true;
	function	dispLoader() {
		console.log("dispLoader");
		if (backCo)
		{
			if (loader.css('display') != 'none')
			{
				disp = false;
				console.log("set none");
				loader.css('display', 'none');
			}
		}
		else
		{
			if (!disp && loader.css('display') != 'block')
			{
				disp = true;
				console.log("set block");
				loader.css('display', 'block');
			}
		}
	}
	function		getNameColor(color) {
		if (color == 0)
			return 'BLACK';
		if (color == 1)
			return 'WHITE';
		return 'NONE';
	}
	return {
		dispWinner: function(color) {
			$('#player_name').text(getNameColor(color));
			$('#winner_div').openModal({dismissible:false});

		},
		setBackCo: function(state) {
			backCo = state;
			dispLoader();
		},
		dispNbStone: function(black_stone, white_stone) {
			$('#nb_black_stone').text(black_stone);
			$('#nb_black_stone').text(white_stone);
		},
		dispNewGame: function(state) {
			if (state)
				$('#ask_new_game').openModal({dismissible:false});
			else
				$('#ask_new_game').closeModal();
		},
		dispTurnOf: function(color) {
			if (color == -1)
			{
				$('#waiting_action').text("AI");
				$('#disp_turn_back').css('display', 'block');
			} else {
				$('#waiting_action').text(getNameColor(color));
				$('#disp_turn_back').css('display', 'none');
				$('#disp_turn_of').css('display', 'block');
			}
		}
	}
})();
