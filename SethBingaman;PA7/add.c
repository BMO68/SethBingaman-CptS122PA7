/* */

#include "Header.h"


void menu_loop()
{

	srand((unsigned)time(NULL)); /* seed random-number generator */ 

	int condition = 0;
	while (condition != 3)
	{
		printf("1) Print Rules \n2) Play Game \n3) Quit \n");
		scanf("%d", &condition);
		switch (condition)
		{
		case 1:
			print_rules();
			break;
		case 2:
			play_game();
			break;
		}
	}
	exit(0);
}

void print_rules()
{
	printf("In poker, players form sets of five playing cards, called hands. The order \n");
	printf("of scoring goes from highest to lowest: Five of a kind, Straight Flush\n");
	printf("Four of a Kind, Full House, Flush, Straight, Three of a Kind, Two Pair, One Pair\n");
	printf("and High Card");
	system("cls");
}


void receive_hand(Player* player1,Player* house, Deck deck[])
{
	 //0 is available, 1 is taken
	int hand_count = 0;
	while (hand_count != 5) //41, 7, 42, 32, 33
	{
		int random = rand() % 52;
		if (deck->taken_cards[random] != 1)
		{
			player1->player_hand[hand_count] = random;
			deck->taken_cards[random] = 1;
			hand_count++;
		}
	}
	hand_count = 0;
	while (hand_count != 5)
	{
		int random = rand() % 52;
		if (deck->taken_cards[random] != 1)
		{
			house->player_hand[hand_count] = random;
			deck->taken_cards[random] = 1;
			hand_count++;
		}
	}
}

void play_game()
{

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initializes suit array */
	const char* suitarray[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };


	/* initalize deck array */
	Deck deck;


	initialize_deck(&deck);

	Player player1;
	player1.player_hand;
	Player house;
	house.player_hand;

	//printf("Play Game?\n");


	receive_hand(&player1, &house, &deck);

	get_best_hand(&deck, &player1);

	dealer_evaluation(&house, &deck);

	evaluate_points(deck, &player1);

	evaluate_points(deck, &house);

	show_dealer_hand(&deck, &house); 

	is_win(&player1, &house);

}

