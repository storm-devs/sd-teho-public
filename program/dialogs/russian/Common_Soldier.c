// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple("Pirates in the town?! Can't believe it... Seize "+ GetSexPhrase("him","her") +"!!", "That's a pirate! Seize "+ GetSexPhrase("him","her") +"!!!");
					link.l1 = RandPhraseSimple("I am a pirate and so what?", "Heh, you may try...");
					link.l1.go = "fight"; 
					break;
				} 
				dialog.text = RandPhraseSimple("A spy! Surrender your weapon and follow me!", "An enemy agent! Seize "+ GetSexPhrase("him","her") +"!");
				link.l1 = RandPhraseSimple("Shut up, sissy!", "Fuck you!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("Who are you and what are you doing here?", "Stand there! Who are you and on what right are you trying to enter the town?");
						link.l1 = "Look at this paper, soldier. I am here on permission from the Inquisitor, Father Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("Who are you and what are you doing here?", "Stand there! Who are you and on what right are you trying to enter the town?");
						link.l1 = "Look at this paper, soldier. I am here on permission from the Inquisitor, Father Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					dialog.text = RandPhraseSimple("Who are you and what are you doing here?", "Stand there! Who are you and on what right are you trying to enter the town?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Officer, I have " + GetRusNameNationLicence(HOLLAND) + ", so I am here on legal grounds. Here, please take a look...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Don't you see on the mast of my ship the flag of " + NationNameGenitive(sti(pchar.nation)) + "?!";
						}
						else //если причалил не в городе
						{
							link.l2 = "I dropped anchor off near " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " under the flag of " + NationNameGenitive(sti(pchar.nation)) + ". What don't you understand?";
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Pirates in the town?! Can't believe it... Seize him!", "That's a pirate! Seize him!");
							link.l1 = RandPhraseSimple("Yes, I am a pirate - now what?", "Heh, catch me if you can...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Don't you see the flag of " + NationNameGenitive(sti(pchar.nation)) + " on my ship?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "I dropped anchor near " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " under the flag " + NationNameGenitive(sti(pchar.nation)) + ". What don't you understand?";
						}
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, captain, we've had such a great time with you at sea! So many ships we have sunk together under your command! And here...";
									link.l1 = "And here, my friend, you can feast your eyes upon charming ladies, for you will not see them at sea.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Captain, what have we done to deserve this?! We aren't landlubbers, are we?";
									link.l1 = "Quiet, sailor! Your post is an important and honorary one, so quit your whining.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "What's up with the sea, captain? Will we ever see it again?";
									link.l1 = "But of course, sailor! Once you are relieved from duty, you can go to the pier and enjoy the sea as much as you like.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "I want to complain, captain: every one of us longs to ship out. We're all totally fed up with this land duty!";
									link.l1 = "I'm tired of this whining! You drink enough on land as well as at sea! Serve where the captain ordered! Or you will be hanged as an example to others.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "I'll tell you in confidence, captain, the new governor is a grafter and embezzler of funds. But that's really not my business...";
									link.l1 = "Exactly, corsair. Your business is standing at your post and keeping order. And to hang the governor on the yardarm is my business. Good job!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Thank you for not forgetting about us, captain! We'd go through fire and water for your sake!";
									link.l1 = "I know your type, crooks! All you really love are gold and rum. Now, there's a party at the tavern today, I'm buying. Don't forget to show up.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Oh, captain, it's been so long since we've last time been in a bloody fight! Corsairs simply cannot be guards, don't you think so?";
									link.l1 = "No time for relaxing, corsair! Enemy armadas are scouring the seas near our islands, and we must be ready for a bloodbath at any time.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Captain, they say that the Crown has sent another squadron our way?";
									link.l1 = "Of course, corsair. While we live, there will be no peace for us. And even in Hell we will be fighting devils!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Now that was a real party yesterday, captain! It's a pity you weren't there.";
									link.l1 = "No big deal, I'll make up for it. And actually I don't envy you, guys.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "I'll tell you in confidence, captain, 'cause you've always treated us well - we had some good time with a really nice chick yesterday...";
									link.l1 = "Heh, corsair, a noose is something you really need!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Captain! Please relieve me from this cursed duty! I simply can't play the part of a keeper of order anymore.";
									link.l1 = "Night watch on a ship is no cakewalk, either. Now duty is duty, whatever and wherever it is.";
									link.l1.go = "exit";
								break;
							}
							link.l2 = RandPhraseSimple("I've got an important business!", "I have business to you.");
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("Alert! Here is armed sick psycho!", "To arms, to arms! Here is crazy bastard!");
								link.l1 = RandPhraseSimple("Huh? What?", "Uh, why are you doing this?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							dialog.text = LinkRandPhrase(RandPhraseSimple("Do you have business with me, captain?", "I have business to do. If you need to ask anything, just be quick about it."), RandPhraseSimple("Captain, I'm really busy, so you'd better find other people to talk to.", "Is anything wrong, captain? If not, then please be so kind to let me pass."), "Give me a way, captain, I am in a hurry.");
							link.l1 = LinkRandPhrase("Sorry, buddy, I have taken you for someone else.", "Alright, go about your business.", "No, nothing.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("I have several questions for you.", "I have business to you."), RandPhraseSimple("I can see that you're in a hurry. I won't delay you for long - just one question.", "I wanted to ask something."), "Your business can wait. I want to ask you one thing.");
							link.l2.go = "quests";//(перессылка в файл города)
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Just look  "+ GetSexPhrase("at that scoundrel! He dared to show his face","at that scoundrel! She dared to show her face") +" in " + XI_ConvertString("Colony" + npchar.city)+ ". Seize "+ GetSexPhrase("him","her") +"!!!", "Ha, I recognized you, "+ GetSexPhrase("scoundrel","rascal") +"! Seize "+ GetSexPhrase("him","her") +"!!!");
							link.l1 = RandPhraseSimple("Argh!..", "Well, you've asked for it...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "Oh, look who's there! Lady " + pchar.GenQuest.EncGirl.name + " herself honored us with her presence! I wonder how you dared? We've been looking for you! Please proceed to the dungeon - your cell is ready and waiting for you. ";
							link.l1 = "What utter nonsense are you talking!? Me and my "+ GetSexPhrase("cavalier","companion") +" were taking a stroll in the jungle, pocking flowers. Leave me alone! Where are the manners of these martinets?! As soon as they see an attractive girl, they begin nagging at her! "+ GetSexPhrase("My dear, please tell those blockheads to get lost and leave an honest woman alone!","Darling, please tell those blockheads...") +"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "Oh, there you are, beautiful! Your dad got the entire garrison up to find you and bring you back home.";
							link.l1 = "Get lost! I know where I am going and I do not need your help! Captain, tell them to take their hands away from me.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "The regulations of the guard duty do not allow me to talk to strangers!";
							link.l1 = "Good job, soldier! Carry on!";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Something wrong? Have you noticed any disturbance?";
							link.l1 = "No, everything's fine. Still, your vigilance is commendable.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Duels and brawls are forbidden on the streets of the town, weapon may be unsheathed only in case of danger.";
							link.l1 = "Alright, I'll keep that in mind.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "What a fair weather! And here I am, standing like a statue for no purpose...";
							link.l1 = RandPhraseSimple("No relaxing, soldier. The enemy is watchful.", "You should not be complaining of your duty, soldier. Keep your spirits high!");
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Find someone else to talk to, if you're in the mood for talking. I am here to keep order, not to chit-talk!";
							link.l1 = "Good job, soldier, you know your duty well! No need to be rude, though.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Keeping order is not all that easy, as it might seem. It's an important and dangerous job. I remember a case in the garrison...";
							link.l1 = LinkRandPhrase("Don't get distracted while on duty.", "No talking while on duty!", "Stand where you are. You can chit-talk at the tavern all day, when you're relieved.");
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = RandPhraseSimple("Do not distract me, " + GetAddress_Form(NPChar) + ", I am on duty.", "Just go by, " + GetAddress_Form(NPChar) + ", do not distract a guardsman from his duty.");
							link.l1 = "I was just checking, if you had fallen asleep - you were standing there just like a statue.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hey, " + GetAddress_Form(NPChar) + ", don't you happen to have a sip of wine to wet my throat? I am dying of thirst.";
							link.l1 = "Duty is duty. Keep your patience until you are relieved.";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("You're not the first sailor to distract me from duty. Hell, where are all those beautiful seductive widows...","Hello, beautiful! Wanna flirt with a brave soldier just a little") +"?";
							link.l1 = RandPhraseSimple("You must have forgotten that you were on duty, not in the brothel.", "Your business is to keep order... And stop drooling already.");
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("You look like a strong guy, don't you? Would you like to sign up for duty at the fort's garrison? We have roomy barracks, hearty meals and free booze.","Oh, young lady, you have no idea, how pleasant it is to meet such a nice damsel in this back of beyond!") +"";
							link.l1 = ""+ GetSexPhrase("That's certainly tempting, but I still must refuse. All that drill is just not for me.","Thank you for a compliment, soldier.") +".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Such heat... I would gladly give up half of my life to go back to Europe.";
							link.l1 = RandPhraseSimple("Yeah, you don't look much like a seasoned warrior.", "A soldier's duty is never easy.");
							link.l1.go = "exit";
						break;
					}
					link.l3 = "Just a second. I wanted to ask you something...";
					link.l3.go = "quests";//(перессылка в файл города)						
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("I suspect trickery... Come with me to the commandant, "+ GetSexPhrase("my friend","my dear") +", and we'll figure it all out...", "Hmm... Something tells me that you're not the one, who you're pretending to be... Now surrender your weapon, " + GetAddress_Form(npchar) + ", and follow me for further investigation!");
			link.l1 = RandPhraseSimple("Screw you!", "When two Sundays come in one week...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, I see... Everything seems to be in order, you're free to go, " + GetAddress_Form(pchar) + ".", "I must have got a bit tired of standing on watch... Everything seems to be fine, " + GetAddress_Form(pchar) + ", I am sorry.");
			link.l1 = "That'll teach you!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("Oh, I see... Everything seems to be in order, you're free to go, " + GetAddress_Form(pchar) + ".", "Let's see now... Well, everything seems in order, " + GetAddress_Form(pchar) + ", I am sorry.");
			link.l1 = "That'll teach you!";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Just come to think of it! Such insolence! To come here under the guise of a merchant! Your pictures are posted in every barrack, you bastard! You won't get away with it this time! Seize him!";
				link.l1 = RandPhraseSimple("Arrgh!..", "Well, you've asked for it...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (pchar.location != "Minentown_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "Have you come to trade here? May I ask how? Where is your ship? You know, it all looks very suspicious, and I am forced to detain you until we figure it all out. Surrender your weapons and follow me!";
				link.l1 = RandPhraseSimple("Fuck you!", "When two Sundays come in one week...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Your license has to be revoked since it is expired and is not valid for that reason. Surrender your weapons and follow me for further investigation!";
				link.l1 = RandPhraseSimple("Screw you!", "When two Sundays come in one week...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Everything looks okay. Still, I must note that your license expires today. I will let you pass this time, but you still will have to get a new license.";
				link.l1 = "Thank you, I'll get a new one at my earliest convenience.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Everything looks okay. Still, I must note that your license expires rather soon - it is still valid only for " + FindRussianDaysString(iTemp) + ". So keep that in mind, " + GetAddress_Form(npchar) + ".";
				link.l1 = "Thank you, I'll get a new one at my earliest convenience.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Well, everything looks fine. Your license is valid for another " + FindRussianDaysString(iTemp) + ". You may pass.", "Everything is clear, "+GetAddress_Form(npchar)+". You can freely go in and out of town, your license is valid for another " + FindRussianDaysString(iTemp) + ". Sorry for bothering you.", "Everything looks fine, " + GetAddress_Form(npchar) + ", I am no longer keeping you here.");
				link.l1 = RandPhraseSimple("Excellent. Best regards.", "Thank you, officer.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Hey, buddy, don't break anything in the lighthouse.", "A lighthouse is a very important town object. Be careful!");
			link.l1 = RandPhraseSimple("Alright, don't worry.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Don't walk close to the cannons - it is a military facility!", "Strangers are not allowed at the cannons!", "If I notice you hanging around near the cannons, you're done!");
			link.l1 = RandPhraseSimple("I got it.", "Alright, I got it.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "And just who are you, captain? Aren't you, by chance, a partner in crime of the most notorious thief in this settlement?";
			link.l1 = "Whom did you just call a partner in crime?! Are you sunstruck or what?! Hey, take your paws away from the girl!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Actually, I've "+ GetSexPhrase("got to know her","got to know her") +" recently...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+ GetSexPhrase("Sir","Miss") +", we have an order to detain her and take her to the dungeon. And if you think that you can stop us, you are mistaken.";
			link.l1 = "Let's see, then...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "Oh, really? In that case I would advise you to check your pockets. That lady is a professional, you know";
			link.l1 = "Thank you, I will do that. How could I make such a fool of myself...";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+ GetSexPhrase("Sir","Miss") +", we have an order to find that lady and bring her to her father.";
			link.l1 = "Well, an order is an order - go ahead, then.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Too late for that, because I am already taking to her father.";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Captain, we have an order, and if you think that you can stop us, you are mistaken.";
				link.l1 = "Let's see, then...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Heh, "+ GetSexPhrase("you're a lucky man","you're a lucky lass") +". Her father promised a generous reward to one who brings her back to him.";
				link.l1 = "Don't despair - you still have many rewards ahead of you.";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		
		//замечение по обнаженному оружию
		case "SoldierNotBlade":
			dialog.text = LinkRandPhrase("Hey, what's the deal with all that weapon swinging?! Put it away this instant!", "I order you to put away your weapon at once!", "Hey, " + GetAddress_Form(NPChar) + ", stop scaring the people! Put away your weapon.");
			link.l1 = LinkRandPhrase("Alright, I'll put it away...", "Already done.", "As you say...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Screw you!", "I guess I'm gonna use it!", "I'll put it away when the time is right.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}