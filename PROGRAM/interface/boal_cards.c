
int scx, scy, spx, spy, sgxy, ssxy, smxy;
int move_i, dir_i, dir_i_start;
bool openExit;
int  money_i, moneyOp_i;
string money_s;

ref npchar;

int cardsPack[36], cardsP[36], cardsN[36];
int howCard;

int howPchar, howNpchar;
int iRate, iMoneyP, iMoneyN, iChest, iExpRate;
int bStartGame;

int iTurnGame;
int iHeroLose, iHeroWin;

void InitInterface(string iniName)
{
    GameInterface.title = "";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("My_eventMoveImg","MoveImg",0);
	SetEventHandler("My_eStartGame","StartGame",0);
	SetEventHandler("My_eOpenCards","OpenCards",0);
	 
	
    sgxy = 50;
    ssxy = 70;
    
    scx = 114;
    scy = 170;
    
    spx = 172;
    spy = 188;
    
    openExit = false;  
    
    pchar = GetMainCharacter();
    
    iRate  = sti(pchar.GenQuest.Cards.iRate); 
    
    
    
    npchar = GetCharacter(sti(pchar.GenQuest.Cards.npcharIdx));
    
    switch (iRate)
    {
        case 100 :
            money_s = "silver";
            iExpRate = 1;
        break;
        
        case 500 :
            money_s = "gold";
            iExpRate = 2;
        break;
        
        case 1000 :
            money_s = "silver";
            SetNewPicture("SCROLLPICT", "interfaces\card_sukno.tga");
            iExpRate = 3;
        break;

        case 5000 :
            money_s = "gold";
            SetNewPicture("SCROLLPICT", "interfaces\card_sukno.tga");
            iExpRate = 6;
        break;
    }
    if (money_s == "gold")
    {
        smxy = sgxy;
    }
    else
    {
        smxy = ssxy;
    }
    CreateImage("BLANK","","", 0, 0, 0, 0); 
    
	CreateImage("Pack","CARDS","pack", 40, 203, 20 + spx, 199 + spy);

    SetNewPicture("ICON_2", "interfaces\PORTRAITS\64\face_" + pchar.faceId+ ".tga");
    
    CreateString(true,"Money","",FONT_NORMAL,COLOR_MONEY, 613,348,SCRIPT_ALIGN_CENTER,1.1);
    CreateString(true,"MoneyInChest","",FONT_NORMAL,COLOR_MONEY,615,292,SCRIPT_ALIGN_CENTER,1.3);
    
    if (rand(1) == 1)
    {
        dir_i  = -1;  
    }
    else
    {
        dir_i  = 1;  
    }
    dir_i_start = dir_i; 
    
    CreateString(true,"Beta_P", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 380, 370, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_N", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 380, 210, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_Next", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 230, 310, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_MoneyN", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 210, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_WinLose", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 370, SCRIPT_ALIGN_LEFT,1.0);
    
    NewGameBegin();
    iTurnGame = 1; 
    iHeroLose = 0;
    iHeroWin  = 0;
}

void ProcessBreakExit()
{
	Exit();
}

void ProcessCancelExit()
{
	Exit();
}

