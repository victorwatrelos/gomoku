DisplayModule = (function() {
	var loader = $('.hide-board');
	var backCo = false;	
	var	disp = true;
	var	nbTurn = 0;
	function	dispLoader() {
		if (backCo)
		{
			if (loader.css('display') != 'none')
			{
				disp = false;
				loader.css('display', 'none');
			}
		}
		else
		{
			if (!disp && loader.css('display') != 'block')
			{
				disp = true;
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
			var	str = '';
			switch (color) {
				case 0:
					str = 'The winner is the black player';
					break;
				case 1:
					str = 'The winner is the white player';
					break;
				case 2:
					str = 'DRAW';
					break;
			};
			$('#winning_info').text(str);
			$('#winner_div').openModal({dismissible:false});
			$('#nb_turn_winner').text(nbTurn + ' ');

		},
		setBackCo: function(state) {
			backCo = state;
			dispLoader();
		},
		dispNbStone: function(black_stone, white_stone) {
			$('#nb_black_stone').text(black_stone);
			$('#nb_white_stone').text(white_stone);
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
		},
		dispLoopStat: function(data) {
			nbTurn = data.turn_nb;
			$('#nb_turn').text(data.turn_nb);
			if (data.time.color == 0)
				$('#black_duration').text(data.time.duration);
			if (data.time.color == 1)
				$('#white_duration').text(data.time.duration);
		},
		dispFinalStat: function(data) {
			$('#black_average').text(data.black.average_time);
			$('#white_average').text(data.white.average_time);
			$('#black_info').text(data.black.info);
			$('#white_info').text(data.white.info);
		}
	}
})();
