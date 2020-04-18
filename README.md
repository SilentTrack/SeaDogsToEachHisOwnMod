# SeaDogsToEachHisOwnMod

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