void Exit()
{
    if (openExit)
    {
        DelEventHandler("InterfaceBreak","ProcessBreakExit");
    	DelEventHandler("exitCancel","ProcessCancelExit");
    	DelEventHandler("ievnt_command","ProcessCommandExecute");
    	DelEventHandler("My_eventMoveImg","MoveImg");
    	DelEventHandler("My_eStartGame","StartGame");
    	DelEventHandler("My_eOpenCards","OpenCards");

        if (sti(pchar.GenQuest.Cards.SitType) == true)
    	{
			if(npchar.id == "AffairOfHonor_WolvesAndSheeps_Man")
			{
				DoQuestFunctionDelay("AffairOfHonor_AfterCards", 0.6);
			}
			else
			{
            DoQuestCheckDelay("exit_sit", 0.6);
    	}
    	}
        interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;

    	Statistic_AddValue(Pchar, "GameCards_Win", iHeroWin);
		Achievment_SetStat(pchar, 25, iHeroWin);
    	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*5*iHeroWin);
    	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*2*iHeroLose);
    	Statistic_AddValue(Pchar, "GameCards_Lose", iHeroLose);
		Achievment_SetStat(pchar, 26, iHeroLose);
    	
    	bQuestCheckProcessFreeze = true;
    	WaitDate("",0,0,0, 0, iTurnGame*15);
    	bQuestCheckProcessFreeze = false;
    	RefreshLandTime();
    	EndCancelInterface(true);

	}
	else
    {
        PlaySound("interface\knock.wav");
    }

}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	ref chr = GetMainCharacter();

	switch(nodName)
	{
    	case "B_PACK":
    		if(comName=="activate" || comName=="click")
    		{
                if (openExit == true)
                {   
                    if (bStartGame != 100)
                    {
                        dir_i = -dir_i_start;
                        dir_i_start = dir_i;
                        iTurnGame++;
                        NewGameBegin();
                        openExit = false;
                    }
                    else
                    {
                        PlaySound("interface\knock.wav");
                    }
                }
                else
                {   
                    if (bStartGame <2) break; 
                    if (bStartGame == 100) break; 
                    
                    if (dir_i == 1 && (iMoneyP - iRate) < 0)
                    {
                        PlaySound("interface\knock.wav");
                        SetFormatedText("INFO_TEXT", "You dry? What a shame.");
                        break;
                    }
                    if (dir_i == -1 && (iMoneyN - iRate) < 0)
                    {
                        PlaySound("interface\knock.wav");
                        SetFormatedText("INFO_TEXT", "Fuck, I am broke!");
                        break;
                    }
                    
                    if (dir_i == 1)
                    {
                        move_i = 0;
                        PlaySound("interface\took_item.wav");
                        PostEvent("My_eventMoveImg", 100);
                        
                        PutNextCoin();
                        money_i++;

                        iMoneyP = iMoneyP - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsP[howPchar] = cardsPack[howCard];
                        howPchar++;
                    }
                     
                    ShowMoney();
                }
    		}
    	break;
    	
    	case "B_ICON_1":
    		if(comName=="activate" || comName=="click")
    		{
                if (dir_i == 1 && bStartGame != 100 && bStartGame > 1 && !openExit) 
                {
                    dir_i = -1; 
                    SetNextTip();
                    if (dir_i_start == -1)
                    {
                        SetFormatedText("INFO_TEXT", "Open up!");
                        bStartGame = 100;
                        PostEvent("My_eOpenCards", 2000);
                    }
                    else
                    {
                        SetFormatedText("INFO_TEXT", "A card for me...");
                        
                        move_i = 0;
                        PlaySound("interface\took_item.wav");
                        PostEvent("My_eventMoveImg", 500);
                        
                        PutNextCoinOp();
                        moneyOp_i++;
                        iMoneyN = iMoneyN - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsN[howNpchar] = cardsPack[howCard];
                        howNpchar++;
                        ShowMoney();
                    }
                }
                else
                {
                    PlaySound("interface\knock.wav");
                }
    		}
    	break;
    	
    	case "B_ICON_2":
    		if(comName=="activate" || comName=="click")
    		{
                
    		}
    	break;
	}
}

void MoveImg()
{
    CreateImage("BLANK","CARDS","blank", 90+move_i*25, 210+ dir_i*move_i*22, 90 + scx+move_i*25, 210 + scy + dir_i*move_i*22);
    move_i++;
    if (move_i < 10)
    {
        PostEvent("My_eventMoveImg", 100);
    }
    else
    {
        CreateImage("BLANK","","", 0, 0, 0, 0);
        PlaySound("interface\button3.wav");
        
        RedrawCards();
        
        
        if (bStartGame < 2)
        {
            dir_i = -dir_i; 
            bStartGame++;
            if (bStartGame == 1)  PostEvent("My_eStartGame", 500);
        }
        
        SetNextTip();
        BetaInfo();
        CheckGame();
    }
}

void PutNextCoin()
{
    CreateImage("Money_"+money_i,"CARDS",money_s, 280+money_i*3, 280-money_i*3, 280+money_i*3 + smxy, 280-money_i*3 + smxy);
}
void PutNextCoinOp()
{
    CreateImage("Money_"+(18+moneyOp_i),"CARDS",money_s, 380+moneyOp_i*3, 280-moneyOp_i*3, 380+moneyOp_i*3 + smxy, 280-moneyOp_i*3 + smxy);
}

