///----------------------------------------------------------------------------------------
/// TILES
///----------------------------------------------------------------------------------------


/// standard tile definition format:
/// #define t_

//SPECIAL TILES IN ALL CAPS
#define t_EOT					0x0000 // end of the tiles
#define t_SKIP				0x0001 // skip a tile in a map
#define t_SPAWN				0x0002 // the palce where a player will spawn by default
//standard stuff
#define t_dirt					0x0100
//stone and stone quarter blocks
#define t_stone					0x0200
#define t_stone_up_right		0x0a00
#define t_stone_down_right		0x0b00
#define t_stone_down_left		0x0c00
#define t_stone_up_left			0x0d00
//portals
#define t_portal_green			0x0300
#define t_portal_red			0x0400
//boxes
#define t_box_closed			0x0101
#define t_box_opened			0x0201
//studded & studded quarter blocks
#define t_studded				0x0500
#define t_studded_up_right		0x0600
#define t_studded_down_right	0x0700
#define t_studded_down_left		0x0800
#define t_studded_up_left		0x0900



///----------------------------------------------------------------------------------------
/// ITEMS
///----------------------------------------------------------------------------------------


/// standard item definition format:
/// #define i_			0x

//SPECIAL ITEMS IN CAPS
#define i_EOI			0x0000
#define i_SKIP			0x0001
#define i_UNKNOWN		0x0002
//GAK
#define i_GAK_blue		0x0100
#define i_GAK_orange	0x0200
#define i_GAK_green		0x0300
#define i_GAK_yellow	0x0400
#define i_GAK_pink		0x0500
//misc crap
#define i_bananas		0x0600
#define i_scroll		0x0700
#define i_laptop_SWAG	0x0800
#define i_laptop_twilight 0x0900
//computer
#define i_computer_motherboard	0x0101
#define i_computer_tower		0x0201
#define i_computer_monitor		0x0301
#define i_computer_keyboard		0x0401
#define i_computer_mouse		0x0501
#define i_computer_hard_drive	0x0601
#define i_computer_processor	0x0102
#define i_computer_RAM			0x0202
#define i_computer_power_supply	0x0302
#define i_computer_power_cable	0x0402
#define i_computer_SATA_cable	0x0502
#define i_computer_DVD_drive	0x0602
