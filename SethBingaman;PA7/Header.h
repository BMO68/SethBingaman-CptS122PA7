/* */

#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#endif

void print_rules();

void play_game();

void menu_loop();

//void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[]);
//
//void shuffle(int wDeck[][13]);

typedef struct card {
	int face;
	int suit;

} Card;



typedef struct player {
	int player_hand[5];
	int suitfrequency[4];
	int facefrequency[13];
	int points;

} Player;

typedef struct deck {
	Card deck[52];
	int taken_cards[52];

}Deck;

void initialize_deck(Deck* deck);

void receive_hand(Player *player1, Player* house, Deck deck[]);

void switch_cards(int choice_card, Player* player1, Deck deck[]);

void show_dealer_hand(Deck* deck, Player* house);

void get_best_hand(Deck* deck, Player* player1);

void dealer_evaluation(Player* player, Deck* deck);

void evaluate_points(Deck deck, Player* player);

int royal_flush(Player* player);

int straight_flush(Player* player);

int four_of_a_kind(Player* player);

int full_house(Player* player);

int flush(Player* player);

int straight(Player* player);

int three_of_a_kind(Player* player);

int two_pair(Player* player);

int one_pair(Player* player);

void is_win(Player* player, Player* house);

void wins_with(Player* player);