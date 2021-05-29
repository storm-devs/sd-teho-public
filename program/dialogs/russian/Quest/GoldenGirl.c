// диалоги персонажей по квесту Дороже золота
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
       case "First time":
			dialog.text = "What do you want?";
			link.l1 = "I should go...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "Captain Charles de Maure! At last! His Excellence Jaques Di Lu Parkes is demanding to see you! This is urgent!";
			link.l1 = "Why am I not surprised? Very well, please tell His Excellence that I am coming soon.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "My eyes must be deceiving me if it is Charles de Maure himself! I don't do such receptions very often and I am delighted that managed to find some time to spare for my humble cloister. Lucky me! This deserves a toast!";
			link.l1 = "My regards, madam. Forgive me for a possible disappointment of my manner - it's been a very long while since attended such… events last time. A ship's etiquette narrows to subordination, clean scarfs and a regular cup of refreshing coffee every morning.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "So charming, Captain, you still have your Paris gloss with you. I can see its shy glance under this seasoned and salted mask. Don't you worry, I am so glad to finally meet you that I can forgive you for many things. For now. We will see how it goes with us in the future. Red or white?";
			link.l1 = "A perfect moment for a rum joke, but alas, I am not in the mood, I am sorry. I'll gladly drink anything your pretty hands pour me.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "Nice one. But I insist. A taste for wine can tell a lot about a man and I intend to learn everything about you tonight. So I ask again: red or wine?";
			link.l1 = "Have it your way. I can see that you are drinking red. Same for me - I'd like to learn something about you too.";
			link.l1.go = "Julianna_3";
			link.l2 = "In this case, I'll have white but you choose. This should work in both ways, don't you agree?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "Splendid, so it's my turn now? This one is Burgundy Pinot Noir, winemakers call it 'a naughty girl'. It is not an easy variety to handle and it's aftertaste can be quite deceiving as well. Satisfied?";
			link.l1 = "Pinot Noir, huh? Works for me. Unreliable and mysterious, a bleak taste at first but let it breath for a while and you'd be surprised. A light dance of shades and tastes, a choice of an experienced connoisseur. First impressions lie, right? I drink to your eyes, madam!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "Splendid, so it's my turn now? I have wonderful Sauvignon Blanc, right from Loire valley. Pretty wild, you can almost feel how it pops on your tongue. And a cherry on a top - a note of gunpowder. I suppose you share something in common.";
			link.l1 = "I expected better, maybe something like Riesling. Well, let's have this simple brute smelling like summer and gun powder. Ever heard that some folk mistakes it for pipi de chat? I'll drink to your smile, as bright as these sapphires!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "Remarkable, Charles! Can I call you like that? I wasn't wrong about you, in different day you'd be the star of my night. But alas, my Captain, today you have strong competition. It appears that we are on a verge of a scandal over there, do you see?";
			link.l1 = "I am hearing angry voices. Who is this unpleasant monsieur and what did he do to displease our dearest governor?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "This 'unpleasant' monsieur is Angerran de Chievous, an unrecognized bastard of Count de Levi Vantadur. You are entertaining their topic of argument. De Chievous has been trying to earn my good favor for years, and he followed me here, thinking that he can replace his father for me. Even though he is not a lawful son, he is rich and powerful. Stubbornness is another of his traits, for some people it replaces wisdom. Just before your arrival he and Jaques started arguing about the obvious subject. His Excellence always protects me in a very touching way, you should see! Come on, let's observe and see how it ends this time.";
			link.l1 = "I smell trouble in the air. Why there is always a catch, even in such a wonderful night?!";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "Beg your pardon, Charles?";
			link.l1 = "Forget it. Please introduce me to your pushy friend, then we'll see...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "Monsieur, allow me introduce to you my dear guest - Captain Charles de Maure, in flesh, has honored us with his visit! Such famous figures are not often guests here.";
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "Charles, I don't like where this is going! Jaques is deaf to my arguments while Angerran is surely up to something. This fighting had a purpose and I need you help!";
			link.l1 = "I don't follow you I am afraid. What can I possibly do here? He refused to duel me already...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "Captain, please don't disappoint me. Just a moment ago you were a virtuoso of conversations and now your world is split between things you can poke with a sword and things you can't. Think out of the box! Let's spoil Angerran's play. He want to challenge poor Jaques on his own, but that's just dull! Let's run a tournament! Several gentlemen here can support serious stakes and your luck is already known as legendary! Perhaps cards will favor it tonight?";
			link.l1 = "I don't quite see how it will prevent de Chievous from fighting our sweet governor but I am in, milady. Anything to discard that little smile of his.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "Splendid, no go to the table and have something to eat, it will be a long night. Once you are ready, see me in the hall, we will need more room for this. In the meantime, I will throw a show, persuading others to give me spectacles and games of high stakes. I might even shout at them to make these cocks notice a lady drowning in boredom. Please do not interfere, no one must know we are in the same team tonight. See you later, my Captain!";
			link.l1 = "Whatever you say, m'lady, whatever you say...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "Well, congratulate me, it worked! A bit of pride, some prejudice and voila! Make a bored face, they are watching us. Let them think you are interested in drinking, not in me\nA tournament is about to begin, stakes are high, no second chances and rematches. Somehow I know you are used to this. You will handle this. Remember, Angerran is definitely up to something, he will make a move against our friend Jaques, but he didn't consider your arrival. Be my ace in a hand, because seeing his confident smug face is never a good sign. We have eight players but I made sure you won't face him until the finale\nOh! Your first opponent! Colonel and our fort's Commandant. Sea versus land - a worthy challenge for guests with military experience! Applause!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "You did great, Charles, just splendid. Angerran and Jaques are about to face each other just in a moment. Shame they didn't listen and postpone the tourney for a week. I could gather a truly stellar party gossips of which would travel to Paris! Well, next time perhaps. It appears that your next opponent is a worthy competitor to your luck, a true sea wolf, Captain Moreno! Captains, please!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Alas, your luck failed you, Captain. I am sorry, but the game is over for you. Angerran is already playing against Jaques, so I should go. Farewell.";
				link.l1 = "It was a pleasure... madam.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "I congratulate you on your well deserved victory, Captain! It's still unclear who will face you in our finale… Let's step aside a bit. Lower your voice and observe that table. Look, there he goes! I am starting to see what Angerran is up to! He already stripped sweet Jaques of cash but not letting him leave the table. When I passed by, the poor sod gambled on some documents over a whole ship with cargo. Sadly, luck is not on his side tonight. Or someone told her to.";
				link.l1 = "Think de Chievous is cheating?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "Alas, your luck failed you, Captain. I am sorry, but the game is over for you. Angerran is already playing against Jaques, so I should go. Farewell.";
				link.l1 = "It was a pleasure... madam.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "He definitely could if he wanted but I have no proof. Our dear governor is good with cards, but so is his opponent. Angerran didn't even blink when he gambled on his frigate, imagine that. If we had this duel in Paris or in Lion, it would become a legend, Charles! Nevertheless, he might be just lucky tonight. Let's approach them and see for ourselves.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "Charles, hold me or I will fall... Or I won't - these idiots will not even notice me feinting. Did you see this? Jaques, damn your stupidity! Like a child, Jesus An imbecile child!";
			link.l1 = "Marquise, I don't think I follow you.  What's going on over that table now? What are they gambling on?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "On me, Charles. Our sweet, stupid Jaques gambled on me. Angerran found his only soft spot and hit it in the right moment.";
			link.l1 = "Blast! But I am the next in the tourney, I could gamble back his bloody ship!  Why?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "Because Angerran had put a great thought in it and planned everything through. Listen to me, we have not much time. You have to do the same to him. Strip him of everything, take all his cash, all his ships, provoke him! Make him lose his head on reputation, honor, passion, on anything! You've seen how it is done tonight. Corner him and force him to make a stake\nI am begging you, Charles! I am ready for anything, but I am not going to him. Not like this! Even Count Vantadur will not stand against an honest card winning, he won't even lift his finger to help me out. See, cards are fucking sacred for noble people, damn them! You are my last and only hope, Charles!";
			link.l1 = "Don't bury our governor just yet, madam. Maybe he will win his ship back? Luck is a fickle... woman.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "You still don't get it, do you? Luck has no place at that table! Angerran de Chievous calls all shots. He discovered a way to both have me and keep his father away from this. I have now idea long has he been planning it, but he has almost won by now. He is owning the game and we have only one chance to break it. Here, take this! I am going to feint, will give a minute or two. Use it wisely.";
			link.l1 = "Marquise... Somebody, please help! Madam is not feeling well! Quick!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "No, no I fine… It's a bit stuffy here... I am so sorry, gentlemen. I will leave you for some fresh air for a moment. You can go on without me.";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "Not at this moment and not in St. Pierre but I know someone. I promise you, Angerran, this will be a worthy painting...";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "Angerran, you are impossible! Learn how to lose! This is just a game and you can predict everything. Finish your wine and get dressed - the rules remain - a defeated leaves our comfy party.";
			link.l1 = "Marquise, wait...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "This is going too far, gentlemen! Stop it at once! We all are very tired after the exhausting night and I am afraid I have to ask my guests to say goodbye. You can continue your argument tomorrow as it befits to men of honor unless you change your minds. But no one is touching arms here, is that clear?";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "Charles, I am afraid I will have to ask you to take your leave as well. Go upstairs and take a room for yourself. I will arrange everything. I am grateful for everything you've done for me beyond any measure but I need some time for myself and your dreadfully tired.";
			link.l1 = "It's not too bad, madam, but I won't say no to a bed. This casual party had me harder than a squadron naval combat. I understand that all this wasn't easy for you either, marquise. Get some rest and don't you worry, you owe me nothing. All I need right now is a sleep.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "I'll make sure they will wake you by midday. It's dawn already, so I can't wish you good night any more. Sleep well.";
			link.l1 = "You too, marquise.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "There you are, Charles. To be honest, I didn't sleep at all, but you look well rested. How was your sleep? Breakfast is on the way.";
			link.l1 = "Your hospitality is legendary, madam, but I am afraid I have no time to enjoy it. His Excellency, de Chievous' seconds, ships I won - all this is waiting for me.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "You won not only the ships. This is another thing I wanted to ask you about, Charles...";
			link.l1 = "I am neither Jaques nor Angerran, marquise. I don't gamble over women to gain their favor. You owe me nothing.";
			link.l1.go = "Julianna_41";
			link.l2 = "You are under my protection, marquise. Neither Jaques, nor Angerran will ever trouble you, I can promise you that.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "You are either fabulously honorable or in love, Charles. And not with me. But again, I am eternally grateful to you with all my heart. If I can be of any help for you - just tell me.";
			link.l1 = "Julianne, time is running and I am facing the most uneasy task ahead. De Chievous is a scum and even an honest duel can quickly end up like the one we observed last night. Let's talk later when all this is done for good. I thank you for a chance to sleep in silence and I am looking forward to see again.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "I am grateful to you with all my heart, Charles… Trust me, being your prize is a sort of victory for me as well. Say you and I should continue this conversation in the more… private environment?";
			link.l1 = "Julianne, time is running and I am facing the most uneasy task ahead. De Chievous is a scum and even an honest duel can quickly end up like the one we observed last night. Let's talk later when all this is done for good. I thank you for a chance to sleep in silence and I am looking forward to see again.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "I won't delay you any longer then, my Captain. Remember though, Angerran is dangerous. I can't judge his combat capabilities but he took part in several wars and fought in Rocroi. I also hear about a couple of duels he won. Most of all, he is a deceitful type as you noticed yourself. I beg you to be careful and please see me afterwards!";
			link.l1 = "Care amazingly suits you, marquise. Believe me, de Chievous is not the first bastard standing in my way. I will manage. Now I really should go to see His Excellence and discuss the dueling business.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "Godspeed, my Captain! And tell Jaques to keep himself as far away as possible from the doors of my home.";
			link.l1 = "Word. See you, marquise!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "Captain, you made it, what a relief! How did it go? Are you bleeding?!";
			link.l1 = "It's not my blood... at least not all of it. Marquise, where is de Chievous?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "I was going to ask you the very same thing - you didn't put him down? What happened? Why am I seeing a half of town's guards outside?";
			link.l1 = "I told the governor that you might be in danger. De Chievous got wounded and run away, unleashed his thugs on us. It was a massacre. Although, stories like this are not for your beautiful ears. It's over. You are free from him and from our 'sweet' Jaques.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "This is so bad, Charles. Enemies like Angerran de Chievous should be killed for good when you have a chance. I know the man for many years - he is not a forgiving type. Sooner or later, he will find his way to revenge. But I don’t like how you are slouching, was your wound taken of?";
			link.l1 = "Just a scratch, it's been much worse. Hurts a bit, that's it. Thank you for caring about me, madam, but I should go...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "Captain, you gambled for me, risking your ships and wealth, you fought for me in a deal, risking your life and career. The least thing I could do for you is take care of your wounds and give you a place to rest safely. No! I don't want to hear any more of this. Take my hand and follow me upstairs. Your room is waiting for you.";
			link.l1 = "I am taking your offer, madam, thank you. But I'd rather not put any weight on you. I'll make it to upstairs myself.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "Marquise, you are my guardian angel. I am afraid, it's me who owes you now.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "Charles, you are an example of chivalry! I swear to God, if you keep being like that, I will loose my head! Alright, my knight, I'll send Denise to you, she will take of your wounds as any proper physician would.";
			link.l1 = "Thank you, marquise. If my heart wasn't already occupied, I'd gladly play along. But alas! Good night!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "In this case, I demand you indulge me right away. Hold my hand and do what I say. Denise! Bring lint, hot wine and something to eat upstairs! Let's go, my Captain. And remember - no arguing this time!";
			link.l1 = "As you say, marquise, I am all yours.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithJulianna"); // найти нужные локаторы
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Good morning, Charles. How are those 'scratches' of yours?";
				link.l1 = "Thanks to your efforts I feel reborn. Please accept my sincere gratitude, Julianna.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "Good morning, my hero. How are those 'scratches' of yours?";
				link.l1 = "Thank you for your concern, madam, I am totally fine. I'd pay a fortune to get your Denise to serve as my ship's physician. She is a miracle!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "I fear, it won't be easy to arrange. But I'd never dare to wake you without a serious reason. Believe me, I guarded your sleep fearlessly, but this man below is very persistent. He says he is one of your crew and this is urgent.";
			link.l1 = "My crew? You did the right thing waking me, marquise! I'll be on my way immediately.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "In the different circumstance I would, my captain, but we will have to postpone. You are expected by an extremely uneducated monsieur downstairs. He says he is one of your crew and this is urgent.";
			link.l1 = "We will get back to it, Madame, when I am back. I hope this is not about Spanish laying siege again.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "Charles, you are back! What news did your man bring? You didn't even say goodbye!";
			link.l1 = "I apologize, marquise. De Chievous played dirty again. He stole my ship and set sail this night. One of my trusted officers had been on that ship and I can't leave her in the hands of that bastard.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "Her? You have a female officer stationed on your ship? This goes against everything I know about seamanship. What makes you think she still lives?";
			link.l1 = "I hope. Julianna, hope is all I have got so far. I must learn more about Angerran de Chievous. I absolutely must find out where did he go! I must bring her back!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "Now I see! You are indeed in love, my knight! I would gladly give a half of my life for such loyalty and attachment without a second though!";
			link.l1 = "I didn't take any vows, but this woman means a great deal to me, marquise.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "This jealously touching. Hear this, Charles, I am ready to go jealous over you! But what courtesan can stay deaf to the voice of true love? Besides, you saved me, my knight, of course I will help you. Ask away.";
			link.l1 = "Thank you. You have been knowing de Chievous for quite some time. Where could he go after all that fuss in order to wait out his father's wrath?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "What if I can seduce you with a brunch? You didn't think of this… girl for two days, perhaps she can wait for one day more?";
			link.l1 = "Marquise, I realize how I might look in your eyes, but what's done is done. Even though I didn't take any vows, my heart belongs to her. I beg you to understand me and help me.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "Come on, Charles! Defending yourself with a talk of love before a courtesan? I haven't laughed like that in a long time! You are so incredible! Relax, what happened in this house, stays in this house. I remember what I owe you. Ask away.";
			link.l1 = "Thank you. You have been knowing de Chievous for quite some time. Where could he go after all that fuss in order to wait out his father's wrath?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "Truth to be told, even though inviting Angerran de Chievous might not be the most pleasant thing to do, it is still very politically useful. His is a welcome guest anywhere, including nations allied with France. But I know only on one man nearby who will always lend him a hand and a sanctuary. Francois de Lyon, the governor of our Guadeloupe colony. He is an old associate of the count de Levi Vantadur and always had a soft spot for this bastard.";
			link.l1 = "Guadeloupe it is! It is the best lead I could dare to hope for! If we set sail this evening, we will be only a day behind them.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "Wait, Charles, there is something else. I received a letter for you just recently. I assumed it had something to do with the duel, but I am not sure anymore. Here it is.";
			link.l1 = "No seal, but the paper is expensive. I don't like this...";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Come on, Charles! Don't keep me in suspense, is it from him?";
			link.l1 = "Yes, it is from him. She is alive! He captured her during while stealing my ship. Now he suggests we meet and talk this through in a civilized environment. Just as you have said, Guadeloupe, Basse-Terre.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "Monseniour de Lyons will definitely choose the son of Leve Vantadur over you. De Chievous might set up a trap for you again! You've made a very powerful enemy by defending me, Charles. I wish I could help you, but I fear that all I can do is to ask you to be careful.";
			link.l1 = "Julianne, I would had never make in the New World if always chose direct approach. Shady business is not my strongest field, but I will find a way.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "Any news, captain?";
			link.l1 = "Alas, nothing...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "Welcome back, Charles! I am glad you are alive and kicking. What news?";
			link.l1 = "Everything we knew about de Chievous's capabilities turned out to be a gravely understatement. The bastard is holding my… officer captive and I have two weeks to collect the ransom. I fear that it can't happen without your help.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, your love is quite a windflower, yet I owe you a great deal and will help you as best I can. How can I be of service to you?";
			}
			else
			{
				dialog.text = "Charles, I already told that I will never forget what you did for me. I will do what I can to repay you. I am ready, yet I don't quite understand how can I be any use for you at this?";
			}
			link.l1 = "Please sit, Julianna. See, Angerran's ransom is you. And I don't mean an official patronage, I mean like a tied captive in his cargo hold.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "I am speechless... But your face tells me that is not a joke. Did he lose his mind?";
			link.l1 = "More like, he believes that I did. He is desperate enough to cross all possible lines.";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "And what, you are asking me not to scream during my abduction? Captain, don't you think this is a bit too much ask? I owe you a great deal, but saving someone else's love by giving my own life to the hands of inglorious bastard … You are the chivalry here while I am an extremely realistic and materialistic woman.";
			link.l1 = "I am afraid, madam, that is exactly what I am asking of you. Pack your things, we are leaving. I am deeply sorry for this but time is short.";
			link.l1.go = "Julianna_76";
			link.l2 = "Marquise, I don't kidnap women who put their trust in me. And this might be our chance.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "You are full of surprises, Charles. Heard that? That was all the grace I had for you just shattered. Love or not, I will not allow you to kidnap me. Guards! Help!!! Anyone!!!!";
			link.l1 = "And here I thought we were friends.";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "This is an outrage! What did you turn my lounge into?! What sort of demonic horror is this? Charles, come back to your senses! You are a nobleman, not a damned pirate!!";
			link.l1 = "I've already made apologies to you. I asked you not to complicate things further - you didn't listen. Believe me, I don't like what I am doing, but I have no choice. I will do whatever it takes for that woman's sake.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "What kind of dame would choose such a chevalier as yourself? I will go myself, keep your hands away of me! You are not stealing a cow, so show some dignity!";
			link.l1 = "Fine. Come with me, madam. Stay behind my back and keep your head down - perhaps they will start shooting.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "For a moment I thought that I don't know you at all, Charles. That look… But what are you about to do then? What chance did you mention?";
			link.l1 = "Why the bastard uses me to get to you? Why did he orchestrated that card game instead of just taking what he wanted? What is he afraid of?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "Nothing. Alas, but the reasons behind all that are dull primitive. Count Henri still has a soft spot for me. Angerran would risk a great deal if he did anything to me against my will. I am sorry Charles, but it's a dead end. He will deny everything and will get away with it. No one will believe the words of you, the abductor, while his father will destroy you.";
			link.l1 = "Damn it! I wish it didn't come to this... Get ready, marquise, we must go. And yes, I ask you to keep quite.";
			link.l1.go = "Julianna_76";
			link.l2 = "But the bastard must have other weaknesses besides his father, right? He is not perfect, quite the opposite more like!";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "I don't know if this will be useful for… us. Angerran had some dealings with the local pirate baron. Jaques Baraban?";
			link.l1 = "It's Barbason, madam. Nice couple, both of them! But Jaques the Kind has no love for me and I can't launch an assault on Le Francois without a solid certainty.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "You are being too straight forward again, my knight. Remember captain Moreno? Your second gambling adversary? I bet he came here because of Angerran. He must know something of value to us.";
				link.l1 = "Captain Moreno, huh Yes, of course. Is he still here in town? Where can I find him?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "You are being too straight forward again, my knight. Someone always knows something and not everyone can keep their mouth shut in certain situations. My… pupils hear things, in this house. Give me a day and I will learn more or I will find you someone who will.";
				link.l1 = "Marquise, I thought that being concerned suits you, but you being in anger suits you even more. Thank you, you are installing a hope in me!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "Yes, he is still here and I will spare you of running around searching him. Come here tomorrow evening - captain Moreno will be waiting for you here, in this room. I wish I could do more than that, but  I can't, Charles.";
			link.l1 = "It is already more than nothing, marquise. Thank you. See you tomorrow evening.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "I wish I heard that from you in a different situation, Charles. Come see me tomorrow evening. I hope I will get what you need.";
			link.l1 = "Thank you again, Julianna! Tomorrow evening then.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "Here you are, my friend! Captain Moreno is already waiting for you.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "Charles, I think I found something. Remember captain Moreno? The one who played against you that ill night?";
				link.l1 = "I do, what a vagabond. What about him?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "I always knew that, Bartolomeo de la Cueva. This is why you got to my party in the first place. It was like adding jalapenos to one's dinner. I know that you and your boys have been poking around this island for a couple of weeks already. I know this must be somehow connected to the pirate baron of Le Francois and Angerran de Chievous. Tell my friend all about and we will keep your legend in return. Otherwise I will call the guards who are already standing behind the doors. I called for them upon you arrival.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "Not just them! Angerran presented me with a necklace, a beautiful one! Large and clean pearls including this one, dark as southern night, in the middle. But he ordered it from the local jewelers!";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "I bet he did not do it just to please me with a luxury gift. Although, that gift was his last resort to get my favor within the boundaries of decency. Angerran has no titles and land, even his frigate remains his only until his father decides otherwise. He makes a use of power and influence but he has no source of income of his own. Perhaps he got tired of waiting for fathers donations and decided to fix his financial state?";
			link.l1 = "Wait, madam! The card game! If we are right, and de Chievous planned the whole thing ahead, he must had needed a lot of money for stakes in order to corner our governor hard enough. Asking a parent for such money could bring his unwanted attention to the matter. Stealing already stolen treasures from privateers seems like a quite and safe way to obtain the needed coin. Nobody would know!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "To us, Charles! Angerran must not get away with this this time. His position over me has gone too far and I would like to help you see to that.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "A loser pirate and an almost enamored courtesan. Charles, you got a dream team for yourself!";
			link.l1 = "Nevertheless, thank you, both of you. Sincerely! Now I need to think this through for a bit and to conduct a plan.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "This house has anything its guests desire. I'll make the arrangements. Join us when you are ready, Charles.";
			link.l1 = "Very well, madam.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "Nothing, but someone in the town is searching for him. They are actively inquiring about you and other guests of that night. I don't know what is going on just yet, but I am sure you stepped into something bigger than you think. ";
			link.l1 = "Something bigger? What's your meaning, Julianne?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "Angerran... I mean Monseniour de Chievous gave me a marvelous pearl necklace as a gift. One of the pearls was black as night. I thought it was just a fake with a nice story behind it. I never wore it, didn't want to give false hopes, but it is so mesmerizingly beautiful.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "What will you do, Charles? Do you have any clue what's going on?";
			link.l1 = "Not yet, I will. De Chievous is neck deep in something serious and this is my chance. His homeland won't dare to touch him but British authorities just might. I'd rather not abduct you, Julianne.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "That's so very sweet of you, Charles, but not very funny.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "Charles, did you learn anything? You look nervous... What's wrong?";
			link.l1 = "Damn it! I wish things were different… Pack your stuff, we should go, Marquise. Please don't make any troubles.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "Charles, come in. Baronet is already here and we had a pleasant chat. I was just telling him about your interest in the ongoing events.";
			link.l1 = "Julianne, I am not so sure it was wise...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "Baronet, it appears that you men just dropped something behind the door! Would you kindly tell them to behave better?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "Horrible! What do we do now?!";
			link.l1 = "Damn it! I wish things were different... Pack your stuff, we should go, Marquise. Please don't make any troubles.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "God almighty! What did you do with my living room, gentlemen?! This is looking like a medieval nightmare! Who are these people? And where are the guards?";
			link.l1 = "You alright, Julianne? Good. I bet that the guards are spending their well earned bribe in a tavern. Baronet, my congratulations are in order - you've managed to piss Goodman Jack real bad. Such messy and ill-prepared assassination attempt is not his style at all.";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "I apologize for interrupting you exciting discussion but unless some of you is wounded let's move to a cabinet. A sight like this is not very comforting for a lady… Only the ceiling is bloodless!";
			link.l1 = "Then go upstairs, marquise. You really should lie down for a bit and away from all the blood. Baronet Cortney and I will talk this through. Shall we continue?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, are you ready to share your plan with us?";
			link.l1 = "Almost. Tell me, is de Chievous a pedantic type? Does he keep his books and logs in order?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "Angerran is an embodiment of lingering when it comes to finances! He signs more paper than any banker I know. I guess he's been like that since his childhood when he didn't know who he his father was and lived in poverty in the streets.";
			link.l1 = "Splendid! Now, we need his log and his books! They will do as a viable proof for brits. We must find out how to get them! I wish I knew about this when I had his ship in my possession... sigh.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "Wait, Charles, do you really think that after all what happened I will allow to sell myself to de Chievous like some farm goat?";
			link.l1 = "Don't you worry, Julianne, it will take just a few day. I promise that they will treat you like a priceless vase from China. Correct me if I am wrong, but de Chievous will never show himself to the exchange?";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "I am sure of it. Angerran will be waiting under the wing of Francois de Lyons and will never dare to meet you in the open sea. But about this capture of mine...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, I am sorry to interrupt, but didn't you forget to ask my opinion about all of this? Weeks inside those squeaky coffins… Do you even realize what you asking me for?! Obviously you are attached to that... girl, but I am not one of your crewmen! I am sorry but all this doesn't sound like a serious love story.";
				link.l1 = "I am afraid, marquise, I will have to insist. I can not afford to lose her.";
				link.l1.go = "Julianna_127";
				link.l2 = "We all make mistakes, Julianna. You of all people should know that. I am asking you to help me.";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "Charles, I am sorry to interrupt, but didn't you forget to ask my opinion about all of this? Weeks inside those squeaky coffins Do you even realize what you asking me for?! Your feelings are worthy of classical literature about chivalry but I am just a common courtesan. I admire you and I want to help you, but everything has a limit!";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "I understand, Charles. I want to believe in perfect true love, but I guess there is no such thing in this world.";
				link.l1 = "Thank you, marquise. I must make everything right this time. I learnt a lot from this story, and I pray that I won't pay a too terrible price for what I have done.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "You've made your mind, I supported you all the way, but enough is enough. To sacrifice everything for the sake of love you had already abandoned in my bedroom. All of this is very touching, Charles, but I am not that young and naive.";
				link.l1 = "I am afraid, marquise, I will have to insist. I can not afford to lose her.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "Well, Captain, do what you want. I won't resist you but be aware that I am doing it against my will.";
			link.l1 = "Think of me what you want, Julianna, I've earned it. But I will get her back no matter the cost.";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "Julianna, listen, I know what I am asking you of. To leave everything behind and to let others to drag you into a questionable gamble. But at this moment you are my only hope! I need your assistance in this and I will remain in your debt until I die!";
			link.l1 = "Very well, Captain. In the end, Angerran must be put down for good. I will help you out but tell me how are going to rescue me from his ship?";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "Wait. You can take my necklace pearl, the English are hunting for black pearl right? This one will make them listen to you. What's next?";
			link.l1 = "Next I will take the investigator aboard and we will sail to Guadeloupe. We will run an official search on de Chievous frigate when she will return with you aboard. The Mercury business was a serious incident involving our ally, thus De Lyon will have to allow it!";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "He will tell everyone that it was his men who saved me from captivity. And be aware, Captain, I haven't yet to decide what I will tell them.";
				link.l1 = "Telling nothing would be just fine, marquise. Believe me, I will drag you out and make Angerran pay for everything.";
			}
			else
			{
				dialog.text = "I will them that I was abducted by strangers, right from my house, to be put aboard Angerran's ship. It will appear as he like he paid mercenaries to kidnap me.";
				link.l1 = "Another nail to Angerran's coffin, marquise.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Give me time until morning unless you want to carry me in a sack. Send a couple of men to assist me too - a woman of statue can't travel without any commodities. Charles, you save me and I will help you out, also please take this priceless black pearl, my gift to you. If this works out, we are even.";
				link.l1 = "As you say, marquise. Godspeed, both of you! See you here again once it's over.";
			}
			else
			{
				dialog.text = "I will be good to go by sunrise.  I am not going to rattle around in a cargo hall, so make sure to prepare a decent room, or whatever you call it, for me. Charles, here, take this. This is precious black pearl. I realize that it costs more than this place, but some things cant be measured in gold. I hope it will be of any use for you. God help you!";
				link.l1 = "Godspeed, both of you! See you here again once it's over.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			// черная жемчужина - установить картинку
			sld = ItemsFromID("Reserve_item_02");
			sld.picTexture = "ITEMS_40";
			sld.picIndex = 3;
			sld.Weight = 0.2;
			sld.price = 20000;
			sld.name = "itmname_blackpearl";
			ChangeItemDescribe("Reserve_item_02", "itmdescr_blackpearl");
			GiveItem2Character(pchar, "Reserve_item_02");
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Congratulations, Captain. Your plan succeeded. What a massive scandal you've orchestrated! English took Angerran and his ship with all its contents excluding me.";
				link.l1 = "Sir William didn't even come to say goodbye. He promised to apologize.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "Charles, we did it! They will release you at any moment! We must leave the island as quickly as possible though. The governor is very upset by Angerran's recent arrest.";
				link.l1 = "I am glad to see you, Julianne. How are you? How did the exchange go? Is she alright?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "I assume he had been too busy for that. Like our governor right now. You better leave the town before he recalls your existence. He did love Henri's son, but the British papers cornered him completely. I wouldn't wait for him to decide to unleash all his frustration upon you.";
			link.l1 = "Fair enough. Plus, she is waiting for me in Martinique. How did the exchange go? Is she alright?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "Forgive me, but I don’t want to talk about it. Ask her instead. Farewell, Captain. I will return on my own. I need to take a rest from the sea - Francois is a quite nice host when he is not being bothered by boring British officials.";
			link.l1 = "I am sincerely sorry about all this, Madame. Thank you for your cooperation anyway. I am pleased to hear that you've made a new... friend.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "Thank you too, Charles, for keeping your word. Find Bartholomew in my house in St. Pierre. Farewell. We will see each other again.";
			link.l1 = "Farewell, Julianne. Godspeed.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "I haven't seen her, but Bartholomew took her alive and healthy. That Englishman arrested de Chievous and his property right under a nose of the local governor - he didn't even say a word! Miraculous!";
			link.l1 = "You know, it went surprisingly smoothly, considering the background behind this arrest. Although, it is still ought to backfire later. Whatever! I must go to Martinique at once, I must see her as soon as possible!";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "No doubt you two have a lot to say to each other. Oh, Charles, I wish I had a man with such fire in his eyes beside me. Let us hurry, I really miss hot bath and clean sheets. Bartholomew will be waiting us in my house in St. Pierre.";
			link.l1 = "Yeah, the romance of sea voyages is overrated. You shall have my cabin, marquise, it is the least I can do. Come on.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "You have already done for me everything you possibly could, Charles. You've made a cynical woman to believe again.";
			link.l1 = "Me too, Julianne. Me too.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, I am so pleased you've come! How is that dame of yours? Is she alright?";
				link.l1 = "All is well, thanks to you, Julianne. I wanted to say it to you again.  You are a marvelous woman and I will be forever in your debt for all your courage and ingenuity.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "Charles, I am so pleased you've come! How is that dame of yours? Is she alright?";
				link.l1 = "All is well, thanks to you, Julianne. I wanted to say it to you again.  You are a marvelous woman and I will be forever in your debt for all your courage and ingenuity.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "Maybe it is I who is in your debt. After all you saved me from two extremely pesky patrons. I think I still owe you. Ask for anything, Charles.";
			link.l1 = "In that case I do have a little favor to ask, my lady. You can do something to make us even.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "I am all ears, my Captain. What is it?";
			link.l1 = "People make mistakes, but it doesn't make the world bad. Remember that and be happy, Julianne. You deserve to be happy.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "I... I will try, Charles. Thank you. Will you come to visit me from time to time… as a friend? You will always be welcome at my place!";
			link.l1 = "Appreciate it, marquise. Farewell and remember what you promised to me.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "Yet apparently not marvelous enough… but I am happy that it ended well for you.  You owe me nothing, after what you did I can't thank you enough too! Come see me whenever you are ashore. You will always be welcome at my place, as a friend!";
			link.l1 = "Thank you, marquise. I wish all the best. Farewell!";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "Charles, my friend, you are so rude - visiting me so rarely! I missed you, you know that? Fancy some wine? I am dying to listen exciting stories firsthand! And to try out your famous fortune!";
			link.l1 = "Marquise, I just wanted to say hi and to make sure you are alright.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак дил ду Парке
		case "governor":
			dialog.text = "And there you are, my friend! Glad to meet you!";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "Well, the way you treat my friend leaves me no choice, monsieur. I accept your challenge. Time and place?";
			link.l1 = "Here and now. Call servants, tell them to bring candles, a cozy twilight like this won't do. This place must be bright as day!";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "My friend, please, don't take this too personal. Angerran is a nasty piece of work, that's true, but you shouldn't snipe at him. Leave this to me.";
			link.l1 = "You sure, your Excellency? He is as drunk as my quartermaster after a week on the shore, but he surely knows how to handle his sword. I can tell such thing at once.";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "God forbid, Charles! I am not dueling him. We will gamble, cards are arms of civilized men. I will do him dry and send him to you begging for a loan for a safe return to Quebec.";
			link.l1 = "That's a solid plan alright. But if you ask me, I'd prefer the bastard dead, not poor. Godspeed, Your Excellence!";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "Damn it, Angerran, no way it could be a ten there! No way!";
			link.l1 = "Was that an accusation? It was your deal, monsieur.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "It wasn't. I am just... a bit overexcited and I apologize. It was an accident and I demand a chance for a rematch! This ship, I… must get it back! Or screw the game, just tell me for how much are willing to sell her to me? Name the price and I'll see it paid tomorrow before noon!";
			link.l1 = "Alas, but I believe with all my heart that one can't buy back the spoils of gamble. You can only win them back. The flute is mine now and I have no intention of selling it. I am sorry that your passion put you in such position, sometimes we should be more realistic about our capabilities... Perhaps you've got more ship papers?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "You are a scum, Angerran and you have me cornered. I believe I can give a stake you will accept.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "Charles, you are my only hope, I beg you to help me! That flute and her... cargo has already been sold to the Dutch Company. I must pass all the documents to them tomorrow. I thought I'd stay here for the whole night, so I brought them with me. I will face a disastrous situation if the deal is off!";
			link.l1 = "But 'sweet Jaques', don't you agree that the woman you favored is facing even more disastrous situation now? I had my share of gambling and I understand something like gambling over a ship, even if she is not your own. But gambling over a dame?! You've surprised me, truly! And now all you care about is a fate of your deal?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "Don't judge me, Charles. Favoring an ex lover of a powerful count and even falling in love just for a bit is nothing compared to owing one million pesos to Peter Stuyvesant. How do I explain this to his agent? Imagine all the reputation damage!";
			link.l1 = "I had a similar debt before and I did alright. So will you. See you around, Jaques. No promises and I won't even ask what is the cargo worth of one million you keep in the flute.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "There you are, Charles. I was about to send for you. De Chievous is insisting on a duel and already rejecting any chances for reconciliation. You did well with cards but are you sure you want to keep doing this?";
			link.l1 = "I have an itchy suspicion, Your Excellency, that you wanted this outcome all long. So I say yes. This must be solved for good. What about the terms of the duel?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "You are too all in your head, my friend. Some parts of our world still don't revolve around you. Believe me, I am deeply disappointed of how everything went last night. Very deeply. But first, let's discuss the fate of your... winning.";
			link.l1 = "Fine. Do you want to know how to return your flute or how Madame Julianne is doing?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "I can see you've changed your inappropriate irony for spite? Charles, we are on the same side of things, don't forget that.";
			link.l1 = "Disputable argument, Your Excellency. To put it lightly. Now where do we start: the ship or the dame?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "The Stuyvesant deal of course - his agent has been waiting for me all morning and I am running out of excuses. I need the flute papers, Charles.";
			link.l1 = "Fine. She is yours. I don't believe de Chievous played honestly, therefore you can have your property back for a half of its price. 150 000.";
			link.l1.go = "governor_18";
			link.l2 = "I'd be glad to oblige. What was the cost of the vessel you said? 500 000? Works for me.";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Now, it will be four hundreds and sixty thousands pesos including taxes. Deal. 135 000.";
			link.l1 = "I don't even want to add a toxic comment here. Pay up, get your documents and be done with it.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "You don't take a pity on old friends, right Charles? Now, with all taxes included...";
			link.l1 = "Card debts and friendship have nothing in common, Your Excellency. You will pay taxes yourself as a buyer or I sell the ship in Le Francois. Mind you, I am not taking advantage of your position... yet.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "Fine, so be it. Now, the duel. I don't need troubles with count de Levi Vantadur, therefore everything must go as legally right as possible. Did you hear me, Charles? According to the law! I will send two officers of my garrison to accompany you - both of them are noble and respected men. They will be your seconds instead of your regular... companions. I want everything to be crystal clear until the business is done!";
			link.l1 = "How nice of you. And what if our good friend will decide to play dirty? I prefer to trust my back to people who knows how to do it, rather than to people who were born in right families.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "Charles, stop behaving yourself like this duel is between you and I. This is a serious business. De Chievous is not a man who you kill and just get away with it. Any outcome will be followed by investigations, even by a court perhaps. We will need trustworthy witnesses. See, I am taking care of you! The most important thing though is that you can not kill him\nI understand, Angerran is determined and most likely he is decent fighter but, Charles, you can not kill him! Wound him, humiliate him even, but stop right there. If you kill him - there will consequences both of us will not be able to either dodge or survive. Even though count de Levi Vantadur never officially recognized his bastard, he has no other sons. His rage will have no breaks.";
			link.l1 = "Wonderful, so I'd rather allow myself to get killed rather than allowing the enraged count to kick you from your governor seat?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "I am afraid that if you don't listen, we won't outlive Angerran de Chievous much longer. Remember that and be careful. The duel is set for ten o'clock tonight past the town gates. My officers will meet you there. Now, for the last item: Madame Julianne Botot - how is she?";
			link.l1 = "You want to know whether I already took advantage of my prize? No, Excellency, not yet or never - it doesn't matter. What does matter is that you are off the marquise's home forever. She was crystal clear about it. I can't judge her for it. Julianne will choose her next patron herself.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "You sure know how to surprise, Charles. Whatever, I have a tedious meeting with the Company's agent to attend to. You should go, get yourself ready and I remember what I warned you about.";
			link.l1 = "I will definitely try, Excellency. But it's a fight, so no promises. Thanks for helping me.";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "You live, Charles! What a relief, how your fared? Is this blood?! Did de Chievous make it?";
			link.l1 = "Unfortunately yes. He is wounded, not seriously. He had to flee, but he also thrown his thugs at us. In short, some of this blood is not mine.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "Bastard! And my men? Are they alive to testify what happened?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "They are alright, Excellency. A bit beaten, but they'll live.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "No all of them, Excellency. One gentleman didn't make it - de Chievous took the effort to bring musketeers along. I couldn't do anything.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "It was hell let loose there, Excellency. Bot brave gentlemen fell in combat. If it wasn't for them, things would get ugly for me. De Chievous orchestrated a proper fucking ambush.";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "Splendid! I will get their written testimonies in a presence of reliable witnesses. De Chievous will pay for this!";
			link.l1 = "I don't think we can do even a slightest damage to his name. I'd rather find him to finish the job myself despite all your warning.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "Terrible. But we will get written testimony from one witness at least. De Chievous will pay for this!";
			link.l1 = "I don't think we can do even a slightest damage to his name. I'd rather find him to finish the job myself despite all your warning.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "Damn him! They were good men, Charles! I swear, the bastard will pay!";
			link.l1 = "I don't think we can do even a slightest damage to his name. I'd rather find him to finish the job myself despite all your warning.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "Forget about it, Charles. The bastard did all the needed damage himself. I'd wager he is on the run now, hiding in the dirt of some poor colony. It's unlikely he is now any of a threat to you. This villainy was just a fleeing snake's bite. You seem to be hurt too, are you in a need of physician?";
			link.l1 = "Thanks for your concerns, Excellency, but I am fine.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "Good to know. You can breath freely now, this story over. Relax and get back to your business. By the way, about that… We didn't finish our previous talk about your recent winnings. Have you decided what will you do with... it?";
			link.l1 = "I don't quite follow you, Jaques What, did you mean the marquise? Shit! Madam Botot! De Chievous is on the run, he is no longer a threat to me, but he desperate and he can do anything! I should go! Send the guards to the marquise house, now!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			dialog.text = "A famous Captain you say? The one who repelled the Spanish assault almost scorched this tiny town? I see. What is you poison?";
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "Pinot Noir, same as our beautiful hostess? Are you sure you can properly taste after all this sea salt? Normally, people of your caliber prefer to drink stuff that can dissolve an old boot.";
			link.l1 = "If this was a suggestion to walk past the gates together then I am in. I don't like you sir either and I am glad the feeling is mutual. Let's cut the talking, you are not good in it anyway. I leave to you the choice of terms and arms.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "A bouquet of dirt and cat piss? Charming! They don't even mature this sour crap in barrels, cause it won't become a wine anyway, ever. Tell me, does the sea salt hammer a taste this hard?";
			link.l1 = "If this was a suggestion to walk past the gates together then I am in. I don't like you sir either and I am glad the feeling is mutual. Let's cut the talking, you are not good in it anyway. I leave to you the choice of terms and arms.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "Ha, such a brave boy! Now chill your temper and keep your distance. We are not in a tavern and I am not a drinking buddy of yours. You are below my station, we shouldn’t even be talking right now. Now, Jaques and I have an unfinished business...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "Julianne are you alright? Water, you idiots! Bring water!";
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "You are quite right, it's muggy here. It's been a most entertaining game so far, but let's make a small break before the finale. Bye, bye Jaques - remember the terms of our tourney?\nAnd here we have Charles de Maure, correct? A captain with a poor taste for wine, I remember you. Don't you worry, after I am done here, you will drink only water. So take your time, enjoy the moment, drink something. When you are ready, come join me in the small room. We will end the night in a more comfy environment...";
			link.l1 = "Looking forward to, monsieur.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "There you are, at last. Ready to part with your money?";
			link.l1 = "I'd rather add yours to them. Please!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "Well said, alas our dear governor had insisted on changing the rules right before his shameful defeat. Now we are obliged to add something more to money at stake. Stakes must be acknowledged equal by both parties. My stake is the flute with silver.";
			link.l1 = "Come on, this is dull - I can get one with gold in a few weeks of raiding. Give me something bigger.";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Yes, I've seen your ship. Let's raise it - two ships against one. My frigate and flute with silver against your ship?";
				link.l1 = "A worthy game! Madam Botot was wrong - THIS duel will live in legends. Deal!";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "Look at this, our captain is a naughty boy! However, privateering is sacred. How about a warship then? A frigate, 48 guns. Faster than many corvettes - a product of royal shipyards, improved even further by the best shipwrights in the world. Culverins she carries have excellent range and accuracy. What say you?";
					link.l1 = "Much better, I am in! Let's go!";
				}
				else
				{
					dialog.text = "I heard what you anchored here, Captain. Be thankful that I agreed to accept your old tub as a stake. Come, unless you refuse?";
					link.l1 = "Fine, you have a point. Let's go.";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "Game over, Captain, you got what you wanted. Gloat if you'd like. I suggest we discuss the terms of buyout of my frigate tomorrow noon.";
					link.l1 = "That's it? I sincerely believe, same as you, that what's lost in a gamble can not be bought out, only won back. Or I can sell her for lumber to local fishermen and tell them all about your generous donation.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "So the Fortune had her say. This turned out most curiously. Congratulations. Captain de Maure. I suggest we discuss the terms of buyout of my frigate tomorrow noon.";
						link.l1 = "That soon? We are disappointing other guests, monsieur. If I recall correctly, you still have one more ship. I sincerely believe, same as you, that what's lost in a gamble can not be bought out, only won back.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "So the Fortune had her say. This turned out most curiously. Congratulations. Captain de Maure. You earned a decent drink, try Sangiovese. I assume, Jaques will pay you well for this tub, at appears he has feelings for it, feeling bigger than to other certain things. Will be sufficient to buy a decent wine.";
						link.l1 = "Surrendering already? We are disappointing other guests, monsieur. If I recall correctly, you still have one more ship. I call you frigate versus my flute with silver since you considered my own ship too modest.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "Bad luck, Captain. Nevertheless, I appreciate your bravery, plus I am in the good mood today. I'll take your gold but keep your ship. Get off my sight and please avoid gambling in the future. Someday, it will kill you.";
				link.l1 = "Very noble of you, I didn't expect that. Farewell, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "These is a notable difference between gloating and mocking your defeated opponent, monsieur de Maure.";
			link.l1 = "Already consider yourself defeated? But it all started so well… ah! Madam Botot, believe your salon just got another rich story about differences between saying and doing!";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "What else do you want? I don't have more ships behind my belt as well as enough cash to cover even just one ship. Gambling over doubloons is not serious after all we have seen tonight too.";
			link.l1 = "Are you less resourceful than our sweet Jaques Di Lu Parkes? I am gifting you the most beautiful chance to prove that not all of love is for sale. Fortune doesn't sell her favor too. The silver ship and your frigate versus the thing you value more than gold.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "Captain, this is not even funny. Let's get this over with - dawn is soon. We will discuss my frigate's buyout tomorrow.";
			link.l1 = "Fine, you have it - three ships! Including a real warship versus the most… well expensive dame of New World. Can you even refuse such a stake?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "It would be a madness. Though, it is a madness, monsieur de Maure. Please. But remember, it was your idea.";
			link.l1 = "This is going to be the legend they will be savoring for year behind closed  door! Hey you, more wine and candles! Game must go on!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "Just recently you assumed this flute as unworthy stake against our vessels. What has changed?";
			link.l1 = "Got bored. Let's add some spice to our duel - your frigate and my ship versus...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "The flute you valued so poorly? Are you in fever by chance? You don't look too well.";
			link.l1 = "I am perfectly fine, thank you. You didn't listen. Two to one stakes are not quite spectaculous, that's right, so let's even the odds! Not all valuables can be measured in gold, don't you agree? Or perhaps you just prefer not to fight the wind, anything goes not according to a plan and you change your course? Pity then, it seems I was wrong about you. Madam Botot, I believe your salon just got another rich story about differences between saying and doing...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "Don't try to get under my skin, monsieur de Maure, you are well too naive for that.";
			link.l1 = "Indeed. The lack of will is not a sin... unless you are a military man of course. Or a nobleman, family honor, as you might know, is such a burden sometimes. Not likely are familiar with such dilemmas at all though.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "Are you trying to start a duel or to continue a game?";
			link.l1 = "Both would do. I will be giving credit to Marquise's wine collection while you pull yourself together.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "So be it. This night should end properly. Two great ships against the old tub filled with silver and the best woman of New France! Breath deeper, monsieur de Maure, this stake will become a legend among high society's gossips.";
			link.l1 = "Your defeat will become a legend, indeed, monsieur de Chievous. Bring us more wine and candles! Let's do it!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "You lost your head over luck, monsieur de Maure. You are risking here, favor of lack is brief.";
			link.l1 = "Brief favor is a road to true love. Which can be said about bought loyalty. It leads only to contempt or boredom.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "Your attempts to get under my skin amuse me. You'd better ask madam Juliana about things like favor, love and everything else you can buy or not. But make haste - she is leaving the town tomorrow.";
			link.l1 = "At least your knowledge of the subject is one-sided. You can't win the favor of Lady Fortune by either winning or paying here, thus you can't know her love. It takes courage, monsieur, and a wiliness to take a risk. Not to mention that more… earthly ladies value these thing too. I call two my ships against one of yours, are you in?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "You want to continue that eagerly? Fine, whatever. But at least lets add some drama to it, monsieur de Maure. You were saying something about love and prices? I hereby suggest to even our stakes - that tub of yours and the flute with silver versus my frigate and the best woman of New France. What say you now?";
			link.l1 = "I say that you definitely know how to gamble in style, monsieur! More wine and candles! Let's go!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Unbelievable, monsieur de Maure, this is just unbelievable!";
				link.l1 = "Yeah right, Europe hadn't known such defeat since the Battle of Rocroi, monsieur de Chievous. An artist who lives somewhere inside me is trembling of desire to picture such a historical moment. It is a shame I don't draw anymore. But perhaps madam Julianne has a talented artist around?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "Bad luck, Captain. Nevertheless, I appreciate your bravery, plus I am in the good mood today. I'll take your gold but keep your ship. Get off my sight and please avoid gambling in the future. Someday, it will kill you.";
				link.l1 = "Very noble of you, I didn't expect that. Farewell, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "No, you don't understand. This is so unbelievable, that it simply can't be!";
			link.l1 = "All of us have seen the cards, monsieur de Chievous - Fortune never lies.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "Fortune doesn't, but you, monsieur de Maure It appears to me that behind your impudence had a plan behind it not just passion. You are a liar and a cheat - I am ready to confirm this before all the guests.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "monsieur de Chievous, did I hear it right? You are ready to confirm your suspicions not only with words? It seems that your insults are going too far and I, as opposed to you, value my family honor.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "Second son, a cheat and a con artist will not talk to me about family honor! Shut up, Julianne, I will address you later! Charles de Maure, I insist you give me satisfaction immediately! Sword or pistol?";
			link.l1 = "Both. To be honest, I am glad you've changed your mind. Remember I suggested we take a walk past the gates? What did you say about my unworthy station? Perhaps the game of cars gifted you with some courage after all?";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "Too great of honor but I concur with marquise. I will end you like a nobleman, de Maure, even though you don't deserve this. I will challenge to a duel tomorrow midday through His Excellency the governor. Come see him by yourself or send your seconds to discuss terms. See you. Madam, my respects.";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "And there you are, the fortune's favorite. Took care of your things, I hope? Didn't forget to confess? They say hell can be rather uncomfortable without it.";
			link.l1 = "Talk is cheap, monsieur. You can't play cards properly, now let's put your fencing skill to a test. Let's dance!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "Nice.. one, damn you. But I still live!";
			link.l1 = "Your wound doesn't look nice, but you should show yourself to a doctor nevertheless. Clearly, you can't go on like this. It looks like we are done here. I won, and I didn't cheat. I suggest I return your ship to you and you will leave St. Pierre. We will never see each other again.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "What an enormous chivalry! Look, monsieur de Maure, you may be a natural swordsman but you most definitely cheated at cards. I messed with the deck trice. Trice! No miracle in the world could possibly save you, but you won anyway! I wish I knew how did you do it... Whatever, soon you will tell the Devil all about it. Hit them lads!";
			link.l1 = "You bastard! Monsieur, to arms!";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
            LAi_SetImmortal(npchar, false); // Captain Beltrop, снимаем проверку на жизнь и восстанавливаем её
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "I admit, Monseniour de Maure, I am a bit surprised seeing you here. That means I wasn't wrong and the wild lass means something to you?";
			link.l1 = "I wonder what's your good friend's de Lyons stance about kidnapping officers from respected captains of our Navy? Perhaps we should ask him to join us and tell him the whole story?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "That won't help you a bit, trust me. Also I treated your wench better than a captured general. For now. But everything can change and it's up to you, Charles.";
			link.l1 = "I don't recall us having a lovers' shot with you. Don't Charles me, Monseniour de Chievous. Get straight to the point and tell me what do you want from me?";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "From you? Nothing, God forbid! You and I just settled an unfortunate fight after some scandalous card game, had a few drinks and left this room as good ol' friends.";
			link.l1 = "Angerran, you look alright despite of your recent wound and every minute of this worthless chitchat makes me want to fix that. Even the thought of spoiling these fine carpets of Francois de Lyons is getting more and more appealing to me.";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "But good old Francois loves these carpets, Charles. Everybody loves something. Since you are here you must love your girlfriend in arms. I am ready to return her to you in return for my property. You messed up game and even though I don't usually forgive such transgressions, I can make an exception for you. You will give me the prize I so desire and I will give you the same. Then we will beautifully part our ways. So much for love.";
			link.l1 = "You think that I carry the marquise like a fucking jewel in my purse? Nonsense! How can I possibly give her to you?!";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "I don't care at all, Charles. You have two weeks to deal with it. And yes, I want this prize to be received secretly. Say, some captain who had won a ridiculously expensive courtesan, but failed to gain her favor nonetheless, could do something stupid about it, right? Think you are already desperate enough, Charles?";
			link.l1 = "I want to see my officer first in order to make sure if she still lives.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "Out of the question. You will have to trust my word. She remains in a safe place and she will stay there until I get my prize. But if you will continue insisting on seeing her beforehand, I will gladly indulge you by sending you some part of her. What are your favorites? An ear, a nose a couple of fingers?";
			link.l1 = "Lay a hand on her, you scum, and I will strangle you with bare hands, I swear to God!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "Calm down. Everything what is about to happen is completely on you. I don't like violence, I use it only when I have to. Don't make me. Just hand me over my prize on Cape Scott Head at Dominica less than in two weeks and you will get what is yours. I don't care who you will do it. If you want to steal - steal, you are a pirate after all, only well dressed.";
			link.l1 = "You are delusional, I am not a damn slave trader...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "Breath deeper, we are about to fashionably parade in front of old Francois. We are friends now, remember? Smile Charles, come on! Let's part our ways. Cape Scott Head, Dominica, two weeks. Don't be late.";
			link.l1 = "I'll see you there.";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			dialog.text = "Good evening, madam Botot, captain de Maure. I ask you to keep calm.";
			link.l1 = "Marquise, behind me, now! Monseniour, what's the meaning of this?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			dialog.text = "I have a dozen of men behind the door and emergency powers authorized by your State. The guards won't help you. Therefore, please put your sword away, sir. I just want to talk. For now.";
			link.l1 = "Monseniour, who are you and how did you get here?! You should explain yourself!";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "Allow me to introduce myself - sir William Cortney, Baronet Cortney. Now let's all calm down and talk.";
			link.l1 = "Fine, Monseniour Cortney, we are all ears.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "Please excuse me for eavesdropping, but the current circumstances leave me no other choice. Even though I remain anonymous here in St. Pierre, I am undertaking an extremely important investigation on behalf of the Crown of England. Concerning a currier ship lost in the sea. Ever heard of a brigantine the Regina? ";
			link.l1 = "I haven't and I don't follow your shady hints, Monseniour. I am an honest captain...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "I don't give a slightest damn about shady little dealings of yours, sir. I did some digging about you and, to be honest, made your my first suspect when I heard that you visited Martinique right after the Regina had disappeared. However, you are not an idiot and your men didn't toy around with pearls here. Therefore, you are above suspicion, for now.";
			link.l1 = "Pearls? What pearls are you blabbering about?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "Handpicked, large sized pearls from the Spanish West Main's operations. The pearls are black too, meaning they are extremely rare, have you ever heard about such?";
			link.l1 = "I guess, yet I always thought it's just another seafarer's bullshit story. The Flying Dutchman like. Julianne, what's wrong?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "I have to ask you to present it here, madam. It's a matter of utmost importance. In the meantime, you sir must tell me all about captain Moreno. I suspect it was him who gave you that lead. I am most curious to learn about his role in this play.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "Moreno is not his real name, Monseniour Cortney. His name is Hernando Vasquez also known as the Bloody Don, a Spanish pirate who used to be a quartermaster of the Albatross - the vessel of infamous Bartholomew the Portuguese.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "We only shared a couple of words. I don't have much to tell. He looked like a real sea wolf.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "My, my. And may I ask how do you know that?";
			link.l1 = "I used to know his captain. Actually it was I who captured and surrendered him to the Dutch. It's a long story. It's a shame I didn't get Vasquez himself back then...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "You are a sea wolf yourself, sir. I don't believe you failed to notice more.";
			link.l1 = "Just a slight accent, the way he looked and behaved. I bet he is a Spanish, Monseniour Cortney.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "That is a game breaker, sir. And it is bad. Madam, did you find the necklace? Let me inspect it\nYes indeed, this is one of the Spanish black pearls. Take a look, this seafarer's bullshit is pretty much real. All is left is to find out how that de Chievous got one of those. By the way, isn't he a bastard of Duke de Levy Vantadur?";
			link.l1 = "That's him alright. As far as we know he had dealing with the local pirate baron at Le Francois. Perhaps he bought this pearl from him?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "Maybe so. But I don't like the Spanish trail in this at all. Anyhow, thank you for your cooperation. I am afraid I must visit you again tomorrow at the same time of day. I would ask for captain Maure's presence as well. Perhaps I will have more questions for you. I should go to Le Francois now.";
			link.l1 = "Monseniour Cortney, wait. Perhaps I could join you? Jaques Barbason has earned his nickname not for being a loving and gentle person, plus this matter has some interest for me too.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "Captain, I am moved by your concern but it is a no. This is a business of State. The scoundrel knows his place and wouldn't dare to lay a hand on the Crown's emissary, otherwise his pathetic village is no more! I apologize for the intrusion again, madam. Good evening.";
			link.l1 = "See you tomorrow evening, Baronet.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			dialog.text = "Don't be mad at her, Captain. I can be very persuasive. Your story is impressive, really. I believe I might have a use for you.";
			link.l1 = "You look content, how did it go in Le Francois?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "As I expected, that baron of yours was meek like a lamb. He told me everything I wanted to hear. As I said, I can be extremely persuasive.";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "Today I came here on my own, there are no my men behind that door. What the hell?!";
			link.l1 = "I have a bad feeling about this. Julianne, get behind me, now! Baronet, do emissaries of the Crown fight just as good as they talk?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			dialog.text = "You sure know how to handle a sword, Captain Uh, in all honestly, it wasn't a walk in a park. Who the hell were these people?!";
			link.l1 = "We should ask their friends - I hear more steps. I wish it were the guards...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "Unbelievable! You think the bastard dared to do all this?! He will pay, I swear!";
			link.l1 = "Breathe. Goodman will weasel his arse out of any accusations. He will tell you it was just an ordinary raid of petty burglars on a wealthy household. Besides, he is a damn pirate, why would he care about authorities! Nevertheless, now I am sure that you managed to learn something truly viable. I ask you to share this knowledge with me.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "I can't really say no, can I? Otherwise the next attempt might be a success? Fine, I will pretend I didn't notice a sign of threat in your tone. Let's say I am returning you a favor. Goodman Jack didn't sell pearls to your noble bastard. He was buying. That's it.";
			link.l1 = "So it was de Chievous who intercepted the Regina? A scoundrel he is, but it's hard to believe he would lower himself to ordinary piracy.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "One would hardly call the Regina a regular prize of a pirate, Captain. We assume she had at least half a dozen of black pearl. Even a single black pearl is priceless. I absolutely have to meet that sir de Chievous at all cost.";
			link.l1 = "I can be of some help here, Monseniour. But let me get something straight first. I didn't seem to care about madam Botot's necklace, therefore the pearls are not the reason you are here. What else did the Regina had onboard?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "Very well, I take it I'll have to tell you more considering… circumstances. See, the cargo is not that important compared to the ship herself. Currier brigantine the Regina had been assigned to a port of San Jose, Trinidad. Her captain used to gather intel and did some... errands for us\nThe last errand of his was to transport spoils our capers managed to extract from the Spanish pearl operations. It took three years of our efforts to get that lead. Black pearls are surely significant but losing the Regina is fateful. It wasn't an accident, someone who knew about her pearl must also had known about the rest.";
			link.l1 = "Splendid, so it's intelligence services business after all! Are you afraid that the entire spy network you built is in danger? Now I can see the whole scope of your troubles.";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "Ever heard of John Thurloe? He is the head of Crown intelligence. One day I will be in London, reporting him, personally, about the fate of the Regina. I must find where is leaking and... deal with the source. Plus, there is also that mysterious captain Moreno of yours. If the Spanish tracked our colonial spy network, years of hard and laborious work will go down south!";
			link.l1 = "You know all of that is starting to make sense if you look at the bigger picture. I am starting to think that someone with a Spanish accent told de Chievous about the Regina and black pearls.";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "We think alike. There is no better way of exploiting an exposed spy network. A diplomatic incident with a man of a such high standing involved… Such incident can seriously damage relations between Britain and France, all you need is to feed right leads and just wait for an international scandal. Perhaps even that lead about black pearls had been deliberately fed to us too.";
			link.l1 = "That damn Castilians, right? So what do we do about de Chievous?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "To be honest I have no idea. If it is a Spanish provocation than it would be wise just to ignore it. But I must learn how did he find out about the Regina and how bad it looks for our network in Spanish colonies. I also owe you my life and I intend to repay.";
			link.l1 = "Honesty for an honesty, Baronet. I could use any help I can get. I am already desperate enough to consider abducting the marquise.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "You do realize that this is how de Chievous covers his tracks? It will be so easy to put all if that mess on you, including the disappearance of the Regina. Therefore, I propose the following. Marquise Botot told me that de Chievous will not attend the exchange and would safely remain in Basse-Terre. It's either he realized in what mess he got himself into or he is starting to suspect something. He will be as careful as a kitchen mouse. This is why I will go to Dominica with you.";
			link.l1 = "But his prisoner is my priority, I can't risk on her life! She is a hostage awaiting an exchange!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "Don't you worry - I will press Jaques Di Lu Parkes and will get an arrest warrant for de Chievous's vessel. I doubt that his men are fully aware of the situation they are in, otherwise they would had been more careful with those pearls. We will go to them on a longboat and present them a warrant directly.";
			link.l1 = "Yeah, I remember your gift of coercion, Monseniour, but it is a risk. And a heavy one.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "You're quite right, but you'll have to take it if you wish to accept my help. Once we are done at Dominica, I will go to Basse-Terre and demand governor de Lyon to surrender your adversary. My powers allow it. We can't let de Chievous to sneak away.";
			link.l1 = "Are you really up for it, Monseniour? It might start a war, right?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "I bet they will never allow it to happen. It's definitely a no go since we already know the truth. Politics is a whore, Captain. I promise I will introduce de Chievous to British dungeons, just for you personally. That sounds like a quite solution even his father would consider a reasonable price.";
			link.l1 = "I can't say I like your plan but I see no other.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "I assure you that we will make it. I should go now to see a governor and give orders to my men. If you see the marquise, tell her that she may keep the pearl as a gratitude for her assistance to the investigation.";
			link.l1 = "Thanks, Baronet. See you on my ship, we a setting sails soon.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			dialog.text = "William Cortney, Baronet Cortney, at your service. By the power vested in me by British Empire with all support from her trusted ally France, your vessel is hereby under arrest. Here are the papers, please make sure to read them and tell your men to keep their hands away from weapons. You are detained but nor yet arrested. If you don't do anything stupid, you will be released in the first port.";
			link.l1 = "Baronet, I must retrieve my... my officer!";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			dialog.text = "Don't you worry Captain, I will see her to your ship. I ask you to return to the longboat now. I will take command over this ship and sail to Basse-Terre. Feel free to leave us if you have got no intentions of mocking your archenemy personally. I only ask you to transfer a few of your men to me to help us getting to Guadeloupe.";
			link.l1 = "Very well, Monseniour. I'd rather not. Send him my worst regards. Good bye and thanks again!";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			dialog.text = "Charles, I am glad to see you. I had hoped for your return but never really believed in it.";
			link.l1 = "Likewise, Baronet. Did you come to pay the Marquise a visit? Where is she by the way?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "You still don't get it, do you? She fled. Also, Angerran de Chievous sends you his sincere apologies. I had managed to persuade him that you were never a part of the game, yet just another victim of it. Just like him. The good man didn't bother to write, but he is deeply sorry about how things went.";
			link.l1 = "Deeply sorry, isn't he?! What are talking about, Monseniour?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "You and I, we overlooked the main thing. How did he learn about the pearls? Who were that Spanish captain invited to this very house? Who could move the bastard to pursue such prize?";
			link.l1 = "You serious? It can't be...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "It definitely can. Marquise played her part perfectly, she almost pulled the whole thing through. However, thanks to an investigation of ours, I approached de Chievous as he was not a as a thief and a pirate, but as a victim of deceit which he is. He found out what she had dragged him into pretty quickly, yet he had no evidences and decided to act on his own. You know what happened afterwards.";
			link.l1 = "You mean that all of that had been orchestrated by the Marquise? De Chievous bought it like a careless infant!";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "Precisely. Passion is a very dangerous thing, Charles! Remember that night when you gambled in this very house? Angerran was going to squeeze evidences he needed from the marquise by gaining a patronage over her. Yes, he cheated, but he was desperate after years of hopeless passion ended by the most devastating betrayal! But you stepped in, called yourself her champion and succeeded in that role. De Chievous though that you and her are of the same mind. He stole a ship he lost to you in order to prevent you from getting its logs. He used your officer to try pit her and you - his deadly enemies as he believed.";
			link.l1 = "I am out of words!";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "Now you know how it is, Charles! The Marquise is smart, breathtakingly beautiful and no less dangerous. I don't know how long she manipulated the best people of New France. For many years, I'd say. Anyways, it concerns you no more. It was a pleasure to meet you again, but I got more rooms to turn upside down, it's a big house. We probably won't find anything, but we have to try at least\nOne more thing before we part our ways. Here, take this. A souvenir to remember. Perhaps you will gift it to your lady friend when you are ready. You are very lucky, you know. Especially when compared to de Chievous, poor bastard!";
			link.l1 = "You are right, I am. Fare well and Godspeed in your searches, Baronet!";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			dialog.text = "What a nice day we are having today, eh Captain? I heard of your exploits, yet I never imaged you to be a banal pirate. Such insolence - to come to St. Jones after what you did!";
			link.l1 = "I may be a pirate, that's quite true, sir, but do I look like an idiot? Why on Earth would I come here after sacking the Mercury and relieving her of Spanish pearls?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "I admit, this is the only reason why you are having this conversation now instead of waving on a noose. See, there is tiny detail we concealed in this case. And I am not talking about the pearl we found on you. It's the name of the brigantine.";
			link.l1 = "Meaning?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			dialog.text = "A currier brigantine, the Regina had been signed to San Jose port for the last two years. Her captain gathered intel for us and also performed… errands of all kinds. We are officially searching for her on the pretext of the lost diplomatic mail she carried. It is not much of a ploy, I admit. Still, you couldn't learn the ship's true name without properly searching through her captain's cabin.";
			link.l1 = "I was blind but now I see. Please hear me out, sir, I will explain!";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "Well, try harder, captain. Your life is hanging in the balance.";
			link.l1 = "I have nothing to do with this spy story! Neither do the Spanish. Your network is safe, don't you worry. However, you had a leak and someone used it. And then, I got myself into an argument with this someone. I found evidences of his involvement in the Mercury business and I wanted to use them to beat him. God be witness, I thought of this case as an ordinary action of piracy, I couldn't even think that Crown's intelligence has something to do with it! All I have is this pearl, yet I know very well when and where you can find more.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "Ever heard of John Thurloe? He is the head of Crown intelligence. One day I will be in London, reporting him, personally, about the fate of the Mercury. Therefore, give me a name of that miserable adversary of yours.";
			link.l1 = "Angerran de Chievous,  Count de Levy Vantadur bastard. I suppose that he considered the Mercury to be only a transporter of capers' plunder. He might had known about pearl, yet had no idea about British intelligence's connection.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "You don't disappoint, Captain, I give you that! What a choice of entertainment and enemies! Very well. What other evidences besides the pearl do you have?";
			link.l1 = "De Chievous has a frigate. I used to own it... for one night only, yet I've managed to learn something. He is an extremely pedantic man, you will learn all about his attack on the Mercury from his log. I am pretty sure that he still posses a portion of the prize too. Maybe even more black pearls if there were more than one.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "More than one, you can count on that. We would never put the Regina at risk for a batch of common pearls. I hope you realize that I absolutely must to talk with Monseniour de Chievous. I don't give a damn about pearls, but I must find out more about the leak. My superiors will bury me if I won't deliver a full picture to them.";
			link.l1 = "I'd be glad to arrange a meeting for you, but we must hurry! At this very moment de Chievous's frigate is on it's way to Guadeloupe, where its owner currently resides under protection of the local governor. I am sure that he is aware of what he had done and will flee from the New World as soon as possible.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "These are very serious accusations of very serious people, Captain. Do you realize what… shitstorm might backfire afterwards? A brigand attack of a vessel flying a flag of an ally? This can seriously complicate relations between two great nations. I find it hard to imagine how deep did he manage to get under your skin to make you eager to risk that much.";
			link.l1 = "He took something from me, milord. Something I value the most. I must fix that. If it leads to war, then I will be serving my country under its flag. Nevertheless, de Chievous will get what he deserves!";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "Did anyone ever told you that you are a man of great danger, Captain? Ready to start a war on a half of the globe in order to achieve you goal? Very well, let's do it your way. I will go to Basse-Terre with you. I can let go of such trace. I will send a scribe to write down your evidence while I am preparing my vessel.";
			link.l1 = "Thank you, sir. But we don't have time to spare here, I warn you!";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "Captain de Maure, we will make it in time, I have no doubt in you. However, if this adventure won't work out… do you understand me? I can't promise you even a proper grave.	";
			link.l1 = "Yes, milord. I understand you completely.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "The die is cast, Captain. I demanded a meeting with Angerran de Chievous. His frigate will be searched immediately upon her arrival. Francois de Lyon has his doubts, by seals on my papers hold him back for now. I ask you to stay in town until the situation is settled one or other way around.";
			link.l1 = "Sure thing, milord, I understand.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "Then I hope you will understand this as well. Hand you sword to gentlemen over there and follow them so I am sure you will keep your promise.";
			link.l1 = "Unbelievable... milord Cortney, are you serious?!";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "Dead serious. You still remain one of my major suspects and letting you go at this circumstances would be most stupid of me. I will apologize to you in any way I will find fit when and if you words prove true.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "Greeting, monsieur de Maure. Shall we?";
			link.l1 = "With pleasure, what are the rules? To be honest, I was too busy with food and probably misheard the terms.";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "Rules are simple. 10 000 pesos for a card, we play until one of us surrenders. Receipts and credits are not accepted.";
			link.l1 = "Works for me. Let's do it, Colonel.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Damn it! Never again! Very well, monsieur de Maure, best of luck in the next round.";
				link.l1 = "My pleasure, Colonel. Farewell.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "You fought well, but Lady Fortune had her own plan. Farewell, monsieur de Maure. Thank you for the game.";
					link.l1 = "Yeah, I guess I overestimated myself in this. Farewell, Colonel.";
				}
				else
				{
					dialog.text = "You decided to refuse of further game and thereby admitted defeat! You fought gloriously, but fortune judged otherwise. Goodbye, monsieur de Maure, thanks for the game.";
					link.l1 = "Yeah, I guess I overestimated myself in this. Farewell, Colonel.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Captain Charles de Maure, what a fucking surprise!";
					link.l1 = "Captain. Moreno my ass! What brings you here?!";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "Captain Charles de Maure, my pleasure.";
						link.l1 = "Have we met before, monsieur... Moreno?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "Captain Charles de Maure, my pleasure.";
						link.l1 = "Have we met before, monsieur... Moreno?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Captain Charles de Maure, my pleasure.";
				link.l1 = "Have we met before, monsieur... Moreno?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "It's a long story. Same as always, captain. I can see it in your eyes that you have questions. Just make keep it quiet and pretend you are mocking a simple sailor.";
			link.l1 = "Yeah, this fancy suit is looking good on you, my simple friend. I'd say you know how wear it.";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "Only on rare occasions, on luck. Today's day. Let's gamble, Captain. People are watching, it is not polite to keep them waiting.";
			link.l1 = "Right, we'll talk later. Deal... captain Moreno if you please.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "I know you a bit, but this is irrelevant. Deal the cards, Captain de Maure, people want a show.";
			link.l1 = "Curious. Especially your Spanish accent along with madam Botot's credits to you. Very well. Sea versus sea, let's do it!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "I remembered you alright. When you and my ex captain skewered my boys in Le Francois. The bastard got what he deserved anyway, not without your help as I recall. But don't wait for my gratitude's, you killed Franz Garke and I am not forgiving you for him.";
			link.l1 = "The Portuguese's quartermaster? Bloody Don, right? This night is just getting better and better. Let's do it!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "You decided to refuse of further game and thereby admitted defeat! I take it Lady Fortune had her saying. Bye, Captain.";
				link.l1 = "Likewise, monsieur Moreno. Thank you for the game.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "I take it Lady Fortune had her saying. Farewell, Captain, perhaps we will meet again.";
					link.l1 = "Likewise, monsieur Moreno. Thank you for the game.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "I take it Lady Fortune had her saying. Bye, Captain, perhaps we will meet again in different circumstances, he-he.";
						link.l1 = "Looking forward to, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "That's it. Fortune has decided, Captain. Farewell.";
						link.l1 = "Bye, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "That's it. Fortune has decided, Captain. Farewell.";
				link.l1 = "Bye, monsieur Moreno.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "So nice to see you, Monseniour captain de Maure! To be honest, I expected to see anything, including a full guard complement, but not you.";
			link.l1 = "Monseniour Moreno, are you having some troubles with the local officials? Nice to you too by the way.";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "I say, one can't refuse our hostesses invitation. At least, not that kind of invitation. Come on Charles, stop with this comedy. Marquise made sure I know that she knows my true identity.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "Madam, you are charming! This new friend of yours once already tried to turn me in. Actually, it didn't turn very well. But now I owe him one, so there is no need for threats, don't you worry.";
			link.l1 = "Appreciate it, Bartholomew. Angerran de Chievous cornered me into an extremely uncomfortable position and I absolutely have to bring him down. A life of… someone very dear to me depends on that. Trust me, this time nothing will stop me.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "Enough, Captain, we are friends, right? Remember that race across a half of the Archipelago? Such things means a lot. I will do my best to help you out. Ever heard of the Mercury?";
			link.l1 = "Now, what is it? A ship?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "A British brigantine, to be precise. Her role was to carry spoils of colonel Doyley's privateers who sacked Spanish pearl operations on the West Maine. The ones which occasionally fish legendary black pearls, ever heard of that? If my information source is reliable, several of such pearls had been stored on the Mercury. A month ago I layed an ambush between Martinique and Guadeloupe, waiting for those fine gentlemen. But it was in vain! We spent a week in the sea until we had to call it a failure.";
			link.l1 = "Right, so your source wasn't reliable after all and you got no prize for yourself. What de Chievous has to do with all this?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "Had the same thoughts until I found out that the Mercury never showed up at Antigua. Imagine my surprise because they saw her near Curacao and no way she could get past me near Martinique. The brits are raging! Imagine missing such prize and all! In any case, I got curious and started investigating. about that special someone who ruined the fun for everyone. Such loot can not be sold fast, so I went to Le Francois to find the bastard and to get what he owed me.";
			link.l1 = "Your story rings a bell. Ever heard of the word 'Karma'? You definitely know how find troubles on your backside. But I still don't see how that can be any of use for me?";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "Don't rush it, Captain, I am about to tell you the best part of my story. That unwashed, well-dressed friend of yours - his boys left a noticeable trail of great pearls in local stores. A pride of Spanish pearl operations which they wasted in great numbers.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "";
			link.l1 = "Think de Chievous bought stolen pearls from Jaques the Kind and his boys? I am afraid this... is not enough.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "It is, cap. He didn't buy, he was selling! I talked with Barbason about this and he confirmed that he bought a significant batch of perfect pearls from some partner of his. He sent it to Europe afterwards. We also have that black pearl in the necklace and the fact that de Chievous ship went through repairmen works. Workers told me that his frigate had holes from twelve pounders. Who in their right mind would ever attack a frigate with such babies?";
			link.l1 = "Sounds like our brigantine! Plus, I remember de Chievous boasting about how fast his frigate is. But why this madness? We are in piece with Britain, why risk so much and for what? Black pearls are extremely rare alright, but not unavailable.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "And that is where he got wrong! The brits has already started an official investigation of the Mercury's disappearance, although they call her a missing courier ship with some important documentation onboard. Any leads will be generously rewarded, any responsible will be severely punished. The best part is that they have sent a special noble official to Antigua who is now tirelessly digging through the case. I don't recall his name, fancy as his smug face, but I am glad that he is not hunting me!";
			link.l1 = "Now that's something! It appears that they want those black pearls badly. I wonder how many of them they had on the Mercury and how all this knowledge can be useful to me?";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "Why, the scum managed to piss you off too, marquise? Winky bastard! I am with you on this too, Captain de Maure! No one dares to steal the loot from Bartolomeo the Portuguese!";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "I need a proper drink after all this talking. Marquise, sine we are friends now...";
			link.l1 = "I don't think they have rum in this house, Bartholomew.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "Yeah right, just put his frigate into attention of that British investigator! If this is our plan than I don't recognize our good old captain de Maure!";
			link.l1 = "You'll laugh, but that's the plan. I will need help from both you. Madam - you will be a prisoner of the pirate I hired - Bartholomew, that's you part.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "And about this villany of mine too! Bartolomeo the Portuguese never abducted a woman!";
			link.l1 = "And he won't, but it will look like it for the men of de Chievous. Plus, there is no need to tell them your name. Take our lady onboard and meet with Angerran's frigate near Cape Scott Head. Trade Julianna for my officer and get back to Martinique. Then wait for marquise and me.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "This was all very fascinating and all, you are a natural chevalier, Charles. But how the hell are we supposed to return her after the exchange?";
			link.l1 = "I will handle it. We don't have much time, so let's split. You and the marquise will go Dominica while I will rush to St. Jones. I will find Colonel Doyley or that British investigator and will tell him who is responsible for the Mercury's disappearance.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "Have you put any thought into the shitstorm that will surely follow after such incident, Captain? At this moment, Antigua is a hornets nest and you are telling me to throw a rock at it. I remember wars started because of less!";
			link.l1 = "One problem at a time... I will bring her back at all costs! Let de Levy Vantadur to clear all the mess on his own if he is as powerful as they say! Also, de Chievous will have a hard time explaining how Madame Botot ended up aboard his ship.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Ready? On a prayer! Marquise, are you ready to be abducted?";
			}
			else
			{
				dialog.text = "Ready? On a prayer! Marquise, how long it will take you to pack up?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", monsieur de Maure. My name is "+GetFullName(npchar)+", and this is "+GetFullName(characterFromId("GG_SecundantGG_2"))+". His Excellency requested us to witness your duel with monsieur de Chievous.";
			link.l1 = "Good evening, gentlemen. I hope everything will go smoothly and no is going to do tonight. But be ready for anything anyway. This guy can be a disappointment.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "Your unrest is groundless. According to the preset terms of this duel, under no circumstances seconds may interfere. But thank you for warning us anyway. Your opponent has arrived. Godspeed, Captain. His Excellency asked me to tell you that he will pray for your... prudence.";
			link.l1 = "I am sure, it will help me quite a lot. Whatever, let's begin.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "Cap, we have a problem. Our ship is... well, no more.";
			link.l1 = "Wait, what?! How, who? A full watch unit was supposed to be stationed on her, so what the fuck are you talking about?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "No, Cap, not the ship. She's shiny. The frigate you won yesterday, so she is ours now too, aye? We sent only a prize crew of a dozen there. She said that would suffice.";
			link.l1 = "Just fucking stop and tell me exactly what happened from the beginning!";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "No idea, Cap. The frigate set sail in the mists of morning. The watch noticed her absence few hours later when the mist was no more.";
			link.l1 = "It simply can't be! She would never do this to me! Although… shit, we had a fight just recently. Could she...";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "One fears it is even worse, Cap. Fishermen found two our boys from the prize crew early morning. Both dead, throats cut.";
			link.l1 = "Fucking nightmare! De Chievous! He stole his ship while I had been busy with the marquise! I hope she lives... If she lose just a hair, I...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "Will you give the orders to the boys to get ready, Cap? We can set sail in two hours time, everybody's being on edge whole morning.";
			link.l1 = "Too early for that. I must think this through properly and talk to someone.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "Captain de Maure, what is going on? Did someone attack madam?";
			link.l1 = "You shouldn't have come here. Well, God is my witness, I didn't want this.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "Monseniour, we almost lost hope of having you here. I can see marquise Botot in your longboat. Not even going to ask. Your companion is waiting for you. She is safe and sound, take her and get the hell out of here.";
			link.l1 = "If you layed a finger on her, I will tear you old tub to pieces!";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "What an unexpected show of care. Don't you worry, she was held like a prisoner queen. Your threats are of no concern to me. By the way, Chevalier de Chievous sends his regards.";
			link.l1 = "Screw him and his regards. Where is my... officer? Let's commence the exchange.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "Monseniour, we almost lost hope of having you here. Your companion is waiting for you. She is safe and sound... wait who the hell is this? Where is the marquise?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "You sword, sir. And no funny business, my lads are a bit edgy nowadays. You don't want to get a bullet, do you?";
			link.l1 = "You serious? Fine, take it, but be gentle, it costs more than your barracks. I demand a meeting with baronet Cortney, you Excellency!";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "Don't worry, I am sure he will find some time to pay you a visit.";
			link.l1 = "You try to help someone...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "I don't like this too, Monseniour. Alas, this insolent brit has an authority even Monseniour de Lyon can't do much about it. I apologize, Captain, hand over your sword please.";
			link.l1 = "I do hope, Monseniour de Chievous won't be sharing the same cell with me. Let's go, gentlemen, I am dead tired. Finally, some sleep.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "I don't want to seem impolite, monsieur, but I don't have time to talk now, you see what's going on. I don't want to miss anything!";
			link.l1 = "As you wish, monsieur.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "This evening will go down in history, I feel it! People will be discussing it from here to Versailles! My Marianne will be delighted and will want to know all the details. Please, monsieur, step aside, you're blocking my view.";
			link.l1 = "I'm leaving already, monsieur, enjoy the show, and say hello to unforgettable Marianne... whoever she is.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "Bah! So, here is monsieur de Maure! Excuse me... captain Charles de Maure! Join me, please, here is a magnificent selection of wines from the good Old World. With what do you want to start the evening: there is a novelty - Cabernet Sauvignon from the shores of our beloved Gironde, or unfading classic - Italian Sangiovese?";
			link.l1 = "Thank you, monsieur, we will drink with you, but a little later.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "Oh, captain de Maure! Would you like some more wine... hick? Take a look at what we have just been served - Syrah of 1643 year made, just from the northern hills of the Rhone Valley. This is, damn it, a real pearl! And the year was excellent in every way, I tell you ... one defeat of the Spaniards at Cape Gat is worth it! By the way ... why does everyone fuss like that, do you know? Does anyone feel bad? However - well, cheers...";
			link.l1 = "Well, at least someone pays tribute to the treats. Au Revoir, Monsieur.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "Oh, captain Charles de Maure, I heard about you, like everyone else in this city! let me introduce myself - "+GetFullName(npchar)+", meeting you is a great honor, believe me! Are you really on good terms with our governor? Can you introduce us? I want to express my deepest respect to him and...";
			link.l1 = "Maybe later. Have a good evening, monsieur.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "Monsieur de Maure, have you seen this?! Our esteemed governor and monsieur de Chievous himself - I thought they would kill each other right here! Grandiose! Marquise Botot has surpassed herself today - it's all so damn exciting! I'm impatiently waiting the continuation. By the way, maybe now is the right moment? You promised to introduce me... ";
			link.l1 = "I don't remember that I promised anything. I'm sorry, I have to go.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "Monsieur de Maure, you finally got to the salon of the brilliant madame Botot! She has already rumored a couple of times that she wanted to see you. Managed to evaluate her 'pupils'? Yes, stars like the marquise are not for mere mortals like you and me. But believe me: these ladies are real works of art. Perhaps, less amazing, but still - like Michelangelo and, say, Titian.";
			link.l1 = "An interesting comparison, monsieur. Well, I'm leaving you to enjoy... Titian.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "No, it's always funny here, but now the air clearly smells like a luxurious scandal, do you feel? Lady Jacqueline is waiting for me upstairs, but I still can't move away from the gaming tables! His Lordship and monsieur de Chievous are worthy opponents and are extremely determined. It seems that bets today will not just fly to the stars, but will break the firmament right to devils!";
			link.l1 = "The devils are below, monsieur.  There must be angels behind the firmament of heaven.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "Well, at least one nice meeting! We have already met, captain de Maure, but you hardly remember. "+GetFullName(npchar)+" - was the captain of the sixth infantry company of the garrison, fought with you on our streets with the Spaniards. True, I got a bullet to my knee and most of the battle I was admiring how this same brothel was burning, while I was lying in a ditch. Now here - again civil, and again admire it, now from inside.";
			link.l1 = "Glad to meet you, monsieur. That day was really hot, but admittedly, this place has got all good from that day!";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "And how do you like the atmosphere here, captain? It seems that these secular wallies decided to make a goddamn mess! Interestingly, can the governor's chair be played like a bet in cards? Remember my word - it will end with steel. It's a pity, with my knee, such entertainments are no longer for me. However, somewhere I saw Jacqueline - her gentleman is seriously passionate about what is happening... I'll go and try my luck, while everything is still calm here.";
			link.l1 = "Good decision, I wish you success, monsieur. And I have to go back to... wallies.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
