// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("The town is alerted. Seems like it's time for me to take up arms too...", "Aren't you being chased by all town's guard?. To me, soldiers!!!", "You won't find a shelter here. But will find a few inches of cold steel under a rib!"), 
					LinkRandPhrase("What do you want, scoundrel?! A municipal guard has taken your track already, you won't escape too far, "+ GetSexPhrase("dirty pirate!","scoundrel") +"!", "Stop! "+ GetSexPhrase("Dirty killer! Guard!!!","I am not afraid of you! Soon you will be hang up in our fort, there's no place to hide...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Seems like you're tired of being alive...", "And why don't you want to live calmly, citizens..." + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Go to hell!", "There are a few seconds left for you in this world..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Hello, sailor! My name is "+GetFullName(npchar)+", and I am the only living soul here. Actually, we're all still gonna die, ha-ha-ha! Why did you come?", "Hello! I haven't seen a living man for a long time... Allow to introduce myself - "+GetFullName(npchar)+", and this cemetery is my last refuge. Apparently, here I will be buried. How can I help you?");
				link.l1 = "Hello, "+npchar.name+"! My name is "+GetFullName(pchar)+", and I am a captain. I walked in the jungle and came here. Thought I'd take a look inside this comfortable house, to see who is not afraid to live here...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А-а, my old friend, captain "+GetFullName(pchar)+"! Come in, come in!";
				link.l1 = "Welcome, friend! Very glad to see you. Don't you see at nights dancing skeletons and dead people with copper coins on eyes in your dreams?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "And why should I be afraid, captain? To afraid living people is necessary, the dead don't bite. Eh! Once I had a quite different life, and now I'm a watchman of this cemetery. I look after graves. And also trade some odd bits sometimes...";
			link.l1 = "And what do you trade in, please, tell me?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "What brought you to me this time?";
			link.l1 = "Show me what you have for sale today.";
			link.l1.go = "trade";
			link.l2 = "I want to ask you a question...";
			link.l2.go = "quests";
			link.l3 = "Nothing serious. Simply came to greet you.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "I have a lot of free time, therefore I like walking in the jungle and collect useful plants and fancy stones. Then I sell them in the town. They don't cost a lot, but however it's better, than nothing. And I get most various things from my friends......";
			link.l1 = "Friends? You mean, you resell what others bring to you?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... No, they all give me free of charge. Who can be friends of a cemetery watchman, if not deadmen?";
			link.l1 = "Wha... Do you rob dead bodies?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "I don't rob, just take off things they don't need already. Different poeple are buried here. Many unknown and not from our lands. The commandant brings from the town a dead body and says 'This is for you "+npchar.name+", send him in the last way'. Homeless, hanged pirates, bandits killed by guardians, all are buried here, and old "+npchar.name+" buries their bodies on a Christian custom.";
			link.l1 = "I see. Well, money is money, show me what you have.";
			link.l1.go = "trade";
			link.l2 = "Got it. I have to go. I was glad to meet you.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("And you, "+GetFullName(pchar)+", are a thief, guard!!!", "What the Hell! I looked away for a moment and you're already trying to steal what belongs to me! Hold a thief!!!", "Guard! Rob!!! Catch a thief!!!");
			link.l1 = "Oh shit!!!";
			link.l1.go = "fight";
		break;
	}
}
