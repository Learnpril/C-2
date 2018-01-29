/*April Young, Assignment 2, W18 CS F002B 01Y Interm Software Design C++. Professor: Joanna Lankester */

#include <cstdlib> //for randomizing shuffle
#include <time.h> //for randomizing shuffle
#include <iostream>
#include <string>


using namespace std;

class Card
{
public:
	enum Suit { clubs, diamonds, hearts, spades };

	Card(char value = 'A', Suit suit = spades);
	string toString();
	bool set(char value, Suit suit);
	Suit getSuit() const { return suit; }
	char getValue() const { return value; }
	bool getErrorFlag() const { return errorFlag; }
	bool equals(Card card) const;

private:
	Suit suit; //{ clubs, diamonds, hearts, spades }
	char value; //('A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K')
	bool errorFlag;
	static bool isValid(char value, Suit suit);
};


class Hand
{
public:

	static const int MAX_CARDS = 30;

	Hand();
	void resetHand();
	bool takeCard(Card card);
	Card playCard();
	string toString();
	int getNumCard() const { return numCards; }
	Card inspectCard(int k);

private:
	Card myCards[MAX_CARDS];
	int numCards;
};



class Deck
{
public:
	Deck(int numPacks);
	bool init(int numPacks);
	void shuffle();
	Card dealCard();
	int getTopCard() const { return topCard; }
	Card inspectCard(int k);

private:
	static const int MAX_PACKS = 6;
	static const int NUM_CARDS_PER_PACK = 52;
	static const int MAX_CARDS_PER_DECK = MAX_PACKS * NUM_CARDS_PER_PACK;

	static Card masterPack[NUM_CARDS_PER_PACK];
	Card cards[MAX_CARDS_PER_DECK];
	int topCard;
	int numPacks;
	static void allocateMasterPack();
	static bool masterPackBeenBefore;
};


//////////////

Card::Card(char value, Suit suit)
{
	set(value, suit);
}

string Card::toString()
{
	string errorLabel = "[ illegal ]";

	if (errorFlag)
		return errorLabel;

	//string(1, value) prints the value to concatenate with "of"
	string labelSuit = string(1, value) + " of ";
	switch (suit)
	{
	case spades:
		labelSuit += "Spades";
		break;
	case hearts:
		labelSuit += "Hearts";
		break;
	case diamonds:
		labelSuit += "Diamonds";
		break;
	case clubs:
		labelSuit += "Clubs";
		break;
	default:
		labelSuit += "ERROR";
		break;
	}
	return labelSuit;
}

bool Card::set(char value, Suit suit)
{
	if (isValid(value, suit))
	{
		errorFlag = false;

		this->suit = suit;
		this->value = value;

		return true;
	}
	else
	{
		errorFlag = true;

		return false;
	}
}


bool Card::equals(Card card) const
{
	if (this->suit == card.suit && this->value == card.value)
		return true;
	return false;
}


bool Card::isValid(char value, Suit suit)
{
	value = toupper(value); //make unput CAPS
	if ((isdigit(value) && value > '2' && value < '9')
		|| value == 'A' || value == 'T' || value == 'J' || value == 'Q' || value == 'K')
	{
		return true;
	}
	return false;
}


Hand::Hand()
{
	numCards = 0;

}


void Hand::resetHand()
{
	numCards = 0;
}


bool Hand::takeCard(Card card)
{

	if (numCards >= MAX_CARDS) 
	{
		return false;
	}

	if (card.getErrorFlag() == false)
	{
		myCards[numCards] = card;
		numCards++;
	}
	return true;
}


Card Hand::playCard()
{
	if (numCards <= 0)

		return Card('#', Card::spades); //error

	Card tempSlot = myCards[numCards - 1]; //take away card
	numCards--;

	return  tempSlot;
}

string Hand::toString()
{
	string handString = "Hand = ";

	for (int i = 0; i < numCards; i++)

		handString += myCards[i].toString() + ", ";

	return handString;
}

Card Hand::inspectCard(int k)
{
	if (k > numCards || k < 0)
	{
		return Card('#', Card::spades); // return error card
	}
	return myCards[k];
}


////////////////////////////////////////////////////////////////////////////////////DECK

Card Deck::masterPack[NUM_CARDS_PER_PACK];

bool Deck::masterPackBeenBefore = false; //bool for allocateMasterPack();


