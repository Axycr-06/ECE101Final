/*
Author: Shane Dyke

Due Date: 2025-05-07

Course: ECE 101

Final Project: UNO digital card game

Description: This program simulates a simplified version of the UNO card game. It initializes a deck of cards, shuffles them, and deals cards to players. The program allows for multiple players and handles the drawing of cards from the deck.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct card_t{
   
   char name; //’0’-‘9’ for number cards, ‘A’ for AND, ‘O’ for OR, ‘N’ for NOT, and ‘R’ for Reverse.

   char color; //’R’ for red, ‘Y’ for yellow, ‘G’ for green, ‘B’ for blue, and ‘S’ for special cards

} card;

typedef struct player_t{
   char playerName[20]; //name of the player
   
   card *deck; //pointer to the player's hand of cards
   
   int decksize; //size of the player's hand

} player;

void initializeDeck(card cards[]) {
   //Create deck of 100 cards
   //two sets of 0-9 cards of each color
   //5 of each special card

   char colors[4] = {'R', 'Y', 'G', 'B'};
   char special[4] = {'A', 'O', 'N', 'R'};

   //loop 4 time for 4 colors
   //loop 20 times for 20 0-9 cards
   for(int i = 0; i < 4; ++i){
      for(int j = 0; j < 20; ++j){
         cards[i * 20 + j].name = j % 10 + '0'; //0-9
         cards[i * 20 + j].color = colors[i]; //R, Y, G, B
      }
   }

   //create special cards
   for(int i=0; i<5; ++i){
      for(int j=0; j<4; ++j){
         cards[80 + i * 4 + j].name = special[j]; //A, O, N, R
         cards[80 + i * 4 + j].color = 'S'; //special
      }
   }
}

// Function to shuffle the deck of cards
void shuffleDeck(card deck[]) {
   //shuffle 10000 times as per the requirement
   for (int i = 0; i < 10000; ++i) {
      int index1 = rand() % 100; // Generate a random index
      int index2 = rand() % 100; // Generate another random index
      // Swap the cards at the two random indices
      card temp = deck[index1];
      deck[index1] = deck[index2];
      deck[index2] = temp;
   }
}

// Draw a single card from the deck and place it in a player's hand. Return 1 if the draw was successful, 0 if deck is empty.
int drawCard(card deck[], int *deckSize, player p){
   if(deckSize == 0){ //if deck is empty
      return 0; //return 0
   }
   p.deck[p.decksize] = deck[*deckSize - 1]; //draw card from deck and place in player's hand
   p.decksize++; //increment player's hand size
   *deckSize--; //decrement deck size
   return 1; //return 1 for success
}


int main(void) {

   int deckSize = 100; //size of the deck
   card *cards = malloc(deckSize * sizeof(card)); //create deck of cards

   initializeDeck(cards); //create the deck

   srand(time(NULL)); //seed the random number generator

   shuffleDeck(cards); //shuffle the deck
   

   //deal 7 cards to each player
   printf("Enter number of players: ");
   int numPlayers;

   scanf("%d", &numPlayers); //get number of players
   player *players = malloc(numPlayers * sizeof(player)); //create array of players
   for (int i = 0; i < numPlayers; ++i) {
      players[i].deck = malloc(7 * sizeof(card)); // allocate memory for each player's hand
      players[i].decksize = 0; // initialize deck size
   }

   for(int i = 0; i < numPlayers; ++i) {
      printf("Enter name of player %d: ", i + 1); //get player name
      scanf("%s", players[i].playerName); //store player name
      
      players[i].decksize = 0; //initialize deck size
      for(int j = 0; j < 7; ++j) { //deal 7 cards to each player
         if(drawCard(cards, deckSize, players[i]) == 0){ //draw card from deck
            printf("Deck is empty\n"); //if deck is empty
            break; //break out of loop
         }
      }

   }

   for(int i=0; i<numPlayers; ++i){
      printf("%s's hand:\n", players[i].playerName); //print player name

   }





   return 0;
}
