#include "../include/config.h"
#include "../include/GameApp.h"
#include "../include/GuiAvatars.h"

#define LIB_GRAVE_OFFSET 230

GuiAvatars::GuiAvatars(CardSelector* cs) : cs(cs), active(NULL)
{
  Add(self           = NEW GuiAvatar   (SCREEN_WIDTH, SCREEN_HEIGHT, false,
					GameObserver::GetInstance()->players[0], GuiAvatar::BOTTOM_RIGHT, this));
  Add(selfGraveyard  = NEW GuiGraveyard(SCREEN_WIDTH - GuiAvatar::Width - GuiGameZone::Width/2 - 5, SCREEN_HEIGHT - GuiAvatar::Height - 5, false,
					GameObserver::GetInstance()->players[0], this));
  Add(selfLibrary    = NEW GuiLibrary  (SCREEN_WIDTH - GuiAvatar::Width - GuiGameZone::Width/2 - 5 , SCREEN_HEIGHT - GuiAvatar::Height - 5 + GuiGameZone::Height + 5, false,
					GameObserver::GetInstance()->players[0], this));

  Add(opponent          = NEW GuiAvatar   (0,  0,  false, GameObserver::GetInstance()->players[1], GuiAvatar::TOP_LEFT, this));
  opponent->zoom = 0.9;
  Add(opponentGraveyard = NEW GuiGraveyard(5 + GuiAvatar::Width * 1.2 - GuiGameZone::Width / 2, 5,  false, GameObserver::GetInstance()->players[1], this));
  Add(opponentLibrary   = NEW GuiLibrary  (5 + GuiAvatar::Width *1.2 - GuiGameZone::Width / 2, 5 + GuiGameZone::Height + 5, false, GameObserver::GetInstance()->players[1], this));

  cs->Add(self); cs->Add(selfGraveyard); cs->Add(selfLibrary);
  cs->Add(opponent); cs->Add(opponentGraveyard); cs->Add(opponentLibrary);
  selfGraveyard->alpha = selfLibrary->alpha = opponentGraveyard->alpha = opponentLibrary->alpha = 0;
}

float GuiAvatars::LeftBoundarySelf(){
  return SCREEN_WIDTH - 10;
}

GuiAvatars::~GuiAvatars()
{
}

void GuiAvatars::Activate(PlayGuiObject* c)
{
  c->zoom = 1.2;
  c->mHasFocus = true;
  
  if ((opponentGraveyard == c) || (opponentLibrary == c) || (opponent == c))
    { opponentGraveyard->alpha = opponentLibrary->alpha = 128; active = opponent; opponent->zoom = 1.2;}
  else if ((selfGraveyard == c) || (selfLibrary == c) || (self == c))
    { selfGraveyard->alpha = selfLibrary->alpha = 128; self->zoom = 1.0; active = self; }
  if (opponent != c && self != c) c->alpha = 255;
}
void GuiAvatars::Deactivate(PlayGuiObject* c)
{
  c->zoom = 1.0;
  c->mHasFocus = false;
  if ((opponentGraveyard == c) || (opponentLibrary == c) || (opponent == c))
    { opponentGraveyard->alpha = opponentLibrary->alpha = 0;  opponent->zoom = 0.9;}
  else if ((selfGraveyard == c) || (selfLibrary == c) || (self == c))
    { selfGraveyard->alpha = selfLibrary->alpha = 0; self->zoom = 0.3; }
  active = NULL;
}

int GuiAvatars::receiveEventPlus(WEvent* e)
{
  return selfGraveyard->receiveEventPlus(e) | opponentGraveyard->receiveEventPlus(e);
}

int GuiAvatars::receiveEventMinus(WEvent* e)
{
  selfGraveyard->receiveEventMinus(e);
  opponentGraveyard->receiveEventMinus(e);
  return 1;
}

bool GuiAvatars::CheckUserInput(u32 key){
  if (self->CheckUserInput(key)) return true;
  if (opponent->CheckUserInput(key)) return true;
  if (selfGraveyard->CheckUserInput(key)) return true;
  if (opponentGraveyard->CheckUserInput(key)) return true;
  if (selfLibrary->CheckUserInput(key)) return true;
  if (opponentLibrary->CheckUserInput(key)) return true;
  return false;
}

void GuiAvatars::Update(float dt)
{
  self->Update(dt);
  opponent->Update(dt);
  selfGraveyard->Update(dt);
  opponentGraveyard->Update(dt);
  selfLibrary->Update(dt);
  opponentLibrary->Update(dt);
}

void GuiAvatars::Render()
{
  JRenderer * r = JRenderer::GetInstance();
  float w = 50;
  float h = 60;
  if (opponent == active){
    r->FillRect(opponent->actX, opponent->actY, w * opponent->actZ , h * opponent->actZ, ARGB(200,0,0,0));
  }else if (self == active){
    r->FillRect(self->actX - w * self->actZ, self->actY - h * self->actZ,  w * self->actZ , h * self->actZ, ARGB(200,0,0,0));
  }
  GuiLayer::Render();
}