void PackShake()
{
    
    int  i;
    bool ok;
    int  nextCard;
    
    howCard = 0;
    while (howCard <36)
    {
        ok = false;
        while (!ok)
        {
            ok = true;
            nextCard = rand(35)+1;
            for (i=0; i<howCard; i++)
        	{
                if (nextCard == cardsPack[i])
                {
                    ok = false;
                    break;
                }
        	}
        	if (ok)
        	{
                cardsPack[howCard] = nextCard;
                
                howCard++;
                
        	}
    	}
    }
     
}
void RedrawCards()
{
    int i;
    string sTemp;
    int k;
    k = scx;
    if (howPchar > 6)
    {
        k = scx/2;
    }
    for (i=0; i<howPchar; i++)
	{
        sTemp = "c"+cardsP[i];
        CreateImage("PCard"+i,"CARDS", NullCharacter.Cards.(sTemp).pic, 400 - howPchar*k/2 + i*k , 394, 400 - howPchar*k/2 + i*k + scx, 394 + scy);
	}
	k = scx;
	if (howNpchar > 6)
    {
        k = scx/2;
    }
	for (i=0; i<howNpchar; i++)
	{
        sTemp = "c"+cardsN[i];
        sTemp = NullCharacter.Cards.(sTemp).pic;
        if (!openExit)
        {
            sTemp = "blank";
        }
        CreateImage("PCard"+(18+i),"CARDS", sTemp, 400 - howNpchar*k/2 + i*k , 36, 400 - howNpchar*k/2 + i*k + scx, 36 + scy);
	}
    
}
void RedrawDeck()
{
    
    int i;
    for (i=35; i>=0; i--)
	{
        CreateImage("Money_"+i,"","", 0, 0, 0, 0);
        CreateImage("PCard"+i, "", "", 0, 0, 0, 0);
	}
	money_i = 0; 
    moneyOp_i = 0;
    iChest = 0; 
    
    iMoneyP = sti(pchar.Money);
    iMoneyN = sti(npchar.Money);
    ShowMoney();
    
    
    PackShake();
    howPchar  = 0; 
    howNpchar = 0;
    SetNextTip();
    BetaInfo();
}

void SetNextTip()
{
    if (dir_i == 1)
    {
        if (bStartGame <2)
        {
            SetFormatedText("INFO_TEXT","You go."+NewStr()+"Bid!");
        }
        else
        {
            SetFormatedText("INFO_TEXT","Your turn!");
        }
    }
    else
    {
        if (bStartGame <2)
        {
            SetFormatedText("INFO_TEXT","Come to daddy."+NewStr()+"Coins on the table!");
        }
        else
        {
            SetFormatedText("INFO_TEXT","Now my turn!");
        }
    }
}
int CountCardsP()
{
    int ret = 0;
    int i;
    string sTemp;
    
    for (i = 0; i < howPchar; i++)
    {
        sTemp = "c"+cardsP[i];
        ret += sti(NullCharacter.Cards.(sTemp).count);
    }
    return ret;
}

int CountCardsN()
{
    int ret = 0;
    int i;
    string sTemp;

    for (i = 0; i < howNpchar; i++)
    {
        sTemp = "c"+cardsN[i];
        ret += sti(NullCharacter.Cards.(sTemp).count);
    }
    return ret;
}
void BetaInfo()
{
    if (bBettaTestMode)
    {
        GameInterface.strings.Beta_P       = "Beta_P " + CountCardsP();
        GameInterface.strings.Beta_N       = "Beta_N " + CountCardsN();
        GameInterface.strings.Beta_Next    = "Beta_Next " + NextCardPack();
        GameInterface.strings.Beta_MoneyN  = "Beta_MoneyN " + MakeMoneyShow(iMoneyN, MONEY_SIGN,MONEY_DELIVER);
        GameInterface.strings.Beta_WinLose = "Beta Win " + (Statistic_AddValue(Pchar, "GameCards_Win", 0)+iHeroWin) + " Lose " + (Statistic_AddValue(Pchar, "GameCards_Lose", 0)+iHeroLose);
    }
}
int NextCardPack()
{
    string sTemp;
    int ret;
    
    sTemp = "c"+cardsPack[howCard-1];
    ret = sti(NullCharacter.Cards.(sTemp).count);
    
    return ret;
}

void StartGame()
{
    move_i = 0;

    PlaySound("interface\took_item.wav");
    PostEvent("My_eventMoveImg", 100);

    if (dir_i == 1)
    {
        PutNextCoin();
        money_i++;

        iMoneyP = iMoneyP - iRate;

        howCard--;
        cardsP[howPchar] = cardsPack[howCard];
        howPchar++;
    }
    else
    {
        PutNextCoinOp();
        moneyOp_i++;
        iMoneyN = iMoneyN - iRate;
        howCard--;
        cardsN[howNpchar] = cardsPack[howCard];
        howNpchar++;
    }
    iChest += iRate;
    ShowMoney();
}

void ShowMoney()
{
    GameInterface.strings.Money        = MakeMoneyShow(iMoneyP,MONEY_SIGN,MONEY_DELIVER);
    GameInterface.strings.MoneyInChest = MakeMoneyShow(iChest,MONEY_SIGN,MONEY_DELIVER);
}

