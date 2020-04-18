
int CreatePanamaCharacters(int n)
{
	ref ch;
	
	
	
	
	
	makeref(ch,Characters[n]);			
	ch.id		= "Panama_Mayor";
	ch.model	= "huber_21";
	ch.sex = "man";
	ch.name 	= "Pedro Carrilia";
    ch.lastname = "de Gusman";
	ch.City = "Panama";
	ch.location	= "Panama_townhall";
	ch.greeting = "mayor_1";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.nation = SPAIN;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	EquipCharacterbyItem(ch, GUN_COMMON); 
	EquipCharacterbyItem(ch, BLADE_LONG); 
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.standUp = true; 
	LAi_SetImmortal(ch, true);
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			
	ch.id		= "Panama_Priest";
	ch.model	= "priest_4";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "Panama";
	ch.location	= "Panama_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_church.c";
	ch.greeting = "padre_1";
	ch.nation = SPAIN;

	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		
	ch.id		= "Panama_waitress";
	ch.model	= "women_12";
	ch.sex = "woman";
	ch.City = "Panama";
	ch.location	= "Panama_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Waitress_dialog.c";
	ch.greeting = "waitress";
	ch.nation = SPAIN;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			
	ch.id		= "Panama_tavernkeeper";
	ch.model	= "barmen_3";
	ch.greeting = "barmen_1";
	ch.sex = "man";
	ch.City = "Panama";
	ch.location	= "Panama_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = SPAIN;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;


	makeref(ch,Characters[n]);			
	ch.id		= "Panama_trader";
	ch.model	= "trader_3";
	ch.greeting = "store_2";
	ch.sex = "man";
	ch.City = "Panama";
	ch.location	= "Panama_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = SPAIN;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	 

	makeref(ch,Characters[n]);			
	ch.id		= "Panama_usurer";
	ch.model	= "banker_3";
	ch.sex = "man";
	ch.City = "Panama";
	ch.Merchant.type = "jeweller"; 
	ch.location	= "Panama_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Usurer_dialog.c";
	ch.nation = SPAIN;
	ch.greeting = "usurer_2";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 18000; 
	ch.money = USURER_MIN_MONEY + rand(USURER_NORM);
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			
	ch.id		= "Panama_PortMan";
	ch.model	= "citiz_4";
	ch.sex = "man";
	ch.City = "Panama";
	ch.location	= "Panama_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.greeting = "portman_4";
	ch.nation = SPAIN;
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			
	ch.id		= "Panama_Hostess";
	ch.name		= "Dolores"
	ch.lastname = "";
	ch.model	= "maman_8";
	ch.model.animation = "woman_B";
	ch.sex = "woman";
	ch.City = "Panama";
	ch.location	= "Panama_SecBrRoom";
	ch.location.group = "goto";
	ch.location.locator = "goto8";
	ch.Dialog.Filename = "Common_Brothel.c";
	ch.greeting = "maman_2";
	ch.nation = SPAIN;
	ch.questChurch = ""; 
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	n = n + 1;

	return n;
}

