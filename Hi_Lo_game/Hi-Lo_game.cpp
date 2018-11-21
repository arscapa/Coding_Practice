#include <iostream>
#include <ctime>


void playGame(const int x)
{
	const int guessAllowed = x;
	int randomNum = 1 + (std::rand() % 100);
	std::cout << "Let's play a game. I'm thinking of a number. You have " << guessAllowed << " tries to guess what it is." << std::endl;
	int guessNum = 1;
	int guess;
	bool check = false;
	
	do{
		std::cout << "Guess #" << guessNum << ": ";
		std::cin >> guess;
	
		if (guess < randomNum){
			std::cout << "Your guess is too low" << std::endl;
			guessNum++;
		}
		if (guess > randomNum){
			std::cout << "Your guess is too high" << std::endl;
			guessNum++;
		}
		if (guess == randomNum) {
			check = true;
			std::cout << "Correct! You win!" << std::endl;		
		}
	} while (guessNum <= guessAllowed && check == false);
	
	if (check == false) {
		std::cout << "Sorry, you lose. The correct number was " << randomNum << std::endl;
	};
}

bool playAgain()
{
	std::cout << "Would you like to play again (y/n)? ";
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
	const int guessAllowed = 7;
	
	do 
	{
	
		playGame(guessAllowed);
	
	} while (playAgain());
	
	std::cout << "Thanks for playing." << std::endl;
	
	return 0;		 	
} 

