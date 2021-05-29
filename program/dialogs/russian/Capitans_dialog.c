// разговор с капитаном на палубе  Boal
//homo 25/06/06
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
    //homo Осады
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap, sGroup;
    string fort;

    if (CheckAttribute(aData, "nation"))
    {
	    sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
	    sGroup = "Sea_"+sCap+"1";
	    
	   // string myships  = GetCompanionQuantity(PChar);
       // string escships = Group_GetCharactersNum(sGroup);
        
        switch(sti(aData.conation))
        {
            case 0:  fort = "English fort"; break;
            case 1:  fort = "French fort"; break;
            case 2:  fort = "Spanish fort"; break;
            case 3:  fort = "Dutch fort"; break;
            case 4:  fort = "Pirate fort"; break;
        }
        int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
        int fortDamage = CheckFortInjuri();
        int SquadronDamage = CheckSquadronInjuri();
        
    }

    int iMoney;
	ref sld;
    
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		if(sti(npchar.money) > CAP_MAX_MONEY || sti(npchar.money) < CAP_MIN_MONEY) 	
		{
			npchar.money = CAP_MIN_MONEY + rand(CAP_NORM);
		}
	}
    //homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "First time":
			if (!bDisableMapEnter)
			{
				//--> Jason эскорт 2 уровень
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "begin" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Hello, captain. Goddammit, you have no idea how glad I am to see you!";
					link.l1 = "Hi. Allow me to introduce myself - " + GetFullName(PChar) + ". I am glad to see you alive and kicking as well, I've come here specifically to seek you out - and your ship.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Have you brought the material I requested?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "Yes. Everything you need to repair your vessel is in my hold.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "No, I'm still working on it.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Ahoy, " + GetAddress_Form(NPChar) + ". My name is " + GetFullName(NPChar) + ", I am the captain of this ship. Allow me to express my sincerest gratitude for your help in a fight with this damned pirate scum - if you hadn't interfered, things could have turned out pretty grim for us. You actually saved us, goddammit!";
					link.l1 = "It was nothing,  " + GetAddress_FormToNPC(NPChar) + ". Allow me to introduce myself - " + GetFullName(PChar) + ", I came to you at the request of harbor master "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". He briefed about the misadventures of your caravan and sent me to find your ship.";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
					Pchar.GenQuest.MoneyForCaptureShip = makeint(Group_GetLiveCharactersNum( GetGroupIDFromCharacter(NPChar)))*(7 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					dialog.text = "Hold on, you may kill me this way. What do you want from me?";
					//выкуп
					link.l1 = "Let's resolve this matter peacefully. Ransom, I guess, will be the best decision. A sum of "+Pchar.GenQuest.MoneyForCaptureShip+" pesos will suit me fine, "+GetAddress_FormToNPC(NPChar)+". And after that you can get lost!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "I would like to see what you've got in your hold. And after that you and your crew can go wherever you want.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "Hello, mynheer. Nice seeing you. Captain Longway probably will come on board later, right?";
					link.l1 = "Good afternoon, mynheer Stuyvesant. Allow me to introduce myself - " + GetFullName(pchar) + ". Longway will not come, he's not on 'Meifeng'.";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					dialog.text = "Ahoy, captain. What has brought you to my flute?";
					link.l1 = "Good afternoon, mynheer Keller. Allow me to introduce myself - " + GetFullName(pchar) + ". I have come for your aid in some unusual affair.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! I am "+ GetFullName(NPChar) +" - captain of a ship belonging to the "+NationKingsName(NPChar)+". fleet. What has brought you on board of my ship?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! I am captain "+ GetFullName(NPChar) +". What has brought you on board of my ship?";
    			}
    			link.l1 = "My name is " + GetFullName(Pchar) + ". I have some business to you!";
    			link.l1.go = "quests";
                link.l2 = "Oh, nothing, just "+ GetSexPhrase("came","came") +" to greet you!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "Haven't you noticed, , " + GetAddress_Form(NPChar) + ", that we're in a battle? It's not time for talking!";
    			link.l1 = "Absolutely agree! I will return to my ship.";
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "I am listening to you very attentively,  " + GetAddress_Form(NPChar)+".";
                link.l1 = "I want to know the latest news of the archipelago.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //
                if (CheckAttribute(NPChar, "EncGroupName")) // только для фантомов грабеж
                {
                    link.l2 = RandPhraseSimple("Do you have any idea who I am? I think, it's perfectly clear that my guns can make a sieve of your old tub. Let's resolve this in a peaceful manner. Ransom is fine decision to me.",
                                               "Only us... and the sea... What do you think about appeasing my men... for your own safety?.");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "Where are you coming from?";
	    			link.l3.go = "price_1";
	    			link.l4 = "Wanna trade?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "I am looking for a pirate ship acting in these waters. Have you seen anything suspicious?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "Wanna relax?";
			    link.l5.go = "Play_Game";
                link.l9 = "I guess I should go.";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "I'm not authorized to deal with you. Talk to the commander of our squadron. His name is  " + GetFullName(characterFromID(NPChar.MainCaptanId))+
                              ", you can find him on the " + XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName) + " '" + characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name + "'.";
                link.l1 = "Thanks. I'll do as you say.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "Why not?";
			link.l1 = "Let's take a look at the goods.";
			link.l1.go = "Trade_2";
			link.l2 = "Sorry, but I've changed my mind"+ GetSexPhrase("","") +".";
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = "What are you suggesting?";
			link.l1 = "Wanna play a game of cards for some serious money?";
			link.l1.go = "Card_Game";
   			link.l2 = "How about rolling some dice in poker-joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "I am sorry, but I have some business to do.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "I won't gamble with crooks!";
    			link.l1 = "As you wish.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "Why not? I certainly wouldn't mind a break...";
    			link.l1 = "Excellent.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "What are the rules?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Well, let's begin, then!";
			link.l1.go = "Cards_begin";
			link.l3 = "No, it's not for me...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "Let's agree on the bet, first.";
			link.l1 = "Let's play for 100 pesos.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Let's play for 500 pesos.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "I guess I should go.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Are you joking or what? You have no money!";
                link.l1 = "It happens.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Well, that's enough, or I won't have enough money to maintain the ship...";
                link.l1 = "Pity.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Fine, let's play for 100 coins.";
			link.l1 = "Let's begin!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Are you joking or what? You don't have 1500 pesos!";
                link.l1 = "I'll find them!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "No, these bets will certainly get me in the end.";
                link.l1 = "As you wish.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Fine, let's play for 500 coins.";
			link.l1 = "Let's begin!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "I won't gamble with crooks!";
    			link.l1 = "As you wish.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Why not! Relaxing is always good for health... but not always for the purse...";
	    			link.l1 = "Excellent.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "What are the rules of our game?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "No, I am done for today. I've got things to do.";
	    			link.l1 = "As you wish.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Well, let's begin, then!";
			link.l1.go = "Dice_begin";
			link.l3 = "No, it's not for me...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "Let's agree on the bet, first.";
			link.l1 = "Let's play for 50 pesos.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Let's play for 200 pesos.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "I guess I should go.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "You are well-known as a"+ GetSexPhrase("cheater","cheater") +".. I will never roll dice with you.";
                link.l1 = "It's all lies! Well, so be it.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Are you joking or what? You have no money!";
                link.l1 = "It happens.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "That's enough! I am done with gambling - before they label me as a peculator and force me to leave a ship.";
                link.l1 = "Pity.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Fine, let's play for 50 coins.";
			link.l1 = "Let's begin!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "You are well-known as a"+ GetSexPhrase("cheater","cheater") +". I will never roll dice with you.";
                link.l1 = "It's all lies! Well, so be it.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "I heard that you're a very good player. I won't be playing high stakes with you.";
                link.l1 = "Shall we lower the bet, maybe?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "I am sorry, but I have to go.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Are you joking or what? You don't have 1500 pesos!";
                link.l1 = "I'll find them!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "No, these bets will certainly get me in the end.";
                link.l1 = "As you wish.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Fine, let's play for 200 coins.";
			link.l1 = "Let's begin!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = "Why do you want to know? This is my privacy.";
					Link.l1 = "As you wish.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "I am coming from the city of" + GetCityName(sld.City) + ".";
					Link.l1 = "What are the prices of goods at the local store?";
					Link.l1.go = "price_2";
					Link.l9 = "I should go.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "I have told you everything already. Don't bother me for nothing.";
				Link.l1 = "Yeah, you're right. Farewell.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "Here you go... (you have received the price list)..";
			Link.l1 = "Thank you very much!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            {
                Dialog.text = "Ha-ha-ha! Great joke, I've got more ships. Return to your ship and drown with it.";
                link.l1 = "More doesn't mean stronger, buddy.";
                link.l1.go = "Boarding";
            }
            else
            {
                if(rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)) )
                {
                    Dialog.text = "Captain, you shouldn't have done your dirty business on the board of my ship. But I will show mercy and let you return to your ship to drown with it.";
                    link.l1 = "We'll see, who's gonna become shark's food today!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName))*(7 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
                    Dialog.text = RandSwear() + "Yes, I've heard a lot about your outrages. So be it, but remember " +
                                  XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + " won't let it go unpunished!";
                    link.l1 = "Excellent. A sum of "+Pchar.GenQuest.MoneyForCaptureShip+" pesos will suit me fine, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "Oh, nevermind. I was simply joking"+ GetSexPhrase("","") +"!";
                    link.l2.go = "exit";
                }
            }
            // тут нужен учет запрета повторного наезда
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal злопамятность :)
        break;
		
		case "surrender1" :
			Diag.TempNode = "surrender_goaway";
            Dialog.Text = "Here you go - and now get lost!";
			Link.l1 = "Nice! And you stay healthy too, friend!";
			Link.l1.go = "exit";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -2); 		
			ChangeCharacterComplexReputation(pchar,"authority", 1.0); 							
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 7 + rand(10));
		break;
		
		case "surrender_goaway":
			Dialog.Text = "What else do you want from me?";
			Link.l1 = "Nothing.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "Seems, I have no other choice rather than submitting to you.";
			link.l1 = "Move on, now!";
			link.l1.go = "surrender3";				
		break;
						
		case "surrender3":
			Diag.TempNode = "surrender_goaway";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			DialogExit(); 
			LaunchTransferMain(pchar, sld, "Transfer");
		break;
				
        case "rumours":
			Dialog.Text = SelectRumour(); // to_do
			Link.l1 = RandPhraseSimple(RandSwear() + "This is very interesting. Another question?",
                                     "Just another affair.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Thanks, and I should go.",
                                     "All the best.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "Get out of my ship!";
			Link.l1 = "I am already leaving.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "Our conversation is over. I'm not gonna tell you anything new "+GetAddress_Form(NPChar)+".";
			Link.l1 = "All right. See you at the sea!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "Here you go - and now get out!";
			Link.l1 = "Nice!";
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 7 + rand(10));
        break;

        case "Boarding":
            if (CheckAttribute(NPChar, "MainCaptanId"))
            {
                PChar.StartBattleAfterDeck = true;
                PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
                PChar.StartBattleEncGroupName = NPChar.EncGroupName;
            }
            DialogExit();
            Diag.CurrentNode = Diag.TempNode;
        break;
        
        case "QuestAboardCabinDialog":  // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = "Hold on, you may kill me this way. What do you want from me?";
			Link.l1 = "To kill you!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "Surrender!";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "Отдай нам карту, Билли (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "Well, we'll see, bastard!";
			Link.l1 = "And what do I have to see?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "Fine, you won!";
			Link.l1 = "Smart decision!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "Hope you choke on it!";
			Link.l1 = "Very good, get into shackles and shut your mouth, prisoner.";
			if (rand(1) == 1)  // пример!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
			    Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;
		
		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = ""+ GetSexPhrase("Came here","Came here") +", made a mess"+ GetSexPhrase("","") +",and took everything"+ GetSexPhrase("","") +", now you wanna make me a slave? Never!";
			Link.l1 = "Then prepare to die.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "No, I haven't seen any suspicious ship that looked like pirates.";
			Link.l1 = "I see.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "In the name of "+NationKingsName(NPChar)+" surrender, "+ GetSexPhrase("filthy pirate","foul wench!") +"! Then your life will be spared until a fair tribunal, where you will be judged for all "+NationNameSK(sti(NPChar.nation))+"ships that you have plundered"+ GetSexPhrase("","") +".";
			Link.l1 = "Screw you! You should surrender!";
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;
		
		case "Siegehelp":		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			
    			dialog.text = "I am listening, but please be quick, we have a battle with " + fort +
                          "right now, and I must rule the battle.";
                link.l1 = "That is why I am here,  " + GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "attack_fort";

                link.l2 = "In that case I won't take anymore of your time. Farewell, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "I am not authorized to deal with you. Talk to the commander of our squadron. His name is  " + GetFullName(rchar)+
                              ", you can find him on " + XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName) + " ''" + rchar.Ship.Name + "''.";
                link.l1 = "Thanks. I'll do as you say.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "And what do you mean?";
                link.l1 = "I can assist you in a crushing the fort of the colony of " +GetConvertStr(aData.Colony+" Town", "LocLables.txt")+ " and capture the city, and a prey, resulting in the case of our success, we divide among us.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "Actually, my business is hardly worth your time. Farewell, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "You again? I though we had already discussed everything.";
            link.l1 = "You're right. I guess I've forgotten"+ GetSexPhrase("","") +".";
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
            Diag.TempNode = "Siegehelp_0";

		break;
		
		case "Siegehelp_1":
            SiegeResult("");
            if (sti(aData.win)==0)
            {
                dialog.text = "And what share of loot are you expecting to receive?";
                link.l1 = "A half.";
                link.l1.go = "Big_part";
                link.l2 = "One third.";
                link.l2.go = "Middle_part";
                link.l3 = "A quarter.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "I have no need in your services, captain! I will seize this colony by myself and I need no help in doing that.";
                link.l1 = "Why are you so certain, " + GetAddress_FormToNPC(NPChar) + ", anyone can have a stroke of bad luck.";
                link.l1.go = "attack_fort_03";
                link.l2 = "In that case I'll take no more of your time, " + GetAddress_FormToNPC(NPChar) + ". Farewell!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "On the other hand, my ships are pretty damaged in this battle, and reinforcements certainly wouldn't hurt. If you agree on " + GetPart(4) + ", then, I guess, we could come to an agreement.";
                link.l1 = "That suits me, " + GetAddress_FormToNPC(NPChar) + ". I will try to assault the fort, and you will support us with the fire of your ship's guns.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "I'm not so cheap, " + GetAddress_FormToNPC(NPChar) + ". I am sorry for the distraction"+ GetSexPhrase("","") +" you from pressing affairs. Goodbye!";
                link.l2.go = "exit";
            }else{
                dialog.text = "There are enough ships in my squander to reduce this fort to dust - it's only a matter of time. And now, could you please leave my ship? Victory awaits me!";
                link.l1 = "Well, in that case, " + GetAddress_FormToNPC(NPChar) + ", allow me to take my leave. Farewell!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "The fort cannons have damaged my ships severely, and we might surely be the losing side in the upcoming battle. I accept your help and I agree on your terms.";
                link.l1 = "Excellent, " + GetAddress_FormToNPC(NPChar) + ", in that case we will try to assault the fort, and you will support us with the fire of your ship's guns.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 2;
            }
            else
            {
                dialog.text = "Isn't it too much, captain? You have " + GetNumShips(GetCompanionQuantity(PChar)) +
                              ", and my squadron has " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". I can offer you " + GetPart(4) +
                              ". And consider it fair.";
                aData.PartAttaksFort = 4;
                link.l1 = "I agree"+ GetSexPhrase("","") +", " + GetAddress_FormToNPC(NPChar) + ", in that case I will assault the fort, and you will support us with the fire of your ship's guns.";
                link.l1.go = "attack_fort_04";
                link.l2 = "Unfortunately, I don't think so, " + GetAddress_FormToNPC(NPChar) + ". There's nothing more to discuss. Farewell.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "As soon as the fort is captured, we will start to deploy landing parties on the shore, and then we will continue fighting in the town itself, where I hope to meet with you.";
            link.l1 = "So be it. See you soon, " + GetAddress_FormToNPC(NPChar) + "!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "I think I will agree on your terms. Joint operation will increase my chances to win this fight. If everything goes as planned, you will receive your share of the loot.";
                link.l1 = "It's great that we've come to an agreement, " + GetAddress_FormToNPC(NPChar) + ". I will order my men to assault the fort immediately.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
                dialog.text = "Isn't it too much, captain? You have " + GetNumShips(GetCompanionQuantity(PChar)) + ", and my squadron has " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". I can offer you " + GetPart(4) + ". And consider it fair.";
                link.l1 = "I "+ GetSexPhrase("agree","agree") +", " + GetAddress_FormToNPC(NPChar) + ", in that case I will assault the fort, and you will support us with the fire of your ship's guns.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Unfortunately, I don't think so, " + GetAddress_FormToNPC(NPChar) + ". There's nothing more to discuss. Farewell.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "My ships are weary, and any fresh force is welcome in this situation. I accept your help and I agree on your terms.";
            link.l1 = "I am glad"+ GetSexPhrase("","") +", " + GetAddress_FormToNPC(NPChar) + ".. I will immediately order my men to begin the assault of the fort.";
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // все, все свободны
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = "Hello, captain! That certainly was a hard battle, but we managed to break the furious resistance of the town's defenders. We have plundered " + sti(aData.loot)+
                          " pesos. According to our deal, your share is "+ilt+
                          ". Please accept this money; you certainly deserve every last coin of it. And now please excuse me, but I must return to my business.";
            link.l1 = "In that case, I will leave you, " + GetAddress_FormToNPC(NPChar) + ". Farewell!";
            link.l1.go = "exit";
            //AddDialogExitQuest("End_Siege_and_Attaks_City");

            Diag.TempNode = "no_return_02";
            AddMoneyToCharacter(PChar, ilt);
            ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            ChangeCharacterComplexReputation(PChar,"nobility", 10);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
            AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
            aData.loot = sti(aData.loot) - ilt;
            if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
            //--> слухи
            SiegeRumour("I've been told that you had helped our squadron in the assault of the "+NationNameSK(sti(aData.conation))+" colony - "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+"! We're so thankfull to you, "+ GetAddress_Form(NPChar)+".", "", sti(aData.nation), -1, 30, 3);
            //<-- слухи
		break;

        case "no_return_02":
            dialog.text = "Ahoy, captain! Do you have business to me?";
            link.l1 = "No, " + GetAddress_FormToNPC(NPChar) + ". Goodbye!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "I am listening to you, but please be quick about the goal of your visit, I don't have much time. I have an important and secret mission, and also I am ordered to sink all suspicious ships in the open sea, which could present any danger to our convoy.";                          
                link.l1 = "In that case I won't take anymore of your time. Good luck, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "I am not authorized to deal with you. Talk to the commander of our squadron. His name is " + GetFullName(rch)+
                              ", you can find him on " + XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName) + " ''" + rch.Ship.Name + "''.";
                link.l1 = "Thanks. I'll as you say.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "Nice to meet you, and my name is " + GetFullName(npchar) + ". So you have come to help us? In that case I am especially glad, since our current situation is critical indeed - we are alone at the shores of an uninhabited island, the ship is hardly seaworthy, the crew has suffered heavy losses...";
			link.l1 = "Like I heard, you had a battle with pirates, and then there was that storm...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "Correct. My ship was badly damaged in the battle - we even had to stand againts a boarding attack led by those pirate bastards. Later, a storm caught us… oh, I don't want even think about it. We were carried to this inhospitable shore. We had been praying a whole day to the Blessed Virgin to save us from the storm and to keep our anchor chains in one piece\nAnd here we are. We have been repairing our ship for a week, but see for yourself: only fifty men left and we also lack of wooden planks - and where are we supposed to get them from? Jungles? Obviously. Working hard every day and yet we only have the fifth part of total material needed\nSailing with such damage is as good as suicide. Now you see how we are doing here, captain...";
			link.l1 = "Yeah... Your situation is unenviable. Let's think what we could undertake and how I can help you.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "Eh, I wish we had enough planks and sailcloth - in such case we would repair our ship in a week\nCaptain, since you've come here on purpose, perhaps you could visit the nearest port and buy materials we need? This would solve our problem. Don't worry about coins, I will compensate all expenses.";
			link.l1 = "Of course. What exactly do you need to deliver, and how much?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + drand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + drand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + drand(7)*10;
			dialog.text = "I have already figured all this out. Considering what we already have, I need "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" planks, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" sailcloth and "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" cotton. With these materials, we would manage to repair the ship in one week and then we could set sail.";
			link.l1 = "Okay. I will bring you all materials which you need. Wait for me - I'll return no later than in ten days.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "Thanks a lot, captain! Now that's a weight off my mind. We will be waiting and praying for your successful return!";
			link.l1 = "Don't you worry. Soon you will have everything you need for the repair.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "27");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sIsland", XI_ConvertString("Colony"+pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sQty1", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)));
			AddQuestUserData("Escort", "sQty2", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)));
			AddQuestUserData("Escort", "sQty3", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)));
			Diag.TempNode = "WM_Captain_again";
			SetFunctionTimerCondition("WM_Captain_Over", 0, 0, 11, false);
			pchar.questTemp.WPU.Escort = "wait";
		break;
		
		case "WM_Captain_again":
			dialog.text = "We will be eagerly waiting for your return, captain!";
			link.l1 = "Weigh anchors!";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "Excellent! Now we can start to repare the ship!";
			link.l1 = "My men will give you a hand - this way it will be faster. Besides, I must accompany you to the colony of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+", so the sooner we're done with the repairing, the better for me.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "Really, I have no idea how to thank you properly, captain... Please order to unload the materials in a cove called " + XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore) + " - there we have everything ready for repairing.";
			link.l1 = "Fine. We'll meet on the shore.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "When will we begin the repairing, captain? I'll be waiting for you on the shore.";
			link.l1 = "Yes, of course. I am leaving now.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "Well, everything seems ready for the repairing. I think we should be done in about five days.";
			link.l1 = "Very good! I was going to explore this island anyway, so I will make good use of this time.";
			link.l1.go = "Repair_start_1";
		break;
		
		case "Repair_start_1":
			DialogExit();
			pchar.quest.WM_Captain_Over.over = "yes";//снять прерывание
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			RemoveCharacterGoods(pchar, GOOD_PLANKS, sti(pchar.questTemp.WPU.Escort.Planks));
			RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, sti(pchar.questTemp.WPU.Escort.Sailcloth));
			RemoveCharacterGoods(pchar, GOOD_COTTON, sti(pchar.questTemp.WPU.Escort.Linen));
			DoQuestFunctionDelay("RepairShip_WithoutMasts", 5.0);
		break;
		
		case "Repair_end":
			dialog.text = "Well, that's it. We're done with the repairing, and the ship is ready to set sail. When do we depart, captain?";
			link.l1 = "If you are ready, I see no point in hanging in there. Weigh anchors!";
			link.l1.go = "Repair_end_1";
		break;
		
		case "Repair_end_1":
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("Escort", "30");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity));
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//деньги за материалы
			dialog.text = "I want to thank you one more time, captain - you greatly helped me and my crew to get out of that scrape. Like I promised, I will compensate the costs of the materials needed to repair my ship. Here are "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", please, take them. And this is my personal gift to you.";
			link.l1 = "I was happy to help you.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(drand(10)+1), 1);
			dialog.text = "And now, it's time to say goodbye, captain. Don't forget to visit the port authority - you are being waited there. See you!";
			link.l1 = "Have a nice day, " + npchar.name + "!";
			link.l1.go = "WMShip_final_2";
		break;
		
		case "WMShip_final_2":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) AddQuestRecord("Escort", "31");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) AddQuestRecord("Escort", "37");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S")) AddQuestRecord("Escort", "40");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		break;
		
		case "VSP_Captain":
			dialog.text = "Is that so? And I was thinking that they had forgotten us. Yeah, my ship got the worst of all. We were left to struggle the elements of nature after the storm forced the pirates to stop an attack of our caravan. We were carried to this inhospitable shore\nSpent a few days repairing and resting. This pagans attacked us again, as soon as we were going to sail away\nAnd then the storm hit us again - we thought that the Lord finally decided to finish us, but you arrived. Thanks the Holy Mary! Thank you again, captain!";
			link.l1 = "It's all over, " + GetAddress_FormToNPC(NPChar) + ". Now I must escort you to "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+", in order to protect it from other possible troubles. Are you ready to go now? The storm has already begun to decline.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "But of course! The sooner we leave this place, the calmer my men will be - they have already suffered too much. Let's set sail!";
			link.l1 = "Just follow my ship - and calm down your crew, there is nothing to fear now.";
			link.l1.go = "VSP_Captain_2";
		break;
		
		case "VSP_Captain_2":
			pchar.quest.DisasterShip_GetOut.over = "yes";
			DialogExit();
			Group_DelCharacter("WMShip", "WMCaptain");//иначе будет клон
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			AddQuestRecord("Escort", "36");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of"+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.questTemp.WPU.Escort = "win";
			pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
			pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
			Diag.currentnode = "VSP_Captain_again";
			Delete_EscortStorm();//уберем шторм
		break;
		
		case "VSP_Captain_again":
			dialog.text = "Should we set sail, captain?";
			link.l1 = "Sure. I will return to my ship now.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "I want to thank you one more time, captain - you greatly helped me and my crew to get out of this scrape. Here are"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". The entire crew chipped in, so don't even think to renounce it. And this is my personal gift to you.";
			link.l1 = "I was happy to help you!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "I want to thank you again, captain, for saving our asses from this mess. Here, accept these coins - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  and here, take this gift. It's not much, but this is all I can do to thank you for what you've don. Please, don't reject the offer\nMy former crew is amazed by you and your fighting with the Indians and pirates. All of them are wishing to join you. I hope that you won't refuse an application of loyal services from sailors who have just lost their vessel?";
			link.l1 = "Of course, not. I will gladly keep it. I was happy to help you!";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			dialog.text = "Okay. But, mynheer, would you explain what is happening here? How come that you are in command of 'Meifeng'! Did something happen to Longway?";
			link.l1 = "I have all explanations you need - and some other important information as well.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "Then I am all ears.";
			link.l1 = "There was a coup in Willemstad. Lucas Rodenburg took the place of the governor and has put Matthias Beck in prison on a ridiculous suspicion that he had connections with British intel.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Hmm... Mynheer, the things you're telling me are truly surprising. I had received news from Willemstad not so long ago, and there was nothing like that in it.";
			link.l1 = "Please hear me out, mynheer Stuyvesant. You must have gotten the news through Rodenburg, and he must be sure that you won't get to Curacao.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "Mister, I like what you're saying less and less. Just who are you?";
			link.l1 = "I am just a captain and just a man not indifferent to the fate of Dutch colonists. Lucas Rodenburg ordered Longway to destroy your ship and kill you as well. And since 'Meifeng' would not cause you to become suspicious, he would have carried it out without any effort.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "So, you mean to say that Lucas...";
			link.l1 = "Decided to remove you from power in the easiest way possible - by simply eliminating you. Save for you, there is no other person in the region capable of putting up any significant resistance to Rodenburg's influence on the Archipelago.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "I can't believe it!";
			link.l1 = "I didn't fall for that crap with Beck connected to English intel and did undertake my own investigation. I found out that 'Meifeng', loaded with picked cutthroats, left for Philipsburg. I've run them down and gave them battle. Longway was captured, and he gave me all this information, including your whereabouts.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "Hm... That seems probable. No one, save for Rodenburg, knew or could know about me schedule and route! Goddammit! It's treason! Where is Longway?!";
			link.l1 = "I have set him free in exchange for his voluntary confession. I must say, he was not too eager to carry out Rodenburg's order, but neither could he disregard it. He also said that he would not return to Rodenburg's service - this last dirty affair made his cup run over.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "All right... Captain " + GetFullName(pchar) + ", you will go to Willemstad with me. You will sail on 'Meifeng' ahead of my ship. If what you've said is true, Lucas must be arrested, and you will provide your assistance in this. But if you lied to me... You have only yourself to blame.";
			link.l1 = "For me, there is no point in lying to you, mynheer. Let's hurry!";
			link.l1.go = "Stivesant_9";			
		break;
		
		case "Stivesant_9":
			DialogExit();
			Diag.CurrentNode = "Stivesant_10";
			AddQuestRecord("Holl_Gambit", "3-52");
			pchar.questTemp.HWIC.Self = "WayWithStivesant";
			Group_DelCharacter("Stivesant_Halleon", "Stivesant");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = 40;
			DeleteAttribute(npchar, "LifeDay");
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Seek_Piter.win_condition.l2 = "Day";
			pchar.quest.Seek_Piter.function = "StivesantOnStreet";
			pchar.quest.Terms_Over.win_condition.l1 = "Timer";
			pchar.quest.Terms_Over.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Terms_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 15);
			pchar.quest.Terms_Over.function = "QuestShipsTerms_Over";
		break;
		
		case "Stivesant_10":
			dialog.text = "Captain, go to 'Meifeng'. It's time for us to set sail.";
			link.l1 = "Yes, mynheer, of course.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "Very interesting! Please, tell your story. I'll try to do my best to help.";
			link.l1 = "Mynheer Keller, do you remember how you had met a flute on your way to Willemstad several months ago. There was a family of Jewish refugees on it. You have dined on the board of that ship and then continued on your journey.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "Yes, I guess so... Yes, I remember it quite clear now. So, what's the deal?";
			link.l1 = "The flute was sunk by pirates on that very day. Only two refugees managed to save themselves - Solomon and Abigail, his daughter. They found refuge on an island just in several miles from where the attack occured. I need to find that island. Could you please recall where you'd met that flute? This is very important.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "And that's all you need? I know this island. It's very close by, between Trinidad and Curacao. A small desert uninhabited island. There are even no Indians there.";
			link.l1 = "And do you know it's approximate coordinates?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "I can tell you the exact coordinates. It's at 12  48'  North and 64  41'  West. Look for it there. The island is rather small, but you should be able to easily locate it.";
			link.l1 = "Thank you, mynheer Keller! You've helped me a lot. Goodbye.";
			link.l1.go = "Keller_5";
		break;
		
		case "Keller_5":
			DialogExit();
			Diag.CurrentNode = "Keller_6";
			pchar.quest.Keller_fail.over = "yes";
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DeleteAttribute(pchar, "questTemp.HWICMC");
			AddQuestRecord("Holl_Gambit", "3-66");
		break;
		
		case "Keller_6":
			dialog.text = "Did you want anything else, captain?";
			link.l1 = "No, thanks. I was already returning to my ship.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = "no ships"; break;
       case 1: numships = "one ship";      break;
       case 2: numships = "two ships";       break;
       case 3: numships = "three ships";       break;
       case 4: numships = "four ships";    break;
       case 5: numships = "five ships";     break;
       case 6: numships = "six ships";    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = "all loot"; break;
       case 2: numpart = "half of the loot"; break;
       case 3: numpart = "third of the loot"; break;
       case 4: numpart = "quarter of the loot";      break;

    }
    return numpart;
}

int findPriceStoreMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[40];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            storeArray[howStore] = n;
            howStore++;
            
            // homo 05/09/06
            if ( CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City ) return n;
            //
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}