//a constructor that populates the arrays and assigns initial values to members.
Deck::Deck(int numPacks = 1)
{
	if (masterPackBeenBefore == false)
	{
		allocateMasterPack(); //populate cards if it hasn't been allocated before
	}

	if (init(numPacks) == false)
	{
		topCard = 0; //topCard is like numCards for Deck Class
	}
}


/*
re-populate cards[] with the standard 52 × numPacks cards.  
We should not repopulate the static array, masterPack[], since 
that was done once, in the (first-invoked) constructor and  never 
changes.  If numPacks is out-of-range, return false without changing 
the object;  else return true and make the change.
*/
bool Deck::init(int numPacks = 1)
{
	topCard = numPacks * NUM_CARDS_PER_PACK;  //topCard is numCards for Deck

	if (numPacks > MAX_PACKS || numPacks <= 0)
	{
		return false;
	}
	else
	{
		//loop packs and then individual cards to populate
		for (int i = 0; i < numPacks; i++) //packs i
		{
			for (int j = 0; j < NUM_CARDS_PER_PACK; j++) //cards j
				cards[(i * NUM_CARDS_PER_PACK) + j] = masterPack[j];
		}
		return true;
	}
}

/*mixes up the cards with the help of the standard random number generator.*/
void Deck::shuffle()
{
	Card tempSlot = Card('A', Card::spades);
	srand(time(0));


	for (int i = 0; i <= topCard; i++) //remember topCard is like numCard. Count that instead of 52.
	{
		int randomizer = rand() % topCard; //put INSIDE loop
		tempSlot = cards[i];
		cards[i] = cards[randomizer];
		cards[randomizer] = tempSlot;
	}
}


/*returns and removes (effectively, not physically) the card in the top occupied position of cards[].*/
Card Deck::dealCard()
{
	if (topCard <= 0)
	{
		return Card('#', Card::spades); //error
	}

	Card tempSlot = cards[topCard - 1]; //take away card, topCard is like numCards
	topCard--;

	return  tempSlot;
}


/*Accessor for an individual card.  Returns a card with errorFlag = true if k is bad.*/
Card Deck::inspectCard(int k)
{
	if (k > topCard || k < 0 ) //topCard is numCard for Deck.
	{
		return Card('#', Card::spades); // return error card
	}
	return cards[k];
}


/*  
this is a method that will be called by the constructor.  
However, it has to be done with a very simple twist:  
even if many Deck objects are constructed in a given program, 
this static method will not allow itself to be executed more than once.  
Since masterPack[] is a static, unchanging, entity, it need not be 
built every time a new Deck is instantiated.  So this method needs 
to be able to ask itself, "Have I been here before?", and if the answer is "yes", 
it will immediately return without doing anything;  
it has already built masterPack[] in a previous invocation. 
*/
void Deck::allocateMasterPack()
{
	Card::Suit valueSuit;
	char valueChar;
	int i;
	int j;

	for (i = 0; i < 4; i++) //suit
	{
		valueSuit = (Card::Suit)i;
		masterPack[13 * i].set('A', valueSuit);

		for (valueChar = '2', j = 1; valueChar <= '9'; valueChar++, j++)
		{
			masterPack[13 * i + j].set(valueChar, valueSuit); //2-9 because of j counting up (ref from module)
			masterPack[13 * i + 9].set('T', valueSuit);
			masterPack[13 * i + 10].set('J', valueSuit);
			masterPack[13 * i + 11].set('Q', valueSuit);
			masterPack[13 * i + 12].set('K', valueSuit);
		}
	}
}


