////////////////////////////////////////////////////////////////////
/*

File:			utils.cpp

Class impl:		Error

Description:	Some useful utility functions. 
				Mainly string functions at the moment 

Author:			Al McLuckie (al-at-purplepup-dot-org)

Date:			08 May 2007

History:		Version	Date		Change
				-------	----------	--------------------------------
				0.4		05.12.2007	Fix stricmp call

Licence:		This program is free software; you can redistribute it and/or modify
				it under the terms of the GNU General Public License as published by
				the Free Software Foundation; either version 2 of the License, or
				(at your option) any later version.

				This software is distributed in the hope that it will be useful,
				but WITHOUT ANY WARRANTY; without even the implied warranty of
				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
				GNU General Public License for more details.

				You should have received a copy of the GNU General Public License
				along with this program; if not, write to the Free Software
				Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/
////////////////////////////////////////////////////////////////////

#include "utils.h"
#include <algorithm>	//for std::min and std::max (if used) amongst other things
#include <cctype>
#include <sstream>
#include <cstring> 	//for strcasecmp/stricmp etc


void Utils::makeUpper(std::string &s)
{
	std::transform(s.begin(),s.end(),s.begin(),toupper);
}

void Utils::makeLower(std::string &s)
{
	std::transform(s.begin(),s.end(),s.begin(),tolower);
}

void Utils::trimRight(std::string &s, const std::string &t) 
{
	s.erase(s.find_last_not_of(t)+1);
}

void Utils::trimLeft(std::string &s, const std::string &t) 
{
	s.erase(0, s.find_first_not_of(t));
}

void Utils::trim(std::string &s, const std::string &t)
{
	trimLeft(s, t);
	trimRight(s, t);
}

//strip any non alpha (A-Z) letters from the string passed in
void Utils::makeAlpha(std::string &s)
{
	std::stringstream sOut;
	for (int i=0; i<(int)s.length(); ++i)
		if (isalpha(s[i])) sOut << s[i];
	s = sOut.str();
}


//function to take a string description (eg instructions or word definition) and split it up into lines ready for display on screen
void Utils::buildTextPage(std::string &inStr,unsigned int nCharsPerLine, std::vector<std::string> &outVect)
{
	outVect.clear();
	
	//split string up into lines displayable on screen...
	unsigned int start = 0, lastBreak = 0, curr = 0;
	std::string line;
	while (1)
	{
		if (curr-start > nCharsPerLine || curr == (unsigned int)inStr.length()-1  || '\n' == inStr[curr])
		{
			//if no break found, just copy up to the MAX chars and cut off
			if (lastBreak == start)	lastBreak = start+nCharsPerLine;
			//if we are at end of string, make sure its all added
			if (curr == (unsigned int)inStr.length()-1)
				lastBreak = (unsigned int)inStr.length();
			if ('\n' == inStr[curr])
				lastBreak = curr;

			//copy from start to lastBreak as one line
			line = inStr.substr(start, lastBreak-start);
			outVect.push_back(line);	//add to list of lines
			start = lastBreak+1;
		}
		//find next break
		if (' ' == inStr[curr] || '\n' == inStr[curr]) lastBreak = curr;
		//are we completely done?
		if (++curr >= (unsigned int)inStr.length()) break;
	}
}


/*
float Utils::round( float x, int places )
{
    float const shift = powf( 10.0f, places );

    x *= shift;
    x = floorf( x + 0.5f );
    x /= shift;

    return x;
} 
*/
/*
inline int Utils::round(float fl)
{
	return (int)((fl*10 + 0.5) / 10.0);
}

*/
/*
int Utils::RandomInt(unsigned int limit)
{
	return (int)m_randInt.Random(limit);
}
*/  
