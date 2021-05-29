void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - drand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("What girls, dear?! Half the garrison is after you, and look at him, came straight to the brothel!","Get lost, will you? Half the garrison is after you!") +"", "All town guards are looking for you. I'm not a fool to provide services to you at this moment ...", "You have nothing to do here!"), 
					LinkRandPhrase(""+ GetSexPhrase("Just dare to touch my girls and I will skin you alive!","Get lost, you creep!") +"", "Dirty"+ GetSexPhrase("","") +" murderer, leave my establishment, now! Guards!!!", "I am not afraid of you, "+ GetSexPhrase("scoundrel","rat") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, an alarm is never a problem for me...", "They will never catch me."), 
					RandPhraseSimple("Just shut up, stupid crone.", "Shut up if you don't want problems..."));
				link.l1.go = "exit";
				break;
			}
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "You're such a stately man. Moreover, my girls like you very much. I would like to ask you for a little favor for my establishment.";
				link.l5 = "I am flattered, that's for certain. What is it that you need my help with?";
				link.l5.go = "Badboy";
				link.l8 = "I am sorry, but I am busy at the moment.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "Oh, you have returned! Have you arranged that "+pchar.GenQuest.Badboy.Brothel.Name+" to leave my girls alone?";
					link.l5 = "Yes. He won't show his face here anymore.";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector"))
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0)
				{
					dialog.text = "Captain, can I ask you about a favor?";
					link.l5 = "For you, madame, anything you like! I am at your service!";
					link.l5.go = "Portugal";
					link.l8 = "I am sorry, but I am busy at the moment.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				dialog.text = "Have you talked with Hugo, mynheer captain?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "Moreover, ma'am, here is your money. Everything went in the most favorable way...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "Yes, I conveyed him your request.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Oh my, look at this! Charley Prince, a famous corsair! In flesh!";
				link.l1 = RandSwear()+"Hello Janette. I am here on the mission for Marcus Tyrex.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Are you ready to get an uforgettable relax, my brave corsair?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "I am! Charley Prince doesn't waste words like he wastes money, ha-ha!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "Almost... I guess I have lost a purse in your establishment... I will be back with money!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". Welcome to my house of love. My name is " + npchar.name + ", and I am the boss here. "+ GetSexPhrase("What can I do for you, " + GetAddress_Form(NPChar) + "?","Frankly, I am a bit surprised to see you here, " + GetAddress_Form(NPChar) + ", but I assure you that we render services not only for men.") +"",
				TimeGreeting() + ". I greet you, "+ GetSexPhrase("stranger","young lady") +", in my humble establishment. Allow me to introduce myself, I am "+ NPChar.Name + " - holder of this asylum for men hungry for a woman's touch. "+ GetSexPhrase("What can I do for you?","Although we have a thing or two for ladies, too...") +"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". How can I help you, " + GetAddress_Form(NPChar) + "?",
				TimeGreeting() + ". What can I do for you, " + GetAddress_Form(NPChar) + "?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идет квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name + ", I want to spend some quality time with one of your girls.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идет старт Шарля
			{
				link.l3 = "It's been a while since I spoiled my men last time. Can I do a bulk order for girls for my guys?";
				link.l3.go = "ForCrew";
			}
			link.l4 = "I have a question.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "Listen, " + npchar.name + ", I am looking for the ring of the governor. He had a rest in your establishment and probably lost it here.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			link.l9 = "Nevermind, I am already leaving.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("What do you want, handsome?","I am listening to you, captain.");
				link.l1 = "Listen, " + npchar.name + ", I found these papers in a private room of your institution ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let me see! Hmm... some captain had lost his documents, right? I think you should ask the harbor master about this.";
				link.l1 = "Perhaps, perhaps...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Let me take a look! Oh! Judging by the name, they belong to my esteemed customer and a worthy citizen of our town. I can hand him these documents myself.";
				link.l1	= "Probably, not...";
				link.l1.go = "exit";
				link.l2 = "Excellent! Always glad to help a good person and a worthy establishment.";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+ GetSexPhrase("We're always happy to serve a customer. Now tell me, handsome - have you already picked anyone or you don't much care?","Well, my girls are certainly able to... help you. Have you already picked anyone or you don't much care?") +"";
					Link.l1 = ""+ GetSexPhrase("Heh, I just need a whore and I need her right now. I don't care which one, your girls all look good to me...","Anyone will be fine if she knows her duties, of course...") +"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Yes, there is one, "+ GetSexPhrase("who took my fancy...","she would be the nicest...") +"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "I have no free girls for you today, we already have too many customers. Come tomorrow, and you won't regret it!";
					Link.l1 = "Pity, I just began to enjoy it.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. you've already paid for the girl. don't distract me please.";
				Link.l1 = "Alright, I'm coming.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "I don't have any free girls right now, you'll have to check back in a couple of days.";
				Link.l1 = "Fine, as you say.";
				Link.l1.go = "exit";	
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("Well, excellent, my stallion!","They all are very skilled at what they do, have no doubt.") +" I can offer you a very nice girl, her name is " + GetFullName(sld) + ", and she is free at the moment. That pleasure will cost you " + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + ". Agree?";
				Link.l1 = "No. I guess no. It's too expensive...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "Of course, how could I refuse?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Oh crap, I don't have that much money with me...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "Fine, "+ GetSexPhrase("handsome","beautiful") +". " + sld.name + " will be waiting for you in a privacy room on the second floor.";
				Link.l1 = ""+ GetSexPhrase("Fine, I am coming, then","Fine, I am coming, then") +"...";
				Link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in location " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "Oh, you see, the problem is that " + sld.name + " is not a cheap girl, her price is " + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + ". And I see that you just can't afford her at the moment. Come back when you'll be rich"+ GetSexPhrase(", dear","") +"...";
				Link.l1 = "That's my luck...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "I am always happy when girls and customers develop warm feelings for each other... Tell me her name.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Hmm... you must be mistaken. I have no such girl in my establishment. Perhaps you got her name wrong.";
				Link.l1 = "Hmm... but I have just talked with her.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Perhaps, it will be better to ask her name once again, just to be sure. I will talk with you later about this.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld) + ", you're talking about her?";
				Link.l1 = "Yeah, about her.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "No, it's not her.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "Then perhaps, you should tell me her name once again, and maybe I'll realize, about who you are talking about.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Perhaps, it will be better to ask her name once again, just to be sure. I will talk with you later about this.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Hmm... Want to help your guys 'let off some steam'? You see, this establishment of mine is a reputable one, and I have the best girls around. But I know several port wenches, and they'll be happy to please all your sailors which are free of a watch. That will cost you " + FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost) + ".";			
			link.l1 = "Fine, I agree.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Guess they can manage without it...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "It's not my business, but I think that at first you should earn enough money to hire a crew, and only then worry about its spirit.";
			    link.l1 = "You're probably right...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "Dear, just what are you doing?! And looked like a decent captain... You won't 'fly' away this time, handsome. Guards will cut off your wings...";
			link.l1 = "Shut up, old hag.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "I haven't found any ring.";
			link.l1 = "And your girls?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "They have not too. If a customer forgets or loses anything, my girls bring it to me. But no one have brought me the governor's ring.";
			link.l1 = "I see... But could it be that they decided to keep it for themselves?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "Unlikely. Girls are allowed to keep gifts from the customers, but that's all.";
			link.l1 = "I see. Well, thanks, " + npchar.name + ".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "Oh, here you are...";
			link.l1 = "Here I am, my lady!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришел
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("You'd better leave the establishment!", "All the guards in the town are looking for you! Guess it's better for you to leave...", "You've made a mess and now you've shown up here?! No, not this time..."), 
					LinkRandPhrase("Get lost!", "Filthy murderer, get out of here! Guards!", "I am not afraid of you,"+ GetSexPhrase("scoundrel","rat") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, an alarm is never a problem for me...", "They will never catch me."), 
					RandPhraseSimple("Heh, what a stupid wench you are...", "Shut your mouth whore, or I will shut it with something else..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Hello, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase("",", hee-hee..") +". You have to see the ma'am and fill out the order.", 
				"You again? Please talk with the keeper. She's in her office.", 
				"Look, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", I do hope that you are as stubborn in other things as you are in talking... Again","Once again") +" I ask you to see the owner of the establishment.", 
				"Oh, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", aren't you a stubborn one!",", Hee-hee... You're a stubborn one, aren't you?") +" You have to see the ma'am and fill out the order.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Alright, "+ GetSexPhrase("beauty, ","") +"I got it"+ GetSexPhrase("","") +".", "Yeah, right...",
                      ""+ GetSexPhrase("Have no doubt, my pretty, I am as stubborn and strong as a bull!","Yeah, yeah...") +"", ""+ GetSexPhrase("Oh hell, I must have missed something... I am sorry, dear.","Okay, okay.") +"", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "And where is she?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+ GetSexPhrase("Oh, beauty, I bet I could drown in your eyes...","You look so beautiful, babe!") +"", ""+ GetSexPhrase("You know, I've never met such a beautiful woman before!","You know, I've never met such a nice chick before!") +"", ""+ GetSexPhrase("Darling, you are so beautiful.","Damn, I was so tired of all those rednecks... And you're so charming!") +"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("Listen, "+ GetSexPhrase("beauty","deary") +", haven't you found a wedding ring here, by a chance? One man seems to have lost it...", 
					"Darling, haven't you found a wedding ring in this establishment, maybe noticed something like that?", 
					"Listen, "+ GetSexPhrase("my kitty","babe") +", haven't you seen a wedding ring around here?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "Hey there, sweetheart. Marcus Tyrex sent me, take a look at this amber necklace...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "She's in her office. You can get there from here through the door opposite to the exit on the street, or from the street on the other side of the house. Her name is " + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
			Link.l1 = "I see, "+ GetSexPhrase("sweetheart","darling") +", thanks.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Oh my, it's so nice to hear such things! Hey, I am free at the moment, so if you pick me, you won't regret it...", "You really think so? You know, it's so cute... Listen, I am free at the moment, so you can pick me."+ GetSexPhrase(" I promise you the sea of love and an ocean of caress...","") +"", ""+ GetSexPhrase("Do you think so? Oh, I am really flattered. You know, I rare hear such compliments...","Oh, girl... if you only knew how fed up I was with rednecks...") +" Hey, listen, I am free at the moment, so you can pick me to make you happy. I will not disappoint you, I promise...");
				link.l1 = "Well, I pick you, then!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+ GetSexPhrase("No, that was just a compliment to a nice lady","That was just a compliment") +".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("You know what I say, sweetie? I don't need this cheap talks. Do business or leave!","That's all I needed! Compliments from women!") +"", ""+ GetSexPhrase("Are you one of those who think that women love with their ears? Well, dear, that's just not true. If you want me, then pay to the madame and save me from your empty talks.","Lass, don't squander yourself on hollow talk. If you mean business - then pay...") +"", ""+ GetSexPhrase("Oh, another lover of sensuality... You just pay and I am yours. It's all that simple, without all this gentle nonsense!","What's up with you, darling? If you want to indulge yourself in pleasures, then just pay and stop all that nonsense!") +"");
				link.l1 = "Oh, what a grasp!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + " completes all formalities in her cabinet. Go see her"+ GetSexPhrase(", my hero,","") +" and say my name - " + npchar.name + ". I'll be waiting for you...";
			Link.l1 = "I see, darling, I'll be back soon...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("You have already paid.", 
				"I told you 'go upstairs'.", 
				"Upstairs, young man.", 
				"Some people think so slow...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yeah, I know.", "I remember.",
                      "Oh, don't repeat yourself, I remember about her.", "Hmm, what do you mean?.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("I just don't quite understand you."+ GetSexPhrase(" First you make compliments, and then you step back of your words. What a strange type...","") +"", 
					"Compliments again?.", 
					"The keeper is in her office. Got it?", 
					"We must not insult our customers, but seems like you're asking for it"+ GetSexPhrase("","") +"...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("It just happened the way it did...", "Alright, I'll do that.",
						"Yeah, I got it.", "Beg pardon, my love.", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Thanks for the compliment. If you wanna take me, just go and see the ma'am. Everything as usual.";
				Link.l1 = "I see.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Dear, we have already talked it all over. ","") +"Don't make me wait for too long...", 
						""+ GetSexPhrase("Hmm... Listen, dear, I","I") +" find your words very nice and so on, but could you get down to business...", 
						"Perhaps, you will just discuss this with madame, won't you?", 
						"Hm... I don't even know what to say...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("I would never do that, wait for me!", "Certainly!",
							"Of course, as you say!", "I am already running to see your madame...", npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "I was waiting for you, but you didn't come and take me... I can't say I liked that...";
					Link.l1 = "You see, it just happened that the way it did...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Oh, that's you again, my "+ GetSexPhrase("glorious corsair","pretty lass") +"! If you want me again, come see the ma'am, you won't be disappointed..."+ GetSexPhrase(" By the way, I recognized you, dear, but we are told that we must speak with all customers equally, there shouldn't be a favorite one, sorry about that...","") +"";
				Link.l1 = "Don't worry, darling. Wait for me just a little bit, "+ GetSexPhrase("cutie","cutie") +", and soon we'll meet in private again.";
				Link.l1.go = "exit";
				Link.l2 = "It's very pretty that you remember me, but I cannot spend this night with you, sorry about that.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("So,"+ GetSexPhrase(" dear friend,","") +" you'd better be engaged in business. It will be more useful, than doing nothing.", 
					""+ GetSexPhrase("Hmm, why are you ","Why are you") +" saying the same things over and over again?", 
					"Hey, isn't that enough?!", 
					"Hm, what a surprise, nothing new"+ GetSexPhrase(", once again all those stupid attempts on charming! If you wanna have sex with me, go and see the madame, you featherbrain!","...") +"", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Yeah, I've heard"+ GetSexPhrase("","") +" you...", "Hmm, that's the way it turns out...",
						"Hmm, maybe that's enough, or maybe not ...", "Watch your tongue"+ GetSexPhrase(", goat","") +"...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ohh, it's you again! "+ GetSexPhrase("And once again all those stupid compliments. Nothing ever changes in this world... If ","Just to remind: if ") +"you wanna"+ GetSexPhrase("have some good time","have some good time") +" with me, pay to the owner of the establishment. I could not care less for your words.";
				Link.l1 = "It's not a big surprise...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "I can't say It made me happy... A pity.";
			Link.l1 = "I am sorry...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "Ah, you've finally arrived! Great! We can speak freely, nobody's listening...";
				Link.l1 = "So, it was the Spaniard who gave you the blue amber?";
				Link.l1.go = "mtraxx_2";
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("I am very happy to see you in our private room. "+ GetSexPhrase("So, what are we going to do next?","How about we enjoy ourselves?") +"", "Don't be shy"+ GetSexPhrase(", feel yourself at home for at least two hours.",". I'll be able to entertain you, have no doubt.") +"");
					Link.l1 = RandPhraseSimple("I think it will not be boring...", ""+ GetSexPhrase("Let's have some good time, baby!","Let's waste no time!") +"");
				break;
				case "1":
					dialog.text = "Oh, that's you again, my "+ GetSexPhrase("glorious corsair! I promised you something and I am ready to keep my word","pretty lass! You will never forget the next two hours") +"...";
					Link.l1 = "Now that sounds tempting...";	
				break;
				case "2":
					dialog.text = "Ohh, here you are , finally. So, let's not waste time!";
					Link.l1 = ""+ GetSexPhrase("Let's not, pussy...","Now show me what you can do...") +"";
				break;
			}
			Link.l1.go = "exit";
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(pchar, 23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			NextDiag.TempNode = "Horse_AfterSex";
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
				else 												AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "Captain, why are you so silent?";
				link.l1 = LinkRandPhrase("Well, that's me.", "We'll talk next time.", RandPhraseSimple("I am paying you not for talking.", "But you, "+ GetSexPhrase("beauty","deary") +", weren't as silent all that time."));
				link.l1.go = "exit";
				link.l2 = ""+ GetSexPhrase("You were just great, I almost lost my mind! It's a very rare occasion, when a woman is both so beautiful and hot","Ohh, you certainly know how to please a woman... I am so excited.") +".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Did you like it?", "So, what can you say? Was everything okay?", "So,"+ GetSexPhrase(" corsair, is, everything"," everything") +" fine?");
						Link.l1 = RandPhraseSimple(""+ GetSexPhrase("Of course, everything is fine","You're certainly know your duties") +".", ""+ GetSexPhrase("Everything's fine, babe","You know, I was quite pleased") +".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("So, did I keep my promise?", "So,"+ GetSexPhrase(" did you like me",", did you like it") +"?", "I hope, "+ GetSexPhrase("you were pleased, because I am ve-e-ery pleased","you were pleased, because I did my best") +"...");
						Link.l1 = RandPhraseSimple("Yeah, I liked it a lot.", ""+ GetSexPhrase("We had a great time, you were gorgeous!","Everything was simply terrific!") +"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("Well, that's it, you have to go.", "Your time is over,"+ GetSexPhrase(" caprain,","") +".");
						Link.l1 = RandPhraseSimple("Yeah, see you...", "Goodbye and thank you...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "So, how did you like it here?";
				link.l1 = "Tell me beauty, haven't you seen a gripsack anywhere around?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Drop in again sometimes...", "Bye. We'll be waiting for you anytime...", "We'll be glad to see you here again...");
				Link.l1 = "Alright...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "Was it that brown chest with a grip?";
			link.l1 = "Yeah, something like that...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "Since the owner of that chest never showed up again, madame has taken it to her boudoir.";
			link.l1 = "Thanks, babe. Goodbye.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "Then drop in anytime, I'll always be glad to see you. You're so "+ GetSexPhrase("gentle, not like those others","gentle, not like those rednecks") +" no hello, no goodbye, and even often try to hurt...";
			link.l1 = "What do you mean by that?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "There was a master sergeant just before you. Usually he doesn't pay us a visit, but this time some devil has brought him here. Moreover, he has picked me... He was groaning while being over me for a few minutes, and then called me a low-skilled and rushed to some cove. He took off so quickly that he almost left his pants down there, ha-ha-ha...";
			link.l1 = "Don't you know, "+ GetSexPhrase("beauty","darling") +", who men really are? He had told his wife that he would go to the brothel for 'inspection', then he told his mistress that he was in a hurry to his wife, but the only thing he always wanted is going to patrol that cove. "+ GetSexPhrase("Ha-ha-ah!..","Ha-ha-ha!") +"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true; 
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("No, darling, sorry, but no. I would gladly help you, but I can't.", 
					"No, "+ GetSexPhrase("handsome","young lady") +", I haven't seen any ring...", 
					"Sorry, but no. I haven't seen any ring.");
				link.l1 = "Pity... Well, thank you anyway.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Do you mean the governor's ring?";
					link.l1 = "Exactly, babe!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("No, darling, sorry, but no. I would gladly help you - but I can't.", 
						"No, "+ GetSexPhrase("handsome","young lady") +", I haven't seen any ring...", 
						"Sorry, but no. I haven't seen any ring.");
					link.l1 = "Pity... Well, thank you anyway.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "I am sorry, but the ring was given to me as a present! So I am not obliged to return it.";
			link.l1 = "A present?! And who gave it to you?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "The governor himself, of course!";
			link.l1 = "But he was... tipsy, to say the least. He can't remember a thing.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "And what do I have to do with it? If he was drunk, it's his problem, not mine!";
			link.l1 = "Do you really need to quarrel with him? It's a wedding ring, and you know it... Just give it back, such a small thing is not worth any trouble.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Well, I'll give the ring back, but you will pay me five thousand pesos.";
				link.l1 = "Fine, take your money and give me the ring.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Oh, well. Let him have it!";
				link.l1 = "That's for sure, darling!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "Here you go...";
			link.l1 = "Fine, then. Thanks for help, darling.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "You see, there is one nasty customer we have - "+pchar.GenQuest.Badboy.Brothel.Name+". And he's really annoying us every time he comes! First he gets drunk at the tavern, then he comes over here, picks up a girl and makes a violent uproar\nAnd the worst thing about it that he is of noble descent, he's a distant relative of our governor, so we are forced to suffer all his escapades. Maybe you could make that young brazen man... well... a little bit calm down... so that he would stop visiting my establishment?";
			link.l1 = "Governor's relative, you say? Hmmm... I'd rather not get in confrontation with the authorities. Well, just understand me. I am really sorry.";
			link.l1.go = "exit";
			link.l2 = "I think I can arrange that. Tell me, where can I find that scrapegrace?";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "By this time usually he is already at the tavern. He gets drunk there and then comes over to visit.";
			link.l1 = "I see. Well, I'll probably meet him there.";
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "Oh, you're a real man, aren't you? I always knew that I could count on you..";
			link.l1 = "I am always happy to help such a nice lady and her... wards.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "You are not only brave, but also very gallant. I would like to thank you in a special way - in a way only a woman can thank a man. You will never forget this, I promise. Come upstairs, brave sailor...";
			link.l1 = "...";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = "There is one man and he owes me some money... I don't know how to say...";
			link.l1 = "No words! I'll find him and shake him out to the last peso just for one look of your fathomless eyes! Just tell me his name!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "No, no, you haven't correctly understood me, Captain! This man... do not do anything bad to him. Just remind him of his debts. His name is Hugo Avendell, and I suppose you will find him there, where very cheap booze is sold. Only God's sake, do not apply force to him!\nJust say... remind him that he promised to pay. I don't want to contact the guard, but I have friends officers, so tell him that I'm waiting, and with all due respect to him, no later than tomorrow, I'll be forced to take action. Just remind him of his promise.";
			link.l1 = "Your word is my law, madame. I will gladly fulfill your request.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			//создаем Хьюго
			sld = GetCharacter(NPC_GenerateCharacter("Avendel", "Hugh", "man", "man", 10, HOLLAND, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_04", "pistol1", "bullet", 50);
			sld.name = "Hugo";
			sld.lastname = "Avendell";
			sld.dialog.FileName = "Quest\Portugal_dialog.c";
			sld.dialog.currentnode = "Avendel_tavern";
			sld.greeting = "avendel_1";
			sld.rank = 12;
			LAi_SetHP(sld, 80, 80);
			SetSelfSkill(sld, 10, 12, 10, 10, 70);
			SetShipSkill(sld, 50, 75, 15, 15, 25, 55, 10, 15, 30);
			SetSPECIAL(sld, 3, 8, 3, 10, 10, 3, 6);
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "Gunman");
			GiveItem2Character(sld, "blade_12");
			sld.equip.blade = "blade_12";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			TakeNItems(sld, "bullet", 10);
			AddItems(sld, "gunpowder", 10);
			LAi_SetCharacterUseBullet(sld, "bullet");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			LAi_SetImmortal(sld, true);
			LAi_SetSitType(sld);
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "Thank you, captain. I do hope that he would show a due prudence.";
			link.l1 = "I am certain of that, madame. Now allow me to take my leave.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Oh no! Don't tell me you've done something terrible to him... He had no money, and I knew it! We just grew up in the same small town, I would never turn to the guards! I just wanted to scare him a bit... to shake him up before he would drown in the bottle!";
			link.l1 = "Hmm... Nevertheless, here's your money. And don't worry about Hugo, he's fine... At least he will if he sobers up.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Oh, Captain, you don't understand! He was one of... well, you know, they are called bounty hunters - mercenaries, they track down pirates and robbers and eliminate them. But, he was not the most fortunate, to say the least\nNot so long ago, he finally splurged and lost his crew and ship, since then he has been floating at the bottom of his mug, day after day. I, for old memory, allow him to come here sometimes. He's so... so pitiful now. He was the most handsome man in our town on the coast of La Manche, and look at him now\nI know that he promised you something, and you paid out of pocket! I'll give you this money, just don't do anything bad to him, I beg you, captain!";
			link.l1 = "Okay, okay, madame, I got it. Keep the money, it's yours. As for you friend, I promise that I will not hurt him. And now allow me to take my leave, I've got some business to do. Also, I was happy to help such a beautiful lady.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Shush, keep your voice low... Go ask Madame Lolita to have a date with me. Then come upstairs, where we can talk freely. And not a word until then... Hey, sailor, go pay to Madame before touching me! (giggles)";
			link.l1 = "On my way, sweetheart...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "Nah, not me. I'll tell you the whole story, just don't interrupt me.";
			link.l1 = "I am all ears!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Alright then. About a week ago, a military ship arrived to Santo Domingo. It was damaged, either in a storm or a fight, so the repairs began right away, and the crew moved to the fort. Its captain, however, spent all his free time right here. For two days straight he had been drinking and relaxing accompanied by one of our girls. It was she who got the gemstone, and not just one. She bragged about it to no end - Lolita lets us keep customers' presents\nSilly girl didn't even know the true value of the gift, whereas I sized it up straight away. When she told me of how the drunk captain boasted about a mountain filled with ambers, I promptly sent a letter to Tyrex...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "By the captain's next arrival I set everything up so his favorite girl was busy with another client, and got the 'job' for myself. I tried to get the coordinates out of him, alas, to no avail. He just kept boasting how he would become as rich as Crassus and get back to the Old World\nNot a single word about the location. The only thing I found out was that his ship was repaired and it was going to sail to Havana, where he would try arranging for a mission in the right direction, he isn't the ship's owner after all.";
			link.l1 = "So, he is in Havana now?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Sailed off two days ago at dawn. You are the seaman here, you do the counting.";
			link.l1 = "Captain's name, his ship's type and name, anything?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "What do, you take me for a fool? His name is Esberdo Cabanas, captain of the Cantavro. I think sailors called it a schooner.";
			link.l1 = "And that's all you know?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "What more do you want? I'm sure you could catch up with him before Havana. Don't waste time though, I don't think he'll take a long rest before leaving Cuba towards his stash, and then it's a lost cause. On a second thought, you could stay for an hour or two, you did pay for it after all.";
			link.l1 = "Good point, darling. Two hours won't make much of a difference...";
			link.l1.go = "exit";
			sTotalTemp = npchar.id;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(pchar, 23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
				else 												AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_R":
            dialog.text = "O-oh... What a pity. And I thought you are here on vacantion. My girls miss brave corsairs so much. Very well then, speak, what's the task?..";
			link.l1 = "Marcus tasked me to drive a helluva party in your establishment for two days, to drink all the wine and screw every girl. When will we begin?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "Ah, Charlie Prince, your humour is as sharp as your sabre! You almost got upset... Girls! We have a guest, a special guest! Bring wine and meals!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "Call every pretty girl here! We are going to rest and fun! Yo-ho-ho!..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Hold on a minute, Janette. I need to grab the gold from my ship for you and your ladies. See you in a minute!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "I wish all our customers were as sweet, handsome and generous as you are... We'll give you a perfect relaxation. Girls!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
