//Contine adding siginificant comments

//My girlfriend is Super Awesome!
int deckSize = 100; //number of cards in the deck
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct card_s{
   
   char name; //’0’-‘9’ for number cards, ‘A’ for AND, ‘O’ for OR, ‘N’ for NOT, and ‘R’ for Reverse.

   char color; //’R’ for red, ‘Y’ for yellow, ‘G’ for green, ‘B’ for blue, and ‘S’ for special cards

   struct card_s *listp; // pointer to the next card in the list (extra credit)

} card;

typedef struct player_s{
   char name[20]; //name of the player
   
   card *hand; //pointer to the player's hand of cards
   
   int handSize; //size of the player's hand

} player;

void CreateDeck(card cards[]){
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
         cards[i * 20 + j].listp = NULL; //set to null for now
      }
   }

   //create special cards
   for(int i=0; i<5; ++i){
      for(int j=0; j<4; ++j){
         cards[80 + i * 4 + j].name = special[j]; //A, O, N, R
         cards[80 + i * 4 + j].color = 'S'; //special
         cards[80 + i * 4 + j].listp = NULL; //set to null for now
      }
   }
}

// Function to shuffle the deck of cards
void ShuffleCard(card cards[]) {
   //shuffle 10000 times as per the requirement
   for (int i = 0; i < 10000; i++) {
      int index1 = rand() % deckSize; // Generate a random index
      int index2 = rand() % deckSize; // Generate another random index
      // Swap the cards at the two random indices
      card temp = cards[index1];
      cards[index1] = cards[index2];
      cards[index2] = temp;
   }
}

void deleteCard(card *cards, int index) {
   //delete the card at the given index
   for (int i = index; i < deckSize - 1; i++) {
      cards[i] = cards[i + 1]; //shift cards to the left
   }
   deckSize--; //decrease the size of the deck
}

void dealCard(card *cards, int index) {
   //deal the card at the given index
   printf("Dealt card: %c%c\n", cards[index].name, cards[index].color);
   deleteCard(cards, index); //delete the card from the deck
}

void printDeck(card *cards) {
   //print the deck of cards
   for (int i = 0; i < deckSize; i++) {
      printf("%c%c ", cards[i].name, cards[i].color);
   }
   printf("\n");
}


int main(void) {

   card cards[deckSize]; //create deck of cards
   CreateDeck(cards); //create the deck

   printDeck(cards); //print the deck
   ShuffleCard(cards); //shuffle the deck
   printf("Shuffled deck:\n");
   printDeck(cards); //print the shuffled deck

   //seed the random number generator
   srand(time(NULL)); //seed the random number generator

   //deal 7 cards to each player
   printf("Enter number of players: ");
   int numPlayers;

   scanf("%d", &numPlayers); //get number of players
   player *players = malloc(numPlayers * sizeof(player)); //create array of players





   return 0;
}
