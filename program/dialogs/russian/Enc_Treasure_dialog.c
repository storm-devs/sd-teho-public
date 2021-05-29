//navy
#include "DIALOGS\russian\Common_Duel.c" 
// boal 29.05.04 даем карту клада
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	aref   item;
	bool   ok;
	
	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	ProcessDuelDialog(NPChar, link, Diag); //navy

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();			
		break;

        case "Map_NotBuy":
            dialog.Text = "I assure you, you'll get rich. I'll wrap it for you in a cloth and in a handkerchief, if you like.";
			Link.l1 = "Stay there, I'll be right back!";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "Pssst... Listen now... I've got something interesting for you...";
			Link.l1 = "What are you talking about?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = (GetCharacterItem(Pchar, "map_part1")>0)  && (GetCharacterItem(Pchar, "map_part2")>0);
            if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "About a drink! H-Hic... drink with me!";
    			Link.l1 = "Oh, shut up. I thought you were serious.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "I've got something for you at a reasonable price.";
    			Link.l1 = "And what could it be?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "Oh, get lost. I've got no time for this.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "That's a great map. You will never buy anything like that in the store. It shows where a treasure is hidden. I can't get there myself, but the map is genuine, I swear.";
			Link.l1 = "That's interesting, How much do you want?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "Oh, get lost. I've got no time for this.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
            dialog.Text = "It costs only "+Pchar.GenQuest.TreasureMoney+" doubloons."; // Addon-2016 Jason
			Link.l1 = "Alright. And wrap it in a nice piece of cloth.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(Pchar.GenQuest.TreasureMoney)) // Addon-2016 Jason
			{
			   Link.l1.go = "map_treasure_buy";
			}
			else
			{
			   Link.l1.go = "Map_NotBuy";
			}
			Link.l2 = "That's too expensive. I don't need it.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "Here you go. Now you're going to become rich!";
			Link.l1 = "Thanks!";
			Link.l1.go = "exit";
			RemoveItems(pchar, "gold_dublon", sti(Pchar.GenQuest.TreasureMoney)); // Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "Let's have a drink, will we? Hic... They serve great rum here!";
			Link.l1 = "I have no time!";
			Link.l1.go = "exit";
			ok = (GetCharacterItem(Pchar, "map_part1")>0)  || (GetCharacterItem(Pchar, "map_part2")>0);
            if (GetCharacterItem(Pchar, "map_full") == 0 && !ok)
            {
				Achievment_SetStat(pchar, 68, 1); // ugeen 2016
    			Link.l2 = "You sold me a fake map!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "Who are you? Hic! I don't know you and I don't care!";
			Link.l1 = "Nevermind...";
			Link.l1.go = "exit";
			Link.l2 = "You sold me this forgery! I will beat the crap out of you...";
			Link.l2.go = "outraged"; //navy -- дуэли!!!
			Diag.TempNode = "let_s_duel";
			npchar.LifeDay = 1; // чтоб не слетел на выходе
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "tavern_keeper":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}
