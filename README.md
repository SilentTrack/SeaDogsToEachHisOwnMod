# SeaDogsToEachHisOwnMod

Included files:
PROGRAM/battle_interface/BattleInterface.c
PROGRAM/battle_interface/landinterface.c
PROGRAM/characters/RPGUtilite.c
PROGRAM/dialogs/russian/Common_Soldier.c
PROGRAM/dialogs/russian/Smuggler Agent_dialog.c
PROGRAM/dialogs/russian/Smuggler_OnShore_dialog.c
PROGRAM/quests/reaction_functions.c
PROGRAM/sea_ai/AIShip.c
PROGRAM/shizukamod_console.c

Missing change:
Achievement related;
Initializing Mary and Helen;
Saga dialog; quests_reaction.c
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); 
				}
				pchar.questTemp.LSC.Mary = "fail";
				RemoveItems(pchar, "key_mary", 1); 
				DeleteAttribute(pchar, "questTemp.LSC.MaryWait"); 
			}
Hook mod;
Merchant tweaks: utils.c
Failed attemp for 42 pounders(walk around it with console :)): initGoods.c
