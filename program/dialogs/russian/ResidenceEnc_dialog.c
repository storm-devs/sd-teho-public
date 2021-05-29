
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Jesus! Such a mean man in my chambers! Get away from here or I will call the guards!", "That can't be happening... Who let this rat get in my house? Get away from here bastard! You have nothing to do here! Go away!", "Such a strange times have come. Rats are getting in my bedroom! Go away!");
				link.l1 = RandPhraseSimple("Easy there...", "Watch your mouth...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("What are you doing in my bedroom? Go away from here!", "What a shame! I ask you to leave this place immediately!", "Excuse me, sir, but you haven't been invited here. Please, leave my room!");
				link.l1 = RandPhraseSimple("Pardon me... I am leaving.", "Sorry, wrong door. I have to go.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, what was that?! I am such a fool! Walking around, don't see a thing... Guards!!!";
			link.l1 = "Shut up!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Get away from here, rat!", "Get away from the governor's estate immediately, rat!", "I don't care about what you are doing at home of the governor of " + XI_ConvertString("Colony" + npchar.city + "Gen") + "But my advice - get lost, now!");
				link.l1 = RandPhraseSimple("Keep it easy, pal...", "Watch you words!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Greetings! I am a governor's servant. My name is " + GetFullName(NPChar) + ".", "I watch over this place, " + GetAddress_Form(NPChar) + ".", "You know, " + GetAddress_Form(NPChar) + ", our governor is a good man and pays us well...");
				link.l1 = RandPhraseSimple("Nice.", "Hm, very well...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "So you decided to rob the governor?! Guards, get the thief!!";
			link.l1 = "Shut you mouth!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("You'd better get away from here, "+ GetSexPhrase("pal","girl") +"...", "Go away!", "Missed the door, "+ GetSexPhrase("pal","girl") +"? ? This estate belongs to governor of " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".");
				link.l1 = RandPhraseSimple("I'll leave when I want!", "It's not your business...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Today, I have been ordered to serve here. Nice place...", "I protect the estate of " + GetAddress_Form(NPChar) + ".", "My order is to protect the governor's estate.");
				link.l1 = RandPhraseSimple("Good luck, then...", "Hmm, I see...");
				link.l1.go = "exit";
			}
		break;
	}
}
