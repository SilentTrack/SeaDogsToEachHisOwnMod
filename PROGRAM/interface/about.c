

float fNewPos;
#define MAX_LINE         147

string STR_TEXT[MAX_LINE] = {
"",
"",
"",
"",
"",
"",
"",
"��������� ����",
"",
"",
"",
"",
"",
"",
"",
"",
"������ 'Seaward.Ru'",
"",
"�������� �������",
"������ (Eddy) ������",
"",
"������� ����-��������",
"������� (ALexusB) �����������",
"",
"���-��������",
"���� (Ursus) �����",
"",
"���������",
"����� (incus) �������",
"���� (free_corsair) �������",
"�������� (Dogeva) ���������",
"",
"��� ��������",
"����� (incus) �������",
"",
"3D-�������������",
"���� (Ursus) �����",
"������ (Eddy) ������",
"������� (lexa) ��������",
"",

"��������� �������: ���������",
"������ (Delamer) ��������",
"",
"��������� �������: ���� � ������",
"������� (LexaLloyd) ���������",
"����� (Pavka) ������",
"������� (SeaLegend) ���������",
"",

"����� � ��������� ����",
"������� (ALexusB) �����������",
"������ (Eddy) ������",
"",
"������ �����������",
"������� (ALexusB) �����������",
"",
"������ ������� �������",
"������� (ALexusB) �����������",
"",
"���� � �������� ������������ �������",
"������ (Eddy) ������",
"",
"������ ��������",
"������ (Eddy) ������",
"������� (ALexusB) �����������",
"",
"����������������",
"������� (ALexusB) �����������",
"������ (Eddy) ������",
"������� (Navy) ������",
"������ (homosapienz) ������",
"",
"Sound Engine",
"'FMOD Ex Sound System' (Firelight Technologies)",
"",
"��������� ����� � �����",
"������� (Navy) ������",
"����� (incus) �������",
"",
"������������",
"������ (Delamer) ��������",
"������� (�����) ��������",
"������ (homosapienz) ������",
"������ (Dir) �����",
"������� (LexaLloyd) ���������",
"�������� (Strelok) �������",
"��������� (Alex_S) �������",
"��������� (Kaly) �������",
"",
"����-����",
"������� (dark toster) ���������",
"������ (RIZIY) �������",
"����� (����) �����",
"������ (Jacques) �������",
"������� (Forsayte) �����",
"����� (Destynar) ���������",
"����� (Pavka) ������",
"������� (�����) ������",
"������� (SeaLegend) ���������",

"",
"����������� �� ����",
"������� (ALexusB) �����������",
"",
"������ 'Seaward.Ru' ����������",
"������� �������� � ����� ���������",
"�� ��������������� ����������� ������� ����",
"",
"",
"",
"�������� '������'",
"",
"����-��������� �� ����������",
"������� �������",
"",
"��������� ������ ������� ��������",
"������ ��������",
"",
"��������",
"���� ���������",
"",
"������������ ������ ������������",
"����� ��������",
"",
"PR ���������",
"���� �������",
"����� ��������",
"����� ���",
"", 
"",
"",
"������ '�������'",
"",
"������������ ������",
"����� (Gray Angel) �������",
"",
"��������",
"������� (Lokk) �������",

"",
"���",
"���� (Ursus) �����",
"����� �������",
"",
"������������",
"������ (Nike) ��������",
"���� (Vano) ��������",
"",
"",
"",
};

