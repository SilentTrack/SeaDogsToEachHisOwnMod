#define MAX_RUMOURS 19  
#include "scripts\Rumour_templates.c"
#include "scripts\Rumour_func.c"
#include "scripts\Rumour_generate.c"
#include "scripts\Rumour_Data.h"
#include "scripts\GoldFleet.c"

object	Rumour[MAX_RUMOURS]; 
object RumourParams;         

int id_counter;

void SetRumourDefaults()
{
	int i;
	ref CurrentRumour;
	id_counter = 0;

	for(i = 0; i < MAX_RUMOURS; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = id_counter;  
		CurrentRumour.text = DEFAULT_TEXT[i];
		CurrentRumour.state = "1"; 
		CurrentRumour.tip = "citizen,capitan"; 
		CurrentRumour.rep = "none" 
		CurrentRumour.starttime = (DateToInt(0));
		CurrentRumour.actualtime = (DateToInt(40));
		CurrentRumour.event = "none"; 
		CurrentRumour.next = "none"; 
		id_counter++; 
	}	
}

void RumourInit();
{
	
	trace("�����!");
	TemplateLoad();
	SetRumourDefaults();
	
	SaveCurrentQuestDateParam("Siege_DailyUpdate");
}

