// Глэдис Мак Артур - приемная мать Элен
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ah, captain! You know, have told everything to Helen. You can't imagine what a load has been taken off my mind!";
				link.l1 = "You have done everything right, miss McArthur. The girl needs to know the truth. And I am here because of her.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "Greetings, "+pchar.name+"! I am glad to see you! Want some rum?";
				link.l1 = "Thank you, miss McArthur but I am too busy right now.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "What do you want, sir?";
			link.l1 = "Are you Gladys McArthur?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "I am. I don't remember you, young man. So explain what do you want from me?";
			link.l1 = "I am interested in the story of your daughter's disappearance, miss McArthur. Why have you decided that she disappeared? I have heard that Helen had a very skilful crew...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ah, I am absolutely sure! Look, my late husband's mors anniversary was five days ago. Helen loved her father and she would never miss such a date. She has left only for a few days to get a load of red wood from friendly Miskito people\nThe Indians respect and fear our patron Jan Swanson, they would never do any harm to her. Mister Swanson has already spoken to them. The wood was loaded the same day. No one has seen Helen since then.";
			link.l1 = "Perhaps, the pirates attacked her?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Nonsense! You must know already that mister Swanson is one of the five pirate barons and he is a member of council of the Brethren of the Coast. No pirates are allowed to hunt here without his permission. It could be a newbie though...";
			link.l1 = "And what about the Spanish? Could she face a Spanish patrol?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "I am not good in politics, but they say that the local gold and silver mines are completely wasted, not much treasures left to risk lives of noble hidalgos. So they are rare guests here. Besides, the Indian people are hostile to them\nA random meeting with a Spanish patrol couldn't end bad for Helen, she didn't do anything criminal from even their point of view. 'Rainbow' was flying the Dutch flag and all Helen's papers were in order including a trade license.";
			link.l1 = "Did anything special happen before her last sail? Perhaps, some odd event which you've missed?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Ah, of course, not! Thank God, we are living peaceful lives here. Yet, a few weeks ago Helen received a letter from another unwanted admirer begging for a date. She is a pretty girl, but not a rich one\nSo she has got plenty admirers, though she doesn't like any of them and she doesn't want to get married. She has already fooled a lot of folks. So frivolous just like her mother was!";
			link.l1 = "You don't look like that type of women, miss McArthur...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "What? Ah, whatever, I am broken-hearted. What was I saying? Ah, yes, the letter. So, that letter was written by Jimmy Higgins. He is one of Jackman's men and he lives in Maroon Town. He visits our town quite often. Jackman is a pirate baron too, but mister Swanson doesn't like him, I don't know why.";
			link.l1 = "And Helen?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Oh she was laughing really loud. She had received a proposal from a captain of English corvette a day earlier and she rejected even him. And now this common boatswain from an old pirate's old tub... Not a chance, the daughter of Sean McArthur will get a more imposing husband!";
			link.l1 = "And what was the name of that English captain?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Oh, how do I know? Real gentlemen are rare guests here. I am sorry, I didn't mean to offend you. Ask that Higgins. He must remember his name. Jimmy was trying to duel with that captain for Helen. His pals barely managed to stop him from that. But both of them had left Blueweld few days before Helen sailed off.";
			link.l1 = "Well, thanks for your story. I will try to find your loss. If I learn something, I will tell you or mister Swanson. I hope to find your daughter alive and in one piece.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Are you going to look for her? God be with you, let Him guide you and fortify your hand! I will be praying for you! Tell me your name, honourable man?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". I hope to return back soon with good news, miss McArthur. Farewell!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "Have you got any new information about my poor daughter, "+pchar.name+"?";
			link.l1 = "I am sorry, miss McArthur, I have got nothing new to tell you so far but don't despair. I'll continue my search. The lack of bad news is also a good news itself.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "You were late, captain. A body of my poor daughter was found at the shores of Antigua. Lord, how they had been torturing her before her death! I have failed to preserve my beautiful girl...";
			link.l1 = "I am sorry. There was nothing I could do...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ah, young man, please, leave me alone with my grief...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "I don't even know how to thank you, captain, for saving my daughter. She has told me everything and I admire your braveness and honour. Here, take these golden doubloons. It is not much, but I offer them in all sincerity. And don't even think to refuse!";
			link.l1 = "Fine, Gladys, I won't. But I have saved your daughter not for coins and you know that.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Keep this money to yourself, Gladys. You need it more.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "I am glad that I was able to pay you somehow for your honourable deed. The doors of my home are always opened for you. Helen and I will be glad to see you any time.";
			link.l1 = "Thank you, miss McArthur. I will visit you and Helen when I have an opportunity.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ah, please... I just wanted to repay you as I could for your honourable deed. Know that the doors of my home are always opened for you. Helen and I will be glad to see you any time.";
			link.l1 = "Thank you, miss McArthur. I will visit you and Helen when I have an opportunity.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			dialog.text = "Ah, monsieur de Maure! I am always glad to see the saviour of my daughter in my house. Do you want to see Helen? She is upstairs in her room. After the loss of 'Rainbow' and her wonderful rescue she avoids going out. It's the first time I see her in such confusion...";
			link.l1 = "Thank you, miss McArthur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ah, monsieur de Maure! I am always glad to see the saviour of my daughter in my house. Do you want to see Helen?";
			link.l1 = "No. I want to ask you a few questions and I really hope on your candour. Helen's safety depends on this. Is this ring familiar to you?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Good Lord! This is... her father's ring!";
			link.l1 = "Mister McArthur's?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "No. Helen is our stepdaughter, but she doesn't know that, her parents died so I have decided to take her as my child. Sean adopted her, but even he didn't know that she is not my daughter.";
			link.l1 = "So who are her real parents?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "I know her father as a pirate Butcher of frigate 'Neptune'. I saw him only twice. And her mother was a beautiful young woman, red hair, dressed in men's clothes. That's pretty much all I can tell you about her, except that she was a bad mother\nI'd never leave such baby in the stranger's hands. Both of them died tragically. And the promised courier has shown himself twenty years later and turned out to be you. Did Butcher send you? Is he alive?";
			link.l1 = "Calm down, miss Gladys! There are no reasons to suspect that Butcher has revived, though you are the second who had such an idea. I have recently met a man who was supposed to show you this ring...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "";
			link.l1 = "A simple occasion has prevented him to do so in time and he was suffering all his life because of failing the last order from his captain. He died not long ago and... well, enough of sad news. Tell me, Gladys, didn't Helen's mother left any token to her child in the memory of her? Some little thing perhaps?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "She left me a strange piece of the old map. Joked that it was her legacy. What good can the piece of paper do? I believe it was only a bad joke. She was overexcited and a bit out of her mind. But I preserved this 'gift'\nWho knows... If you want, I can give it to you if you promise to tell me the whole story one day.";
			link.l1 = "Absolutely, miss McArthur. I will take this scrap for a while. I need to talk with mister Swanson.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "You help us again, monsieur de Maure! And I don't have any idea how to thank you. At least, take my husband's pistol. He was always being proud of it and told me that it is very rare. It has been just lying here for a long time. Let it serve you! Take it, take it!";
			link.l1 = "Thanks, Gladys. This pistol is really excellent. Thank you and farewell.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Let this pistol serve Helen. I have got enough of weaponry.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "But why do you keep refusing to accept my gifts? You make me upset...";
			link.l1 = "I think that I will make you happy now. I am going to return the gold which the courier was supposed to deliver you for the worthy keeping of captain's Butcher daughter. Sure, these doubloons won't repay all your love and loyalty, but they belong to you anyway. You can do with them whatever you want.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ah, captain! I don't know what to say... I couldn't imagine that such... honourable men even exist! Go to my daughter and tell her the good news!";
			link.l1 = "I am on my way, miss McArthur.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Helena_hire":
			dialog.text = "Are you serious? What do you mean?";
			link.l1 = "According to the ask of mister Swanson I am going to take Helen to my ship as an officer. She is in great danger. Helen will need a solid protection while Jan and me are dealing with this matter. I hope that I will be able to provide such a protection.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ah, that is so good! I wouldn't dare to ask you for this myself. It will be the very best protection for my girl. Helen will be so glad to sail again!";
			link.l1 = "Thank you for your compliment, miss McArthur. And now I have to see your... stepdaughter.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}