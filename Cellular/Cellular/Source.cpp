#include <iostream>
#include <string>

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

	Automaton(int rule);
//	string toStringCurrentGen();
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

	string thisGen = "*"; // 1 means *
	string extremeBit = " "; // 0 means blank

	//use "0" and "1" to reset gen?
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


/*
string Automaton::toStringCurrentGen() //just string
{
	string returnString = thisGen;

	int stringSize = returnString.length(); //length of thisGen
	int stringWidth = 0;

	if (stringSize < displayWidth) //positioned in the center of the larger 
		//returnString, with the excess padded by extremeBit characters.
	{
		returnString = returnString + extremeBit;
	}

	if (stringSize > displayWidth)//it has to be truncated 
		//(on both ends) so that it is perfectly centered in the returned
		//returnString, any excess trimmed off both ends, equally.
	{
		stringWidth = (stringSize - displayWidth) / 2;
	}

	return returnString;
}
*/

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

bool Automaton::setRule(int newRule)/////////////////////////////////////
{
	return true;
}


void Automaton::resetFirstGen()
{
	//strings not ints
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
		return false;

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
void Automaton::propagateNewGeneration() //workhorse (last)
{

}

//main just put in automaton (mumber initialize to)
//callprop in a loop


int main()
{

	int rule = 3;
	Automaton automatonObject(rule);

	if (automatonObject.setDisplayWidth(2) == true) //that int means something!
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

	return 0;
}



//make new automaton makestuff call reset print again .stuff