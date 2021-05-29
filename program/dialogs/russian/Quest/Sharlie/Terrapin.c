// НПС по квесту Суп из черепахи
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
		case "First time":
			dialog.text = "What do you need?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "Lord colonel is participating in military exercise at the moment. What do you want from him, cap?";
				link.l1 = "This time, Ben, you're the one I need. I have bad news about your sister Molly. The beautiful girl is in hot water. She is captured by Tortuga pirates. She needs help and she has asked to warn you. The man who took it upon himself to pass on the message was killed, but before his death, he'd managed to tell me about your sister's request.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "If you're on your way to Colonel Fox, then keep on going the other way. He's not taking guests.";
				link.l1 = "Thank you!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "The colonel is not here. Come again later.";
				link.l1 = "All right...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "You are the very first who called my sister a beauty. God gave her a grenadier's stature and the Jericho's horn instead of throat. True! Our Molly can fight for herself\nBut our Lord's fantasy didn't apply to everything above her neck, the best thing he could think of is to stick a pockmarked face of late dad to those fine breasts. And I must say, sir, that his face used make horses fall down in a faint.";
			link.l1 = "I see you're not particularly upset...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "And why would she show up at Tortuga? Molly is a servant of Catherine, a daughter of our brave colonel, she was going to pay her father a visit by his anniversary. But the squadron her ship is a part of is delayed\nIf you want to see the true Molly Jones and her mistress, who is very beautiful by the way, come here in a month. Not earlier.";
			link.l1 = "It turns out that your sister Molly Jones has been serving Ms. Fox and at the present moment resides on the other side of the ocean?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "Exactly so! The last courier informed us that Cromwell's military squadron and a brig with Catherine aboard were supposed to leave London only a month ago. We will learn if it is really so from the coming mail. Though the ships haven't arrived yet and the colonel had strictly forbidden 'Albatross' to sail alone\nDid you know that his beloved wife died during an attack of French corsair? It wasn't easy for the colonel and he dreads the fire... So I can't help you with Molly Jones, captain! There are a lot of colonist girls named Molly! Having a surname Jones in Britain is as good as having no surname at all\nEvery dog at Antigua knows me and my commander. Not surprised that some poor girl who got in troubles wants my help. I'd like to, but I don't have coins for a ransom. I am living in debt, my salary for three months must arrive with 'Albatross'.";
			link.l1 = "Apparently, I'm mistaken indeed. But thanks anyway for the clarification.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "Not at all, captain.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("VOICE\Russian\sharlie\Rober Marten-01.wav");
			dialog.text = "What do you want?! I don't wanna talk.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "I've got some business for you, captain. I see that you're not in a cheerful mood and maybe my proposition will lighten you up a bit.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "Quiet down. Drink some rum. I'm mistaken, buddy. I'm sorry.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "The beginning of it sounds quite appealing! And your face looks like I've seen it somewhere too... I just can't remember where I saw you. Lay it on me!";
			link.l1 = "I'm aware of your business with Thibaut... Chill out! You don't have to fear me. I've got a deal to propose you.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "Damn it to hell! Fuck that drunk swine!... I didn't manage to...";
			link.l1 = "You've got that right. Your sailor was too much of a big mouth, but his rumours haven't got anywhere beyond me. And they won't get any further since you're the one that has taken care of it, haven't you?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "Caramba! I've recognized you now! You're that guy who washed up Colonel Doiley and took his whole island! You were involved in some large-scale schemes in the Dutch West India Company, you're rubbing elbows with a West Main baron.... Your name is... "+GetFullName(pchar)+", right?";
			link.l1 = "You possess some fairly accurate information. Yes, it is me. But could you calm down for a second, Robert!";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("VOICE\Russian\sharlie\Rober Marten-02.wav");
			dialog.text = "Argh! Well, how can I calm down, when one of the most famous schemers of the archipelago has taken an interest in me and not only that, but he's found out about my business too! What the hell got into me to attack this brig! What do you want from me?";
			link.l1 = "Cut it out and listen to me. It looks like we both want Levasseur's head on a stake. That pompous big-shot has known his day and has started to bother serious people. I intend to alter the balance of power on the island and put de Poincy in his place, but I don't want to spill any excess blood of any men from my homeland, not to mention because of some scumbag. You can help me. And I can help you and Thibaut keep your privileges.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "I can not believe my ears! You are right, we share goals. With you, it can go much more interesting... Thibaut is a good fencer, but he doesn't have balls to cut his uncle's throat. But such shark as you can do it. Your fame is well known\nI don't need your guarantees, but I will help you in return for the beauty. I need her as my hostage until I finish my business in the Caribbean. Soon, English frigates will start hunting me. The devil's got made me to attack that brig! It looked such an easy prey after the storm...";
			link.l1 = "What was so special about her? The girl you were concealing from Levasseur?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "Yes. You must convince Thibaut to part ways with the girl. I asked him to look after her until I clarified who she was, but this miss Jones, or whatever her name is, has completely spun his head around and now Henry is even hiding her from me. Bring that she-devil to me and I'll organize a meeting for you with Levasseur out of town. At that point, you'll have an opportunity to gank him. I'll be waiting at Fisheye Beach.";
			link.l1 = "Deal. Now tell me how to catch Thibaut.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "Tavern folks can show you way to his house. Henri is quite noted. Threaten him with an exposure and make him bring the prisoner girl to me. Same day I will let Levasseur know that his nephew is hiding a rare beauty in city dungeons\nMy courier will find you in a tavern. After he fails to find Henri, the governor will go to the dungeons with a small suite and you will have a nice opportunity to deal with him.";
			link.l1 = "Where shall I deliver the girl?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "Tell him to deliver her himself to the beach. I'll tell him a thing or two while I'm at it...";
			link.l1 = "All right. Consider it a deal. See you on Tortuga!";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "If everything goes as planned, we'll never meet each other again. I do hope. Farewell!";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
		break;
		
		case "rober_abordage":
			dialog.text = "Argh! I didn't see it coming... You've come for my soul, but we didn't argue at all, pal! I did everything as agreed! What the hell?!";
			link.l1 = "You had an order on you, Robert. The order was given to me. So I'm fulfilling my assignment.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "You devil! This is impossible! He couldn't have found everything out so quickly! And how did he even find it out?!";
			link.l1 = "You mean Fox? No. I am not from him. The colonel still doesn't even know you cut his daughter down. Your old buddy Henry Thibaut is the one that wants you dead. He hired me.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "Got damn secular papejoy! I should have iced him while he was on the 'Voltigeur'... How much did that rat promise you?";
			link.l1 = "It's not everyday that one gets to learn his price, is it Robert? Thibaut priced you at a quarter million, but I convinced him that you cost more. So your cost is equal to a hold sack of silver three hundred thousand pesos. Are you glad?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "Wait a second... Let's make a deal! I'll pay you more!";
			link.l1 = "Out of what funds, Robert? I'm absolutely sure you're lying. You don't have that much money as Henry promised me. And that's not the main thing anyway. If it wasn't for one fact, I would've refused his proposition to hunt you down and end your dirty affairs with Thibaut.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "What fact is that?";
			link.l1 = "You killed the girl. Her guilt was nothing more than being Colonel Fox's daughter. I hate scumbags that put defenseless women to death! So I'm not making any kind of a deal with you. I won't even consider it. Don't hold your breath.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("VOICE\Russian\sharlie\Rober Marten-03.wav");
			dialog.text = "Fuck! But what did I have to do?! I couldn't let her away alive and ship her endlessly on the boat! And who are you... you con artist, you schemer, you hitman to lecture me about morals! Take a look at yourself! At your 'methods'! You're not better than me! By no means!";
			link.l1 = "Enough. Martene, draw your blade! It's time we wrap this duel up.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "Screw you!";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("VOICE\Russian\sharlie\Henry Thibault-02.wav");
			dialog.text = "What are you doing in my home, sir?";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. I have arrived from a man you know. His name is captain Robert Martene.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "Hm. And? So?";
			link.l1 = "Captain Martene awaits you right now on Fisheye Beach. But not alone. He would also appreciate a glimpse of Molly Jones in your company. Do you understand what I mean?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("VOICE\Russian\sharlie\Henry Thibault-01.wav");
			dialog.text = "Alas, sir, I don't. I've never heard of any Molly Jones and Robert has never had a need to send a parlementaire to me who I've never seen before. For your information, monsieur, I am the second man here after my governor uncle, so...";
			link.l1 = "Life is an unpredictable beast, Henry... Right now you are the second man on the island and in a couple of hours you could be in shackles in the casemates for the life of whom nobody will give you a single peso. You have transgressed on your uncles order, haven't you, monsieur Thibaut? What's more important to you: a rootless girl or your precious life?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "Huh.. You're talking through your hat!";
			link.l1 = "You, just like anyone else must know your uncle's temper. Levasseur will find out that you are hiding the girl before the sun sets. Don't ask me how Robert found that out, just heed my words: he's scared to death and ready to pull up his anchor right away. He didn't dare to even enter the town and paid me a hefty sum to deliver this message to you.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "Damn... It can't be!";
			link.l1 = "It's up to you, sir. Martene will not wait for you any longer than two hours. He values the head on his own shoulders. It's only as a sign of your friendship that he's still sticking around the Tortuga shore and not hiding somewhere with the Dutch.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "Caramba! How could my uncle find that out?";
			link.l1 = "Tongues, Henry. Long tongues. Even I know that you and Robert hid the beauty from Levasseur that came off the English brig seized by your buddy. Do you really doubt that I'm the only one informed about this story?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "Looks like you're telling the truth, sir. Tell Martene...";
			link.l1 = "I don't think you understand, Henry. Martene isn't going to wait for you. Your only hope is to bring the girl out of here, the reason both you and Robert have egg all over your faces. Run over there where you're hiding, grab her by her pretty little hands, and take her over to the Voltigeur. Unless you find her, your uncle won't manage to present you a thing.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "All right. We'll do that then. Thanks for your help, sir! Off I go!";
			link.l1 = "No need to thank me, monsieur. My work is paid for... I wish you to make it out of the water dry.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("VOICE\Russian\sharlie\Henry Thibault-02.wav");
			dialog.text = "What are you doing here, sir? I didn't invite you here.";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. I have arrived from a man you know. His name is captain Robert Martene.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "Hm. And? So?";
			link.l1 = "Captain Martain awaits you right now on Fisheye Beach. But not alone. He would also appreciate a glimpse of miss Catherine Fox in your company. Do you understand what I mean?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "Alas, sir, I don't.";
			link.l1 = "That's what I was expecting you to say. Of course, I highly doubt you could have previously been introduced to Colonel Fox's daughter, commander of the Sea Foxes... Damn these  games! You and Robert have stirred up so much trouble that I doubt you'll stand the racket! The girl captured from the English brig that you've been concealing from Levasseur that you know as Molly Jones is the daughter of Colonel Fox, Catherine Fox!";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "What?";
			link.l1 = "You've turned somewhat pale, sir. So listen to me closely, Henry, and pay attention: you and your buddy Robert are in deep shit. From week to week, Cromwell's military squadron arrives to the Caribbean. Only its flagship is capable of carrying your vaunted La Roche in a couple hours. What do you think? Is the attack of the English brig and the captivity of Fox's daughter reason enough for this?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "But that's not all. Your schemes have become known not only to me. Your governor uncle will find out that you're transgressing on his order and concealed a girl from him that the old coot would definitely have wanted to take for himself. What do you think, Henry? What will your uncle do to you? You must know like no one else how sharp his temper must be...";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "All lies!";
			link.l1 = "Is it? My dear, you can ask your friend Martene. He was the one that sent me to you. Levasseur will find out that your hiding the girl before the sun sets. Don't ask me how Robert found that out, just heed my words: he's scared shitless and ready to pull up his anchor right away. He didn't dare even come into the town and he's asked me to deliver you this message.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "Martene will not wait for you any longer than two hours. He values the head on his own shoulders. It's only as a sign of your friendship that he's still sticking around the Tortuga shore and not hiding somewhere with the Dutch. However, that poor fellow Robert doesn't even suspect who Molly Jones really is. Same with me, women's fashion connoisseurs! You couldn't distinguish a noble lady from a commoner!";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "What do you want?";
			link.l1 = "Well, finally some wise words from your lips! All right, Thibaut: make your way over where you're hiding her right now, take her gently by her lily hands, and walk with her onto Fisheye Beach where Martene's Voltigeur is. Tell him your plans have changed...";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "Martene must fulfil his promise to me, but he shouldn't even try to take the girl on his own ship. She has to to stay at bay and wait for me. Tell Robert that if he doesn't fulfil his obligations, or takes away Catherine, or if one hair-spring falls off her pretty little head, I will spend the rest of my life to find him and to deliver her to Colonel Fox... alive. Yes, by the way, that includes you as well, Thibaut.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "Who I am and what my opportunities are, you can ask Robert about. He's well aware. If you both will do as I said, then we all win: Robert will be able to continue his pirate business and you will preserve all your priveleges and receive the inheritance of your dear old uncle. As for me... I won't come off a loser either. Is that all clear?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("VOICE\Russian\sharlie\Henry Thibault-03.wav");
			dialog.text = "I'd rather burn in hellfire than do your bidding... "+GetFullName(pchar)+"! And how didn't I recognize you in the beginning! You're surely not planning of leaving neither me nor Robert alive! Your 'methods' are widely known! There's no way I'm giving up Molly... or Catherine for that matter! And you won't leave Tortuga alive, fucker!";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "Stop, coward!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("VOICE\Russian\sharlie\Henry Thibault-04.wav");
			dialog.text = "Well, finally! Captain "+GetFullName(pchar)+", I'm very pleased you've come. Come in, have a sit. Anything to drink? I've got quite a lucrative business proposition for you, captain...";
			link.l1 = "Well, aren't you in the most courteous of moods today, Monsieur Thibaut... Let's not sit around. Let's get right to the crux of the matter.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "The proposition concerns my former friend and companion that you know as Robert Martene, former captain of the 'Voltigeur' galleon...";
			link.l1 = "So, you and Robert are no longer buddies? Fascinating!";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "Captain, please, hear out my motives for seeking your assistance and it'll all become clear. As you know yourself, Martene has grappled with an English brig and captured as a prisoner an English woman, some servant known as Molly Jones, the reason why all this trouble ended getting stirred up.";
			link.l1 = "Of course, I know. As I understand, you have fulfilled my recommendations and led the girl to Martene's ship?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "Yes, I did it. But I regret it every day. Know that Molly is a very charming and beautiful girl, I have never met anyone like her before. I admit, I fell in love with her. She liked me too, she said it herself! I couldn't let uncle to take her\nWhen I was escorting her to the 'Voltigeur' I hoped that uncle will settle down as soon as he finds out that no one is hiding girls from him. Then Robert would take her back to Tortuga, so I could move her to my place. Anyway, that was a deal I made with Martene. But it turned out differently\nWhen I learnt that my uncle got killed, there was no point to hide Molly, so I started to wait for the 'Voltigeur' to arrive with Molly aboard.";
			link.l1 = "Has she arrived?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "Yes. Unfortunately, Molly wasn't on the ship. Robert behaved as if he was butting heads with Lucifer himself. During this short-lived expedition, he somehow found out one terrible detail: the girl, Molly, was not Molly Jones at all, but Catherine Fox! Colonel Fox's daughter herself, commander of the Sea Foxes, the elite English marines! You know what that means!";
			link.l1 = "How about that! Undoubtedly then, Robert has something to be afraid of. But how could it have turned out that way?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "When Catherine was taken into captivity, she intentionally hid her identity pretending to be Molly Jones, a girl that died during the boarding. She was afraid that Martene would find out would who she really was. And she managed to deceive him. But during the last voyage, Robert somehow found out who she really is. He said that he found some letters of hers, or papers...";
			link.l1 = "And where is the girl now if she didn't embark on 'Voltigeur'?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "She's dead. Frightened by the eminent punishment from Fox for attacking the English brig, Martene decided to hide the evidence in the water. She was the last witness of his attack on the 'Albatross'.";
			link.l1 = "Then he might as well have murdered all his sailors... Like Fernand Luc. Otherwise, they'll get drunk one day and open their mouths a little too wide at the tavern...";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "He feels that his whole crew is sworn to him in blood. Maybe he's partially right. But I know Colonel Fox! He'll keep digging until the end of his days to find out who kidnapped his daughter!";
			link.l1 = "I don't even doubt that. Especially after the French pirate killed his wife. Now his daughter too... By the way, are you absolutely sure, monsieur, that Catherine is really dead? Maybe, Robert hid her from you somewhere.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "I'm sure. I spoke with a sailor from the 'Voltigeur'. I believed him. He saw it with his own eyes how they slit the girl's throat and then tied a cannon ball to her feet and threw her overboard.";
			link.l1 = "Yup... Dang. Poor lady. But what do you want from me, Henry?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "I can't sleep at night ever since that day. I see Molly all the time before my eyes... Catherine, rather. I led her to her death by myself! I can't forgive myself for that. Other than that, I don't entertain any illusions about Fox. Sooner or later, he'll hop on Martene's trails, make somebody talk, and when he finds out who killed his daughter all hell's going to break lose. It'll go hard on anybody who was one way or another connected to the whole story.";
			link.l1 = "That includes me.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "Me too. That is why I want you to find Martene before Fox does. Find the bastard and kill him. And make him suffer first if you can. For poor Catherine. When it's done, cut his finger with a ring and bring it to me as a proof\nI know his crooked finger well and the ring. If you do that, I will pay you quarter million in silver.";
			link.l1 = "Looks like you've received a large inheritance from your dear old uncle resting in peace, huh? Tell me, Henry, why did you decide to ask me to help with this matter?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "Because I have learnt some things about you too, "+GetFullName(pchar)+". It was easy, you are a famous man. It is unknown whom you are really working for though, either for de Poincy, or for the Dutch, or for the English or for a pirate Jan Swanson... But one thing is clear: you take delicate, well paid jobs and get them done. And you are not connected to the Spanish\nAfterall, you also took part in the events after which I have inherited my uncle's fortune. Don't deny it... Quarter of million is good money. I will tell you where to find Martene. You only must intercept his ship and board her.";
			link.l1 = "Up the fee by another hundred thousand and I'll take to your problem.";
			link.l1.go = "tibo_34";
			link.l2 = "Alas, Monsieur Thibaut, you'll have to take care of your problem with Martene and Colonel Fox without my participance. I, from my side, promise you that I will not send any word to the colonel about the fate of his daughter and those that are guilty of her death. All the best, sir.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "Sir, fear God... I don't have millions stored up in treasure chests, believe me! I understand that your services cost money, which is why I offered you two hundred fifty thousand right off. All right, how about I add another fifty thousand gold. I just can't offer you any more!";
			link.l1 = "Fine. You've got yourself a deal. Tell me what you know when was the last time you saw Martene?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "He moved to the Spanish to Caracas and managed to seek an audience with don Diego Francisco de Kerres, the governor. It seems that he has bribed him somehow because don granted Robert a protection of the Spanish crown. He sold his galleon. Now he is a captain of heavy galleon 'Infanta'. Looks like Martene had really good savings since he could afford to bribe the governor and to buy and equip a large military ship\nSo, he will sail from Caracas to Santo Domingo on his new ship as a part of Spanish squadron. That is all my agent had managed to find out. The only opportunity to get Martene is to catch up the Spanish squadron\nIf they reach Santo Domingo, it is over. No clue where Robert will go next.";
			link.l1 = "Got it. I'll intercept them.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "And don't forget about the finger with the ring! That's an obligatory condition of our agreement! I want to be absolutely sure that Robert is dead!";
			link.l1 = "All right. Let's not waste any time let's move out to sea at once!";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "Is Martene stinking up the Caribbean with his presence, captain?";
			link.l1 = "He hasn't got long!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "Is Martene stinking up the Caribbean with his presence, captain?";
			link.l1 = "Not anymore. You may fear Colonel Fox no more and that poor girl Catherine is avenged. Here is your proof.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "Yes... That is Martene's finger, without a doubt. You never cease to impress, captain "+GetFullName(pchar)+"! You truly deserve the reputation you are given.";
			link.l1 = "Let's get to the payment, shall we, Thibaut?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You've received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "It's all ready. Here, take your reward.";
			link.l1 = "Great! I'm glad you were able to take care of that ahead of time. I wish that you to not fall into further scrapes like this in the future and you better way of picking your friends. All the best!";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "Thank you for your help, captain! I'll recommend you to all my friends. Good luck!";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "Yes, monsieur "+GetFullName(pchar)+"? Do you have some business with me?";
			link.l1 = "No, monsieur Thibaut. Just decided to stop by for a moment. Goodbye!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "Ah, "+GetFullName(pchar)+"...Come on, what's taking you so long! Now, who the hell knows where Robert Martene is?! If Colonel Fox manages to find eveything out, I think I'll be in a deep trouble...";
			link.l1 = "I see. I was too late. My apologies, Monsieur Thibaut, but I was delayed by some very pressing matters. I'm not going to waste your time. Goodbye.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "What do you want, "+GetFullName(pchar)+"? I don't have time to chat. I've got bigger fish to fry. I have to find Martene before Fox does...";
			link.l1 = "Yes, yes. I'm on my way.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "Are you captain "+GetFullName(pchar)+"?";
			link.l1 = "You've come to the right man, buddy. I'm all ears.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "Your debtor has requested me to tell you that the deed is done and the fish will swim into the net no later than in one hour. So make haste.";
			link.l1 = "I understand. Thank you!";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "Why the hell are you wandering around here? Who are you? Answer me now!";
			link.l1 = "Who the fuck are you and why are you asking me such stupid questions?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "What?! You snotnose! Who am I? I'm the governor of this island, Francois Levasseur, Senior de Renet de Boidouflet de Lettre! And everything on this island is in my jurisdiction! And including you while you're walking on my turf, worm!";
			link.l1 = "Wee-hell... The big bad wolf, huh? You're a little lost, Levasseur, Senior de Renet de whatever. Your time is up. By order of governor-general Francois Longvillier de Poincy you've been removed from your post and sentenced to your immediate death! I am your judge and your executioner in one! Any last word?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "I suppose you're not going to give up and asking me for mercy won't work as well, so go on and get out your sword! You are my job, nothing personal.";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "Fuck! It's a ratbag agent of de Poincy! Take out your weapons! Kill him!";
			link.l1 = "Let us dance?";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "What the fuck are you doing here? Who are you? Answer me, now!";
			link.l1 = "How about that! Didn't see that coming... Monsieur Levasseur himself, I presume?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "Yes, I'm the governor of this island, Francois Levasseur, Senior de Renet de Boidouflet de Lettre! And everything on this island is in my jurisdiction! And including you while you're walking on my turf, you scoundrel! Answer the questions you are asked! Sergeant lock this door. This character seems awful fishy!";
			link.l1 = "You are incredibly insightful, monsieur Levasseur, Senior de Renet de whatever. My presence here won't come to you as any kind of delight. By order of governor-general Francois Longvillier de Poincy you've been removed from your post and sentenced to your immediate death! I am your judge and your executioner in one!";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "I suppose you're not going to give up and asking me for mercy won't work as well, so go on and get out your sword! You are my job, nothing personal. Just serving the state, ha! Sergeant, I don't advise you to interfere while I will carry out the governor-general's orders!";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "Don't listen to him, sergeant! It's a Spanish agent! Kill him! Guards, help! There are Spaniards here!";
			link.l1 = "Never been to Spain, actually.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "Ouch! A little help here! Help me! Soldiers!";
			link.l1 = "Quiet down, you imbecile! If you don't scream, I won't do anything to you!";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "Don't kill me!";
			link.l1 = "Don't be stupid! A man just ran by here ten minutes ago. A well-dressed noble. Where is he hiding? And don't even think about telling me you didn't see him!";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "Monsieur Thibaut?";
			link.l1 = "Well then, so you know him! Where did he run to? Are you going answer or should I give your head a good shake to get it working?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "Oh, don't hurt me! Monsieur Thibaut ran away, that way toward the sea. And he jumped off of the hoist right into the water. He probably died, it's so height...";
			link.l1 = "I don't think so. He's not the type that would commit suicide. And you should walk inside. There's no reason to hang out here...";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "Ouch! A-ouch! Don't shoot!";
			link.l1 = "What?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("VOICE\Russian\Armo02.wav");
			dialog.text = "Who are you? Have you come to kill me or maybe save me, although I wouldn't dare count on it?";
			link.l1 = "I do hope to save you as I'm intending on returning you, Catherine Fox to your father in St. John's. If he gives you a lashing after that for disobeying, then my guilt will be repeated. However, I do hope that the colonel will be happy to see his daughter alive in spite of her airiness running into all that trouble.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "How sweet! Do you know who I am? You are a Frenchman and nevertheless have decided to come here to drag me out of the paws of my countrymen? You've risked your life just for Colonel Fox's daughter?";
			link.l1 = "My fundamental mission on Tortuga was quite different. But I couldn't leave a girl, a noble lady, in the hands of a bunch of scumbags either.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "You are a noble gentleman! What is your name, monsieur?";
			link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "Tell me captain. Do you really want to take me to my father in St. John's?";
			link.l1 = "Yes, although he doesn't take to well to Frenchmen. However there are Englishmen that are scumbags and hounds as well, and what is more English officers. I was a witness to at least one of them... Richard Fleetwood was his name.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "If we make it to Antigua, I'll do everything I can to convince my father that there are true knights among Frenchmen.";
			link.l1 = "I would quite appreciate that... All right, I hope that my dashing eagles have watched my trail along the city housetops and are already looking for us.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("VOICE\Russian\Armo01.wav");
			dialog.text = "I couldn't believe that you are going to keep your promise until now! Too much disgusting things had been happening around me for a while. I thank you, captain, for returning my faith in people and nobleness. You should visit my father when you can!\nHe always respects people like you. And it doesn't matter that you are French. I will do everything to persuade my father to reconsider his attitude to your nation.";
			link.l1 = "Thank you, Catherine. Maybe I will take advantage of your courteous offer.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "I do hope you will, captain. A huge thanks to you once again for what you've done for me. I'll never forget it.";
			link.l1 = "Go on, hurry up to your father. He'll be quite thrilled to see you. Maybe he's already returned from his training. Well, anyway it's time for me to go. Goodbye!";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "There you are, cap! You had us worried sick! A dash like that along the housetops and a jump like that from a gut-wrenching height was hard to expect! We were concerned about you...Welcome on board, cap, the longboat's ready!";
			link.l1 = "Great. Catherine, follow me!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "Hello, monsieur. Are you the captain "+GetFullName(pchar)+"?";
			link.l1 = "Yes, it is me. What's going on?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "Phew, I barely caught up to you... I've come to you on behalf of a gentleman you know by the name of Henry Thibaut.";
			link.l1 = "Henry? And what does he want? To share his joy on account of his inheritance unexpectedly flopping onto him following the death of his late dear uncle?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "Monsieur Thibaut has urgently requested that you come visit him at his mansion on Tortuga as soon as possible. He has well-paid work for you. He also told me to mention one name to you: Robert Martene. That is a spark of little interest for you.";
			link.l1 = "Is that so? And what gave Henry that idea?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "Also if that didn't convince you to come visit him already, he further requested that I add the following: 'Robert Martene must die'.";
			link.l1 = "Alright, alright... Now it's getting interesting. Two sworn friends just got into an argument... Whatever, I'll try and visit Henry when I get the chance.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "Monsieur Thibaut has asked you to not delay with your visit. 'The fish may swim out of the nets in ten days' were his exact words...";
			link.l1 = "He and Robert have the same manner of speaking. All right, I'll pay Henry a visit.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
