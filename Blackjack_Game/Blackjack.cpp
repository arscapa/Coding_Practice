#include <iostream>
#include <array>
#include <ctime>

enum CardRank 
{
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,
	MAX_RANK
};

enum GameResult
{
	BLACKJACK_WIN = 1,
	BLACKJACK_LOSS = 0,
	BLACKJACK_TIE = -1,
};

enum CardSuit 
{
	SUIT_CLUB,
	SUIT_DIAMOND,
	SUIT_HEART,
	SUIT_SPADE,
	MAX_SUIT
};

struct Card 
{
	CardRank rank;
	CardSuit suit;
};

void printCard(const Card card)
{
	switch (card.rank)
	{
		case RANK_2:		std::cout << '2'; break;
		case RANK_3:		std::cout << '3'; break;
		case RANK_4:		std::cout << '4'; break;
		case RANK_5:		std::cout << '5'; break;
		case RANK_6:		std::cout << '6'; break;
		case RANK_7:		std::cout << '7'; break;
		case RANK_8:		std::cout << '8'; break;
		case RANK_9:		std::cout << '9'; break;
		case RANK_10:		std::cout << "Ten"; break;
		case RANK_JACK:		std::cout << "Jack"; break;
		case RANK_QUEEN:	std::cout << "Queen"; break;
		case RANK_KING:		std::cout << "King"; break;
		case RANK_ACE:		std::cout << "Ace"; break;
	}
	
	std::cout << " of ";
	
	switch (card.suit)
	{
		case SUIT_CLUB:		std::cout << "Clubs"; break;
		case SUIT_DIAMOND:	std::cout << "Diamonds"; break;
		case SUIT_HEART:	std::cout << "Hearts"; break;
		case SUIT_SPADE:	std::cout << "Spades"; break;	
	}

};

int getCardValue(const Card &card, int &aceCount)
{	
	switch (card.rank)
	{
		case RANK_2:		return 2; 
		case RANK_3:		return 3;
		case RANK_4:		return 4; 
		case RANK_5:		return 5; 
		case RANK_6:		return 6; 
		case RANK_7:		return 7; 
		case RANK_8:		return 8; 
		case RANK_9:		return 9; 
		case RANK_10:		return 10; 
		case RANK_JACK:		return 10; 
		case RANK_QUEEN:	return 10; 
		case RANK_KING:		return 10; 
		case RANK_ACE:	    
							aceCount++;
							return 11; 
	}
};

void swapCard(Card &a, Card &b)
{
	Card temp = a;
	a = b;
	b = temp;
};

// Generate random number between min and max (inclusive)
// Assumes srand() has already been called
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);		// static used for efficiency, so we only calculate this value once
	// evenly distribute the random number across our range
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
};

void shuffleDeck(std::array<Card,52> &deck)
{
	for(int i=0; i < 52; i++)
	{
		// Generate a random number between 1-52
		int swapIndex = getRandomNumber(0,51);
		
		// Swap cards
		swapCard(deck[i],deck[swapIndex]);
	}
};

void printDeck(const std::array<Card, 52> &deck)
{
	for (const auto &card : deck)
	{
		printCard(card);
		std::cout << ' ';
	}
 
	std::cout << '\n';
}

bool hit()
{
	std::cout << "\nWould you like to hit (y/n)? ";
	char response;
	std::cin >> response;
	
	if(response == 'y' || response == 'Y'){
		return true;
	}
	if(response == 'n' || response == 'N'){
		return false;
	}
	else{
		hit();
	};
}

GameResult playBlackjack(std::array<Card,52> &deck)
// GameResult type b/c game will return GameResult enum value
{
	int playerScore = 0;
	int playerAceCount = 0;
	
	int dealerScore = 0;
	int dealerAceCount = 0;

	
	
	const Card *cardPtr = &deck[0];
	
	// Deal 1 card to dealer and increment cardPtr
	std::cout << "The dealer is showing:" << std::endl;
	printCard(*cardPtr);
	std::cout << "\n";
	
	// Update dealer score and increment ptr
	dealerScore += getCardValue(*cardPtr++,dealerAceCount);
	
	// Deal 2 cards to player
	std::cout << "\nYou've been dealt:" << std::endl;
	printCard(*cardPtr);
	std::cout << "\n";
	playerScore += getCardValue(*cardPtr++,playerAceCount);
	printCard(*cardPtr);
	std::cout << "\n";
	playerScore += getCardValue(*cardPtr++,playerAceCount);
	
	// Play user hand
	while(hit())
	{
		std::cout << "You've been dealt:" << std::endl;
		printCard(*cardPtr);
		std::cout << "\n";
		playerScore += getCardValue(*cardPtr++,playerAceCount);
		
		if(playerScore > 21 && playerAceCount > 0)
			{	
				do{
					playerScore -=10;
					playerAceCount--;
				}while(playerAceCount>0);
			}
		if(playerScore > 21)
			{	
				std::cout << "BUST! You have " << playerScore << std::endl;
				return BLACKJACK_LOSS;
			}
		std::cout << "You have " << playerScore << std::endl;
	};
	
		
	// Play dealer hand 
	std::cout << "Playing dealer hand..." << std::endl;
	
	while(dealerScore < 17)
	{
		// Draw a card, dealer must hit if under 17
		dealerScore += getCardValue(*cardPtr++,dealerAceCount);
		
		// Check if dealer went over 21
		if(dealerScore > 21 && dealerAceCount > 0)
			{	
				do{
					dealerScore -= 10;
					dealerAceCount--;
				}while(dealerAceCount>0);
			}
		if(dealerScore > 21)
			{	
				std::cout << "YOU WIN with " << playerScore << "! The dealer went over 21" << std::endl;
				return BLACKJACK_WIN;
			}
	}
	
	// Determine winner
	if (playerScore > dealerScore)
	{
		std::cout << "The dealer has " << dealerScore << ". YOU WIN!" << std::endl;
		return BLACKJACK_WIN;
	}
	if (playerScore == dealerScore)
	{
		std::cout << "Both the dealer and you have " << dealerScore << ". You've tied. Push" << std::endl;
		return BLACKJACK_LOSS;	
	}
	 else {
		std::cout << "The dealer has " << dealerScore << ". You lose :(" << std::endl;
		return BLACKJACK_TIE;
	};
	
	
}

bool playAgain()
{
	std::cout << "\nWould you like to play again (y/n)? ";
	char response;
	std::cin >> response;
	
	if(response == 'y' || response == 'Y'){
		return true;
	}
	if(response == 'n' || response == 'N'){
		return false;
	}
	else{
		playAgain();
	};
}


int main()
{
	do
	{
		srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
		rand();	
	
		// Create deck of 52 cards
		std::array<Card, 52> deck;
	
		int card = 0;
		for(int suit = 0; suit < MAX_SUIT; suit++)
		for(int rank = 0; rank < MAX_RANK; rank++)
		{
			deck[card].suit = static_cast<CardSuit>(suit);
			deck[card].rank = static_cast<CardRank>(rank);
			card++;
		}
	
		// Shuffle Deck
		shuffleDeck(deck);
	
		// Play game
		playBlackjack(deck);
	
		} while(playAgain());
	
	return 0;
}
