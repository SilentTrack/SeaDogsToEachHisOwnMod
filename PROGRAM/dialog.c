
#include "dialog_func.c"


#define EVENT_DIALOG_START		"evntDialogStart"
#define EVENT_DIALOG_EXIT		"evntDialogExit"

#event_handler("dlgReady", "StartDialogWithMainCharacter");
#event_handler("EmergencyDialogExit","DialogExit");

extern void ProcessDialogEvent();
extern void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag); 

bool dialogDisable = false;
object	Dialog;
ref		CharacterRef;
bool	dialogRun = false;

bool	dialogSelf = false;

string  FullDialogPath;
string	PathDlgLngExtn = "";

string dialogEditStrings[10];

void  ProcessCommonDialog(ref NPChar, aref Link, aref NextDiag)
{
    ProcessCommonDialogEvent(NPChar, Link, NextDiag);
}

void DialogsInit()
{
	
	Set_inDialog_Attributes(); 
}


bool DialogMain(ref Character)
{
	
	if(dialogRun != false) return false;
	
	ref mainChr = GetMainCharacter();
	
	if(!IsEntity(mainChr)) return false;
	if(!IsEntity(Character)) return false;
	if(LAi_IsDead(mainChr)) return false;
	if(LAi_IsDead(Character)) return false;
	
	if(!CheckAttribute(Character, "Dialog.CurrentNode"))
	{
		Trace("Dialog: Character <" + Character.id + "> can't have field Dialog.CurrentNode, exit from dialog!")
		return false;
	}
	
	if(!LAi_Character_CanDialog(mainChr, Character)) return false;
	
	if(!LAi_Character_CanDialog(Character, mainChr)) return false;
	
	CharacterRef = Character;
	
	if( !LoadDialogFiles(Character.Dialog.Filename) ) {
		
		if( !LoadDialogFiles("error_dialog.c") ) {
			return false;
		}
	}
	
	dialogRun = true;
	dialogSelf = false;
	LAi_Character_StartDialog(mainChr, Character);
	LAi_Character_StartDialog(Character, mainChr);
	SendMessage(mainChr, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);
	SendMessage(Character, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);	
	
	
	Dialog.CurrentNode = CharacterRef.Dialog.CurrentNode;
	startDialogMainCounter = 0;
	SetEventHandler("frame", "StartDialogMain", 1);
	SetTimeScale(0.0);
	if (locCameraCurMode == LOCCAMERA_FOLLOW && !CheckAttribute(loadedLocation, "lockCamAngle") && mainChr.location.group != "sit") 
	{
		SetCameraDialogMode(Character);  
	}
	return true;	
}

int startDialogMainCounter = 0;
int dialogWaitGreetingSound = 0;
string dialogGreetingSound = "";

void StartDialogMain()
{
	startDialogMainCounter++;
	if(startDialogMainCounter < 3) return;
	
	DelEventHandler("frame", "StartDialogMain");

	CreateEntity(&Dialog, "dialog");
	Dialog.headModel = CharacterRef.headModel;
	Dialog.gender = CharacterRef.sex;

	DeleteAttribute(&Dialog,"Links");
	DeleteAttribute(&Dialog,"Text");

	if(CheckAttribute(CharacterRef, "greeting"))
	{
		if(CharacterRef.greeting != "")
		{
			if (!CheckAttribute(CharacterRef, "greeting.minute"))
			{
				dialogGreetingSound = CharacterRef.greeting;
				dialogWaitGreetingSound = 0;
				SetEventHandler("frame", "DialogPlayGreeting", 1);
			}
			else
			{
				if (sti(CharacterRef.greeting.minute) != sti(Environment.date.min))
				{
					dialogGreetingSound = CharacterRef.greeting;
					dialogWaitGreetingSound = 0;
					SetEventHandler("frame", "DialogPlayGreeting", 1);
				}
			}
		}
	}

	object persRef = GetCharacterModel(Characters[GetMainCharacterIndex()]);
	SendMessage(&Dialog, "lii", 0, &Characters[GetMainCharacterIndex()], &persRef);

	object charRef = GetCharacterModel(Characters[makeint(CharacterRef.index)]);
	SendMessage(&Dialog, "lii", 1, &Characters[makeint(CharacterRef.index)], &charRef);

	LayerCreate("realize",1);
	LayerSetRealize("realize",1);
	LayerAddObject("realize",Dialog,-256);
	Set_inDialog_Attributes();
	ProcessDialogEvent();

	SetEventHandler("DialogEvent","ProcessDialogEvent",0);
	

	Event(EVENT_DIALOG_START,"");
}

void DialogPlayGreeting()
{
	dialogWaitGreetingSound++;
	if(dialogWaitGreetingSound < 10) return;
	dialogWaitGreetingSound = 0;
	DelEventHandler("frame", "DialogPlayGreeting");
	
	Dialog.greeting = CharacterRef.greeting;
	CharacterRef.greeting.minute = GetMinute();
	
}


