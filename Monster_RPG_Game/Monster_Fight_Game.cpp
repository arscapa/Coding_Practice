#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <stdio.h>
#include <ctype.h>


// Generate a random number between min and max (inclusive)
// Assumes srand() has already been called
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
	// evenly distribute the random number across our range
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

class Creature
{
	// protected so only derived classes can access
	protected:
		std::string m_name;
		char m_symbol;
		int m_health;
		int m_damage;
		int m_gold;
		
	public:
		Creature(std::string name, char symbol, int health, int damage, int gold)
			:m_name(name), m_symbol(symbol), m_health(health), m_damage(damage), m_gold(gold)
			{
			}
			
		std::string getName(){ return m_name;}
		char getSymbol() { return m_symbol; }
		int getHealth() { return m_health; }
		int getDamage() { return m_damage; }
		int getGold() { return m_gold; } 
		
		void reduceHealth(int amt){
			m_health = m_health - amt;
		}
		
		bool isDead(){
			if(m_health <= 0){
				return true;
			}
			else
				return false;
		}
		
		void addGold(int val){
			m_gold = m_gold + val;
		}
		
		friend void levelUp(Creature);
};

class Player : public Creature
{
	private:
		int m_level = 1;
	public:
		Player(std::string name)
			: Creature(name,'@',10,1,0)
		{
		}
		
		void levelUp(){
			++m_level;
			++m_damage;
		}
		
		int getLevel() { return m_level; }
		bool hasWon() { (m_level >= 20) ? true : false; }
};

class Monster : public Creature
{
	public:
			enum Type 
			{
				DRAGON,
				ORC,
				SLIME,
				MAX_TYPES	
			};
			
			struct MonsterData
			{
				const char* name;
				char symbol;
				int health;
				int damage;
				int gold;	
			};
			
			static MonsterData monsterData[MAX_TYPES];
			
			// Constructor for monster
			Monster(Type type)
				: Creature(monsterData[type].name, monsterData[type].symbol, monsterData[type].health, monsterData[type].damage, monsterData[type].gold)
			{
			}
			
			static Monster getRandomMonster() 
			{
				int num = getRandomNumber(0,MAX_TYPES - 1);
				return Monster(static_cast<Type>(num));
			}
};

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
	{ "dragon", 'D', 20, 4, 100 },
	{ "orc", 'o', 4, 2, 25 },
	{ "slime", 's', 1, 1, 10 }
};

bool playAgain()
{
	std::cout << "\nWould you like to play again (y/n)? ";
	char response;
	std::cin >> response;
	std::cin.ignore(32767,'\n');
	
	if(tolower(response) == 'y'){
		return true;
	}
	if(tolower(response) == 'n') {
		return false;
	}
	else{
		playAgain();
	};
}

void attackPlayer(Player &p1, Monster &m1)
{
	// Monster attacks player
	p1.reduceHealth(m1.getDamage());
	std::cout << "The " << m1.getName() << " hit you for " << m1.getDamage() << ".\n";	
}

void attackMonster(Player &p1, Monster &m1)
{
	// Reduce the monster's health by the player's damage
	m1.reduceHealth(p1.getDamage());
	std::cout << "You hit the " << m1.getName() << " for " << p1.getDamage() << " damage." << std::endl;
	
	if(m1.isDead())
	{
		std::cout << "You killed the " << m1.getName() << ".\n";
		p1.levelUp();
		std::cout << "You are now a level " << p1.getLevel() << std::endl;
		std::cout << "You've taken " << m1.getGold() << " gold from the " << m1.getName() << std::endl;
		p1.addGold(m1.getGold());
	}
	else
	{
		std::cout << "The monster has attacked you" << std::endl;
		attackPlayer(p1,m1);
	}
}


void fightMonster(Player &p1)
{
		Monster m = Monster::getRandomMonster();
		std::cout << "You have encountered a " << m.getName() << " (" << m.getSymbol() << ").\n";
		char decision;

		do
		{
		std::cout << "(R)un or (F)ight: " << std::endl;
		std::cin >> decision;
		std::cin.ignore(32767,'\n');
		if(tolower(decision)=='r')
			{
				int escape = getRandomNumber(0,1);
				if(escape == 0){
					std::cout << "You've successfully fled " << std::endl;
					return;
				}
				else {
					std::cout << "You were not quick enough. The " << m.getName() << " caught up to you. " << std::endl;
					attackPlayer(p1,m);
					return;
				}
			}
		else if (tolower(decision)=='f')
			{
				attackMonster(p1,m);
				break;
			}
		else
		{
			std::cout << "Please enter an 'r' or an 'f'" << std::endl;
		}
		}while(true);
		
}



int main()
{
	// Used for generating random number
	srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
	rand(); // get rid of first result
	
	// Begin game
	std::cout << "Enter your name: " << std::endl;
	std::string name;
	std::cin >> name;
	do 
	{
		Player player1(name);
		std::cout << "Welcome, " << player1.getName() << std::endl;
	
		while(!player1.isDead() && !player1.hasWon())
			{
				fightMonster(player1);
			}
		if (player1.isDead())
			std::cout << "You died at level " << player1.getLevel() << " and with " << player1.getGold() << " gold.\n";
		else
			std::cout << "YOU WON! You've reached level " << player1.getLevel() << " and collected a total of " << player1.getGold() << " gold.\n";
	
	
	} while(playAgain());
 
	return 0;
}
