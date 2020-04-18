

#define MAX_GAMEMODE_CONDITIONS 10

#event_handler("frame", "CheckGameModeConditions");
#event_handler("frame", "CheckItemsGameModeConditions");

string GameModeConditions[MAX_GAMEMODE_CONDITIONS] = { "", "", "", "", "", "", "", "", "", "", };
string sCurGameModeCondition = "";

void SetGameModeCondition(string _sQuest)
{

	for(int i=0; i<MAX_GAMEMODE_CONDITIONS; i++)
	{
		if(GameModeConditions[i] == _sQuest) return;
		
		if(GameModeConditions[i] == "")
		{
			SetEventHandler(_sQuest, _sQuest, 0); 
			GameModeConditions[i] = _sQuest;
			return;
		}
	}
	
	Log_TestInfo("Critical Error: No more empty GameMode conditions.");
}

void CheckGameModeConditions() 
{
	for(int i=0; i<MAX_GAMEMODE_CONDITIONS; i++)
	{
		if(GameModeConditions[i] == "") continue;
		sCurGameModeCondition = GameModeConditions[i];
		PostEvent(sCurGameModeCondition, 10);
	}
}


void CheckItemsGameModeConditions() 
{
	if(iScriptItemCount == 0) return;
	int i;
	ref rItem;
	string sItem;
	for(i=iScriptItemStartNum; i<iScriptItemEndNum; i++)
	{
		rItem = &items[i];
		if(!CheckAttribute(rItem, "ID")) continue;
		sItem = items[i].id;
		if(CheckAttribute(rItem, "Script") && CheckCharacterItem(PChar, sItem))
		{
			Log_TestInfo("����� �������� ��������������� �������. ������ - "+rItem.Script);
			SetGameModeCondition(rItem.Script);
			DeleteGameModeConditionFromItem(sItem); 
		}
	}
}

void DeleteGameModeConditionFromItem(string sItemID)
{
	ref rItem = ItemsFromID(sItemID);
	DeleteAttribute(rItem, "Script");
	iScriptItemCount--; 
}


void DeleteGameModeCondition(string _sQuest)
{
	for(int i=0; i<MAX_GAMEMODE_CONDITIONS; i++)
	{
		if(GameModeConditions[i] == _sQuest)
		{
			GameModeConditions[i] = "";
			DelEventHandler(_sQuest, _sQuest); 
			return;
		}
	}
}

