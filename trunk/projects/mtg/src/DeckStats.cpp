#include "../include/debug.h"
#include "../include/DeckStats.h"
#include "../include/Player.h"

DeckStats * DeckStats::mInstance = NULL;

int DeckStat::percentVictories(){
  if (nbgames == 0) return 50;
  return (100 * victories / nbgames);
}

DeckStats * DeckStats::GetInstance(){
  if (!mInstance) mInstance = NEW DeckStats();
  return mInstance;
}

void DeckStats::cleanStats(){
  map<string,DeckStat *>::iterator it;
  for (it = stats.begin(); it != stats.end(); it++){
    delete(it->second);
  }
  stats.clear();
}

DeckStats::~DeckStats(){
  cleanStats();
}

int DeckStats::percentVictories(string opponentsFile){
  map<string,DeckStat *>::iterator it = stats.find(opponentsFile);
  if (it == stats.end()){
    return 50;
  }else{
    return (it->second->percentVictories());
  }
}

void DeckStats::load(Player * player){
  char filename[512];
  sprintf(filename, "Res/player/stats/%s.txt",player->deckFile.c_str());
  load(filename);
}

void DeckStats::load(const char * filename){
  cleanStats();
  std::ifstream file(filename);
  std::string s;

  if(file){
    while(std::getline(file,s)){
      string deckfile = s;
      std::getline(file,s);
      int games = atoi(s.c_str());
      std::getline(file,s);
      int victories = atoi(s.c_str());
      stats[deckfile] = NEW DeckStat(games,victories);
    }
    file.close(); 
  }
}

void DeckStats::save(Player * player){
  char filename[512];
  sprintf(filename, "Res/player/stats/%s.txt",player->deckFile.c_str());
  save(filename);
}

void DeckStats::save(const char * filename){
  std::ofstream file(filename);
  char writer[512];
  if (file){
    map<string,DeckStat *>::iterator it;
    for (it = stats.begin(); it != stats.end(); it++){
      sprintf(writer,"%s\n", it->first.c_str());
      file<<writer;
      sprintf(writer,"%i\n", it->second->nbgames);
      file<<writer;
      sprintf(writer,"%i\n", it->second->victories);
      file<<writer;
    }
    file.close();
  }
}

void DeckStats::saveStats(Player *player, Player *opponent, GameObserver * game){
  int victory = 1;
  if (game->gameOver == player) victory = 0;
  load(player);
  map<string,DeckStat *>::iterator it = stats.find(opponent->deckFile);
  if (it == stats.end()){
    stats[opponent->deckFile] = NEW DeckStat(1,victory);
  }else{
    it->second->victories+=victory;
    it->second->nbgames+=1;
  }
  save(player);

}
