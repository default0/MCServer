
#include "Globals.h"  // NOTE: MSVC stupidness requires this to be the same across all modules

#include "Cavespider.h"





cCavespider::cCavespider(void) :
	super("Cavespider", 59, "mob.spider.say", "mob.spider.death")
{
}





void cCavespider::Tick(float a_Dt)
{
	super::Tick(a_Dt);

	// TODO: Check vanilla if cavespiders really get passive during the day
	m_EMPersonality = (GetWorld()->GetTimeOfDay() < (12000 + 1000)) ? PASSIVE : AGGRESSIVE;
}





void cCavespider::GetDrops(cItems & a_Drops, cPawn * a_Killer)
{
	AddRandomDropItem(a_Drops, 0, 2, E_ITEM_STRING);
	AddRandomDropItem(a_Drops, 0, 1, E_ITEM_SPIDER_EYE);
}




