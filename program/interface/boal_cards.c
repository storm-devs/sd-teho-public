// boal 13.05.05
int scx, scy, spx, spy, sgxy, ssxy, smxy;
int move_i, dir_i, dir_i_start;
bool openExit;
bool cardMove;
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
	/*
	hearts_A,diamonds_A,clubs_A,spades_A  - 124x184
	blank - 124x184
	pack -  186x202
	gold, silver   - 100x100
	A - ace
	J - Jack
	Q - Queen
	K - King
	10..6 - other
	
	screen: -40..680 x -30..510  (720x540)
	*/
	
    sgxy = 50;
    ssxy = 70;
    
    scx = 114;
    scy = 170;
    
    spx = 172;
    spy = 188;
    
    openExit = false;  // можно ли прервать игру
	cardMove = false; // игрок перемещает карту
    
    pchar = GetMainCharacter();
    
    iRate  = sti(pchar.GenQuest.Cards.iRate); // ставки золотых
    
    //pchar.GenQuest.Cards.npcharIdx = GetCharacterIndex("Filosof"); // test
    
    npchar = GetCharacter(sti(pchar.GenQuest.Cards.npcharIdx));
    
	iMoneyP = sti(pchar.Money); // mitrokosta теперь смотрим на реальные деньги только в начале и в конце
	iMoneyN = sti(npchar.Money);
    
	// mitrokosta фикс опыта за некратные ставки -->
	if (iRate >= 100) {
            money_s = "silver";
            iExpRate = 1;
	}
	if (iRate >= 500) {
            money_s = "gold";
            iExpRate = 2;
	}
	if (iRate >= 1000) {
            money_s = "silver";
            SetNewPicture("SCROLLPICT", "interfaces\card_sukno.tga");
            iExpRate = 3;
	}
	if (iRate >= 5000) {
            money_s = "gold";
            SetNewPicture("SCROLLPICT", "interfaces\card_sukno.tga");
            iExpRate = 6;
	}
	if (iRate >= 10000) { // Jason Дороже золота
            money_s = "gold";
            SetNewPicture("SCROLLPICT", "interfaces\card_sukno.tga");
            iExpRate = 8;
	}
	// <--

    if (money_s == "gold")
    {
        smxy = sgxy;
    }
    else
    {
        smxy = ssxy;
    }
    CreateImage("BLANK","","", 0, 0, 0, 0); // выше всех
    
	CreateImage("Pack","CARDS","pack", 40, 203, 20 + spx, 199 + spy);

    SetNewPicture("ICON_2", "interfaces\PORTRAITS\64\face_" + pchar.faceId+ ".tga");
    
    CreateString(true,"Money","",FONT_NORMAL,COLOR_MONEY, 613,348,SCRIPT_ALIGN_CENTER,1.1);
    CreateString(true,"MoneyInChest","",FONT_NORMAL,COLOR_MONEY,615,292,SCRIPT_ALIGN_CENTER,1.3);
    
    if (rand(1) == 1)
    {
        dir_i  = -1;  // кто ходит - комп
    }
    else
    {
        dir_i  = 1;  // кто ходит - ГГ
    }
    dir_i_start = dir_i; // запомним кто начал
    
    CreateString(true,"Beta_P", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 380, 370, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_N", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 380, 210, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_Next", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 230, 310, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_MoneyN", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 210, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_WinLose", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 370, SCRIPT_ALIGN_LEFT,1.0);
    // новая игра
    NewGameBegin();
    iTurnGame = 1; // игра первая
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

		AddMoneyToCharacter(pchar, iMoneyP - sti(pchar.Money)); // mitrokosta раздача денег теперь в конце
		AddMoneyToCharacter(npchar, iMoneyN - sti(npchar.Money));
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
		// Jason Дороже золота
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game")) // идет квестовая игра
		{
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.G1")) DoQuestCheckDelay("GoldenGirl_Game1Res", 1.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.G2")) DoQuestCheckDelay("GoldenGirl_Game2Res", 1.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.G3")) DoQuestCheckDelay("GoldenGirl_Game3Res", 1.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.G4")) DoQuestCheckDelay("GoldenGirl_Game4Res", 1.0);
		}
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
                {   // еще одна игра
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
                {   // ГГ берет карты
                    if (bStartGame <2) break; // еще сдают
                    if (bStartGame == 100) break; // открываемся
                    
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
						if (cardMove) { // mitrokosta фикс множественного взятия
							break;
						} else {
							cardMove = true; // начинаем перемещение
						}
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
                    /*
                    else
                    {
                        PutNextCoinOp();
                        moneyOp_i++;
                        iMoneyN = iMoneyN - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsN[howNpchar] = cardsPack[howCard];
                        howNpchar++;
                    }  */
                    ShowMoney();
                }
    		}
    	break;
    	
    	case "B_ICON_1":
    		if(comName=="activate" || comName=="click")
    		{
                if (dir_i == 1 && bStartGame != 100 && bStartGame > 1 && !openExit) // только передача хода или открываемся
                {
                    dir_i = -1; // смена хода
                    SetNextTip();
                    if (dir_i_start == -1)// комп начинал игру первый
                    {
                        SetFormatedText("INFO_TEXT", "Open up!");
                        bStartGame = 100;
                        PostEvent("My_eOpenCards", 2000);
                    }
                    else
                    {// комп должен себе набрать
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
                //PlaySound("interface\knock.wav");
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
		cardMove = false; // закончили перемещение
        CreateImage("BLANK","","", 0, 0, 0, 0);
        PlaySound("interface\button3.wav");
        // перерисуем все карты на руках
        RedrawCards();
        
        // начало игры, по карте каждому -->
        if (bStartGame < 2)
        {
            dir_i = -dir_i; // смена хода
            bStartGame++;
            if (bStartGame == 1)  PostEvent("My_eStartGame", 500);
        }
        // начало игры, по карте каждому <--
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
    // тасуем карты
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
                //log_info(""+nextCard);
                howCard++;
                
        	}
    	}
    }
    /*howCard = 36;
    for (i=0; i<howCard; i++)
	{
        cardsPack[i] = i-20;
	}*/
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
    // монетки с запасом
    int i;
    for (i=35; i>=0; i--)
	{
        CreateImage("Money_"+i,"","", 0, 0, 0, 0);
        CreateImage("PCard"+i, "", "", 0, 0, 0, 0);
	}
	money_i = 0; // индекс монетки
    moneyOp_i = 0;
    iChest = 0; // на кону
    
    ShowMoney();
    
    // тасуем карты
    PackShake();
    howPchar  = 0; // карты на руках
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
// сдать карту
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
        if (ok == 1) RedrawCards(); // покажем перебор
		// Jason Дороже золота
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game")) // идет квестовая игра
		{
			if (ok == -1) // выиграл комп
			{
				if (iMoneyP > iRate)
				{
					sTemp += NewStr() + RandPhraseSimple("Let's keep playing!","Let's continue!");
				}
				else
				{
					bStartGame = 100;//признах запрета новой игры
					sTemp += NewStr() + "It's over, captain, you have no money to bet! You lost!";
					pchar.questTemp.GoldenGirl.Game.Fail = "true"; // ГГ проиграл
				}
			}
			else
			{
				if (iMoneyN > iRate) // есть деньги на игру
				{
					if (iMoneyP > iRate)
					{
						sTemp += NewStr() + RandPhraseSimple("Let's keep playing!", "Let's continue!");
					}
					else
					{
						bStartGame = 100;//признах запрета новой игры
						sTemp += NewStr() + "It's over, you have nothing to bet! You lost!";
						pchar.questTemp.GoldenGirl.Game.Fail = "true"; // ГГ проиграл
					}
				}
				else
				{
					bStartGame = 100;//признах запрета новой игры
						sTemp += NewStr() + "It's over, I have nothing to bet. You won!";
					pchar.questTemp.GoldenGirl.Game.Win = "true"; // ГГ выиграл
				}	
			}
		}
		else
		{
			if (CheckNextGame() && rand(10) < 10) // есть деньги на игру
			{
				sTemp += NewStr() + RandPhraseSimple("Another ride?","One more time?");
			}
			else
			{
				bStartGame = 100;//признах запрета новой игры
				sTemp += NewStr() + "That's it, I had enough!";
			}
		}
        SetFormatedText("INFO_TEXT", sTemp);
        ret = true;
    }
    else
    {
        ok1 = (CountCardsN() > 16) && (CountCardsN() <22);
        // жухло!!!!! -->
        if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game") && GetCharacterSkillToOld(pchar, SKILL_FORTUNE) + makeint(isEquippedArtefactUse(pchar, "totem_13", 0.0, 2.0)) < rand(12)) // Jason Дороже золота
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
        // жухло!!!!! <--
        
        if (ok1 || (iMoneyN - iRate) < 0)
        {
            if (dir_i == -1 && dir_i_start == 1)// комп ходит последним
            {
                SetFormatedText("INFO_TEXT", "That's good enough for me. Opens!");
                bStartGame = 100;
                PostEvent("My_eOpenCards", 2000);
                ret = true;
            }
            if (dir_i == -1 && dir_i_start == -1)// комп начинает
            {
                dir_i = 1;
                SetFormatedText("INFO_TEXT", "You go. I am full.");
                ret = true;
            }
        }
        else
        {
            if (dir_i == -1 && bStartGame >= 2) // комп играет сам
            {
				cardMove = true; // начинаем перемещение
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
    RedrawDeck(); // новая игра
    bStartGame = 0;
    SetFormatedText("INFO_TEXT","Dealing the cards. "+NewStr()+"Bid!");
    PostEvent("My_eStartGame", 1000);
}

void EndGameCount(int who)
{
    openExit = true;
    if (who == 1) // ГГ
    {
		iMoneyP += iChest;
    }
    else
    {
		iMoneyN += iChest;
    }
}

void OpenCards();
{
	int iRes = 0; // Jason Дороже золота
    string sTemp;
    if (CountCardsP() > makefloat(CountCardsN() + 0.1*dir_i_start)) // преимущество тому, кто сдает (те ходит последним)
    {
        EndGameCount(1);
        sTemp = RandSwear() + "You won. You have " + CountCardsP() +", I have " + CountCardsN()+"." ;
        iHeroWin++;
		iRes = 1; // Jason Дороже золота выиграл ГГ
    }
    else
    {
        EndGameCount(-1);
        sTemp = "I won. I have " + CountCardsN() +", you have " + CountCardsP()+".";
        iHeroLose++;
		iRes = -1; // Jason Дороже золота выиграл комп
    }
	// Jason Дороже золота
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game")) // идет квестовая игра
	{
		if (iRes == -1) // выиграл комп
		{
			if (iMoneyP > iRate)
			{
				sTemp += NewStr() + RandPhraseSimple("Let's keep playing!", "Let's continue!");
				bStartGame = 2;
			}
			else
			{
				bStartGame = 100;//признах запрета новой игры
				sTemp += NewStr() + "It's over, captain, you have no money to bet! You lost!";
				pchar.questTemp.GoldenGirl.Game.Fail = "true"; // ГГ проиграл
			}
		}
		else
		{
			if (iMoneyN > iRate) // есть деньги на игру
			{
				if (iMoneyP > iRate)
				{
					sTemp += NewStr() + RandPhraseSimple("Let's keep playing!", "Let's continue!");
					bStartGame = 2;
				}
				else
				{
					bStartGame = 100;//признах запрета новой игры
					sTemp += NewStr() + "It's over, you have nothing to bet! You lost!";
					pchar.questTemp.GoldenGirl.Game.Fail = "true"; // ГГ проиграл
				}
			}
			else
			{
				bStartGame = 100;//признах запрета новой игры
				sTemp += NewStr() + "It's over, I have nothing to bet. You won!";
				pchar.questTemp.GoldenGirl.Game.Win = "true"; // ГГ выиграл
			}	
		}
	}
	else
	{
		if (CheckNextGame() && rand(10) < 10) // есть деньги на игру
		{
			sTemp += NewStr() + RandPhraseSimple("One more round?","Again?");
			bStartGame = 2;
		}
		else
		{
			bStartGame = 100;//признах запрета новой игры
			sTemp += NewStr() + "We are done here!";
		}
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