void get_best_hand(Deck* deck, Player* player1)
{

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initializes suit array */
	const char* suitarray[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	//display hand to player
	int count = 0, cardswitch = 0;
	char choice = 'Y';
	Card currentCard = deck->deck[player1->player_hand[0]]; //face=10, suit=1
	while (choice == 'Y' && count < 3)
	{
		printf("Your hand: \n");
		currentCard = deck->deck[player1->player_hand[0]];
		printf("1) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
		currentCard = deck->deck[player1->player_hand[1]];
		printf("2) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
		currentCard = deck->deck[player1->player_hand[2]];
		printf("3) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
		currentCard = deck->deck[player1->player_hand[3]];
		printf("4) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
		currentCard = deck->deck[player1->player_hand[4]];
		printf("5) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
		printf("Would you like to replace a card? Y/N: \n");
		scanf(" %c", &choice);

		int count2 = 0;
		while (choice == 'Y' && count2 == 0)
		{
			printf("Which card would you like to replace?: \n"); //add 1) 2) 3) 4) 5)
			scanf(" %d", &cardswitch);
			switch_cards(cardswitch, player1, deck); //add parameters) 
			count2++;
		}
		count++;
	}

	printf("Your hand: \n");
	currentCard = deck->deck[player1->player_hand[0]];
	printf("1) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
	currentCard = deck->deck[player1->player_hand[1]];
	printf("2) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
	currentCard = deck->deck[player1->player_hand[2]];
	printf("3) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
	currentCard = deck->deck[player1->player_hand[3]];
	printf("4) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
	currentCard = deck->deck[player1->player_hand[4]];
	printf("5) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);

}

void show_dealer_hand(Deck* deck, Player* house)
{

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initializes suit array */
	const char* suitarray[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	Card currentCard = deck->deck[house->player_hand[0]]; //face=10, suit=1

	printf("Dealer's hand: \n");
	currentCard = deck->deck[house->player_hand[0]];
	printf("1) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
	currentCard = deck->deck[house->player_hand[1]];
	printf("2) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
	currentCard = deck->deck[house->player_hand[2]];
	printf("3) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
	currentCard = deck->deck[house->player_hand[3]];
	printf("4) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
	currentCard = deck->deck[house->player_hand[4]];
	printf("5) %s, %s\n", suitarray[currentCard.suit], face[currentCard.face]);
}

void card_frequency(Deck deck, Player* player) //output for suit and face; maybe I won't need to use this 
{

	player->points = 0;

	for (int i = 0; i < 4; i++)
	{
		player->suitfrequency[i] = 0;
	}
	for (int i = 0; i < 13; i++)
	{
		player->facefrequency[i] = 0;
	}

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initializes suit array */
	const char* suitarray[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	// Tracking the suits, suitsFreq[4] for(int = 0, int < 5, i++) in the loop, check for suit depending on suit num, we suitsFreq[number] = {0,1,1,3}

	// Royal flush  = all same suit, 10 J Q K A, does suitsFreq have a element that is 5, and numFreq[13], indexes 8-12 are all 1,
	 

	for (int i = 0; i < 5; i++) //for some reason, player* to facefrequency and suitfrequency are not updating through sequential initilization
	{
		int suitindex = deck.deck[player->player_hand[i]].suit;
		player->suitfrequency[suitindex]++;

		int faceindex = deck.deck[player->player_hand[i]].face;
		player->facefrequency[faceindex]++;
	}
}

int royal_flush(Player* player)
{
	int suit = 0;
	for (int i = 0; i < 4; i++)
	{
		if (player->suitfrequency[i] == 5) { suit++; }
	}

	if (player->facefrequency[0] == 1 && player->facefrequency[9] == 1 && player->facefrequency[10] == 1 && player->facefrequency[11] == 1 && player->facefrequency[12] == 1 && suit == 1)
	{
		return 1;
	}

	return 0;
}

int straight_flush(Player* player)
{
	int flagsuit = 0;
	int straight = 0;

	for (int i = 0; i < 4; i++)
	{
		if (player->suitfrequency[i] == 5) { flagsuit++; }
	}
	
	for (int j = 0; j < 13; j++)
	{
		if (player->facefrequency[j] == 1) { straight++; }
		if (player->facefrequency[j] == 0) { straight = 0; }
	}

	if (flagsuit == 1 && straight == 5) { return 1; }
	return 0;
}

int four_of_a_kind(Player* player)
{
	int faceflag = 0; 
	for (int i = 0; i < 13; i++)
	{
		if (player->facefrequency[i] == 4) { faceflag++; }
	}

	if (faceflag == 1) { return 1; }
	return 0;
}

int full_house(Player* player)
{
	int threepairflag = 0, twopairflag = 0;
	for (int i = 0; i < 13; i++) 
	{
		if (player->facefrequency[i] == 3) { threepairflag++; }
		if (player->facefrequency[i] == 2) { twopairflag++; }
	}
	if (threepairflag == 3 && twopairflag == 2) { return 1; }
	return 0;
}

int flush(Player* player)
{
	int suitflag = 0;
	for (int i = 0; i < 4; i++)
	{
		if (player->suitfrequency[i] == 5) { suitflag++; }
	}
	if (suitflag == 1) { return 1;}
	return 0;
}

int straight(Player* player)
{
	int straightflag = 0;
	for (int i = 0; i < 13; i++)
	{
		if (player->facefrequency[i] == 1) { straightflag++; }
		if (player->facefrequency[i] == 0) { straightflag = 0; }
	}
	if (straightflag == 5) { return 1; }

	for (int i = 0; i < 5; i++) //loop split with loop beneath to go through second half of array and then the first half
	{
		if (player->facefrequency[8 + i] == 1) { straightflag++; }
		if (player->facefrequency[8 + i] == 0) { straightflag = 0; }
	}
	if (straightflag == 5) { return 1; }

	for (int i = 0; i < 5; i++)
	{
		if (player->facefrequency[i] == 1) { straightflag++; }
		if (player->facefrequency[i] == 0) { straightflag = 0; }
	}
	if (straightflag == 5) { return 1; }

	return 0;
}

int three_of_a_kind(Player* player)
{
	for (int i = 0; i < 13; i++)
	{
		if (player->facefrequency[i] == 3) { return 1; }
	}

	return 0;
}

int two_pair(Player* player)
{
	int pairflag = 0;
	for (int i = 0; i < 13; i++)
	{
		if (player->facefrequency[i] == 2) { pairflag++; }
	}
	if (pairflag == 2) { return 1; }

	return 0;
}

int one_pair(Player* player)
{
	for (int i = 0; i < 13; i++)
	{
		if (player->facefrequency[i] == 2) { return 1; }
	}

	return 0;
}

void evaluate_points(Deck deck, Player* player) //needs card_frequency first; maybe not -\('.')/-
{
	card_frequency(deck, player);
	player->points = 0;
	// 0 or 1 return functions, 1 means true 0 means false

	if (royal_flush(player) == 1 && player->points == 0)
	{
		player->points = 13;
	}
	if (straight_flush(player) == 1 && player->points == 0)
	{
		player->points = 12;
	}
	if (four_of_a_kind(player) == 1 && player->points == 0)
	{
		player->points = 11;
	}
	if (full_house(player) == 1 && player->points == 0)
	{
		player->points = 10;
	}
	if (flush(player) == 1 && player->points == 0)
	{
		player->points = 9;
	}
	if (straight(player) == 1 && player->points == 0)
	{
		player->points = 8;
	}
	if (three_of_a_kind(player) == 1 && player->points == 0) 
	{
		player->points = 7;
	}
	if (two_pair(player) == 1 && player->points == 0)
	{
		player->points = 6;
	}
	if (one_pair(player) == 1 && player->points == 0)
	{
		player->points = 5;
	}

}

void dealer_evaluation(Player* player, Deck* deck)
{
	for (int i = 0; i < 3; i++)
	{
		if (player->points == 13) { i = 3; }
		if (player->points == 12) { i = 3; }
		if (player->points == 11) { i = 3; }
		if (player->points == 10) { i = 3; }
		if (player->points == 9) { i = 3; }
		if (player->points == 8) { i = 3; }
		if (player->points == 7) { i = 3; }
		if (player->points == 6) { i = 3; }
		if (player->points == 5) { i = 3; }

		int switchcard = rand() % 5 + 1;

		switch_cards(switchcard, player, deck); 
	}
}

void switch_cards(int choice_card, Player* player1, Deck deck[])
{
	int random;
	int available = 0;
	switch (choice_card)
	{
	case 1:
		available = 0;
		while(available == 0)
		{
			random = rand() % 52;
			if (deck->taken_cards[random] != 1)
			{
				player1->player_hand[choice_card - 1] = random;
				deck->taken_cards[random] = 1;
				available++;
			}
		}
		break;

	case 2:
		available = 0;
		while (available == 0)
		{
			random = rand() % 52;
			if (deck->taken_cards[random] != 1)
			{
				player1->player_hand[choice_card - 1] = random;
				deck->taken_cards[random] = 1;
				available++;
			}
		}
		break;

	case 3:
		available = 0;
		while (available == 0)
		{
			random = rand() % 52;
			if (deck->taken_cards[random] != 1)
			{
				player1->player_hand[choice_card - 1] = random;
				deck->taken_cards[random] = 1;
				available++;
			}
		}
		break;

	case 4:
		available = 0;
		while (available == 0)
		{
			random = rand() % 52;
			if (deck->taken_cards[random] != 1)
			{
				player1->player_hand[choice_card - 1] = random;
				deck->taken_cards[random] = 1;
				available++;
			}
		}
		break;

	case 5:
		available = 0;
		while (available == 0)
		{
			random = rand() % 52;
			if (deck->taken_cards[random] != 1)
			{
				player1->player_hand[choice_card - 1] = random;
				deck->taken_cards[random] = 1;
				available++;
			}
		}
		break;
	}
}

void initialize_deck(Deck* deck)
{

	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	const char* suitarray[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	int index = 0;
	for (int i = 0; i < 13; i++)
	{

		for (int j = 0; j < 4; j++)
		{
			deck->deck[index].face = i;
			deck->deck[index].suit = j;
			index++;
		}
	}
	for (int a = 0; a < 52; a++)
	{
		deck->taken_cards[a] = 0;
	}
}

void is_win(Player* player, Player* house)
{
	if (player->points > house->points)
	{
		printf("Player 1 wins"); wins_with(player);
	}
	if (player->points < house->points)
	{
		printf("House wins"); wins_with(house);
	}
	if (player->points == house->points)
	{
		printf("Tie game\n");
	}
}

void wins_with(Player* player)
{
	if (player->points == 13)
	{
		printf(" with Royal Flush\n");
	}
	if (player->points == 12)
	{
		printf(" with Straight Flush\n");
	}
	if (player->points == 11)
	{
		printf(" with Four of a Kind\n");
	}
	if (player->points == 10)
	{
		printf(" with Full House\n");
	}
	if (player->points == 9)
	{
		printf(" with Flush\n");
	}
	if (player->points == 8)
	{
		printf(" with straight\n");
	}
	if (player->points == 7)
	{
		printf(" with Three of a Kind\n");
	}
	if (player->points == 6)
	{
		printf(" with Two Pair\n");
	}
	if (player->points == 5)
	{
		printf(" with One Pair\n");
	}
}