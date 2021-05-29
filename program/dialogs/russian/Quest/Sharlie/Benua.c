// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "It`s good to see you, my son.  You are here to wipe away your debt?";
				if (GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Yes, father. I am.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "I am sorry for the delay, but I am not. But I will, don`t you worry.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Is there anything you need, my son?";
				link.l1 = "Yes, father. I would like to see my brother, Michel de Monper. He said...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Is there something you need, my son?";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // еще не виделись
			{
				link.l1 = "Yes, pater. I need your help. My name is "+GetFullName(pchar)+". Michel de Monper advised me to talk to you.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // еще не виделись
			{
				link.l1 = "Yes, father. I need your help. My name is "+GetFullName(pchar)+". I was advised to talk to you by my brother, Michel de Monper.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Yes, pater. I need a ship to help Michel yet I have just recently arrived to the Caribbean and my purse is empty. My brother told me you could lend me some money...";
				link.l1.go = "FastStart_2";
			}
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Yes, father. I need your help.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && GetCharacterItem(pchar, "gold_dublon") >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Yes, pater. I am.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "No, nothing, father.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			dialog.text = "What brings you to me, my son?";
			link.l1 = "Hello, father. I was advised to talk to you. My name is Charles de Maure. I am searching for Michel de Monper. As far as I know, he should be somewhere here on Martinique. I'm... his brother.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Michel de Monper's brother? De Maure? How strange...";
			link.l1 = "I understand your doubts, father. We simply have different surnames. My father is Henry de Monper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "A-ah, I see now. I used to know Henri de Monper personally. Turn yourself to the light, young man. Right! You look just like him. The same looks, the same noble features! I am glad to see a son of Henri de Monper in our parish\nAnd concerning your question I will tell you that Michel is a high-ranked officer of the Order of Malta, but he is... in trouble. Come here tomorrow, my son, and I will introduce you to one man, I believe he will be able to get you to your brother. Go to the tavern now, take some rest.";
			link.l1 = "Thank you, father. I will be here tomorrow morning.";
			link.l1.go = "Benua_meeting_3";			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "My son, come tomorrow at morning. At the moment, I have nothing more to tell you.";
			link.l1 = "All right.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		case "Benua_maltie":
			dialog.text = "Hello, my son. As promised, the person you need is already here waiting for you. He's ready to bring you to your miserable brother. May the Lord have mercy on his soul...";
			link.l1 = "Who is this man, holy father?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break;
		
		case "escape":
			dialog.text = "Yes, Charles, I'm aware of that. But I must disappoint you. Michel is not here.";
			link.l1 = "What do you mean he's not here? He said that he'd be waiting for me in your church! Father, what happened? Where's my brother?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "My son, your brother was here and he left my modest tabernacle late last night. Where he went, I don't know. But he's left for you this letter.";
			link.l1 = "I can't believe it... after what I did for him! Give me that letter!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Don't get so enraged, Charles. Here's the letter. Read it and then... then I would like to speak with you. But first read your brother's message.";
			link.l1 = "I'm burning from impatience!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "I see you've read the letter. Now I would like to tell you something, Charles...";
				link.l1 = "But... how can that be? What kind of balderdash is this? I know my brother is peculiar, but he's not a madman!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "My son, read the letter. We'll speak later.";
				link.l1 = "Yes, father...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Your brother's actions surprised me as well, Charles. In addition, I still have my moments of perplexity. A loyal servant of the Order and the Trinity and he's behaving like a deserter.";
			link.l1 = "Do you have any idea what is the reason of such strange behaviour?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Alas, I don't. But I suppose that he has motives of his own, deep motives. For abrogating one's entire past would suggest an extremely significant reason. I can't even imagine what it is. But I feel, that it involves something extremely bad... even awful.";
			link.l1 = "What could it be, father?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "My son, a priest sees not with his eyes, but with his heart. I cannot explain to you in words, but... you brother has set forth to do something unclean. I never thought my mouth could utter this, however...";
			link.l1 = "Well, I don't doubt that my brother has planned something unclean. I can even get what is exactly he's planning to do. This 'something' involves something yellow and makes a nice clink sound.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "I don't think the lust for gold is what drives your brother. I would say that he needs something bigger.";
			link.l1 = "I have learned a lot from Michel and have a grasp on his philosophy, so I can assume what's important to him and what isn't. But I will keep your words in mind, reverend father.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "God bless you, my son. Go, now. May the Lord watch over you!";
			link.l1 = "Thank you, father. Goodbye!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			pchar.questTemp.Sharlie = "escape";
			CloseQuestHeader("Sharlie");
			AddQuestRecord("Guardoftruth", "1");
			pchar.questTemp.Guardoftruth = "begin";
			// ставим пленного испанца
			sld = GetCharacter(NPC_GenerateCharacter("spa_baseprisoner", "q_spa_off_1", "man", "man", 30, SPAIN, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_13", "pistol1", "bullet", 150);
			sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
			sld.dialog.currentnode = "spa_prisoner";
			RemoveAllCharacterItems(sld, true);
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest1");
			LAi_CharacterDisableDialog(sld);//запрет диалога
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Michel de Monper's brother? De Maure? How strange...";
			link.l1 = "I understand your doubts, father. We simply have different surnames. My father is Henry de Monper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "A-ah, I see now. I knew Henri de Monper personally. Turn yourself to the light, young man... Right! You look like him. Same looks, same noble side view! I am glad to see a son of Henri de Monper in our parish\nI have already heard that Michel was visited by some man arrived from Europe, but I couldn't even imagine that it was his own brother. I hope that you will be able to help Michel, he is experiencing a difficult time. So how can I be of service?";
			link.l1 = "Michel told me that you would be able to help if I got into specific troubles with the authorities.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "That is what Michel told you? I see. Well, I can be of some help in such matters. I have some influence within Holy Roman Church and Dutch colonies. Therefore I might to intercede for you to the Spanish and the Dutch authorities. Surely, I won't be able to do much if your misconduct is too heavy - in that case only a slight extenuation can be achieved\nIt will require several intercessions for a complete reconciliation. Besides, you will have to supply me with golden doubloons for charities and for voyage spendings. Only one nation at one go, of course. If you find it acceptable then don't hesitate to turn to me, we'll see what can be done.";
			link.l1 = "Thank you! I'll keep that in mind.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "What can I do for you, my son? Speak, I am listening.";
			link.l1 = "Michel told me that you would be able to help if I get into specific troubles with the authorities.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "How can I help you, my son?";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "I've got into troubles with the Spanish authorities.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "I've got into troubles with the Dutch authorities.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Sorry, I think I'll handle things myself.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "So, the noble seniors are eager to put you inside Havana's dungeons...";
			link.l1 = "Exactly so, father...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "So, the smart merchants are eager to put you inside Willemstad's dungeons...";
			link.l1 = "Exactly so, father...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Yes, those rumours have reached our church as well. I can help you with your dilemma. It's something that can be solved. I need two hundred fifty gold doubloons to smooth out the predicament.";
				if (GetCharacterItem(pchar, "gold_dublon") >= 250)
				{
					link.l1 = "Great! Here's the gold.";
					link.l1.go = "agree";
					iTotalTemp = 250;
				}
				link.l2 = "Then it's just the right time for me to find the coins.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Yes, rumours of your 'feats' have reached our church as well. You've tarnished your reputation, my son. You should be more prudent. But I can help you. I need five hundred gold doubloons to smooth out the predicament.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 500)
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
						iTotalTemp = 500;
					}
					link.l2 = "Then it's just the right time for me to find the coins.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Yes, my son. You're just as desperate as your brother... This is probably a family trait. I can't completely correct the situation, but nevertheless, I believe I can soften your dismal predicament. And later we will make more offering if you wish. I need six hundred gold doubloons and I will begin solving your dilemma right away.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 600)
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Then it's just the right time for me to find the coins.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveItems(pchar, "gold_dublon", iTotalTemp);
			Log_Info("You've given "+iTotalTemp+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Now wait at least two weeks. I think that in this time I'll be able to meet and have a word with the right people.";
			link.l1 = "Thank you, father! I will be waiting...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, 10+rand(5), false);
			pchar.GenQuest.BenuaNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? And you are a brother of Michel de Monper? Odd...";
			link.l1 = "I understand your doubts, padre. My father is Henri de Monper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "A-ah, I see. I knew Henri de Monper personally. Turn to the light, young man. Right! Same eyes, same noble features! I am pleased to see a son of Henri de Monper in my church. Hope you will help your brother out. He had a bad luck recently.";
			link.l1 = "Yes, pater. I need a ship to help Michel yet I have just recently arrived to the Caribbean and my purse is empty. My brother told me you could lend me some money...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			dialog.text = "Michel told you so?";
			link.l1 = "Padre, it may sound not trustworthy yet it's true. The sooner I get a ship, the sooner I will get my brother out of jail.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "I see, my son. I can hear you speaking the truth. Well, for the sake of Michel and your father I will help you out. I have some saving, take it. I assume 50 000 pesos and 100 doubloons will suffice.";
			link.l1 = "Thank you, padre. What are the terms?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "No pressure. A half of a year will be enough.";
			link.l1 = "Very good, holy father. Thank you again!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Go with my blessing, my son.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Splendid, my son. Hope that money did you some good.";
			link.l1 = "You bet they did! Thanks!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveItems(pchar, "gold_dublon", 100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, I can't believe my eyes! What brings you here?!";
			link.l1 = "Bless me, Holy Father, cause I am with good news - I am getting married, and would like to see you as a priest at my wedding.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "My son, this is wonderful! So you received that letter from your father and decided, as always, to act according to your own understanding? I am sincerely happy for you! But I'm afraid I can't help you unless you decide to get married exactly in this church.";
			link.l1 = "I understand that your mission is at an impasse, Holy Father? Can I help you with anything, since the marriage in the Spanish chapel, of course, is an adventure I would like, but I am determined to hold a celebration in Martinique. Moderately magnificent, and in the presence of reputable witnesses and honorable guests.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "I'm sorry, my boy, but all your authority is nothing before the stubbornness of the highest hierarchs of the Catholic Church, especially in the Spanish colonies. We didn't agree on the question of sharing the influence of the Catholic missions of our countries, and now I'm here a cross between an honored guest and an honored hostage. The Spaniards are waiting for a better offer from our side. I sent a message to Europe, two months later the answer will come and we will resume negotiations. Maximum - in six months\nYes, the Pope and Mazarin come to a compromise, but it's too early to talk about the real warmheart relationships. Honestly, I'm not sure that we will come to any agreement here at all. It seems to me - Palotti simply keeps the French abbot as an argument in his own politics. However, the inquisitor has got excellent coffee!";
			link.l1 = "I don't have not six months nor even two months! I must fulfill the will of my father, until he finally married me without my agreement. And his health isn't good as it used to be, but I would like to have time to introduce him to my chosen one and future lady of Monper.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "I'm afraid you will have to find another priest for your wedding, my son. Alas, I’m here for a long time.";
			link.l1 = "What would you say if I apart you and the inquisitor's coffee?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "I would gladly accept your help. I suspect that I wasn't chosen for this mission by chance, in bad case, they'll just forget about father Benoit. And, although the Lord commanded to endure, but I am burdened with my conclusion, despite all its... blessings. But, I repeat - Father Palotti unlikely will listen to your requests.";
			link.l1 = "Than I'm going to save my time and I will not try to convince him. We will just leave the church when the service is over and go to my ship. Don't hesitate, Holy Father - they saw our meeting and they could recognize me, and it will be much more difficult to help you to get out from the governor's mansion.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "It's risky, my boy. Very. An escort group is waiting outside to escort me to the mansion, and the city is full of soldiers.";
			link.l1 = "An element of surprise, Father Benoit. I'm good in this - trust me and everything will be fine. In such matters, I have some... experience.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "As you wish. And I would like to ask you to do it without unnecessary bloodshed, but I, too ... had some experience of this kind. So lead, my son. I'm right behind you. But I won't take up weapon, and don't even ask.";
			link.l1 = "Didn't even think, Father. I can handle it. Follow me, but be careful - perhaps, they will shoot at us.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "My son, I didn't have time to thank you for my release. Apparently, the Spanish bishop and the Inquisitior Palotti wanted to disrupt the barely established relations between our cardinal and the Holy See, so you acted completely in the interests of the country. Again. But no one will tell you 'thank you', except me.";
			link.l1 = "Common thing, Holy Father. Glad I managed to help. But, I also have an ask, remember?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Of course! So let's get to the pleasant business - Charles, how are your preparations for such an important day?";
			link.l1 = "Little by little. I knew military campaigns that were prepared easier and faster, but it's worth it!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Sure, my son! And, on this occasion, I want to clarify one moment - how do you see your wedding ceremony?";
			link.l1 = "You mean, how pompous?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Of course, because I must prepare the church, perhaps, you'll want to invite important people.";
			link.l1 = "Nothing special, Holy Father. Those, whom I consider as friends, will be waiting for us elsewhere. Here will be only a few officials, my guys, and ordinary onlookers.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Well, then, I think, we will manage with a small donation.";
			link.l1 = "That doesn't sound scary. And how much is donation in gold?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "For the choir, solemn service, and other expenses - one hundred and a half, nothing more. Plus, the usual donation from the newlyweds, in total - two hundred.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "Here you go, Holy Father.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "About military campaigns... I should take a walk to the bank and return.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "What about the donation, my son?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "Here you go, Holy Father.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Yes-yes, I'll bring it soon...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveItems(pchar, "gold_dublon", 200);
			dialog.text = "There is still a question that needs to be solved - who will be giving away the the bride and testify to the marriage on her part?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson, from Blueveld. He is an Englishman, but a respected person and attached to Helen as his own daughter, and her adoptive mother is Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Baron Noel Forget, I'm sure, he will do me such an honor.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Chevalier Philippe de Poincy, I'm sure, he will do me such an honor.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Well, and who will testify from the groom? Remember, this must be a man of noble birth and a worthy reputation.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Baron Noel Forget, I'm sure, he will do me such an honor.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Chevalier Philippe de Poincy, I'm sure, he will do me such an honor.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey - respectable merchant from Guadeloupe. I only need to stock up on his favorite booze.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey - respectable merchant from Guadeloupe. I only need to stock up on his favorite booze.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Great, I will send out invitations, but guests will need some time to get here. I think, not later than in a month everything will be ready, and the indicated persons will arrive to the city.";
			link.l1 = "So I have time to settle a couple of doings. See you soon, Holy Father and wish me good luck!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Great, I will send out invitations, but guests will need some time to get here. I think, not later than in a month everything will be ready, and the indicated persons will arrive to the city.";
			link.l1 = "So I have time to settle a couple of doings. See you soon, Holy Father and wish me good luck!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Great, I will send out invitations, but guests will need some time to get here. I think, not later than in a month everything will be ready, and the indicated persons will arrive to the city.";
			link.l1 = "So I have time to settle a couple of doings. See you soon, Holy Father and wish me good luck!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "So, this day has come, my boy! Everything is ready - in a couple of hours we'll be able to start. You look pale!";
			link.l1 = "I’m little nervous, Holy Father.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "It's a common thing. This is the most important day in your life, and I am sincerely happy for you, like everyone who came here. I hope you remembered at least the basic prayers - you haven't ever spoiled the church with your attention, have you? However, I will help in any case\nAnd one more thing - as I understand it, the bride won't change her principles and we will not see her in the dress? Well, high society is about to see another surprise from you - you are full of them. And now , go, my son, bring yourself in the proper form and we will begin.";
			link.l1 = "Fine, Holy Father. Let's do it.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Pater noster, qui es in caelis, sanctificetur nomen tuum, ad...";
			link.l1 = "...adveniat regnum tuum";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...fiat voluntas tua, sicut in caelo et in terra. Panem nostrum quotidianum da nobis hodie, et dimitte nobis debita nostra si...";
			link.l1 = "...sicut et nos dimittimus debitoribus nostris";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...sicut erat in principio, et nunc et semper, et in saecula saeculorum. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Dearly beloved, we are gathered together here in the sight of God, and in the face of this Congregation, to join together this man and this woman in holy Matrimony.  Beloved "+sld.name+" and Charles, you listened to the word of God that reminded you of the meaning of human love and matrimony. Now, on behalf of the holy Church, I wish to test your intentions\n"+sld.name+" and Charles, do you have a voluntary and sincere desire to connect with each other by the bonds of matrimony, in the face of our Lord?";
			link.l1 = "Yes.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Do you intend to be faithful to each other in health and illness, in happiness and unhappiness, until the end of your life?";
			link.l1 = "Yes.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Do you have the intention of loving and accepting the children, which our Lord will send you and raise them in the Christian faith?";
			link.l1 = "Yes.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Well, turn to each other and make a vow.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Should anyone here present know of any reason that this couple should not be joined in holy matrimony, speak now or forever hold your peace\nThen, before the face of the Lord, and the people gathered here, I declare you husband and wife! In nomine Patris, et Filii, et Spiritus Sancti. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Whispering) Charles, my son, just move your lips, I beg you - without any sound...";
			else sTemp = "";
			dialog.text = "Newlyweds, kneel down and pray together. Oratio fidelium. "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Прошло некоторое время...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "де Мор";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "My congratulations, son. Your father can be proud of you, and I'm proud. Be happy and take care of each other in our difficult time.";
			link.l1 = "Thank you, Holy Father. It was a wonderful service and I am glad that it was you who held it.";
			link.l1.go = "LH_abbat_38";
		break;
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
