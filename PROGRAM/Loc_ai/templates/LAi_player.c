

#define LAI_TMPL_PLAYER	"player"


bool LAi_tmpl_player_InitTemplate(aref chr)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", false);
	CharacterPlayAction(chr, "");
	DeleteAttribute(chr, "chr_ai.tmpl");
	chr.chr_ai.tmpl = LAI_TMPL_PLAYER;
	if(LAi_IsInitedAI) SetCharacterTask_None(chr);
	return true;
}


void LAi_tmpl_player_CharacterUpdate(aref chr, float dltTime)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_EndGoToPoint(aref chr)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_FailureGoToPoint(aref chr)
{
	SetCharacterTask_None(chr);
}



void LAi_tmpl_player_EndRunToPoint(aref chr)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_FailureRunToPoint(aref chr)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_BusyPos(aref chr, float x, float y, float z)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_FollowGo(aref chr)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_FollowStay(aref chr)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_FailureFollow(aref chr)
{
	SetCharacterTask_None(chr);
}



void LAi_tmpl_player_FightGo(aref chr)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_FightStay(aref chr)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_FailureFight(aref chr)
{
	SetCharacterTask_None(chr);
}


bool LAi_tmpl_player_IsFire(aref chr)
{	
	return LAi_CharacterCanFrie(chr);
}


bool LAi_tmpl_player_IsFight(aref chr)
{
	if(LAi_LocationCanFight()) return true;
	Log_SetStringToLog(XI_ConvertString("CantFight"));
	return false;
}



void LAi_tmpl_player_EndEscape(aref chr)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_EscapeSlide(aref chr)
{
	SetCharacterTask_None(chr);
}


void LAi_tmpl_player_FailureEscape(aref chr)
{
	SetCharacterTask_None(chr);
}



void LAi_tmpl_player_ColThreshold(aref chr)
{
	SetCharacterTask_None(chr);
}



void LAi_tmpl_player_EndAction(aref chr)
{
	SetCharacterTask_None(chr);
}



void LAi_tmpl_player_FreePos(aref chr, aref who)
{
	SetCharacterTask_None(chr);
}


