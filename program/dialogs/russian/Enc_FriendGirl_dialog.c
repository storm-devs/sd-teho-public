void ProcessDialogEvent()
{	
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{		
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase("Oh my Lord, I am so glad that I met you!",
				"Finally someone!",
				"Oh my God, I am so glad to see you!");
			Link.l1 = LinkRandPhrase("What's up, babe?",
				"Any problems, darling?",
				"Don't become so agitated - it isn't good for young lady's health. Just tell me now - what's happened?");
			Link.l1.go = "Step_1";			
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("My friend... she's so brave... she got into an abandoned well!",
				"My friend went down in an abandoned well, and she still hasn't come out! She's spent there several hours!",
				"My friend has just disappeared in an abandoned well!");
			Link.l1 = "And why the hell did she get in there?!";
			Link.l1.go = "Step_2";			
		break;
		case "Step_2":
			dialog.text = "Oh, you know, she doesn't fear absolutely anything! She heard that there was a dungeon full of gold, so she went down there... But I am not a fool, I wouldn't even think of it!";
			Link.l1 = "That's right, there's nothing for you to do in such place.";
			Link.l1.go = "Step_3";			
		break;		
		case "Step_3":
			dialog.text = "But what am I supposed do now? Please, help her, for Heaven's sake!";
			Link.l1 = "Alright, I'll figure it out. And you'd better go home, there's nothing for you to do here.";
			Link.l1.go = "Step_agree";
			Link.l2 = "These are your problems, I don't wanna waste my time. Farewell...";
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //бандюганы
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //монстров не генерить 1 день
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //офицеров не пускать 1 день
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirlF.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirlF.locationId; //флаг для открытия релоада
				string model[10];
				model[0] = "citiz_41";
				model[1] = "citiz_42";
				model[2] = "citiz_43";
				model[3] = "citiz_44";
				model[4] = "citiz_45";
				model[5] = "citiz_46";
				model[6] = "citiz_47";
				model[7] = "citiz_48";
				model[8] = "citiz_49";
				model[9] = "citiz_50";
				i = 0;
				while(i < 3)
				{
					iMassive = rand(9);
					if (model[iMassive] != "")
					{
						iRank = sti(pchar.rank) - rand(5) + rand(5);
						if (iRank < 1) iRank = 1; 
						sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "marginal"));
						SetFantomParamFromRank(sld, iRank, true);
						sld.SaveItemsForDead = true;
						sld.DontClearDead = true; 
						sld.money = iRank*200+1000+rand(500);
						LAi_SetWarriorType(sld);
						LAi_warrior_SetStay(sld, true);
						//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
						LAi_group_MoveCharacter(sld, LAI_GROUP_ENEMY);// лесник изменил группу чтобы ядом таино травить можно было
						LAi_group_Attack(sld, Pchar);// лесник добавил атаку на пчара а то у некоторых баг что они не нападают.
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "quest", "quest" + i);
						i++;
						model[iMassive] = "";	
					}
				}
			}
			else
			{ //и правда девка 
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, PIRATE, 1, false, "citizen"));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground"+ iTemp; //здесь рендом поведения девки: 0-помогите, 1-сама крутая// лесник - раскоментил itemp
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //соотв. озвучка
			   // LAi_SetStayType(sld);
				LAi_SetCitizenType(sld);// чтоб ходила по пещере. лесник
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				GetCharacterPos(pchar, &locx, &locy, &locz); // и ниже - ищем ближейший локатор лесник.
	            ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DialogExit();
		break;			
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = "I don't wanna talk with such a callous "+ GetSexPhrase("clot","wench") +". Get lost!";
			Link.l1 = "Heh, what a bitch...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "Oh my God, I am so glad to see you!";
			Link.l1 = "What's up, beauty?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "I've got lost here! Oh my God, I am so terribly scared!!!";
			Link.l1 = "Well, you're fine now. Follow me, I will show you the way. Once you are on the surface, run home, and pray that I'll never see you here again!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "As you say, " + GetAddress_Form(NPChar) + ".";
			Link.l1 = "Fine.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Wow, it seems that someone else took interest in this dungeon!";
			Link.l1 = "Beauty, what you are doing here?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "None of your business!";
			Link.l1 = "Wow, that's an answer for a million pesos...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "For two million. Will you just go your own way? I don't care less about you.";
			Link.l1 = "Well, the feeling is mutual, but your friend above was worried sick about you...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "What a fool! She would shit her pants with fright, and she thinks that I am as same as her.";
			Link.l1 = "Wow, you surely don't like her. The devil in the skirt - that's who you are.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "Hey, choose your words! And better yet, just get lost.";
			Link.l1 = "Well, if you don't need my help...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "No, I don't!";
			Link.l1 = "Then farewell and good luck to you.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "You again? Get lost, I don't wanna see you anymore...";
			Link.l1 = "Hmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
