/* Default observers/Abilities that are added to the game for a standard Magic Game
 */

#ifndef _MTGRULES_H_
#define _MTGRULES_H_

#include "MTGAbility.h"
#include "Counters.h"
#include "WEvent.h"
#include "CardSelector.h"
#include "ManaCost.h"

class OtherAbilitiesEventReceiver: public MTGAbility
{
public:
    int testDestroy();
    int receiveEvent(WEvent * event);
    OtherAbilitiesEventReceiver(int _id);
    OtherAbilitiesEventReceiver * clone() const;
};
class MTGPutInPlayRule: public MTGAbility
{
public:
    int isReactingToClick(MTGCardInstance * card, ManaCost * mana = NULL);
    int reactToClick(MTGCardInstance * card);
    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    MTGPutInPlayRule(int _id);
    const char * getMenuText()
    {
        return "Play Card Normally";
    }
    virtual MTGPutInPlayRule * clone() const;
};

class MTGAlternativeCostRule: public MTGAbility
{
protected:
    int isReactingToClick(MTGCardInstance * card, ManaCost * mana, ManaCost *alternateManaCost);
    int reactToClick(MTGCardInstance * card, ManaCost * alternateManaCost, int paymentType = ManaCost::MANA_PAID);

public:
    int isReactingToClick(MTGCardInstance * card, ManaCost * mana = NULL);
    int reactToClick(MTGCardInstance * card);

    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    MTGAlternativeCostRule(int _id);
    const char * getMenuText()
    {
        return "Pay Alternative Cost";
    }
    virtual MTGAlternativeCostRule * clone() const;
};

class MTGBuyBackRule: public MTGAlternativeCostRule
{
public:
    int isReactingToClick(MTGCardInstance * card, ManaCost * mana = NULL);
    int reactToClick(MTGCardInstance * card);
    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    MTGBuyBackRule(int _id);
    const char * getMenuText()
    {
        return "Cast And Buy Back";
    }
    virtual MTGBuyBackRule * clone() const;
};

class MTGFlashBackRule: public MTGAlternativeCostRule
{
public:

    int isReactingToClick(MTGCardInstance * card, ManaCost * mana = NULL);
    int reactToClick(MTGCardInstance * card);
    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    MTGFlashBackRule(int _id);
    const char * getMenuText()
    {
        return "Flash Back";
    }
    virtual MTGFlashBackRule * clone() const;
};

class MTGRetraceRule: public MTGAlternativeCostRule
{
public:
    int isReactingToClick(MTGCardInstance * card, ManaCost * mana = NULL);
    int reactToClick(MTGCardInstance * card);
    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    MTGRetraceRule(int _id);
    const char * getMenuText()
    {
        return "Retrace";
    }
    virtual MTGRetraceRule * clone() const;
};

class MTGMorphCostRule: public MTGAbility
{
public:
 
    int isReactingToClick(MTGCardInstance * card, ManaCost * mana = NULL);
    int reactToClick(MTGCardInstance * card);
    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    MTGMorphCostRule(int _id);
    const char * getMenuText()
    {
        return "Play Morphed";
    }
    virtual MTGMorphCostRule * clone() const;
};

class MTGAttackRule: public MTGAbility, public Limitor
{
public:
 
    virtual bool select(Target*);
    virtual bool greyout(Target*);
    int isReactingToClick(MTGCardInstance * card, ManaCost * mana = NULL);
    int reactToClick(MTGCardInstance * card);
    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    MTGAttackRule(int _id);
    const char * getMenuText()
    {
        return "Attacker";
    }
    int receiveEvent(WEvent * event);
    virtual MTGAttackRule * clone() const;
};

/* handles combat trigger send recieve events*/
class MTGCombatTriggersRule: public MTGAbility
{
public:
    MTGCombatTriggersRule(int _id);
    int receiveEvent(WEvent * event);
    virtual ostream& toString(ostream& out) const;
    int testDestroy();
    virtual MTGCombatTriggersRule * clone() const;
};

