//global.h

#ifndef _GAME_GLOBAL_H_
#define _GAME_GLOBAL_H_

#include "platform.h"
#include <SDL.h>

const SDL_Color NORMAL_COLOUR	= {0xDD,0xDD,0xDD,0},
				BLACK_COLOUR	= {0x00,0x00,0x00,0},
				WHITE_COLOUR	= {0xFF,0xFF,0xFF,0},
				GREY_COLOUR		= {0xAA,0xAA,0xAA,0},
				RED_COLOUR		= {0xFF,0x00,0x00,0},
				GREEN_COLOUR	= {0x22,0xAA,0x22,0},
				BLUE_COLOUR		= {0x40,0x40,0xB0,0},
				YELLOW_COLOUR	= {0xFF,0xFF,0x50,0},
				ORANGE_COLOUR	= {0xF0,0x84,0x00,0},
//				BG_COLOUR		= {0xdb,0xdb,0xb7,0},	//same as loaded bg png's
				GOLD_COLOUR		= {0xba,0xa4,0x05,0},
				PURPLE_COLOUR	= {0xcb,0x73,0xc8,0};	//my colour

//seconds per diff level ( ie diff medium = 2 so ((diff_max-2)*COUNTDOWN_xxx) )
const int COUNTDOWN_REWORD		= 60;
const int COUNTDOWN_SPEED6		= 40;
const int COUNTDOWN_TIMETRIAL	= 120;


#endif //_GAME_GLOBAL_H_

