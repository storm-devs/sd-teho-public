// Адольф Барбье - авантюрист
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "I don't want to talk with you. You attack peaceful civilians with no reasons and provoke them to fight. Get lost!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hello, Hello... I haven't seen you before. Recently?";
				link.l1 = "You mean recently on the Island? Yes, you are right. My name is "+GetFullName(pchar)+", a sailor and an adventurer.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Аh, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to know how you're doing. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha, just like me. I am not a sailor though, but my passion for adventures has lead me here. Now I have to rot on this ship's cemetery just like the others. By the way, my name is Adolf Barbier.";
			link.l1 = "It was nice to meet you, Adolf. See you.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "Why the hell have you invaded in my dwelling without my permission?";
			link.l1 = "You are showing bad manners to your guest, Adolf. And I have a business for you.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "I don't do any business with people I don't know! Get out!";
			link.l1 = "Just like that? So you do business with Narwhals, but you won't do with me? Shame...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "What are you talking about, jester? What business with Narwhals? It is your last chance to get out from here or I will have to throw you away myself!";
			link.l1 = "You don't have balls to do so, 'throw master'... Listen to me now. Where is the stutzen which you are going to use to shoot the admiral? Will you tell me yourself or should I become more persuasive?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "What? What stutzen? What admiral? Are you mad, pal? I have sold my stutzen and I don't have it anymore. And it is not your business whom I sold it. I don't give a fuck what they'll do with it. And I am not going to shoot anyone - neither admirals, nor generals. Do you understand me, fucker?";
			link.l1 = "I only understand that you are a liar and a murderer, Adolf. I know that you didn't sold it but redeemed it. I also know that you have received a huge sum to repay your debts and to buy this cabin...";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "This is my money, jerk! I have earned it! And I have sold my stutzen!";
			link.l1 = "You are lying, Adolf. You were hired by Narwhals to shoot the admiral. They have given you money to redeem your stutzen. They have also paid for this place. You know better than me that the bowsprit behind this door is the only place on the island to shoot the rear balcony of the Shark's residence.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "You are insane, jerk! You must be isolated immediately! I have been waiting for this cabin for half a year before Sessile went away from here...";
			link.l1 = "Enough. I will search you and your cabin, I will find the stutzen and a few more evidences, I am sure of it. And then we will go together to the Shark. He will be glad to look into your eyes.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "Ah, you are a sick bastard! I'd better die, than let some crazy scum to touch my belongings!";
			link.l1 = "Then I will touch them without your permission...";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "Well, let's have a talk. What do you want to know?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "What can you tell me about local clans?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Have you explored the outer ring of ships?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Does the island have any connections with Cuba or Main?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I had found a manuscript of one sailor - Alvarado, he was Spanish. He described the Island with a lot of details. He mentioned a few interesting ships - San Augustine, San Geronimo and Tartarus. All of them were part of de Betancourt's squadron, disappeared over fifty years ago\nI made a research about that expedition. So, turned out that there were a forth ship named St. Anna which was carrying the squadron's treasury - a pile of doubloons! Besides, the ships had golden ore in their holds. I decided to find the Island\nMade a deal with a captain I knew and we sailed on his schooner. It's clear how the story ended, I guess. We have found the Island, Betancourt's ships, even his offspring - he lives here, name's Antonio de Betancourt. But I failed to leave this place\nThe schooner was broken by reefs, my companion died and I among other survivors managed to get here. The worst part is that I didn't find what I was looking for - neither St. Anna's treasury, nor golden ore.";
			link.l1 = "I have also read Alvarado's notes. Intriguing story.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Rivados are damned pagan scum. They are offsprings of negro slaves, brought here by de Betancourt from Africa. Though they have learned how to use blades and muskets from white folk, but they are still savages\nNarwhals are good people, smart and decent fighters. They have outstanding craftsmen among them. I know a lot of them. Perhaps one day I'll join their clan\nPirates are a pain in the butt, damn them. We didn't call them, but they have arrived, captured our supplies and dared to sell us our own food! Bastards, hey? Pity that we cannot drive them away and have to live with their presence.";
			link.l1 = "Interesting...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sure. A man has to make coin. Damn pirates demand gold, pesos or different valuables for the food. They sell it much cheaper to such locals like me than to the clans, but it's not a charity anyway. Thank God, there are enough ships at the outer ring to loot, a lot of them still remain untouched by someone since their wreckage\nAn interesting activity, yet dangerous: you may fall to the watered hold, break bones, get stuck in ropes, get smashed by wooden parts or meet giant crabs - they often visit holds out there.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Alas, it doesn't. They say that buccaneers and smugglers from Cuba had been visiting this place long ago - they had been exchanging provision for gold and goods. Even Narwhals visited settlements. But it is a history now. No one would risk to sail on fragile and small boats. Storms destroy small boats in a second and we don't have better vessels here.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, ah? Thief!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest!", "Decided to check my chests? You won't get away with it!");
			link.l1 = "Shit!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to check my chests? You won't get away with it!";
			link.l1 = "Foolish girl!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you'd better take your weapon away. It makes me nervous.", "You know, running with blade is not tolerated here. Take it away.", "Listen, don't play a medieval knight running with a sword around. Take it away, it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Okay.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful, pal, while running with a weapon. I can get nervous...", "I don't like when men are walking in front of me with their weapon ready. It scares me...");
				link.l1 = RandPhraseSimple("Got it.", "I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}