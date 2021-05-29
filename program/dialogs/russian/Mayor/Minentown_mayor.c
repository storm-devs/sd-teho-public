void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("You dare to come here?! Bold action...", "How have those dumbs let an enemy invade here?! It's beyond my mind...", "Well, my guards cost nothing if some idiot is walking around in my residence..."), 
					LinkRandPhrase("What do you want, bastard?! My soldiers have already tracked you down and you won't get away"+ GetSexPhrase(", filthy pirate"," filthy pirate") +"!", "Dirty murderer, get away from my residence! Guards!!!", "I am not afraid of you bastard! You will be hanged, you won't get away..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Soldiers cost nothing...", "They'll never catch me."), 
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I'll cut off your toungue and shove it in your throat...", "I'd tell you, buddy: sit quietly, and you may yet have seen another day..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Enemy in my residence! Alarm!!!";
				link.l1 = "Crap!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + " sir. I am "+GetFullName(npchar)+", commandant of the mine of Lost-Tekes which is owned by " + NationKingsName(npchar)+". Now, would you be kindly to tell me the purpose of you visit, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "It's my first time here and I want to know more about this settlement and its laws...";
				link.l1.go = "info";
				link.l2 = "Just wanted to greet you, I am leaving already.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "You again, sir? What else do you want?";
			link.l1 = "No, it's nothing. I am leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "I respect such discipline. Well, I'll bring you up to speed in that case, since you are that interested\nLos-Teques mine is a property of the Spanish Crown. We mine silver and golden crude ore here, as well as silver and golden nuggets. All gold and silver are belonged to Spain and being transported to the Old World\nThe mine is well guarded, a unit of elite Spanish soldiers is always stationed here. The pirates made several attempts to rob our mine, but the consequences were always bad... for them\nAs you can see, it is a small town. We have a tavern and a store. You can buy golden and silver ingots for a good price there. Besides, our quartermaster who is also a merchant in the store can sell you other interesting metals and ore\nMost of our workers are convicts, but we also have a small amount of black slaves. As you can see, we always have a need for new manpower, every day at least one of these blasted convicts die\nSo, if you bring us slaves we will exchange nuggets for them. Contact with our lead engineer for such matters. You can find him in the shaft\nBehave yourself here. Don't start duels or fights, don't try to steal anything especially gold or silver. We don't have a prison here but we have a court martial\nThat's pretty much of it. Follow these simple rules and you will have no problems. You are allowed to move freely within the mine. Don't forget to visit the tavern, they perform certain... services by my permission. Welcome!";
			link.l1 = "My thanks!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "Robbery!!! That is unacceptable! Prepare yourself, "+ GetSexPhrase("pal","girl") +"...";
			link.l1 = LinkRandPhrase("Shit!", "Carramba!!", "Damn it!");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
