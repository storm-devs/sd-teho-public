#include "DIALOGS\russian\Common_Duel.c"

#define MAX_PGG_STORIES 		9
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		5

string PGG_Stories[MAX_PGG_STORIES] = {
"... only devil and I know the location and the last man standing will take it all!\n",
"... and Maynard said: 'I don't expect mercy so shouldn't you'.\n",
"... he was that drunk that proposed to arrange the very special hell right there, just to see who of us will endure it longer.\n",
"... funny story of my old pal from Porto Belo...\n",
"... No, gentlemen, those are crappy anecdotes. I've got some good stories to fill your ears\n",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!\n",
"... I tend to believe that this 'Flying Dutchman' crap is a fake\n",
"... Ever heard about me being shell shocked at Key West? Although there was no visible damage, I lain for two months. And then my passion persuaded me to confess. They say, with God's help, the matter will go well ... Well, I went, and the priest asked: 'Did you kill many people, my son?' 'And how many ships sunk?' - 'Many' - I answer. And he does not let up: 'Have you seduced many wives?' Then I say: 'Padre, I did not come here to brag'. Ha-ha-ha-ha\n",
"... But in Santa Сruz there was a case during mooring. With a cry of 'Beware!' My sailor throws a whip and hits the local onlooker straight in the forehead! That screams and falls without feelings. The sailor was frightened, not waiting for the ramp he jumped on the pier and gave that poor guy some water. Finally, he woke up and told the sailor: 'You have to shout 'Watch out' when danger is comung, not 'Beware' you idiot! Ha-ha-ha!\n" 
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
"... Got stuck in Florida once...",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!...",
"... She killed the poor bastard right in the middle of the tavern after he suggested testing her 'officer skills' upstairs..."
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
"Decent captains are rare breed in these waters.",
"Nobility is out of fashion these days.",
"Oh, now there's a decent captain, not like you at all, cutthroats! He-he!",
"Gentlemen, we have a decent captain at our table, who had been through fire and water countless times. So, what can you tell us, esteemed one?",
"Now there's another glorious corsair, who is not used to look for royal roads.", 
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
"Now there's another pirate!",
"Gentlemen, we have a gentleman of fortune at our table, I guess?",
"I smell gunpowder and blood! A filibuster aboard!",
"Ohh, gentlemen, now this is a seasoned corsair, who surely has something to tell in a nice company over a mug of rum... Would you like to join us?",
"Oh, I smell gunpowder... Gentlemen, we now have here another glorious corsair, who sure as hell will have a lot to tell on his confession... Ha-ha-ha!",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
//	Dialog.Text = "Вы видите баг... сообщите о нем АТ, для Navy.";
//	link.l1 = "Certainly!";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Hey, get lost, won't you! If you ruin my bargain, I'll rip your heart out!";
			link.l1 = RandPhraseSimple("You dare to threaten me, cur?!", "I will make you choke on your words, scoundrel!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, I see. Business is business. Good luck.";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "Good afternoon, my name is " + GetFullName(NPChar) + ", and yours?";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_GoodRep[iAns], PGG_Meet_BadRep[iAns]);
		}		 
