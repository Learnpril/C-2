#include "stdafx.h"
#include <iostream>
#include <string>
//after

using namespace std;


class Automaton
{
private:
	static const int RULES_SIZE = 8;

	bool rules[RULES_SIZE];
	string thisGen;
	string extremeBit; // bit, "*" or " ", implied everywhere "outside"
	int displayWidth;  // an odd number so it can be perfectly centered

public:
	static const int MAX_DISPLAY_WIDTH = 121;
	static const int CONSTRUCTOR_INT = 79;

	Automaton(int rule);
	string toStringCurrentGen();
	bool setRule(int newRule);      // change rule set
	void resetFirstGen();
	bool setDisplayWidth(int width);
	void propagateNewGeneration();
};

/*
a constructor. Through the mutator, below, we'll sanitize rule and then
convert it to our internal representation. We also need to establish the
seed: a single 1 in a sea of 0s (in this assignment a 1 means an asterisk, '*',
and a 0 means a blank, ' '.  This is accomplished more directly by setting thisGen
to "*" and extremeBit to " ".
*/
Automaton::Automaton(int rule)
{
	resetFirstGen();
	setDisplayWidth(CONSTRUCTOR_INT);
}


/*
This returns a string consisting of the current generation,
thisGen, but does so by embedding it in a returnString whose
length is exactly displayWidth long. If thisGen is smaller
than displayWidth, it is positioned in the center of the larger
returnString, with the excess padded by extremeBit characters.
If thisGen is longer than displayWidth, it has to be truncated
(on both ends) so that it is perfectly centered in the returned
returnString, any excess trimmed off both ends, equally.
*/


string Automaton::toStringCurrentGen() //just string
{
	string returnString = thisGen;

	int stringSize = returnString.length(); //length of thisGen
	int cap = 0;
	int stringWidth = 0;

	while (stringSize != displayWidth)
	{
		if (stringSize < displayWidth) //positioned in the center of the larger
		//returnString, with the excess padded by extremeBit characters.
		{
			returnString = extremeBit + returnString;
			//	cout << returnString;
		}

		if (stringSize > displayWidth)//it has to be truncated
		//(on both ends) so that it is perfectly centered in the returned
		//returnString, any excess trimmed off both ends, equally.
			//string substr (size_t pos = 0, size_t len = npos) const;
			//The substring is the portion of the object that starts 
			//at character position pos and spans len characters
			//(or until the end of the string, whichever comes first).
		{
			stringWidth = (stringSize - displayWidth) / 2;
			cap = stringSize - stringWidth;
			returnString = returnString.substr(stringWidth, cap);
		}
	}
	return returnString;
}


/*
converts the int newRule, a number from 0 - 255, to an array of eight bools.
For example, if the newRule is 182, then this is the binary number 1 0 1 1 0 1 1 0,
which means that the resultant array will be
rule[7] = true,
rule[6] = false,
rule[5] = true,
rule[4] = true,
rule[3] = false,
rule[2] = true,
rule[1] = true,
rule[0] = false.
I have color coded two of the bits in 182 and their corresponding bools
in the array rule[] so you can easily see how the conversion needs to work.
As usual, this must sanitize the int so that only values in the legal
range 0 - 255 are allowed.
*/

bool Automaton::setRule(int newRule)
{
	if (newRule < 0 || newRule > 256)
	{
		return false;
	}
	for (int i = 0; i < RULES_SIZE; i++)
	{
		//bitwise operators can work on decimal ints too! No need to convert newRule beforehand.
		//01001000 & 10111000 = 00001000. AND will only return "1" if both bits are "1". 
		//The leftshift (<<) operator is the equivalent of moving all the bits of a number a specified number of places to the left. [variable]<<[number of places].
		//Shifting to then left is also equivalent to multiplying by a power of 2. 1 << i is 1 shifted left i times, or 1 * 2^i
		//Compare the binary of number newRule and 1 with &, for each i in the array. It will only return a 1 if both compared are 1(&) otherwise, 0. 

		rules[i] = (newRule & (1 << i)) != 0;

		//cout << rules[i] << "  " << i << "  " << "should end here" << endl;
	}
	return true;
}


void Automaton::resetFirstGen()
{
	extremeBit = " "; //0
	thisGen = "*"; //1
}


/*
this is described by the earlier description of displayWidth and MAX_DISPLAY_WIDTH.
I repeat that only odd widths are allowed (for centering purposes).
*/
bool Automaton::setDisplayWidth(int width)
{
	if (width > MAX_DISPLAY_WIDTH || width < 0 || (width % 2 == 0) /*even*/)
	{
		return false;
	}

	displayWidth = width;
	return true;
}


/*
this is the workhorse function.  It will use the three private members thisGen,
extremeBit and rule[], and create the next generation from them.
This method must first append two extremeBits to each side of thisGen in order
to provide it with enough bits (or chars) on each end needed by rule.
This adds four chars to thisGen, temporarily. We then apply rule in a loop
to the new, larger, thisGen, which creates a separate (local) nextGen string.
If you do this correctly, nextGen will be two characters smaller than the
recently augmented thisGen (but still two larger than the original thisGen
that entered the method). You must understand this statement, conceptually,
before you write your first line of code, or you will be doomed. Then, you
replace the old thisGen with our new nextGen.
*/
void Automaton::propagateNewGeneration() //workhorse (last) ABCDEFG
{

}

//main just put in automaton (number initialize to)
//callprop in a loop


int main()
{

	int rule = 3;
	Automaton automatonObject(rule);

	cout << automatonObject.setRule(48) << endl;

	//if (automatonObject.setDisplayWidth(1) == true) //that int means something!
	//{
	//	cout << "true" << endl;
	//}
	//else
	//{
	//	cout << "false" << endl;
	//}

//	cout << automatonObject.toStringCurrentGen() << endl;

	return 0;
}



//make new automaton makestuff call reset print again .stuff