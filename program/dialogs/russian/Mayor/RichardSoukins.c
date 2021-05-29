// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "Do you have any business to me? No? Then get out!";
			link.l1 = "I am leaving already.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Do you have any work for me?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "I picked up the trail, but I need some coins - 30000 pesos to lure the rat from his hole.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Here, I look at this letter which I've found on the smuggler's corpse";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "It's done. Norman Vigo and his ship are gone to the sea devil.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm.. A work, you've said? Actually it's good that you have asked me. I need a man from aside. I want to find out something in the nearest town but my men are known there. Can't promise you a lot but you will get something.";
			link.l1 = "Nice! What's the mission?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Sorry, but I won't risk for a few scraps. Farewell.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Then listen, I had a deal for delivering 200 slaves a month ago with the captain of the schooner 'Saintblue'. I wanted to sell them to the local plantation owner. The time has passed and the client has started to worry, but I yesterday I was told that the schooner was seen not far from the island. But! The captain didn't show up. Today, my client has demanded from me to return his advance and said that he was offered to buy slaves from another seller. More expensive, but the whole bunch of slaves and at once.";
			link.l1 = "And? I have to find 200 slaves in a few days to save you from loosing an advance? For a few coins?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Sure not. Do I look like an idiot? I won't return him an advance anyway. But I need a proof that those slaves which were offered to him are mine. Find those who has offered him a new deal and you will get your 10000 pesos. Deal?";
			link.l1 = "I'm in. Do you have any suspicions? Who could do that?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Not a chance. Look for someone, somewhere and only for 10000? Sorry but it won't work.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "If I had any ideas then I would never use your services. Those men would be dead already. But I am eager to know how they found out about the 'Saintblue's' cargo and my client. It looks like that it was quite easy for them. See now?";
			link.l1 = "Yes, someone has sold you out.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Exactly! I am looking for him. Killing my competitors and returning my slaves are not your priority. I need that rat, actually his head on a skewer if to be honest. See now, why my men shouldn't know a thing about your mission? I will suspect everyone until I'll find out who sells the information. And I don't really want that...";
			link.l1 = "I see. Than I'll keep a low profile. I am on my way.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Thirty thousands you say? That's a large sum... I can only give you 5000 pesos, that's all I have now. And don't even try to escape with money or I'll find you and hang you on the nearest fence! Got it?";
			link.l1 = "Okay, give me five thousand then...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Take it. I am waiting for the result of you search.";
			link.l1 = "It all will be fine.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Excellent news! I was sure that you'd make it. I've got some intriguing information.";
			link.l1 = "I've done my work and I want to have my ten thousands.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Sure, here is you reward. But don't run away, I have one more assignment for you\nPfaifer is a crewman of Norman Vigo of lugger 'Septima'. I am sure that Norman Vigo is the rat, even if he is one of us. He has beem recently seen in the waters of the island. You job is to send this rat to the sea devil. You didn't fail me for the first time, therefore I want to ask you to deal with this matter too. I will pay you 15 000 pesos. Deal?";
			link.l1 = "I am on it! Consider that the traitor Norman Vigo is dead.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "You know, I don't want to take a part in it... I have no time anyway. Sorry, but I am off.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "I know, I know. My men were watching the battle and have already reported to me about your flawless victory. Fine, you've done your job well. Here is 15 000 pesos I promised. And thank you, you helped me with a great deal.";
			link.l1 = "It's fine, I was glad to help! But I have to go now, I've been here too long and I've got a lot things to do. Farewell!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
