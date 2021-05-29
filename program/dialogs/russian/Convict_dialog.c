// диалог каторжников в шахте
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("Sorry, but It would be better for both of us if we don't talk to each other anymore. They will punish me, and you will be asked to leave.", "I have already told you everything, friend. Or do you want me to be flogged because of you?", "I am not listening...", "The spa-ade is striking and clan-angs the pick...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Hard rules you have here...", "No, of course, I don't want it.", "Hmmm...", "Papa, can you hear me...", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Captain, what are you doing? Hide away your weapon, before you'll get a lot of troubles!";
			link.l1 = LinkRandPhrase("Fine.", "Okay.", "Don't worry, I am hiding it away...");
			link.l1.go = "exit";
		break;  
	}
}