string STR_COLOR[MAX_LINE] = {
"",
"",
"",
"",
"",
"",
"",
"blue",
"",
"",
"",
"",
"",
"",
"",
"",
"red",
"",
"yellow",
"������ (Eddy) ������",
"",
"yellow",
"������� (ALexusB) �����������",
"",
"yellow",
"���� (Ursus) �����",
"",
"yellow",
"����� (incus) �������",
"���� (free_corsair) �������",
"�������� (Dogeva) ���������",
"",
"yellow",
"����� (incus) �������",
"",
"yellow",
"���� (Ursus) �����",
"������� (lexa) ��������",
"������ (Eddy) ������",
"",
"yellow",
"������ (Delamer) ��������",
"",
"yellow",
"������� (LexaLloyd) ���������",
"����� (Pavka) ������",
"������� (SeaLegend) ���������",
"",
"yellow",
"������ (Eddy) ������",
"������� (ALexusB) �����������",
"",
"yellow",
"������� (ALexusB) �����������",
"",
"yellow",
"������� (ALexusB) �����������",
"",
"yellow",
"������ (Eddy) ������",
"",
"yellow",
"������ (Eddy) ������",
"������� (ALexusB) �����������",
"",
"yellow",
"������� (ALexusB) �����������",
"������ (Eddy) ������",
"������� (Navy) ������",
"������ (homosapienz) ������",
"",
"yellow",
"'FMOD Ex Sound System' Firelight Technologies",
"",
"yellow",
"������� (Navy) ������",
"����� (incus) �������",
"",
"yellow",
"������ (Delamer) ��������",
"������� (�����) ��������",
"������ (homosapienz) ������",
"������ (Dir) �����",
"������� (LexaLloyd) ���������",
"�������� (Strelok) �������",
"��������� (Alex_S) �������",
"��������� (Kaly) �������",
"",
"yellow",
"������� (dark toster) ���������",
"������ (RIZIY) �������",
"����� (����) �����",
"������ (Jacques) �������",
"������� (Forsayte) �����",
"����� (Destynar) ���������",
"����� (Pavka) ������",
"������� (�����) ������",
"������� (SeaLegend) ���������",

"",
"yellow",
"������� (ALexusB) �����������",
"",
"blue",
"blue",
"blue",
"",
"",
"",
"red",
"",
"yellow",
"������� �������",
"",
"yellow",
"������ ��������",
"",
"yellow",
"���� ���������",
"",
"yellow",
"����� ��������",
"",
"yellow",
"���� �������",
"����� ��������",
"����� ���",
"", 
"",
"",
"red",
"",
"yellow",
"����� (Gray Angel) �������",
"",
"yellow",
"������� (Lokk) �������",

"",
"yellow",
"���� (Ursus) �����",
"����� �������",
"",
"yellow",
"������ (Nike) ��������",
"���� (Vano) ��������",
"",
"",
"",
};


void InitInterface(string iniName)
{
	GameInterface.title = "";
	
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak", "ProcessCancelExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("My_MoveText", "MoveText", 0);

	SetFormatedText("INFO_TEXT", "");
	int i, k;
	
	for(i = 0; i < MAX_LINE; i++)
	{
		SendMessage(&GameInterface, "lsle", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 0, STR_TEXT[i] + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
		if(STR_COLOR[i] != "")
		{
			switch (STR_COLOR[i])
			{
				case "yellow":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,251,237,68));
				break;
				case "red":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,255,162,162));
				break;
				case "blue":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,0,255,255));
				break;
			}
		}
	}

	PostEvent("My_MoveText", 800);
	fNewPos = 0;
}

void ProcessCancelExit()
{
	if(CheckAttribute(&InterfaceStates, "showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}

	IDoExit(RC_INTERFACE_OPTIONSCREEN_EXIT);
	if(!CheckAttribute(&InterfaceStates, "InstantExit") || sti(InterfaceStates.InstantExit) == false) ReturnToMainMenu();
}

void IDoExit(int exitCode)
{
 	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("My_MoveText","MoveText");
    
	interfaceResultCommand = exitCode;
	if(CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit) == true)
		EndCancelInterface(true);
	else
		EndCancelInterface(false);
}

void MoveText()
{
	if(fNewPos >= 1)
	{
		ProcessCancelExit();
	}
	else
	{
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",2, fNewPos);
		PostEvent("My_MoveText", 20);
		fNewPos = fNewPos + 0.0002;
	}
}