int main(int argc, const char * argv[])
{
	/////deck


cout << "deck1: " << endl;

Deck deck1 = Deck(2);


cout << "deck2: " << endl;

Deck deck2;

cout << "deck3: " << endl;

Deck deck3 = Deck(-500);

cout << "deck3 topCard: " << deck3.getTopCard() << endl;



cout << deck2.inspectCard(20).toString() << endl;

cout << deck2.inspectCard(3).toString() << endl << endl << endl;


int numCards = deck1.getTopCard();

while(numCards > 0)
{

cout << deck1.dealCard().toString() << endl;

numCards--;

}

deck2.init();

cout << endl;
cout << "shuffle the deck: " << endl << endl;

deck2.shuffle();

numCards = deck2.getTopCard();

while(numCards > 0) {

cout << deck2.dealCard().toString() << endl;

numCards--;

}



// ************** test interaction with Hand ***********

Deck deck4;

int numPlayers = 0;

const int MIN_PLAYERS = 1;

const int MAX_PLAYERS = 10;

Hand hands[MAX_PLAYERS];

do
{

	cout << "How many players? Range: " << MIN_PLAYERS << " to " << MAX_PLAYERS << ": " ;
	cin >> numPlayers;

}

while (numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS);



// you are not required to write these as separate functions.

// you should write the test code needed to make your output look like mine.

//playGame(deck4, hands, numPlayers);
// deal cards to hands

//printHands(hands, numPlayers);

//resetHands(hands, numPlayers);

deck4.init();

deck4.shuffle();

//playGame(deck4, hands, numPlayers);

//printHands(hands, numPlayers);


cout << " ***** end of professor test cases *****" << endl;

cout << "Call test";


// Add any further test cases needed here


Hand player[MAX_PLAYERS];


for (int i = 1; i <= numPlayers; i++)
{
	cout << i << endl;
	player[i].toString();
	cout << endl << endl << endl;
}

return 0;

}


/*
///////////////////////////////////////////////////////////////////////

OUTPUT:
----------------------------------------------------------------------------------------


deck1:
deck2:
deck3:
deck3 topCard: 0
8 of Diamonds
4 of Clubs


K of Spades
Q of Spades
J of Spades
T of Spades
[ illegal ]
8 of Spades
7 of Spades
6 of Spades
5 of Spades
4 of Spades
3 of Spades
[ illegal ]
A of Spades
K of Hearts
Q of Hearts
J of Hearts
T of Hearts
[ illegal ]
8 of Hearts
7 of Hearts
6 of Hearts
5 of Hearts
4 of Hearts
3 of Hearts
[ illegal ]
A of Hearts
K of Diamonds
Q of Diamonds
J of Diamonds
T of Diamonds
[ illegal ]
8 of Diamonds
7 of Diamonds
6 of Diamonds
5 of Diamonds
4 of Diamonds
3 of Diamonds
[ illegal ]
A of Diamonds
K of Clubs
Q of Clubs
J of Clubs
T of Clubs
[ illegal ]
8 of Clubs
7 of Clubs
6 of Clubs
5 of Clubs
4 of Clubs
3 of Clubs
[ illegal ]
A of Clubs
K of Spades
Q of Spades
J of Spades
T of Spades
[ illegal ]
8 of Spades
7 of Spades
6 of Spades
5 of Spades
4 of Spades
3 of Spades
[ illegal ]
A of Spades
K of Hearts
Q of Hearts
J of Hearts
T of Hearts
[ illegal ]
8 of Hearts
7 of Hearts
6 of Hearts
5 of Hearts
4 of Hearts
3 of Hearts
[ illegal ]
A of Hearts
K of Diamonds
Q of Diamonds
J of Diamonds
T of Diamonds
[ illegal ]
8 of Diamonds
7 of Diamonds
6 of Diamonds
5 of Diamonds
4 of Diamonds
3 of Diamonds
[ illegal ]
A of Diamonds
K of Clubs
Q of Clubs
J of Clubs
T of Clubs
[ illegal ]
8 of Clubs
7 of Clubs
6 of Clubs
5 of Clubs
4 of Clubs
3 of Clubs
[ illegal ]
A of Clubs

shuffle the deck:

6 of Hearts
5 of Clubs
6 of Clubs
T of Clubs
T of Spades
3 of Hearts
K of Clubs
[ illegal ]
8 of Clubs
8 of Spades
J of Spades
Q of Clubs
8 of Hearts
6 of Diamonds
Q of Spades
A of Hearts
J of Clubs
7 of Clubs
4 of Spades
4 of Diamonds
K of Hearts
7 of Hearts
[ illegal ]
5 of Diamonds
3 of Diamonds
7 of Spades
3 of Spades
A of Spades
T of Hearts
[ illegal ]
7 of Diamonds
[ illegal ]
K of Diamonds
5 of Spades
8 of Diamonds
6 of Spades
4 of Hearts
5 of Hearts
A of Clubs
J of Diamonds
K of Spades
3 of Clubs
T of Diamonds
A of Diamonds
A of Spades
Q of Hearts
Q of Diamonds
[ illegal ]
[ illegal ]
[ illegal ]
[ illegal ]
4 of Clubs
How many players? Range: 1 to 10: 4
***** end of professor test cases *****
Call test1



2



3



4





*/