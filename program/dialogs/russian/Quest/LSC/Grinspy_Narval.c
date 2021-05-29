// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "What? What do you want?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". I wanted to meet the leader of the clan.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Want something?";
				link.l5 = "Just wanted to greet you. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Now you know me. My name is Donald Greenspen and don't make me or my men angry. And don't try to visit the 'San Gabriel' until you have got a password. Shop is free to visit, everyone need to trade. Any questions?";
			link.l2 = "No, I got it. See you.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "What business do you have for me?";
			link.l1 = "A very unpleasant one, Donald. There was an attempt on Steven's life last night. Fighters of your clan participated.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "I don't know about that. Why do you think that they were my men?";
			link.l1 = "Because I was there. We are able to see the difference between your men, pirates and Rivados. The group was lead by Mary Casper and Chad Kapper. Do you need more evidences?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "I can only ensure you that me and my men have nothing to do about it.";
			link.l1 = "You will have to ensure admiral of it and it won't be easy. Dodson is very angry at all Narwhals after the attack. He is going to declare you a war - he will stop providing you with a provision and shoot your men whenever any opportunity is given. And it's not just words.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "I hope that admiral understands what he is going to do. Does he doubt that my men can shoot too?";
			link.l1 = "I think he does. He is ready to turn the 'San Augustine' into a fortress and fight until you all starve. Besides, Dodson is going to talk with Rivados and offer them a cooperation. You won't stand a chance against admiral and Rivados together.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Fuck! But we are not a part of this attempt! Why the whole clan must pay for actions of that stupid girl Mary and a bunch of scums from my crew?\nBesides, let's talk logic, by killing Marlow Dodson himself provoked Mary and my soldiers. That's exactly what happens when you commit such meanness.";
			link.l1 = "You don't understand a thing. You were fooled. Why are you so sure that Dodson has killed Alan? Actually he thinks that you have done that to take his position...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "I don't give a shit what he thinks. All evidences are against him. Only he and his men had an access to the prison. Alan was in his hands. Red Mary told me a lot. Before Alan was murdered, Dodson personally visited the prison and he doesn't do it often.";
			link.l1 = "Have you seen his death?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Rubbish! Of course I haven't.";
			link.l1 = "And Chimiset have. Yes-yes, Rivados wizard who had been sitting next to Alan. He was also murdered there recently. I was in the prison a day before his death and had a talk with him. Milrow was killed by Chad Kapper, the boatswain of Shark.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Is it true?";
			link.l1 = "Think about it: Chimiset didn't care about your relationship with the admiral. He had no reason to lie. The old wizard was scared of Chad, he supposed that he would be the next. He was right, Chad had murdered him as soon as he learnt that admiral is going to set him free.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "But why Kapper wanted Alan's death?";
			link.l1 = "Damn, don't you really understand? I have told you that Kapper was working with Red Mary. He wanted to take Shark's position and made a cunning plan to do so. Killing Alan Milrow and spreading gossips about Shark's involvement in his death made Narwhal clan hostile against admiral...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "Silly girl Mary trusted him and stood on the side of the real killer of her boyfriend. They had persuaded a few Narwhals to join them, it must had been easy for Mary. Then they have organized an attack on admiral in Fazio's cabin who was forced to write an invitation to admiral...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "I have a letter from Fazio which explains everything. Chimiset was killed by Chad as a dangerous witness. He was cooperating with Narwhals and Rivados would be really glad to hear that during their talk with Shark. We will easily prove Black Eddie that Chad became one of your kind by showing this letter.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "Hm. You have got all aces, what are doing here then? You want something from me, right?";
			link.l1 = "I do. Because I believe that it was all Chad's plan and you are not involved. Chad has cheated on Mary, she called her friends from your clan to help her, that's a whole story. At least, I haven't found any evidences against you or any other Narwhal...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "But it doesn't mean that there is no other plotters are left. I want you to search for them. Then, perhaps, we will settle things without a slaughter.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "I have already told you that no one else of my men was part of it. After Marlow's death Mary basically left the clan and locked herself in her cabin. Actually, I have no idea how she managed to persuade others to take part in it, but it seems that she had succeeded. I swear that neither me nor anyone else from my clan are acting against admiral.\nWe have lost too many men recently, so we don't want to step into a messy business now. I am not afraid of admiral's attack, even joined with Rivados. Narwhals are true warriors and we will prove that in our last battle. But this would be pointless\nWe have already decided to keep peace with admiral. Rivados are the different matter, we don't negotiate with Negros. I am ready to apologize personally to admiral, to ask forgiveness for my suspicions caused by Milrow's death and for the attack on his life. I will swear on Bible to prove my sincerity. Are you and Dodson fine with that?";
			link.l1 = "I am. Are you sure that there are no tricks from your men should be expected?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "Absolutely. I will inform my clan about the real killer of Alan Milrow. My men's relation to the admiral will be changed immediately, I assure you. Tell me, will a slaughter be needed after that?";
			link.l1 = "No, it won't. I am here to prevent it. I trust you, Donald, and I will try to persuade Shark. I have a few arguments left... See you, Donald!";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "Have you spoken to the admiral already? Any results?";
			link.l1 = "I am in progress. I will see you later...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "Have you spoken to the admiral already? Any results?";
			link.l1 = "Yes, I have. Your apologies are accepted, your clan's accusation is off. There is even more, Shark is offering you to come and see him to discuss terms of the future peaceful agreement between Narwhals and pirates.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "To be honest, I didn't expect... This is a great news. Perhaps we will be even able to reconsider prices for provision for our clan and a new policy concerning Rivados.";
			link.l1 = "That concerns only you and the admiral.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "Yes, of course. You have done a great service to Narwhal clan by preventing the pointless bloodshed and perhaps even the total annihilation of my men. Take this tower musket as a token of my gratitude, you won't find another weapon of this kind\nBesides, you are allowed to visit our restricted areas just like any of clan members.";
			link.l1 = "Thanks! Farewell now, I have a lot of things to do.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "Good luck. See me if you'll have any questions.";
			link.l1 = "Got it. See you!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ho! "+GetFullName(pchar)+"! You are... no, it is impossible! Are you alive?!";
				link.l1 = "Talks about my death were a bit wrong, Donald. Ha-ha, glad to see you!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "A-ah, my friend "+GetFullName(pchar)+"! Need something?";
			link.l1 = "No, I don't. Just wanted to greet you.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "What business do you have for me?";
			link.l1 = "A very unpleasant one, Donald. There was an attempt on Steven's life. Fighters of your clan participated.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "I don't know about that. Why do you think that my men were involved?";
			link.l1 = "Because I personally killed few of them along with Chad Kapper, the admiral's boatswain who is responsible for all of this mess. He wasn't able to do it on his own, so your men were helping him a lot. Admiral knows that and he is very, very angry.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "My men? Who exactly, can you name them?";
			link.l1 = "They didn't introduce themselves. They were just shooting and fencing. Your people are reckless. They can attack even one of their own. Hell with me or with the admiral, but attempting to kill the girl?";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "Hm. Who are you talking about?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "Who am I talking about? I am talking about the attack on Red Mary. Two Narwhals tried to kill her. I got to her cabin in a critical moment by a pure accident. They would have killed her if I came later. I didn't ask their names, I am sorry, I had no time to talk with them, but Mary said that they were Narwhals.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "Who am I talking about? I am talking about the attack on Red Mary and those two Narwhals who killed her."
				link.l1.go = "negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "What? Why didn't she tell me?! I would have acted immediately!";
			link.l1 = "She was scared even to leave her cabin recently. She had an argue with you not long ago so why should she run to you and ask for your help?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "I didn't have an argue with her! She demanded impossible from me, we had a rough chat and I sent her away. But it doesn't mean that I...";
			link.l1 = "Fine, whatever. After all, all problems are solved now. But there are bastards among your men, that is a fact.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "What? Was she killed by Narwhals? Why?";
			link.l1 = "By the order of Chad Kapper, Donald. She knew too much and she didn't want to help Chad. And now the poor girl is dead!";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "I swear, I didn't know about it!";
			link.l1 = "Sure, you didn't... But let's talk about the admiral. Chad Kapper had organized the attempt and your men helped him. They tried to poison Dodson and I barely prevented that.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "I didn't order anything like that. Dodson is aware that I don't support the policy of late Alan and I think that a lean compromise is better than a fat lawsuit.";
			link.l1 = "You will have to ensure admiral in it and it won't be easy. Dodson is very angry at all Narwhals after the attempt. He is going to declare you a war.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "I hope that admiral understands his actions. Does he doubt that my men can shoot back?";
			link.l1 = "He does. He thinks your clan is a bandit cluster and it must be destroyed before you start to kill everyone. Besides, we have got strong connections with Rivados. I can simply talk to Black Eddie and offer him an alliance. You won't stand against us all.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "Fuck! Why does the whole clan have to pay for the actions of a few idiots? Don't think that I am scared. We are warriors and we will prove that even in our last battle. But I want justice. Actually, admiral is responsible for killing Alan Milrow in the prison.";
			link.l1 = "How can you be the leader, Donald... You don't know neither about Mary nor about Alan. Chad Kapper killed him. "+sTemp+" He did that to make Narwhals hostile towards the admiral and drag some of them to his side.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "I see. Fine. Let's have a talk in other way. You are here for some purpose, right? What do you want?";
			link.l1 = "I don't want a bloody mess on the Island. I don't want people to die. I don't like the idea of eliminating all Narwhals, though I assure you that Rivados and us are able to do that. I also think that the whole clan must not answer for actions of some bastards...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "But my vote won't be enough - you should officially ensure admiral that the attempt wasn't approved by you and your clan is not planning to kill Dodson.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "What can I do? I am ready to apologize for the attempt and for my suspicions about Marlow's death. I can assure him that Narwhals are not planning anything against him and I will swear on the holy Bible. Will you and Dodson find it sufficient?";
			link.l1 = "I will. I am sure that it will also work for Dodson if you visit him personally. But first, I will tell him about your intentions and then I will visit you again with results.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "Fine. I will wait.";
			link.l1 = "I'll be back soon...";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "Have you spoken to the admiral already? Any results?";
			link.l1 = "Yes, I have. If you will pay him an official visit then the problem is solved.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "To be honest, I didn't expect... This is a great news.";
			link.l1 = "Yes, you know, I am glad too.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "You have done a great service to Narwhal clan by preventing a meaningless massacre and, perhaps, even the total extermination of my people. I grant you this tower musket - you won't find another weapon like it. You are also allowed to visit our ships without any limitations.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "Thanks. A very valuable gift. Yes, Donald, one more thing: make peace with Red Mary. She is hot-tempered, but she is also sincere and honest. Arguing with you made her part off from the clan and it almost cost her life.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "Thanks. A very valuable gift. And I am really glad that it has ended that well.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "Tell her that I ask her to forgive me for hurting her and for those two scums who dared to attack her. You both are... friends, am I right?";
			link.l1 = "You are right, Donald. I will tell her. And I am really glad that it all has ended that well.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "Good luck. See me if you'll have any questions.";
			link.l1 = "Fine. Good bye!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Take care of Red Mary cause you are lucky to be with her - she is so reckless! She always gets in trouble...", "LostShipsCity", 20, 5, "LSC", "");
		break;
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
			link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Sure.", "As you say...");
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