void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "I don't want to talk.";
			link.l1 = "Hm, I see.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Just a minute, senor, are you "+ GetFullName (pchar) +"?";
			link.l1 = "Yes.. How can I help you??";
			link.l1.go = "zpq_sld2_1";
		break;
		case "zpq_sld2_1":
			dialog.text = "We need you. Your money to be more specific. And don't try to play stubborn because I am not in a good mood today, I can get angry.";
			link.l1 = "Oh, please, what money are you talking about? Do you really think that I will carry the treasure with me?";
			link.l1.go = "zpq_sld2_2";
		break;
		case "zpq_sld2_2":
			dialog.text = "Don't try to fool me. Just give me the money - " + FindRussianMoneyString(sti(pchar.questTemp.zpq.sum)) + " and you may walk your way. Or we will take it by force.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "Don't you work for this prison rat? I have got good news for you then, I sent him to hell.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "Don't you work for this prison rat? Tell him that the money was given to reliable hands, so he may forget about them.";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Fine, take your dirty money, bastard!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "I don't  have them...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		case "zpq_sld2_3":
			dialog.text = "That's your fate then - to die young because of your greed. It is too dangerous to let you stay alive.";
			link.l1 = "Such a self confidence.";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_3_1":
			dialog.text = "He-he, your fate is to die because of your greed then. It works for us, we don't want to share.";
			link.l1 = "It's your greed which will kill you...";
			link.l1.go = "zpq_sld2_4";
		break;
		case "zpq_sld2_4":
			dialog.text = "Hey, guys!! Put a bag on his  head!";
			link.l1 = "Well, it was your choice...";
			link.l1.go = "zpq_sld2_5";
		break;
		case "zpq_sld2_5":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(PChar, true);

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("zpq", "7");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = "Cumana";
			pchar.quest.zpq_seaBattle.function = "zpq_seaBattle";
		break;
		case "zpq_sld2_6":
			dialog.text = "Nice. Give them and get lost, captain!";
			link.l1 = "Ha...";
			link.l1.go = "zpq_sld2_7";
			AddMoneyToCharacter(Pchar, -makeint(pchar.questTemp.zpq.sum));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("zpq", "8");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
		break;
		case "zpq_sld2_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for(int i = 1; i <= 3; i++)

			{

				sld = CharacterFromID("qp2_" +i);
				LAi_SetImmortal(sld, true);
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 6.0);
			}
		break;
	}
}