void SelfDialog(ref Character)
{
	
	if(dialogRun != false) return false;
	
	if(!IsEntity(Character)) return false;
	
	if(!CheckAttribute(Character, "Dialog.CurrentNode"))
	{
		Trace("SelfDialog: Character <" + Character.id + "> can't have field Dialog.CurrentNode, exit from dialog!")
		return false;
	}
	
	CharacterRef = Character;
	
	if( !LoadDialogFiles(Character.Dialog.Filename) ) {
		
		if( !LoadDialogFiles("error_dialog.c") ) {
			return false;
		}
	}
	
	LAi_Character_CanDialog(Character, Character);
	
	dialogRun = true;
	dialogSelf = true;
	SendMessage(Character, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 1);
	
	Dialog.CurrentNode = CharacterRef.Dialog.CurrentNode;
	
	CreateEntity(&Dialog, "dialog");
	Dialog.headModel = Character.headModel;
	Dialog.gender = Character.sex;

	object persRef = GetCharacterModel(Characters[GetMainCharacterIndex()]);
	SendMessage(&Dialog, "lii", 0, Character, &persRef);
	SendMessage(&Dialog, "lii", 1, Character, &persRef);
	

	LayerCreate("realize",1);
	LayerSetRealize("realize",1);
	LayerAddObject("realize",Dialog,-256);
	Set_inDialog_Attributes();
	ProcessDialogEvent();

	SetEventHandler("DialogEvent","ProcessDialogEvent",0);
	

	Event(EVENT_DIALOG_START,"");
}


void DialogExit()
{
	
	if(dialogRun == false) return;
	DelEventHandler("frame", "DialogPlayGreeting");
	
	DeleteClass(&Dialog);
	if(FullDialogPath!="")
	{
		if (CheckAttribute(CharacterRef, "FileDialog2"))
		{
		    UnloadSegment(CharacterRef.FileDialog2);
		    
		    
		}
		UnloadSegment(FullDialogPath);
	}
	if(PathDlgLngExtn!="") UnloadSegment(PathDlgLngExtn);
	if(dialogSelf == false)
	{
		
		ref mainChr = GetMainCharacter();
		
		LAi_Character_EndDialog(mainChr, CharacterRef);
		LAi_Character_EndDialog(CharacterRef, mainChr);
		SendMessage(mainChr, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
		SendMessage(CharacterRef, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
		
		if (locCameraCurMode != LOCCAMERA_FOLLOW)
		{
			locCameraTarget(mainChr);
			locCameraFollow();
		}
	}else{
		LAi_Character_EndDialog(CharacterRef, CharacterRef);
		SendMessage(CharacterRef, "lsl", MSG_CHARACTER_EX_MSG, "InDialog", 0);
	}
	dialogRun = false;
	
	PostEvent(EVENT_DIALOG_EXIT, 1, "l", sti(CharacterRef.index));
}


void StartDialogWithMainCharacter()
{
	if(LAi_IsBoardingProcess()) return;
	if(dialogDisable) return;
	
	int person = GetEventData();
	
	if(person == GetMainCharacterIndex()) return;
	
	if(!IsEntity(&Characters[person])) return;
	
	DialogMain(&Characters[person]);	
	
}

bool LoadDialogFiles(string dialogPath)
{
	
	FullDialogPath = "dialogs\" + LanguageGetLanguage() + "\" + dialogPath;

	
	
	
	 
	

	
	bool retVal;
	
	if( !LoadSegment(FullDialogPath) )
	{
		Trace("Dialog: Missing dialog file: " + FullDialogPath);
		retVal = false;
		
	} else {
		if(!retVal) {
			retVal = true;
			PathDlgLngExtn = "";
		}
	}

	return retVal;
}


string DText(string sString)
{
	return sString;
}


bool SetCameraDialogMode(ref chrRef)
{
	float x1,y1,z1, x2, y2, z2;
	if( false==GetCharacterPos(pchar,&x1,&y1,&z1) ) return false;
    if( false==GetCharacterPos(chrRef,&x2,&y2,&z2) ) return false;

    float a = 0.1;
    float len = GetDistance2D(x1,z1, x2,z2);
	float dx = x1*(1-a)+x2*a;
	float dz = z1*(1-a)+z2*a;
	len = 1;
	float s1 = (dx-x1)*len;
	float s2 = (dz-z1)*len;

    float xcam;
	float zcam;
	if (rand(1) == 0)
	{
		xcam = dx-s2;
		zcam = dz+s1;
	}
	else
	{
		xcam = dx+s2;
		zcam = dz-s1;
	}
	locCameraTarget(chrRef);
	float fH = 1.7;
	if (chrRef.location.group == "sit")
	{
	    fH = 1.15;
	}
	return locCameraToPos(xcam,y1+fH,zcam,false);
}

