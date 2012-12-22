
#include "Globals.h"  // NOTE: MSVC stupidness requires this to be the same across all modules

#include "Chicken.h"





// TODO: Drop egg every 5-10 minutes





cChicken::cChicken(void) :
	super("Chicken", 93, "mob.chicken.hurt", "mob.chicken.hurt")
{
}





void cChicken::GetDrops(cItems & a_Drops, cPawn * a_Killer)
{
	AddRandomDropItem(a_Drops, 0, 2, E_ITEM_FEATHER);
	a_Drops.push_back(cItem((GetMetaData() == BURNING) ? E_ITEM_COOKED_CHICKEN : E_ITEM_RAW_CHICKEN, 1));
}




