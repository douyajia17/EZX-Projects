//gamedata.h
//
//All the types, constants and data used globally for the game; 
//fonts, images, scores, counters etc


#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "SDL.h"
#include "SDL_mixer.h"

#include "image.h"
#include "fontttf.h"
#include "states.h"
#include "words.h"		//SDL.h should be declared before this
#include "score.h"
#include "sprite.h"


#define VERSION_STRING		"v0.4"	//only displayed on menu (playmenu)

const int CURSORW = 40;		//cursor tile width
const int CURSORH = 40;		//height
const int LETTERW = 36;		//letter roundel width
const int LETTERH = 36;		//height
const int BOXW = 90;		//found word box
const int BOXH = 15;		//height

//positions on screen of :
//scratch letter area SCRATCHX/SCRATCHY1 (6 roundels on top)
//scratch box area SCRATCHX/SCRATCHY2 (6 boxes below roundels)
const int SCRATCHX = 35;					//start position of scratch on screen
const int SCRATCHY1 = 28;					//top row
const int SCRATCHY2	= SCRATCHY1+CURSORH+5;	//bottom row

//to persist global data throughout app
class GameData
{

public:
	GameData();
	~GameData();
	bool isLoaded() {return _init;}
	void setDiffLevel(eDifficulty newDiff);

	void LoadOptions();
	void SaveOptions();
	
	//Resources
	//////////////////////////////

	//fonts
	FontTTF _fntTiny;
	FontTTF _fntSmall;
	FontTTF _fntMed;
	FontTTF _fntBig;
	FontTTF _fntClean;
	FontTTF _fontTiny;

	//backgrounds & images
	Image _menubg;
	Image _menubg_plain;
	Image _menu_reword;
	Image _menu_speed6;
	Image _menu_timetrial;
	Image _gamebg;
	Image _game_reword;
	Image _game_speed6;
	Image _game_timetrial;
	Image _scratch;
	Image _cursor;
	Image _letters;
	Image _boxes;
	Image _popupmenu;
	
	Sprite _arrowUp;
	Sprite _arrowDown;
	Sprite _star;

	//sound effectes etc
	Mix_Chunk *_fxCountdown;	//countdown ping noise
	Mix_Chunk *_fxBadword;		//word not in dictionary noise
	Mix_Chunk *_fxOldword;		//word already found and now shown in list
	Mix_Chunk *_fx6notfound;	//6 letter word not found after timeout
	Mix_Chunk *_fx6found;		//6 letter word found
	Mix_Chunk *_fxFound;		//non 6 letter word found
	Mix_Chunk *_fxBonus;		//all words found in time
	Mix_Chunk *_fxWoosh;		//jumble letters sound

//	Mix_Music *_musicMenu;		// ##TODO## temp sound loop


	//Game vars
	///////////////////////////////

	int			_menuoption;	// (0=play, 1=level, 2=hiscore etc)

	eDifficulty	_diffLevel;
	std::string _diffName;
	SDL_Color	_diffColour;

	eGameState	_state;		//state of play...
	eGameMode	_mode;		//type of game

	Score		_score;
	CWords		_words;		//The one instance of the main word manipulation class

	float		_fact;		//frame rate speed factor

	tWordSet 	_unmatchedWords;	//set of words tested but not matching any in dict

	int 		_current_h;			//used to store screen height as SDL_VideoInfo current_w not available in my build
	int			_current_w;			//used to store screen width
	
private:
	bool _init;

};

#endif //GAMEDATA_H
