void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Congratulation! This is a bug. Contact Jason and tell him how and where you got this one. Peace!";
			link.l1 = "I will do it immediately!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(0.25);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Hail to you, son of the sea! I heard about you. You can step easy on our land.",""+npchar.name+" greets you, paleface brother. We are glad to see you as our guest.","I greet you, brave palefaced warrior! "+npchar.name+" is glad to meet a friend of Indians. Go in peace!");
				link.l1 = RandPhraseSimple("And hail to you, red-skinned brother! Good hunt to you!","Greetings, brave warrior! May the gods bless you and your family!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("I have something what could be interesting for you, red-skinned brother. Wanna trade?","I can offer you to buy something interesting, brave warrior. Wanna trade?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Stop, paleface! By what right you walk on my land?","Stop, white man! You on land of my forefathers and my land!","Stop, paleface! You do not belong to my land");
				link.l1 = RandPhraseSimple("Your land? Get lost, you red-faced scum!","Look at him - a talking ape! Get lost, now!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("I've come in peace, red-skinned warrior. We shouldn't fight for nothing.","I am not an enemy for you and your land, warrior. I've come in peace.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > drand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("I've come to trade with you, not to fight.","I don't fight with Indians. I trade with them.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > drand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("You feel sorry for being born, palefaced dog... I cut out your heart and fry it on fire!","I make you eat stones, palefaced dog! We laugh you beg for death on your knees, white cur!");
			link.l1 = RandPhraseSimple("You still can't shut your smelly mouth, painted scarecrow? I will drive you back to the jungle from where you came!","You dare to threaten me, scum?! Now you will climb the tree you've just come down from!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("I hear your voice speaks true. We not bare our axes against you this day. Go in peace, paleface.","Paleface rarely brings peace, but I see in your eyes you speak true. Go now.");
			link.l1 = RandPhraseSimple("A wise decision, warrior. Good luck to you.","I am glad we came to an understanding, warrior.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("You lie, paleface cur! You came here kill Indians! Ready for battle, paleface?!","You kill Indians. White tongue is lying tongue. I cut it of and fry on fire!");
			link.l1 = RandPhraseSimple("Well, buddy, don't blame me then. God knows, I tried to avoid it...","Well, you asked for it, warrior.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Trade? We need weapon of white men. One hand fiery weapon of palefaced! For it we trade our wares! Do you have fiery weapon to trade?";
				link.l1 = "Hmm. I do. And what will you give me in exchange?";
				link.l1.go = "war_indian_trade";
				link.l2 = "You scoundrel! And then you will shoot the colonists with my pistols? No, that won't happen! As for you, jackals, I will cut you all down now...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "You not have what we want, paleface... You be our war trophy!";
				link.l1 = "Try if you dare, scarecrow...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("We no trade with paleface dogs. We kill and take!","We no filthy miskito or arawaks, we no trade with palefaces! We kill them and get war trophies!");
			link.l1 = RandPhraseSimple("Well, then try to rob me, scoundrel!","First, you will need to take my saber from me, you filth!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "You show what you have, and we say what we give for it.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (drand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = drand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(drand(9)+14);
				iTotalTemp = drand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hey-ho! We give you for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (drand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = drand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(drand(3)+1);
				iTotalTemp = drand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hey-ho! Cunning weapon... We give you for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (drand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = drand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(drand(2)+2);
				iTotalTemp = drand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "Hey-ho! Mighty weapon! Many-many enemy kill! We give you for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (drand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = drand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(drand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Fearful weapon... We give you for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (drand(7) < 7)
			{
				if (drand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+drand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = drand(4)+10;
				}
				qty = drand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = drand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(drand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Beautiful and mighty weapon! Many-many enemy kill! We give you for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (drand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = drand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(drand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Handy weapon... We give you for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(0.3);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+drand(2));
			{
				dialog.text = "Good. Here your goods. We no trade anymore. Come later. Better fiery weapon more we give for it. Now go!";
				link.l1 = "Farewell, red-skinned warrior.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "Okay. Here you goods. You have more fiery weapon to trade?";
				if (CheckCaribGuns())
				{
					link.l1 = "I have. Will you buy?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "No. Next time I'll bring more.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Bring. Better fiery weapon more we give for it. Now go!";
			link.l1 = "See you, warrior...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "Then we take everything free, paleface!";
				link.l1 = "You may try...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Hail, white man. What you need in our jungle?","Our jungle very dangerous. What you do here?","What brings you here, brave paleface?");
			link.l1 = RandPhraseSimple("I was just passing by, my red-skinned friend. I believe there's enough place on this path for both of us?","Greetings, son of the jungle! I am here on business, and I don't fight against Indians.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("And why do you need to know? Go your own way and stay away from trouble!","Go your own way, red-skinned one. I have no time to talk with you.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("We peaceful people. We not enemies with white men. Go, but be careful on our land!","I glad meet palefaced friend of Indians. Go in peace, son of sea!");
			link.l1 = RandPhraseSimple("Good luck to you, too, son of the selva...","Farewell, red-skinned friend.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("We peaceful hunters. But we not stand when paleface talks like that on our land!","We not fight with white men, but if white men offend us, we answer like our forefathers taught us!");
			link.l1 = RandPhraseSimple("You still can't shut your smelly mouth, painted scarecrow? I will drive you back to the jungle from where you came!","You dare to threaten me, scum?! Now you will climb the tree you've just come down from!");
			link.l1.go = "exit_fight";
		break;
	}
}
