// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, " + GetAddress_Form(NPChar) + "?", "How can I help you, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hm, what's the big idea, " + GetAddress_Form(NPChar) + "? ","Again with the strange questions? Toots, go have some rum or something...") +"", "Over this whole day, this is the third time you're talking about some question..."+ GetSexPhrase(" Are these some signs of attention?","") +"",
                          "More questions, I presume, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind", "I've got nothing to talk about at the moment."), "No, no beautiful...",
                      "No way, dear, sclerosis...", "No, what questions?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "Listen, dear, they say you were close to my buddy Francois Gontier. Real close...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "I've brought you your pendant with gems. Here you go.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "Nothing at the moment. I'm looking for your pendent.";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "Yes, we were. What of it? I'm not a married girl and I spend time with who I want. Francois is a very respectable sailor, not like our local fishermen and farmers. He's so... Oh! And he gave me such nice presents!";
            link.l1 = "All right, stop! I know what qualities my buddy possesses, you don't have to list them out for me. I don't care what happened between both of you. You can even get married, I don't care. I need to find him right away, understand? Do you know where he's set off to?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "Tee hee... You're his buddy, and you don't know where he's set off to. That's funny!";
            link.l1 = "It's nothing funny, baby. We had agreed to meet on Jamaica and then we have a joint voyage waiting for us... if you understand what I meen. I won't be able to do that alone and he's set off hell knows where!";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "I see. Well, if such a profitable voyage is on the doorstep for you, considering you and Francois are friends... I'll tell you where he's set off to, but for a little reward.";
            link.l1 = "Hm... How much do you want?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "Ew, how disgusting. I don't need any money. Francois promised to give me some pendant with gems. I've already bragged about it to my friends and he's straight gone off... Bring me the pendant and I'll tell you where he has set off.";
            link.l1 = "Oh, you saucy slut! All right, you'll get your pendant.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "Ah, how beautiful! Now my friends will grow green in envy!";
            link.l1 = "Send my pity onto them. Now I'm waiting for an answer. Where has Francois set off to?";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "Yes, of course, mynheer. Francois has gone on course toward Cuba, to Havana.";
            link.l1 = "Thanks, dear. That's all I wanted.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

