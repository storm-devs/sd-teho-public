// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "Speak... But be quick, I am busy.";
				link.l1 = "They say that you are hiring captains.";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "Do you have any business for me?";
			link.l1 = "No, no, nevermind. I am leaving.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "I thought that you are already at the halfway to Saint-Martin, captain...";
				link.l1 = "I am preparing to set sail, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "Ah, captain, there you are! I didn't see you coming, I have just finished reading Ridderbrock's letter, he calls you the guardian of merchants and the God's scourge for pirates! What say you about that?";
				link.l1 = "I'd prefer to stay just a common captain. Common yet rich captain.";
				link.l1.go = "SantiagoTrip";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "Why are you still here and not at the halfway to Cuba?!";
				link.l1 = "Yes, yes, I am on my way, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "Ah, captain! I admit I have already started to worry. How was it?";
				link.l1 = "It was... not without troubles, but I'll tell you about them later. Business first. Senor " + GetFullName(sld) + " told me to say you the following: 'this man has to die'. Then the Geraldi will consider the incident settled. Also, he said that this decision is a will of their family.";
				link.l1.go = "SantiagoTrip_8";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete" && GetQuestPastDayParam("questTemp.HWIC_TaskBerg") > 7)
			{
				dialog.text = "Glad to see you, captain! It's good you came to see me.";
				link.l1 = "Good day, mynheer. I take it that you have already got a new assignment for me for the good of the Company?";
				link.l1.go = "JacobBerg";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "I have told you to moor your ship. Do you even listen to me?";
					link.l1 = "Yes-yes, I got it, I am on my way.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "So, you have moored your ship and now it's the time to give my xebec under your command. Are you ready to get this mission started immediately? My ship is well equipped and ready to sail so there is nothing left to worry about for you.";
					link.l1 = "Yes, sure. I am ready, mynheer Rodenburg.";
					link.l1.go = "JacobBerg_6";
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "I think that you are seeing Longway now. Why are you still here?";
				link.l1 = "Yes-yes, I am on my way.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "Captain... I am already aware about your voyage.";
					link.l1 = "Oh, really? So you must know that...";
					link.l1.go = "Jacob_lostMef";
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "Captain... I am already aware about your voyage.";
					link.l1 = "Is that so? So you must know that...";
					link.l1.go = "Jacob_lostMir";
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "Captain... I am already aware about your voyage.";
					link.l1 = "Is that so? So you must know that...";
					link.l1.go = "Jacob_failFull";
					break;
				}
					dialog.text = "Here you are, captain... I already know everything about your trip.";
					link.l1 = "Is that so? So you must know that...";
			link.l1.go = "Jacob_complete";
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Aren't you already on Antigua? Hm... strange.";
				link.l1 = "Yes-yes, I am on my way.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "I was reported already about your arrival, captain. I also know, that you have lost the Mirage in battle.";
					link.l1 = "You are well informed, mynheer Rodenburg. Despite all of my efforts I wasn't able to save her.";
					link.l1.go = "Fleetwood_fail";
				}
				else
				{
					dialog.text = "I was reported already about your arrival, captain. I see that the Mirage is in your squadron. That is great...";
					link.l1 = "It was all by your instructions, mynheer. You have ordered to kill Fleetwood - he is dead. You have ordered to bring the Mirage to the local port - she is there.";
					link.l1.go = "Fleetwood_complete";
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare" && GetQuestPastDayParam("questTemp.HWIC.Holl.Abby") > 7)
			{
				dialog.text = "Ah, here you are. I am glad to see you. I have another mission for you, just as I have promised.";
				link.l1 = "I am listening, mynheer.";
				link.l1.go = "Abby";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, I am glad to see you, my friend. You were getting late, and I had started to worry. Were you able to get anything from Abigail?";
				link.l1 = "I was able not only to get, but also to solve all problems. I have found the island and the lost money of the Shneur. Solomon is happy and Abigail will say yes. Congratulations, mynheer!";
				link.l1.go = "Abby_2";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Ah, I am glad to see you, my friend. Were you able to get anything from Abigail?";
				link.l1 = "Yes. I had a talk with Abigail and her father. Well... there is a problem, mynheer, the reason is the money they had lost. Abigail is feeling herself... well... unworthy of you, she fears of people's gossips and whispers. I hope that you understand me.";
				link.l1.go = "Abby_6";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, my friend! I hope that you have brought good news?";
				link.l1 = "Our plan was successful! Abigail will say yes. Congratulations, mynheer.";
				link.l1.go = "Abby_8";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "I have been waiting you. My friend, you are in a great danger. I worry about your fate.";
				link.l1 = "What do you mean?";
				link.l1.go = "Merdok";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "I was reported about your arrival, my friend. I am glad that I can see you again. Does it mean that Johan van Merden is dead?";
				link.l1 = "Yes. He and his accomplice are eliminated. It was a tough, but I saw it through.";
				link.l1.go = "Merdok_4";
				break;
			}
			dialog.text = "Anything else, captain? I thought that we have already discussed everything.";
			link.l1 = "No, it is nothing. I am leaving.";
			link.l1.go = "exit";
		}
		dialog.text = "Do you have anything for me?";
		link.l1 = "No-no, don't draw your attention to me. I am leaving.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			dialog.text = "Perhaps the rumours are true. So what?";
			link.l1 = "I am captain " + pchar.name + ", me and my ship can be useful to you.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "Really? Are you serious?";
			link.l1 = "That is why I am here, mynheer.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Hm, fine. By the way, captain - forgot your name - do you know Balthazar Ridderbrock? No? Lucky you! Such greedy, grumpy, hot-tempered idiots are rare sights.\nBut it seems that such outstanding qualities were not enough for the man, so he was smart enough to offend some filibuster by the name of " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " in the local tavern and called soldiers upon him the very moment the offended party fairly touched a sword...";
			link.l1 = "... and surely they had the pirate hanged on the very first free rope?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "It is not that simple. " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " is not a common pirate, but a Dutch privateer, a veteran of fighting the Brits. Besides, local citizens really sympathize him. I can't say the same about Ridderbrock.";
			link.l1 = "So our filibuster is still alive?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "Yes, but he is really angry and that is why Ridderbrock scared shitless. He has reasons for that though.";
			link.l1 = "I suppose, that my fortune is about to end, so will I meet the dear Balthazar soon enough?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "Precisely. People of Philipsburg are desperately waiting for a cargo of sugar, which our mutual acquaintance promised to deliver. I don't consider the man my friend, but, alas, he works for us, so go to a harbour office, find him there and tell him that I order him to set sail immediately.\nYou shall follow him, and, please, escort him to Philipsburg in one piece, I don't want " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " to waste the cargo and reputation of our company.";
			link.l1 = "And what about payment for such, I'd be clear, unpleasant assignment?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "Captain, do your job first. Balthazar will pay you as soon as he reaches his destination and I am not talking about the bottom of the sea. Anyway, return back to me with your report once the job is done. If you successfully do this job, you will be able to count on my further patronage. I don't keep you anymore.";
			link.l1 = "See you, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "Ha-ha-ha... Yes, Ridderbrock is greedy that's for sure. Whatever, I am not interested in him anymore. Let's talk about you, captain. I like your resoluteness so I am going to offer you another job. Don't worry, this time I will pay for it myself.";
			link.l1 = "I am listening, mynheer.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ah, so you are the captain who was protecting a ship of our scrub Ridderbrock? I have heard about it... He paid you only five thousands for your job and he was boasting about it in public at the tavern of Philipsburg drunk as a pig. If I were you, captain, I'd hurt him.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "I need a man for a very important matter. You did well in that story with Balthazar so I suppose... yes, I can trust it to you.";
			link.l1 = "I am honoured. So, what's the matter?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "I am not going to explain you what is the situation here, but be aware that this is not just about me, this is about the Company, so you have a chance to do us a big favour.\nSail to Santiago of Cuba and deliver this package to don " + GetFullName(sld) + ". He has a high position in Geraldi's bank and he is also my... our business partner. Besides, you are to deliver him gold which I will give you right now. I trust in your honesty, captain.";
			link.l1 = "Do you doubt in me, mynheer?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " I am also giving you this short-term trade license in order to spare you from any troubles. This will allow you to visit Spanish colonies for some time.";
			else sTemp = "";
			dialog.text = "Not at all. Trust me, I wouldn't even talk with you about the matter, if I have reasons for that. Know that it took quite a while finding the right courier for the job, so you have only about fifteen days to deliver."+sTemp+"\nMy message must be delivered in time, this is vital, my friend. It will help smooth some things up. Hurry, but be careful, I doubt that this is going to be an easy voyage.";
			link.l1 = "Anything else? Why do you warn me, mynheer Rodenburg?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "Let's just say that it is only my personal suspicions. Don't worry, if you do it as certain and fast as you did the last job, then you will have a chance to become a very valuable agent for delicate matters of the Company.";
			link.l1 = "So, all I have is to deliver this letter and money to the banker at Santiago for fifteen days? Well, it doesn't look much difficult.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "Wait, my friend... I take it that you don't really get the importance of this situation. Doing this job will make me very obliged to you and on the contrary, failing it will make me really upset. In that case I will try to do my best to upset you as well. I hope that we understand each other, captain " + GetFullName(pchar) + "?";
			link.l1 = "Point taken. You have my word. I will do my best to keep you in good mood.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "Very well. Now, take the letter, these chests and remember about terms. And one more thing: try to avoid troubles in Santiago. I expect good news soon.";
			link.l1 = "On my way.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "'Has to die'... just like that. I didn't expect that coming. Hm. You have done your job in the most perfect way, captain. Now tell me about troubles you had faced.";
			link.l1 = "Nothing special... just usual trip troubles.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "I was stunned and kidnapped by one man in Santiago. He was really interested in your business with Geraldi. I managed to escape, but I had to kill him first. He mentioned some Gaston and that is the only thing I got to know from him. I don't have any ideas what was it all about.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "I was stunned and kidnapped by one man in Santiago. He was really interested in your business with Geraldi. I managed to escape, but I had to kill him first. I wasn't able to get to know anything from him.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "Well, let's get straight to more pleasant part. My gratitude is not limited by only my words. Here, take your reward, you have earned it.";
			link.l1 = "Our collaboration is quite profitable.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "Nonsense! Kidnapping you... Wait, though... Gaston! I understand... I guess. Alas, my friend, this is not your business. For the present, at least. We'll see how it goes. Nevermind, glad that you made it alive.\nLet's talk about more pleasant things - accept this reward, it's totally deserved.";
			link.l1 = "Our collaboration is quite profitable.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "Nonsense! Kidnapping you... I have some suspicions though. You'll learn more if you continue working for me. You are lucky and I am glad that you made it.\nLet's talk about more pleasant things - accept this reward, it's totally deserved.";
			link.l1 = "Our collaboration is quite profitable.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "Exactly, my friend, exactly! You can become a perfect agent of the Company if we will continue to work together. Now go, take rest from this mad race. You have lived up to my expectations and I appreciate it. But time is running and I would be really grateful if you will be back in a week, we still have a lot of work to do.";
			link.l1 = "You can count on me, mynheer Rodenburg.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.HWIC_TaskBerg");
			AddQuestRecord("Holl_Gambit", "1-46");
			pchar.questTemp.HWIC.Holl = "SantiagoTripComplete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("The say that mynheer Rodenburg is quite pleased by you, captain. Don't loose your chance, Lucas rarely favors people.", "Villemstad", 10, 3, "");
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "You are smart, captain. Exactly. Well, let's talk details of the upcoming mission...";
			link.l1 = "I am all ears.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "I have a very serious and important mission for you and I expect you to do everything according to my instructions. So, as you know, we have very unfriendly relations with England. Brits are sure that they are the ones, who should rule the world. Problem is - not everyone tend to agree with such claim\nHolland has the biggest trade fleet in the world and our military squadrons can defend interests of the Republic. English hate us for our trading power and they are doing what they can to sabotage the Company's activities. There is a navy captain called Richard Fleetwood, he is basically a pirate who attacks and plunders any ship sailing under Dutch flag. He explains his actions to be counter measures to the 'ghost ship' which sinks English traders. He claims that this ship acts under protection of our colours\nDid you hear about the 'ghost ship', captain?";
			link.l1 = "Well, you can hear that kind of fables in any tavern. Just buy a few cups of rum for an old boatswain and you will get any story you want...";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "It is so, yes. But this matter is a bit more... real. I have investigated actions of that 'ghost ship' and I found out that she is not an ordinary ship, but a ketch named 'Mirage' and she is under the command of Jacob van Berg, who has turned her into a masquerade and pretended her to be the legendary 'Flying Dutchman'.";
			link.l1 = "Van Berg? Huh.. It looks like he is a Dutch afterall, right?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "Jacob van Berg is a Dutch. But my country sentenced him to the gallows a long time ago. He is a criminal, a pirate who acts only on his own. So, Richard Fleetwood is hunting van Berg. This fact we'll use against this insolent brat.\nI don't want to literally eliminate Fleetwood, though he deserved it long ago. Death would not be enough for him. I want not only to kill the scum, but also to destroy his name and crush his honour. This is much more effective measure. This will also teach arrogant Englishmen a lesson.\nLet's talk details now...";
			link.l1 = "Yes, mynheer, from stage to stage. I am starting to loose your point...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "Good. I have managed to learn a location of Jacob van Berg, thanks to my agent. He is in some city of Southern Main. Go to him and find out where did he leave his ghost ship\nThen kill him, find his vessel, capture her and deliver her here. You must capture the 'Mirage', don't even think to sink her.";
			link.l1 = "Hah, at least now I know what to do. Where should I look for that van Berg?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "All details will be provided to you by my agent. His name is Longway, he is a Chinese. Yes, I am also giving you my personal ship, xebec 'Meifeng' for this mission. Longway is her captain, but he will act only as your officer while you are in charge.\nGo to the local harbour office and leave moor all your vessels. Return to me once it's done.";
			link.l1 = "Fine, I will visit the harbour master. I won't make you wait me for too long.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
		break;
		
		case "JacobBerg_6":
			dialog.text = "Longway is waiting for you outside. He will show you your new ship and will give you some information regarding van Berg's location. Good luck, captain and don't let me down! Remember that you also have to preserve the 'Meifeng' so try not to sink her.";
			link.l1 = "I got it. I am on my way!";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "Yes, I am aware that you have failed your mission to capture the pirate vessel. All my plans are ruined. I am taking away 'Meifeng' from you. You can go now, I don't need your services.";
			link.l1 = "I am so sorry for that. Farewell, mynheer Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "Yes, I am aware that you have lost the 'Meifeng'. It is most unacceptable... I am going to take away the captured pirate vessel. You can go now, I don't need your services.";
			link.l1 = "I am so sorry for that. Farewell, mynheer Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "Yes, I am aware that you are a rare muddler and bungler. You didn't captured the pirate vessel and lost my Meifeng. I am really disappointed at you. Get out!";
			link.l1 = "I am so sorry for that. Farewell, mynheer Rodenburg.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "Yes, I am aware that you have perfectly conducted our plan. The filthy pirate is dead and you captured his ship. A payment for this stage of plan is 50 000 pesos, take it.\nI am retrieving the 'Meifeng' from you, it's time for you to take command of the 'Mirage', she will play an important role in the next stage. Are you ready to listen to my instructions?";
			link.l1 = "Yes, sure, mynheer Rodenburg.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are doing some special assignments for mynheer Rodenburg himself. Something about destroying those insolent pirates. It seems that you are a very significant person, captain.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of mynheer Rodenburg himself. Well, don't even come close to him after that...", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Another raid is ahead of you, time to deal with Fleetwood. We should lure him out, using the 'ghost ship'. Organize a trap close to Dominica and the Mirage will serve as a bait.\nFirst, you should let Fleetwood know that the Mirage was seen not far from Dominica. This will force our brave military man to leave all his doings and rush there for a hunt. Surely you must understand that talking to the man himself is too dangerous. Find a drugstore in St. John's. Its owner John Murdock is an old friend of mine.\nTell him that you are acting under my command and he will help you to find ears to fill with a juicy lie about the 'ghost ship' attacking poor English merchants around Dominica.";
			link.l1 = "I see. I will lie something, I am used to it. The prior goal is to eliminate Fleetwood at Dominica, am I right?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "Yes, exactly. Longway on the 'Meifeng' will wait for you near Dominica. Two of you can kill the English dog easily. I ask you to board his ship and search through his cabin. I want to see his logbook, it might help to clear up some things. I will pay extra for the logbook.\nBut your main priority is to kill the bastard, so if boarding him will not be an option - screw it, just sink his tub. Also, preserve 'Mirage' at all costs. She has a role to play in the next stage.";
			link.l1 = "The goal is clear. May I proceed?";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "A piece of advice, captain. Do not drop an anchor at St. John's port. Land at one of the island's bays and get to the city through the jungles, otherwise John won't talk with you concidering it's too dangerous for him. Also, be careful at the sea - the 'Mirage' is too famous among English colonies, so avoid their warships and settlements, I'm sure that you don't want to be attacked. This is it. Set sail and God help you!";
			link.l1 = "Thanks! I am on my way.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "I am glad that you are showing such a conscientiousness, captain... Did you get Richard Fleetwood's logbook?";
				link.l1 = "Unfortunately, I didn't. Didn't get a chance to board him. I had to shoot down his ship with my cannons.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "I am glad that you are showing such a conscientiousness, captain... Did you get Richard Fleetwood's logbook?";
				link.l1 = "Unfortunately, I didn't. I managed to board his ship and to kill the man in a close quarter combat, but I didn't find his journal. The ship was mined and I didn't have much time to look for it.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "I am glad that you are showing such a conscientiousness, captain... Did you get Richard Fleetwood's logbook?";
			link.l1 = "I did. Here it is. I managed to board the Valkyrie. Though it was too close - the damn bastard had mined his ship and blew it sky high. We barely made it.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "Too bad, we could have found a lot of interesting things from it... Whatever. You managed to destroy that insolent English dog and that is the most important. Here is your reward - 100 000 pesos. I am taking the 'Mirage' from you, we are going to return this ship to England.";
			link.l1 = "How?! Why? I don't get it...";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "Excellent! You are really an exemplary military sailor! If all of our captains were like you, Holland would take the first place among sea nations. Here is your reward - 100 000 pesos, and 50 000 pesos extra for the journal. I am taking the 'Mirage' from you, we are going to return this ship to England.";
			link.l1 = "How?! Why? I don't get it...";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "My friend, you are an excellent soldier, but trust me and my experience in the matters of politics. Remember what I said about Fleetwood? I will nail him and his name. And these arrogant nobles from Port Royal will have to swallow and choke.\nWe are going to make Richard Fleetwood a captain of the 'ghost ship', a werewolf who were playing off with two nations, plundering, pillaging and murdering peaceful citizens of both, only to make himself rich. I have already prepared evidences and witnesses and the 'Mirage' will serve as a primal evidence.";
			link.l1 = "And you will sacrifice the excellent ship for that plan?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "This is war. Sometimes we sacrifice not only ships, but settlements with people. And every war comes with losses. Speaking of losses. I have bad news for you.\nWillemstad was attacked by English capers and all ships in the harbour were thrown to fight them\nYour ship was also participating in a battle, but, alas, she was burnt down and sunk.";
			link.l1 = "F...! To sink my ship... What a pity! But there is nothing I can do now.";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "Don't be sad, captain. I have something to please you. I place xebec 'Meifeng' under your command instead of Longway's. You are free to use the ship in any way you want, within reasonable limits of course. And I will be waiting for you tomorrow in the governor's residence, you are nominated for a state award. Don't leave the town, captain.";
			link.l1 = "Am I?! That's great news, indeed. I am honored. By the way, mynheer, but where has Longway gone?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "Longway has suddenly disappeared right after I ordered him to sail to Dominica. I have suspicions that it is English intelligence to blame... or perhaps not. I am investigating this incident.";
			link.l1 = "I see. His help at Dominica would've been most welcome. Fleetwood was a tough guy. I hope that Longway is still alive... Goodbye, mynheer!";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			pchar.quest.Award_FromLucas.win_condition.l1 = "Timer";
			pchar.quest.Award_FromLucas.win_condition.l1.date.hour  = 8.00;
			pchar.quest.Award_FromLucas.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l2 = "location";
			pchar.quest.Award_FromLucas.win_condition.l2.location = "Villemstad_townhall";
			pchar.quest.Award_FromLucas.function = "AwardFromFromLucas";
			AddSimpleRumour("Tell me, captain, was this damned English dog Fleetwood was really responsible for plundering English merchants? Really? Such an artful rogue! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "Too bad... My beautiful plan is flopped. Eh, captain, you were so close to the sacred goal but you have failed it... Well, I will pay you 30 000 pesos for Fleetwood's elimination. I have no more missions for you. You are free to go.";
			link.l1 = "As you wish.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Yes, captain, I have to frustrate you. Willemstad was attacked by the English privateer while you were gone. We have had to take all ships to protect the town. Your stored ship was also participated in the battle but, unfortunately, it was sunk. Alas! I am sorry.";
			link.l1 = "Yes, it is really a pity. But there is nothing I can do. Farewell!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Captain " + GetFullName(pchar) + "! For eliminating Richard Fleetwood, a dangerous state criminal, for exposure of treacherous English conspiracy against the Company, for your bravery and courage, you are awarded with one thousand golden doubloons on behalf of Dutch Republic!\nYou also are to receive this valuable navigation tool - a dream of any military sailor.";
			link.l1 = "I serve the Republic!";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("hol_guber");
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "Congratulations again, my friend. And, please, visit me in a week, I am going to ask you and only you to deal with a very delicate matter.";
			link.l1 = "I got it, mynheer Rodenburg. I will visit you in a week.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("hol_guber");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			pchar.questTemp.HWIC.Holl = "Abby_prepare";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.Abby");
			AddSimpleRumourCity("Oh, they say that you were nominated to a state award by Matias Beck himself! Holland can be proud to have people like you, captain!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "Let me tell one intriguing story first, it will help you to understand how delicate your next task is. A few months ago a flute under English flag was attacked by well-known to you Jacob van Berg, he sank the flute not far from some unknown island. Only two Jewish settlers survived - Solomon Shneur and his daughter Abigail. They lost the rest of their family in the fight. Somehow they reached the island\nSolomon even managed to drag a chest with family gold to a shore. Another well-known character, Richard Fleetwood, was saling had been sailing not far and heard the sounds of fighting and arrived to catch van Berg, but he was too late and the pirate fled. So he decided to check the island for any survivors\nHe saved Solomon and Abigail from eternal life on the desert island, the irony is, that Solomon mistook Richard's ship for Jacob's 'Mirage' and got scared as heck, so he stashed his gold somewhere on the island. As I result, he and his daughter arrived here without a penny, dropped by Fleetwood at Blanca Lagoon\nSolomon told me this story. The Company supports Jewish community here, therefore I made sure they have a roof over their heads, got something to eat and to wear. I visited their place a lot. Abigail is a wonderful young girl. Sincere and naive\nI won't lie to you, captain, I like her and I intend to make her my wife. She likes me too, but something is eating her, and this 'something' interferes with my plans.";
			link.l1 = "Perhaps, her father is the reason?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "This is not about her dad, I am sure of it. Solomon would be in the seventh heaven if I married Abigail. In the matter of fact, he pushes her to accept my proposal. No, there is something different about her. I ask you, my friend, to solve this problem for me. Talk to the girl and find out what is wrong\nYou are a stranger, she might tell you things, she would never tell familiar people because of her girly modesty. Their house is left of governor's palace. Go, you might be fortunate, I know that you are a smooth talker\nBut remember one thing: Richard Fleetwood was the true captain of the 'ghost ship'... Keep it in mind while talking to Abigail.";
			link.l1 = "Ha! Sure I remember that, mynheer Rodenburg. Actually, this is the officially recognized fact... I won't waste time then, I am going to pay your beloved a visit immediately.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
		break;
		
		case "Abby_2":
			dialog.text = "Have you really found the island where Solomon has stashed his savings? This is most excellent! I am starting to think that you are able to do any task... Have you found anything else in the stash?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "No, nothing else. Only money.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "There was an interesting item - a jade skull. I have given it to Solomon, he said that it was a relic of his family. He also said that you were going to buy that item from him...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Hm. Fine then. It is quite odd though. Whatever... I owe you, mynheer, and I will never forget it. I have prepared a reward for you - 50 000 pesos and this amulet. It is yours now.";
			link.l1 = "Thank you, mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "Excellent! Yes I am going to buy this artefact from Solomon, he doesn't need it and I have a very generous buyer for it. Whatever... I have prepared a reward for you - 50 000 pesos and this amulet. It is yours now.";
			link.l1 = "Thank you, mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "Well, I don't have any job worthy of such a captain like you for now. But don't leave Curacao for too long, soon I will need your services again.";
			link.l1 = "I got it, mynheer. Goodbye!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.quest.Merdok_prepare.win_condition.l1 = "Timer";
			pchar.quest.Merdok_prepare.win_condition.l1.date.hour = sti(GetTime());
			pchar.quest.Merdok_prepare.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.Merdok_prepare.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.Merdok_prepare.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.Merdok_prepare.win_condition.l2 = "location";
			pchar.quest.Merdok_prepare.win_condition.l2.location = "Villemstad_town";
			pchar.quest.Merdok_prepare.function = "GiveTaskMerdok";
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			AddSimpleRumourCity("Have you heard the last news? Mynheer Rodenburg is going to marry Abigail Shneur, the daughter of that old crazy Solomon. What can I say, she is a lucky girl...", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "Ha, and that's just it? Ridiculous... Listen to me, my friend, this problem can be easily solved, I know how much money was in Solomon's stash. Two hundred thousands pesos. I am ready to spare this sum for my and Abigail's happiness. I will give you the money and you will leave Curacao for a week or two. Then you will return to Solomon and give him these coins. Pretend that you've found the stash. The wolves are sated and the sheep intact. Here, take required sum. Do you agree with my plan?";
			link.l1 = "I completely agree with your plan. Let's do it.";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "Well, then sail to the open sea and return back to me in ten days.";
			link.l1 = "As you say, mynheer Rodenburg.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Splendid! Once again, you did the job perfectly. I owe you, mynheer, and I will never forget it. I have prepared a reward for you - 50 000 pesos and this amulet. It is yours now.";
			link.l1 = "Thank you, mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "Yes, exactly so. My friend, sometimes it's hard to see who is your friend and who is your enemy. Sometimes you miss the point when your dearest friend turns into arch-enemy. Our mutual acquaintance from St John's, John Murdock also known as Johan van Merden, an ex agent of the Company has sold himself to the English Navy intelligence.\nHis newest mission is to eliminate one of the Company's brightest agents... you.";
			link.l1 = "I am flattered. Sure, you never see such treachery coming.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "Precisely, captain. He is a sly dog. Find the scum and kill him before he strikes you. Sail to Antigua and search for a secret entrance to his drugstore. There is a hatch in front of the church. Use it.";
			link.l1 = "It looks like I don't have a choice.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "There is one more thing, captain. Once Johan will be dead, search his corpse, the house and the dungeon. He has an archive - a fat ledger, he used to write down some juicy notes during his work for the Company. This information will harm us all if our enemies find it.\nFind the archive and deliver it to me, I will pay extra for it. Now go. Godspeed, captain " + pchar.name + ", and try to return in one piece. The Republic needs you!";
			link.l1 = "I promise you, mynheer, to return back in one piece. And what is more, this is actually in my interests. See you soon!";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
		break;
		
		case "Merdok_4":
			dialog.text = "Excellent, captain! I am glad, I really do. Have you found an archive?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "Yes, here it is. There were no any more ledgers neither on the chemist's corpse nor in his chests.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "No. I was looking for it everywhere, yet found nothing.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "That's a pity for sure, but I am fine with that. I am sure that Johan didn't have enough time to give it to the English, otherwise we would see the consequences by now. It is likely that he has hidden it in some secret stash... let it stay there forever! I congratulate you, captain, with the successful end of the mission!";
			link.l1 = "Gratitude!";
			link.l1.go = "Merdok_6";
		break;
		
		case "Merdok_book":
			dialog.text = "Splendid! Now the English won't get it. You have proven that you are the best once again... Give me the book... There is a reward for the archive you found - here, this fine musket. It has been serving me with a great effort and now it's your turn!";
			link.l1 = "Gratitude!";
			link.l1.go = "Merdok_6";
			RemoveItems(PChar, "MerdokArchive", 1);
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "We did well, me and you, captain. It is not an overstatement that you have been a great special agent. You will reach incredible career heights in case you will continue to serve Holland.";
			link.l1 = "It sounds like you are saying goodbyes...";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "I am, " + pchar.name + ". I have accomplished everything I wanted here, so I am leaving to Europe, to my homeland Holland in a week. My wife Abigail and my father-in-law Solomon will accompany me. Peter Stuyvesant has already found a new vice-director, so talk to him if you need something\nAh, for your loyalty I present you the Meifeng, she is yours now, captain, you totally deserved the girl.";
			link.l1 = "Thank you, mynheer Rodenburg. I really have got attached to the Meifeng and I've started to consider her as my property...";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "And now I have to ask you to leave me, my friend, I have got a lot of things to do before we set sail... Visit me in Amsterdam one day! We will share a drink and remember the good old times...";
			link.l1 = "Sure, mynheer. I wish you to be happy and prosperous in your new life! Farewell!";
			link.l1.go = "Merdok_9";
		break;
		
		case "Merdok_9":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("hol_guber");
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Holland with his young wife and the father-in-law. There is a new vice-director in the Company. Isn't that you, captain?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, that you are highly thought of by our authorities. They say that mynheer Rodenburg has appointed you as his successor in the Company. Is that so, captain?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "Ha, a friend of Fleetwood's is here! You have won the boarding, but you are about to see that Lucas Rodenburg will slam the door of his life very loudly!";
			link.l1 = "I don't think that you 'door' will be slammed more loudly than a hatch of the chest with Gaston's head did... Nothing and no one will be able to scare me anymore. Not after that awful day.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("VOICE\Russian\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Ha-ha, conceited English dog! I have fired the cargo hold and the fire will get to the gunpowder room soon enough. Ships are deadly coupled so you won't escape! You will go to hell!";
			link.l1 = "We'll see...";
			link.l1.go = "Lucas_abordage_2";
		break;
		
		case "Lucas_abordage_2":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "Why are you here? Want to mock me? Perhaps you will tell me at last what's your interest in all of this? It was you who captured the brigantine, right? Was it your plan from the beginning?";
			link.l1 = "I am here, Lucas, to give you regards. Best regards from betrayed John Merdock. You was my job and I did it. Farewell now.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("VOICE\Russian\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Johan? Ha-ha! So that was the man behind all of this! Old scum! But the game is not over yet. There is a van Berg coming for you and you won't escape from him! Your life will be ended soon, bastard!";
			link.l1 = "Spare your oratory for the court, Lucas. Farewell.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}