bool CheckGame()
{
    string sTemp;
    int   ok = 0;
    bool  ok1;
    bool  ret = false;
    
    if (CountCardsP() > 21)
    {
        ok = -1;
        sTemp = "Ha! You are going bust, pal. Lucky me!";
        iHeroLose++;
    }
    if (CountCardsN() > 21)
    {
        ok = 1;
        sTemp = RandSwear() + "For f... Bust! You won...";
        iHeroWin++;
    }
    if (ok != 0)
    {
        EndGameCount(ok);
        if (ok == 1) RedrawCards(); 
        
        if (CheckNextGame() && rand(10) < 10) 
        {
            sTemp += NewStr() + RandPhraseSimple("Another ride?","One more time?");
        }
        else
        {
            bStartGame = 100;
            sTemp += NewStr() + "That's it, I had enough!";
        }
        SetFormatedText("INFO_TEXT", sTemp);
        ret = true;
    }
    else
    {
        ok1 = (CountCardsN() > 16) && (CountCardsN() <22);
        
        if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) + makeint(isEquippedArtefactUse(pchar, "totem_13", 0.0, 2.0)) < rand(12))
        {
            if (ok1 && (CountCardsN() + NextCardPack()) <= 21)
            {
                ok1 = false;
            }
            if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) - makeint(isEquippedArtefactUse(pchar, "totem_13", 0.0, 2.0)) < rand(10) && CountCardsN() < 17 && (CountCardsN() + NextCardPack()) > 21)
            {
                ok1 = true;
            }
        }
        
        
        if (ok1 || (iMoneyN - iRate) < 0)
        {
            if (dir_i == -1 && dir_i_start == 1)
            {
                SetFormatedText("INFO_TEXT", "That's good enough for me. Opens!");
                bStartGame = 100;
                PostEvent("My_eOpenCards", 2000);
                ret = true;
            }
            if (dir_i == -1 && dir_i_start == -1)
            {
                dir_i = 1;
                SetFormatedText("INFO_TEXT", "You go. I am full.");
                ret = true;
            }
        }
        else
        {
            if (dir_i == -1 && bStartGame >= 2) 
            {
                move_i = 0;
                PlaySound("interface\took_item.wav");
                PostEvent("My_eventMoveImg", 500);

                PutNextCoinOp();
                moneyOp_i++;
                iMoneyN = iMoneyN - iRate;
                iChest += iRate;
                howCard--;
                cardsN[howNpchar] = cardsPack[howCard];
                howNpchar++;
                ShowMoney();
                
                ret = true;
            }
        }
    }
    return ret;
}

void NewGameBegin()
{
    RedrawDeck(); 
    bStartGame = 0;
    SetFormatedText("INFO_TEXT","Dealing the cards. "+NewStr()+"Bid!");
    PostEvent("My_eStartGame", 1000);
}

void EndGameCount(int who)
{
    openExit = true;
    if (who == 1) 
    {
        AddMoneyToCharacter(pchar, iChest - (sti(pchar.Money) - iMoneyP));
        AddMoneyToCharacter(npchar,  -(sti(npchar.Money) - iMoneyN));
    }
    else
    {
        AddMoneyToCharacter(pchar, -(sti(pchar.Money) - iMoneyP));
        AddMoneyToCharacter(npchar, iChest - (sti(npchar.Money) - iMoneyN));
    }
}

void OpenCards();
{
    string sTemp;
    if (CountCardsP() > makefloat(CountCardsN() + 0.1*dir_i_start)) 
    {
        EndGameCount(1);
        sTemp = RandSwear() + "You won. You have " + CountCardsP() +", I have " + CountCardsN()+"." ;
        iHeroWin++;
    }
    else
    {
        EndGameCount(-1);
        sTemp = "I won. I have " + CountCardsN() +", you have " + CountCardsP()+".";
        iHeroLose++;
    }
    if (CheckNextGame() && rand(10) < 10) 
    {
        sTemp += NewStr() + RandPhraseSimple("One more round?","Again?");
        bStartGame = 2;
    }
    else
    {
        bStartGame = 100;
        sTemp += NewStr() + "We are done here!";
    }
    SetFormatedText("INFO_TEXT", sTemp);
    RedrawCards();
}
bool CheckNextGame()
{
    bool ret = true;
    if (iRate*3 > iMoneyN) ret = false;
    if (iRate*3 > iMoneyP) ret = false;
    
    return ret;
}
