#ifndef _MTGGAMEZONES_H_
#define _MTGGAMEZONES_H_

#include <map>
using std::map;

#include "MTGDeck.h"
#include "MTGCardInstance.h"

#define MTG_MAX_PLAYER_CARDS 100

class MTGAllCards;
class MTGDeck;
class MTGCardInstance;
class Player;

class MTGGameZone {
 protected:

 public:

   enum{
    ALL_ZONES = -1,

    MY_GRAVEYARD = 11,
    OPPONENT_GRAVEYARD = 12,
    TARGET_OWNER_GRAVEYARD = 13,
    TARGET_CONTROLLER_GRAVEYARD = 14,
    GRAVEYARD = 15,
    OWNER_GRAVEYARD = 16,

    MY_BATTLEFIELD = 21,
    OPPONENT_BATTLEFIELD = 22,
    TARGET_OWNER_BATTLEFIELD = 23,
    TARGET_CONTROLLER_BATTLEFIELD = 24,
    BATTLEFIELD = 25,
    OWNER_BATTLEFIELD = 26,

    MY_HAND = 31,
    OPPONENT_HAND = 32,
    TARGET_OWNER_HAND = 33,
    TARGET_CONTROLLER_HAND = 34,
    HAND = 35,
    OWNER_HAND = 36,

    MY_EXILE = 41,
    OPPONENT_EXILE = 42,
    TARGET_OWNER_EXILE = 43,
    TARGET_CONTROLLER_EXILE = 44,
    EXILE = 45,
    OWNER_EXILE = 46,

    MY_LIBRARY = 51,
    OPPONENT_LIBRARY = 52,
    TARGET_OWNER_LIBRARY = 53,
    TARGET_CONTROLLER_LIBRARY = 54,
    LIBRARY = 55,
    OWNER_LIBRARY = 56,

    MY_STACK = 61,
    OPPONENT_STACK = 62,
    TARGET_OWNER_STACK = 63,
    TARGET_CONTROLLER_STACK = 64,
    STACK = 65,
    OWNER_STACK = 66,

   };

   Player * owner;
   //Both cards and cardsMap contain the cards of a zone. The long term objective is to get rid of the array
   vector<MTGCardInstance *> cards; //[MTG_MAX_PLAYER_CARDS];
   map<MTGCardInstance *,int> cardsMap;
   int nb_cards;
   MTGGameZone();
   ~MTGGameZone();
   void shuffle();
   void addCard(MTGCardInstance * card);
   void debugPrint();
   MTGCardInstance * removeCard(MTGCardInstance * card, int createCopy = 1);
   MTGCardInstance * hasCard(MTGCardInstance * card);
   void cleanupPhase();
   int countByType(const char * value);
   MTGCardInstance * findByName(string name);
   int hasAbility(int ability); //returns 1 if one of the cards in the  zone has the ability, 0 otherwise
   int hasType(const char * value); //returns 1 if one of the cards in the zone has the type, 0 otherwise
   int hasSpecificType(const char * value,const char * secondvalue); //returns 1 if one of the cards in the zone has the type, 0 otherwise
   int hasPrimaryType(const char * value,const char * secondvalue); //returns 1 if one of the cards in the zone has the type, 0 otherwise
   int hasTypeButNotType(const char * value,const char * secondvalue); //returns 1 if one of the cards in the zone has the type, 0 otherwise
   int hasName(string value);
   int hasColor(int value); //returns 1 if one of the cards in the zone has the color, 0 otherwise
   int hasX();
   void setOwner(Player * player);
   MTGCardInstance * lastCardDrawn;
   static MTGGameZone * stringToZone(string zoneName, MTGCardInstance * source, MTGCardInstance * target);
   static int zoneStringToId(string zoneName);
   static MTGGameZone *intToZone(int zoneId, MTGCardInstance * source = NULL,MTGCardInstance * target = NULL);
   bool needShuffle;
   virtual const char * getName(){return "zone";};
   virtual ostream& toString(ostream&) const;
};

class MTGLibrary: public MTGGameZone {
 public:
  void shuffleTopToBottom(int nbcards);
  virtual ostream& toString(ostream&) const;
  const char * getName(){return "library";}
};

class MTGGraveyard: public MTGGameZone {
 public:
  virtual ostream& toString(ostream&) const;
  const char * getName(){return "graveyard";}
};

class MTGHand: public MTGGameZone {
 public:
  virtual ostream& toString(ostream&) const;
  const char * getName(){return "hand";}
};

class MTGRemovedFromGame: public MTGGameZone {
 public:
  virtual ostream& toString(ostream&) const;
  const char * getName(){return "exile";}
};

class MTGStack: public MTGGameZone {
 public:
  virtual ostream& toString(ostream&) const;
  const char * getName(){return "stack";}
};

class MTGInPlay: public MTGGameZone {
 public:
  void untapAll();
  MTGCardInstance * getNextAttacker(MTGCardInstance * previous);
  virtual ostream& toString(ostream&) const;
  const char * getName(){return "battlefield";}
};


class MTGPlayerCards {
 protected:
  void init();

 public:
  MTGLibrary * library;
  MTGGraveyard * graveyard;
  MTGHand * hand;
  MTGInPlay * inPlay;
  MTGInPlay * battlefield; //alias to inPlay

  MTGStack * stack;
  MTGRemovedFromGame * removedFromGame;
  MTGRemovedFromGame * exile; //alias to removedFromZone
  MTGGameZone * garbage;
  MTGGameZone * temp;

  MTGPlayerCards();
  MTGPlayerCards(int * idList, int idListSize);
  MTGPlayerCards(MTGDeck * deck);
  ~MTGPlayerCards();
  void initGame(int shuffle = 1, int draw = 1);
	void OptimizedHand(Player * who,int amount = 7,int lands = 3,int creatures = 0,int othercards = 4);
  void setOwner(Player * player);
  void discardRandom(MTGGameZone * from,MTGCardInstance * source);
  void drawFromLibrary();
  void showHand();
  void resetLibrary();
  void initDeck(MTGDeck * deck);
  MTGCardInstance * putInGraveyard(MTGCardInstance * card);
  MTGCardInstance * putInExile(MTGCardInstance * card);
  MTGCardInstance * putInLibrary(MTGCardInstance * card);
  MTGCardInstance * putInHand(MTGCardInstance * card);
  MTGCardInstance * putInZone(MTGCardInstance * card, MTGGameZone * from, MTGGameZone * to);
  int isInPlay(MTGCardInstance * card);
  int isInGrave(MTGCardInstance * card);
  int isInZone(MTGCardInstance * card,MTGGameZone * zone);
};

ostream& operator<<(ostream&, const MTGGameZone&);
ostream& operator<<(ostream&, const MTGPlayerCards&);
istream& operator>>(istream&, MTGPlayerCards&);

#endif