class MTGBlockRule: public MTGAbility
{
public:
    int isReactingToClick(MTGCardInstance * card, ManaCost * mana = NULL);
    int reactToClick(MTGCardInstance * card);
    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    MTGBlockRule(int _id);
    const char * getMenuText()
    {
        return "Blocker";
    }
    virtual MTGBlockRule * clone() const;
};

/* Persist Rule */
class MTGPersistRule: public MTGAbility
{
public:
    MTGPersistRule(int _id);
    int receiveEvent(WEvent * event);
    virtual ostream& toString(ostream& out) const;
    int testDestroy();
    virtual MTGPersistRule * clone() const;
};
//unearths destruction if leaves play effect
class MTGUnearthRule: public MTGAbility
{
public:
    MTGUnearthRule(int _id);
    int receiveEvent(WEvent * event);
    virtual ostream& toString(ostream& out) const;
    int testDestroy();
    virtual MTGUnearthRule * clone() const;
};
class MTGTokensCleanup: public MTGAbility
{
public:
    vector<MTGCardInstance *> list;
    MTGTokensCleanup(int _id);
    int receiveEvent(WEvent * event);
    int testDestroy();
    virtual MTGTokensCleanup * clone() const;
};

/*
 * Rule 420.5e (Legend Rule)
 * If two or more legendary permanents with the same name are in play, all are put into their
 * owners' graveyards. This is called the "legend rule." If only one of those permanents is
 * legendary, this rule doesn't apply.
 */
class MTGLegendRule: public ListMaintainerAbility
{
public:
    MTGLegendRule(int _id);
    int canBeInList(MTGCardInstance * card);
    int added(MTGCardInstance * card);
    int removed(MTGCardInstance * card);
    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    virtual MTGLegendRule * clone() const;
};
class MTGPlaneWalkerRule: public ListMaintainerAbility
{
public:
    MTGPlaneWalkerRule(int _id);
    int canBeInList(MTGCardInstance * card);
    int added(MTGCardInstance * card);
    int removed(MTGCardInstance * card);
    int testDestroy();
    virtual ostream& toString(ostream& out) const;
    virtual MTGPlaneWalkerRule * clone() const;
};

class MTGMomirRule: public MTGAbility
{
private:
    int genRandomCreatureId(int convertedCost);
    static vector<int> pool[20];
    static int initialized;

    int textAlpha;
    string text;
public:

    int alreadyplayed;
    MTGAllCards * collection;
    MTGCardInstance * genCreature(int id);
    int testDestroy();
    void Update(float dt);
    void Render();
    MTGMomirRule(int _id, MTGAllCards * _collection);
    int isReactingToClick(MTGCardInstance * card, ManaCost * mana = NULL);
    int reactToClick(MTGCardInstance * card);
    int reactToClick(MTGCardInstance * card, int id);
    const char * getMenuText()
    {
        return "Momir";
    }
    virtual ostream& toString(ostream& out) const;
    virtual MTGMomirRule * clone() const;
};

/* LifeLink */
class MTGLifelinkRule: public MTGAbility
{
public:
    MTGLifelinkRule(int _id);

    int receiveEvent(WEvent * event);

    int testDestroy();

    virtual ostream& toString(ostream& out) const;

    virtual MTGLifelinkRule * clone() const;
};

/* Deathtouch */
class MTGDeathtouchRule: public MTGAbility
{
public:
    MTGDeathtouchRule(int _id);

    int receiveEvent(WEvent * event);

    int testDestroy();
    const char * getMenuText()
    {
        return "Deathtouch";
    }

    virtual MTGDeathtouchRule * clone() const;
};

/* HUD Display */

class HUDString
{
public:
    string value;
    float timestamp;
    int quantity;
    HUDString(string s, float ts) :
        value(s), timestamp(ts)
    {
        quantity = 1;
    }
    ;
};

class HUDDisplay: public MTGAbility
{
private:
    list<HUDString *> events;
    float timestamp;
    float popdelay;
    WFont * f;
    float maxWidth;
    int addEvent(string s);
public:
    int testDestroy();
    int receiveEvent(WEvent * event);
    void Update(float dt);
    void Render();
    HUDDisplay(int _id);
    ~HUDDisplay();
    virtual HUDDisplay * clone() const;
};

#endif