//		link.l1 = "My name is " + GetFullName(pchar) + ".";
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Booze for everyone! I am captain " + GetFullName(pchar) + ".", 
					"I am captain of '" + PChar.Ship.Name + " and a couple hundreds of real devils! He-he! My name is " + GetFullName(pchar) + "."), 
				RandPhraseSimple("Allow me to introduce myself, gentlemen. I am captain " + GetFullName(pchar) + ".", 
					"We have not been introduced yet. I am captain of '" + PChar.Ship.Name + " under the flag of " + NationNameGenitive(sti(PChar.nation)) + ". My name is " + GetFullName(pchar) + "."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "Well, everyone knows me here! I am " + GetFullName(NPChar) + ". Nice to meet you! What can I do for you?";
		link.l1 = RandPhraseSimple("I have business with you!", "I want to talk to you...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "Well, everyone knows me here! I am " + GetFullName(NPChar) + ", captain " + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + ".";
			link.l2 = "How about you join me? Two ships are better than one. We can do decent business together.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("Would you want to serve as an officer on my ship?", "I think you would do fine as an officer on my ship. What do you say?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(Beta-test) Quests.";
			link.l7.go = "BT_Quest";
			link.l8 = "(Beta-test) Duels.";
			link.l8.go = "outraged";
		}
		link.l9 = "Nothing.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Hey, get lost, won't you! If you ruin my bargain, I'll rip your heart out!";
			link.l1 = RandPhraseSimple("You dare to threaten me, cur?!", "I will make you choke on your words, scoundrel!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, I see. Business is business. Good luck.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "I have already told you everything for today!";
			link.l1 = "Oh, yeah...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("What do you need" + GetFullName(pchar) + "?", "Who's that? Oh, you... Get lost, I am not in the mood...");
		link.l1 = RandPhraseSimple("What about a business?", "I wanted to talk to you...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("Oh, look who's here! It's " + GetFullName(pchar) + ". Any news?", "How are you doing? What can I do for you?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd] + PCharRepPhrase(" What's the news?", " What's the news on the archipelago?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_GoodRep[iAns] + " What's the news?", PGG_Meet_BadRep[iAns] + " What's the news on the archipelago?");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("How about you join me? Two ships are better than one. We can do decent business together.", "You look like an experienced captain. Want to sail under my flag?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("Oh, woe to me... My ship sank!", "Look who's here?! What has brought you here? By the way I lost my ship...");
				link.l3 = RandPhraseSimple("A pity. Maybe you'll have better luck next time.", "You don't say... Well, it's time for me to leave. See ya.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("Would you want to serve as an officer on my ship?", "I think you would do fine as an officer on my ship. What do you say?");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "What's the news?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("What an ugly snout. It just begs for beating.", "Oh, our 'friend'. Would you like a couple of new holes in the chest?");
			link.l8.go = "outraged";
		}
		link.l9 = "Nothing.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer 
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("I have already told you that I am not interested.", "I thought we had already discussed everything.");
			link.l1 = RandPhraseSimple("How could I forget?", "Fair enough. Bye.");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Hmm... perhaps not. Not a second time.", "And you thought I'd take that bait twice?!");
			link.l1 = RandPhraseSimple("Well, as you wish...", "Alright. See ya, then.");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... No, I guess not.", "No, I am a captain, and I don't want to serve as an officer.");
			link.l1 = RandPhraseSimple("Well, as you wish...", "Alright. See you, then.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("You have already a full set.", "I don't think you're ready to give me orders.");
			link.l1 = RandPhraseSimple("Pity...", "Well, fate decreed otherwise.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("That's just what I needed! Our blades shall taste the blood of our enemies! But there is one problem - I still need " + NPChar.Quest.Officer.Price + " pesos to pay off my debts.", 
								"You look like a real old salt. And if you're willing to pay " + NPChar.Quest.Officer.Price + " pesos, we might work well together."), 
				LinkRandPhrase("Your offer is quite flattering to me. I'll agree to work for you for a rather modest fee of " + NPChar.Quest.Officer.Price + " pesos.", 
							"Hmm... You look like a seasoned sailor. Perhaps, I should accept your offer if you're willing to pay me " + NPChar.Quest.Officer.Price + " pesos.", 
							"I think we'll work well together, captain. Just " + NPChar.Quest.Officer.Price + " pesos, and you have a deal."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("That suits me fine. I just hope you're not going to charge me on daily basis.", "That's very expensive, but I hope you're worth it."), 
				LinkRandPhrase("I agree. Consider yourself a part of the crew.", "Hm... I think, I can afford it.", "Looks like you are worth it. Take the coins!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("You're not worth that much. See you...", "Too damn expensive for me."), 
				LinkRandPhrase("Yeah... Greed is not a sin...", "Are you laughing at me? I can buy a dozen like you for such money.", "That's a rip off. Where am I supposed to find such money?")), "exit");
		link.l3 = "Hmm... and just how qualified are you?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "I think you've got problems with cash, captain.";
			link.l1 = "Oh... indeed.";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("Excellent!", "I never doubted you, captain.");
		link.l1 = "Don't be late for departure.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "A bug, inform devs";
		link.l1 = "I will!";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("I have already told you that I am not interested.", "I thought we had already discussed everything.");
			link.l1 = RandPhraseSimple("How could I forget?", "Fair enough. Bye.");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("Sailing with you?! Grow up a bit first!", "I don't think I am interested in it!");
			link.l1 = RandPhraseSimple("Well, as you wish...", "Alright. See ya, then.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... No, I guess not.", "No, thanks. I don't like to serve under anyone.");
			link.l1 = RandPhraseSimple("Well, as you wish...", "Alright. See ya, then.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
					RandPhraseSimple("I like you! You've got yourself a deal! Already I can hear the jingling of pesos in our pockets!", "You're a smart "+ GetSexPhrase("guy","lass") +"... We should work well together!"), 
					LinkRandPhrase("I like your offer. I agree.", 
					"That's interesting. You know, I think that together we can do more!", "That should be fun. You have a deal!"));
			link.l1 = RandPhraseSimple("Great! I'll be waiting for you at the sea!", "Deal! We'll make a great crew.");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("I think you already have enough companions.", "You have enough ships already - why would you need more?");
			link.l1 = "Yeah... Perhaps, you are right.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar,
					RandPhraseSimple("I am bored with you!!! I am leaving your squadron!", "I patience is finished! I am leaving."), 
					RandPhraseSimple("I am tired of your escapades, 'admiral'... Allow me to take my leave.", "I am sick of your command and I am leaving your squadron."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Fine, get lost, then.", "Alright, go wherever you like."),
					RandPhraseSimple("Fine. I won't be holding you.", "That's your choice. I wish you favorable wind."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ehh... how about a small premium?", "Caramba! Oh, hell, perhaps, you would stay? I can even pay your crewmen some extra!"),
					RandPhraseSimple("I would hate to part ways with you... Perhaps, a small compensation can settle our disputes?", "How about increasing your wage?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("One time was good enough for me. I will trust your promises no more!", "You will not entice me with no money! My decision is final!");
			link.l1 = RandPhraseSimple("Alright, so best of luck to you.", "Then get lost and make sure I'll never see you again!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar,
					RandPhraseSimple("A premium? Fine! A sum of " + NPChar.Quest.Companion.Price + " pesos will suit me fine.", 
						"Well, perhaps, if you are ready to pay to my crew " + NPChar.Quest.Companion.Price + " pesos, I might persuade them to stay."), 
					RandPhraseSimple("Alright! I can stay for a small premium of " + NPChar.Quest.Companion.Price + " pesos!",
						NPChar.Quest.Companion.Price + " will satisfy me and my crew for some time."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Are you laughing at me or what?! Get lost, now!", "Ha! I would much rather spend this money on something more useful!"),
					RandPhraseSimple("Oh no. I am not that rich!", "Farewell. I am going to pay this much."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Excellent! Here is your premium!", "I never doubted, that it was all about money!"),
					RandPhraseSimple("Excellent! Glad you are staying.", "Here is what I promised."));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "Select template!";
		link.l1 = "Quest 1 template - sea.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "SELECTED! Quest 1 template - land.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "Quest 1 template - sea.";
		link.l1 = "Oh, yeah...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "SELECTED! Quest 1 template - land.";
		link.l1 = "Oh, yeah...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "I have already told you everything!";
			link.l1 = "Oh, yeah...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("What business?.. Hic! Can't you see - me and the pals are having goo time!.. Hic...",
									"Ehh... No business today!");
		link.l1 = "I see...";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // не занят другими квестами ПГГ
					Dialog.Text = "What talk? Although, you're in time. When it comes to business, I am always ready!";
					link.l1 = "Hmm. What are you talking about?";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("...only me and the devil know that place, and the last one to stay alive shall get everything!..", 
							 "...and Meinard replied: 'I expect no quarter from you and will give you none, either'", 
							 "...and once in the open sea, when he was already a bit tipsy, he suggested: 'Let's make hell for ourselves there and see who stands to the last'.") + 
							 PCharRepPhrase(LinkRandPhrase("Now there's another pirate!",
									"Gentlemen, we have a gentleman of fortune at our table, I guess?",
									"I smell gunpowder and blood! A filibuster astarboard!"), 
								LinkRandPhrase("Decent captains are rare breed in these waters.",
									"Nobility is out of fashion these days.",
									"Oh, now there's a decent captain, not like you at all, cutthroats! He-he!"));
						link.l1 = "I am not shouting, I am telling you - there's a profitable deal!";
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = "Careful, careful! Oh! I know you. You're " + GetFullName(PChar) + ". I have heard much of you.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("I am captain " + GetFullName(pchar) + ".", 
						"I am captain of '" + PChar.Ship.Name + " and a couple hundreds of real devils! He-he! My name is " + GetFullName(pchar) + ".") + " But I don't remember you.", 
					RandPhraseSimple("Allow me to introduce myself, gentlemen. I am captain " + GetFullName(pchar) + ".", 
						"We have not been introduced yet. I am captain of '" + PChar.Ship.Name + " under the flag of " + NationNameGenitive(sti(PChar.nation)) + ". My name is " + GetFullName(pchar) + ".") + " But I don't remember you.");
//			link.l1 = "Hmm... and just who are you? I don't remember you.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "Hi, " + GetFullName(NPChar) + ". How's life?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "I am " + GetFullName(NPChar) + ", captain " + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + NPCharRepPhrase(NPChar, ". The most notorious corsair in the entire Spanish Main.", ". Just a sailor.");
		link.l1 = "Yeah, now I will remember you.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		iRnd = rand(3);
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = iRnd;
		PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GOOD_SLAVES + rand(2);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "I have business with you, "+ GetSexPhrase("buddy","lass") +". I know that I can trust you, but I just can't discuss it at the tavern - too many wrong ears. I'll be waiting for you on board of my ship. The name of my old tub is '" + NPChar.Ship.Name + "'.";
//			link.l1 = "Spit it out now, I have no time for visits.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("I have an interesting affair for you and your cutthroats.", 
								"If we join forces, we may win a really big prize indeed! Of course, we'll have to kill someone in the process. He-he."), 
							RandPhraseSimple("I have a business offer for you, captain.", 
							"Captain, your reputation is peerless, and therefore I offer you to participate in one tempting affair.")) + 
						RandPhraseSimple("Just between the two of us. Let's discuss it in the wardroom of '" + NPChar.Ship.Name + " over the keg of the choicest ale. Today.", "We shouldn't discuss it there, let's negotiate the details on '" + NPChar.Ship.Name + " in peace and quiet. And please don't take too long.");
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("To hell with these delays! If it's good, I wanna know it right away, and even more so if it's bad!", 
								"There's no point in such short wires! There is a suitable room in the tavern - let's head there!"), 
							RandPhraseSimple("And why can't we discuss your offer right know, in the tavern's room?", 
								"I am afraid I have little desire to visit your ship. If you need something, spit it out right here and now!"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "Pssst... We shouldn't discuss business in the tavern - too many wrong ears. I am waiting for you on my ship '" + NPChar.Ship.Name + ". We shall talk there.";
			link.l1 = "I have no time and I don't like visiting.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("I'll come. But if you were just wasting my time, I'll rip your tongue out!", 
					RandSwear() + "Alright, wait for me. I hope your offer is worth it. And don't even think of playing tricks on me!"), 
				RandPhraseSimple("I will gladly accept your invitation, captain.", 
					"You have intrigued me. Of course, I'll come."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Oh, you're seasick, aren't you? Run and hide under your mommy's skirt!", 
					"Too scared?! Get lost!"), 
				RandPhraseSimple("No can do. If you don't care for gold, it's your call.", 
					"It's this way and no other. If you don't want it - fine, there are many others."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ha! You're brave, aren't you? Alright, I'll come!", 
					"I see you can stick to your guns, captain. Alright, wait for me."), 
				RandPhraseSimple("Fine, I agree.", 
					"You are quite a talker. I am ready to discuss business on your vessel."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ha! You thought to lure me to your ship and kill me there? That won't do!", 
					"Your words are not worth a penny! I shall have no business with you!"), "Doubtful offer. I have to refuse.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Rum for me! And you get ought from my sight!", 
					"Haven't we already discussed everything?"), 
				RandPhraseSimple("Go about your own business. I have things to do.", 
					"I don't think we have anything to discuss."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "I told you that I would be waiting for you on my ship!";
		link.l1 = "Oh... sure...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("Oh, no, that won't do... Isn't that too many ships for you, "+ GetSexPhrase("buddy","lass") +"?", 
					"Ha! In such a big company there is no way to keep things secret. Get lost.");
			link.l1 = RandPhraseSimple("As you wish!", 
					"Alright. Not that I care.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Great. Now I am certain that there are no wrong ears around, and my sailors have already been informed. So my offer is to acquire some ownerless stuff.";
//			link.l1 = "And what's so hard about it? Why would you need me for that, in the first place?";
			Dialog.Text = RandPhraseSimple("Welcome aboard, captain!", 
					"Great. Now I am certain that there are no wrong ears around, and my sailors have already been informed. So my offer is to acquire some ownerless stuff.") + 
					" So my offer is to acquire some ownerless stuff.";
			link.l1 = RandPhraseSimple("And what's so hard about it? Why would you need me for that, in the first place?", 
					"Ownerless?! You must be joking!");
		}
		else
		{
			Dialog.Text = "Now I am certain that there are no wrong ears around - go ahead and spit it out!";
			link.l1 = "So my offer is to acquire some ownerless stuff.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("Well, there are people who consider it their own and they need to be convinced otherwise.", 
					"Of course, someone will need to be killed - but certainly this isn't going to be a problem?");
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Down to business!", 
					"That smells with a massacre! And where are they?"), 
				RandPhraseSimple("I would like to know more details about your offer.", 
					"What exactly are you offering me?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("You're pulling the wool over my eyes. I am not going to partake in that!", 
					"That seems easy, but I do not trust you! You want me to pull chestnuts out of fire for you? Well, I disagree!"), 
				RandPhraseSimple("Sounds promising, but I'll pass.", 
					"No, I don't steal, I like when they give me gifts instead."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "And what's so hard about it? Why would you need me for that, in the first place?";
			link.l1 = "Well, there are people who consider it their own and they need to be convinced otherwise.";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "A caravan belonging to " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", transporting ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Slaves";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetConvertStr(PChar.GenQuest.PGG_Quest.Island, "LocLables.txt") + "");
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	", stopped not far from " + sLoc + " at the cove of " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + " to resupply.";
		}
		else
		{
			sTmp += ", was caught in the storm not far from " + sLoc + " and went down. But they managed to secure part of the cargo and landed in the cove of " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + 
				" Now they are waiting their squadron to come.";
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Don't drag, spit it out!", 
					"I was right about you, what else do you know?"), 
				RandPhraseSimple("That's very interesting, please go on!", 
					"A am "+ GetSexPhrase("all","all") +" ears!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("That sounds like a tempting affair, but I still refuse. I don't need to quarrel with " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + ".", 
					"A caravan? Ownerless?! There should be a thousand soldiers guarding it! No, that won't do. I am leaving."), 
				RandPhraseSimple("No, I am not at war with " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", so I am not interested.", 
					"My answer is no! I am not going to ruin my relations with " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + "!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "That smells with a massacre! What about the details?";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "We only have " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " to intercept them.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("In " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " the caravan will go too far, and we won't be able to run it down.", 
						"We have exactly " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " days to kill them all and get the loot!"), 
					RandPhraseSimple("We only have " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " days fro the entire operation at our disposal.", 
						"We should hurry, " + PChar.Name + ". We only have " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "."));
			link.l1 = RandPhraseSimple("We'll do it in time! Let's set sail today.", "Let's not waste time, then. Order to set sail today.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "That's very interesting, please go on.";
			link.l1 = "We only have " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " to intercept them.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Let's not waste time! Off we go!";
		link.l1 = "Off we go!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear() + "You disappointed me, captain. Did you think I am going to invite you for "+ RandPhraseSimple("Sunday mass?!!", "a children play!??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("That's your business. And it's up to me to decide.", 
					"I am not going to hang on the rope for a couple pesos."), 
				RandPhraseSimple("My decision is final, captain.", 
					"We have nothing more to discuss."));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("Oh, come on! Everything will proceed smoothly, and no one will know anything. We'll kill everyone."), 
				RandPhraseSimple("Where are you going, captain? To the authorities, perhaps?", 
					"It's quite unwise to walk into a tiger's den thinking that you'd be able to get out of it easily."));
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Go kiss the sea devil! I am captain " + GetFullName(PChar) + " and I don't care for you! I am leaving!", 
					"I swear by devil, you are really maddening me!"), 
				RandPhraseSimple("Your proposal is not of any interest to me, and there is nothing more for us to discuss. Farewell.", 
					"I think there is nothing more to discuss between us. Sorry, I am busy and I need to go."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear() + PCharRepPhrase(RandPhraseSimple("Seize "+ GetSexPhrase("him","her") +"! Tie "+ GetSexPhrase("him","her") +" to the cannon! Let's see what color "+ GetSexPhrase("his","her") +" guts are!!!", 
					"Hey! Johnny! Henderson! Seize that "+ GetSexPhrase("scoundrel","lass") +"! Don't let "+ GetSexPhrase("him","her") +" to get to the lifeboat!!!"), 
				RandPhraseSimple("A pity, captain! I hope that you would like our hold, though. And then we'll decide what to do with you.", 
					"White slaves are not known to live for long, captain, so make your choice: either Hends shoots you in the head, or you spend the rest of your life in a quarry."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("I will make you eat your foul guts, " + GetFullName(NPChar) + "!!!", 
					"Give way! Scoundrels! I'll kill you where you stand!"), 
				RandPhraseSimple("Your offer is unacceptable... And most unwise!!!", 
					"You're not so hospitable, as I can see... Make way!!!"));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = "So, " + GetFullName(PChar) + ", I see that I made a mistake by getting mixed up with you. Now there's no loot for us. Farewell!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Goddammit! We're late - and all because of those lazy dimwits! Now there is no loot to share with you, " + GetFullName(PChar) + ". Hoist the staysail! We're getting out of here! ", 
					"So, " + GetFullName(PChar) + ", I see that I made a mistake by getting mixed up with you. Now there's no loot for us. Farewell!"), 
				RandPhraseSimple("They disappeared - and all because of your tardiness! Now we are going different ways, " + GetFullName(PChar) + ".", 
					"No way we can run down the caravan now. I made a mistake by getting mixed up with you. Farewell!"))
		link.l1 = PCharRepPhrase(RandPhraseSimple("To hell with that caravan! Pearl divers are even better, and there is no risk involved!", 
					"Luck is with us and tomorrow is another day! There are plenty of pitiful merchant in the seas just waiting for us to take their money!"), 
				RandPhraseSimple("A pity, indeed, that such a brilliant operation turned out to be a total failure! Farewell!", 
					"Man proposes and God disposes... Farewell!"));
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
		CloseQuestHeader("Gen_PGGQuest1");
		break;

	case "Exit_Quest_1_2Late":
        LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = "Oh, why in hell have I mixed up with you. You've ruined everything. So, now you must pay me a penalty of " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + ".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Bloodthirsty "+ GetSexPhrase("scoundrel","filth") +"! Everything went down straight to the sea devil!" + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pesos on the nail, and get out of my sight!", 
						"Have you fancied yourself admiral Nelson? Sank all the booty, "+ GetSexPhrase("idiot","foolish woman") +"! Give me now " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pesos and get lost!"), 
					RandPhraseSimple("Have you decided to wage war here! That is completely unacceptable! But, I guess, we can forget about it, if you pay us " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pesos.", 
						"Your methods are completely unacceptable! You've ruined the whole affair! Immediately pay us our share in the amount of " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pesos and go wherever you choose!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("If not for me, you would be feeding crabs by now, greedy bastard!", 
						"Oh yeah, I should have let their flagship to board you - then you would not be poisoning the air now, swinging on the yard!"), 
					RandPhraseSimple("Your demands are out of place, and youк insinuations are insulting!", 
						"We have not agreed on the penalty, so I am not paying you anything!"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("I cannot give you battle right now, and you know it! Choke on your pesos!", 
								" pesos?!! Well, Lady Luck surely doesn't smile at me this day. I agree."), 
							RandPhraseSimple("Your demands are outrageous, but I think I have no choice.", 
								"Your appetites are excessive, but I have to согласиться!"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "Oh, why in hell have I mixed up with you. You've ruined everything.";
			link.l1 = "Oh, come on! You saw for yourself that there was no other way.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "So, our loot makes up " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ". Let's split.";
			Dialog.Text = PCharRepPhrase("That was a hot deal! So, our loot makes up " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", 
					"Excellent work, captain! Our loot makes up " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text + PCharRepPhrase(" My share is ", " The share of my vessel - ");
			}
			else
			{
				Dialog.Text = Dialog.Text + " Your share is ";
			}
			Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("Everything is correct! The boats are already being loaded!", "Yes, everything is correct. A bargain is a bargain."), 
					RandPhraseSimple("Your calculations are correct. I agree.", "When it comes to splitting, you're irreproachable."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("You dare to demand your share? You should be hanged on the yard right away!", 
						"Your share? Here it's every man for himself. If there was nothing left for you, it's your trouble!"), 
					RandPhraseSimple("I don't think that you can expect any share.", 
						"My answer is no! I am not sharing with scoundrels like you!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Well, alright then, I am not going to argue! Farewell!", 
					"Let's not spill blood and make matters even worse! Next time we'll have better luck!"), 
				RandPhraseSimple("Well, farewell, captain, I am not in the position to make demands...", 
					"The losses and damage to my ship don't allow me to insist on just decision. I'll leave it on your conscience, captain!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Favorable wind to you!", "Seven feet under the keel!"), 
				RandPhraseSimple("Farewell! I hope that fresh sea air will be good for you!", 
					"I hope that our misfortunes don't make you even more intolerable, captain! Farewell!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Did you not get it! You could buy your life instead! Seize the bastard!", 
						"Or you think that we are playing games with you? Well, once we keelhaul you, you should become more compliant!"), 
					RandPhraseSimple("We'll have to shorten your life, then, captain! If you're not going to go in a friendly way, soon you shall meet Saint Martin!", 
						"You leave me without a choice, " + GetFullName(PChar) + "! I will take what's mine, whether you like it or not!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("I swear to devil, you will pay for this!!!", 
						"Yo-ho! Then go and get me, captain " + GetFullName(PChar) + "! "), 
					RandPhraseSimple("The cut will be long and deep!", 
						"Would you like to die quickly or with a little suffering?"));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("",""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "I don't want to deal with you anymore!";
		link.l1 = "No problem at all.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "Nice doing business with you. Good luck.";
		link.l1 = "And the same to you.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("That was a real massacre! A pity there were no wenches with them! The loot makes up  " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", "Not bad, captain! The loot makes up " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text + " My share is ";
		}
		else
		{
			Dialog.Text = Dialog.Text + " Your share is ";
		}
		Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("Totally just, goddammit!", "Everything is perfectly right, goddammit!"), 
			RandPhraseSimple("Your calculations are correct. I agree.", "When it comes to splitting, you're irreproachable."));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/
