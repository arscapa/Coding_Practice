#include <iostream>
#include <array>
#include <ctime>
#include <cassert>



enum GameResult
{
	BLACKJACK_WIN = 1,
	BLACKJACK_LOSS = 0,
	BLACKJACK_TIE = -1,
};



class Card 
{		
	public:
	
		enum CardSuit 
		{
			SUIT_CLUB,
			SUIT_DIAMOND,
			SUIT_HEART,
			SUIT_SPADE,
			MAX_SUIT
		};
		
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
		
	private:
		CardRank m_rank;
		CardSuit m_suit;
		
	public:
		Card(CardRank rank = RANK_4 , CardSuit suit = SUIT_CLUB)
		{
			m_rank = rank;
			m_suit = suit;
		};
		
		void printCard() const
		{
			switch (m_rank)
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
	
			switch (m_suit)
			{
				case SUIT_CLUB:		std::cout << "Clubs"; break;
				case SUIT_DIAMOND:	std::cout << "Diamonds"; break;
				case SUIT_HEART:	std::cout << "Hearts"; break;
				case SUIT_SPADE:	std::cout << "Spades"; break;	
			}
		};
		
		int getCardValue(int &aceCount) const
			{	
				switch (m_rank)
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
};


class Deck
{
	private:
		std::array<Card, 52> m_deck;
		int m_cardIndex = 0;

		static void swapCard(Card &a, Card &b)
		{
			Card temp = a;
			a = b;
			b = temp;
		};
		
		static int getRandomNumber(int min, int max)
		{
			static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);		// static used for efficiency, so we only calculate this value once
			// evenly distribute the random number across our range
			return static_cast<int>(rand() * fraction * (max - min + 1) + min);
		};
	
	
	public:
		Deck()
		{
			int card = 0;
			for (int suit = 0; suit < Card::MAX_SUIT; ++suit)
			for (int rank = 0; rank < Card::MAX_RANK; ++rank)
			{
				m_deck[card] = Card(static_cast<Card::CardRank>(rank),static_cast<Card::CardSuit>(suit));
				++card;
			}
		}	
		
		void printDeck()
		{
			for (const auto &card : m_deck)
			{
				card.printCard();
				std::cout << ' ';
			}
				std::cout << '\n';
		}
		
		void shuffleDeck()
		{		
			for(int i=0; i < 52; i++)
			{
			// Generate a random number between 1-52
			int swapIndex = getRandomNumber(0,51);
		
			// Swap cards
			swapCard(m_deck[i],m_deck[swapIndex]);
			}
		
			m_cardIndex = 0;
		};
		
		const void printcurCard()
		{
			m_deck[m_cardIndex].printCard();
		}
		
		const Card& dealCard()    		// returns a const reference to current card and advances the index
		{
			assert (m_cardIndex < 52);
			return m_deck[m_cardIndex++];
		}
};




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



GameResult playBlackjack()
// GameResult type b/c game will return GameResult enum value
{
	srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
	rand(); // If using Visual Studio, discard first random value
	
	Deck deck;
	deck.shuffleDeck();
	
	int playerScore = 0;
	int playerAceCount = 0;
	
	int dealerScore = 0;
	int dealerAceCount = 0;

	
	// Deal 1 card to dealer, update score, update aceCount if any
	std::cout << "The dealer is showing:" << std::endl;
	deck.printcurCard();
	dealerScore += deck.dealCard().getCardValue(dealerAceCount);
	std::cout << "\n";
	
	// Deal 2 cards to player
	std::cout << "\nYou've been dealt:" << std::endl;
	deck.printcurCard();
	playerScore += deck.dealCard().getCardValue(playerAceCount);
	std::cout << "\n";
	deck.printcurCard();
	playerScore += deck.dealCard().getCardValue(playerAceCount);
	std::cout << "\n";



	
	// Play user hand
	while(hit())
	{
		std::cout << "You've been dealt:" << std::endl;
		deck.printcurCard();
		playerScore += deck.dealCard().getCardValue(playerAceCount);
		std::cout << "\n";
		
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
		dealerScore += deck.dealCard().getCardValue(dealerAceCount);
		
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
 	do {
 		
	 	playBlackjack();
	 	
	} while( playAgain() );
 	
	


	return 0;
    
}
