

void init_tile_attributes()
{
	int i;
	for(i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
		tileAtt[i].walkOn = 0; // cannot walk on tiles by default.
		
		
	}
	
	// 0 = cannot walk on.
	tileAtt[t_EOT].walkOn  = 0;	// eot tile
	tileAtt[t_SKIP].walkOn = 1;	// skip tile
	tileAtt[0x0100].walkOn = 1; // dirt
	tileAtt[0x0200].walkOn = 0; // stone
	tileAtt[t_stone_up_right].walkOn =		1; // stone quarter blocks
	tileAtt[t_stone_down_right].walkOn =	1;
	tileAtt[t_stone_down_left].walkOn =		1;
	tileAtt[t_stone_up_left].walkOn =		1;
	tileAtt[0x0300].walkOn = 1; // green portal
	tileAtt[0x0400].walkOn = 1; // red portal
	tileAtt[0x0500].walkOn = 1; // studded
	tileAtt[t_studded_up_right].walkOn =	1; // studded quarter blocks
	tileAtt[t_studded_down_right].walkOn =	1;
	tileAtt[t_studded_down_left].walkOn =	1;
	tileAtt[t_studded_up_left].walkOn =		1;
}
