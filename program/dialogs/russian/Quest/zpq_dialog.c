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
			dialog.text = "Не хочу разговаривать.";
			link.l1 = "Хм, понятно...";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "zpq_sld2":
			dialog.text = "Минутку, сеньор"+ GetSexPhrase("","ита") +", не вы ли "+ GetFullName (pchar) +"?";
			link.l1 = "Да, именно так. Чем могу служить?";
			link.l1.go = "zpq_sld2_1";
		break;
		
		case "zpq_sld2_1":
			dialog.text = "Вы-то нам и нужны. А вернее, ваши деньги. И не вздумайте упрямиться, я сегодня не в настроении - могу и разозлиться ненароком.";
			link.l1 = "Да помилуйте, какие деньги? Не думаете же вы, что я стану носить с собой казну.";
			link.l1.go = "zpq_sld2_2";
		break;
		
		case "zpq_sld2_2":
			dialog.text = "Не морочьте нам голову. Просто отдайте деньги, которые только что получили - " + FindRussianMoneyString(sti(pchar.questTemp.zpq.sum)) + ", и идите своей дорогой. Или мы заберём их силой.";
			if (pchar.questTemp.zpq == "failed")
			{
				link.l1 = "Уж не на эту ли фортовую крысу вы работаете? Тогда могу вас обрадовать - я отправил"+ GetSexPhrase("","а") +" его к праотцам. Так что проваливайте, пока вас не отправил"+ GetSexPhrase("","а") +" следом.";
				link.l1.go = "zpq_sld2_3_1";
			}
			else
			{
				link.l1 = "Уж не на эту ли фортовую крысу вы работаете? Передайте ему, что деньги попали в надёжные руки, пусть забудет о нём!";
			link.l1.go = "zpq_sld2_3";
			}
			if(makeint(Pchar.money) >= sti(pchar.questTemp.zpq.sum))
			{
				link.l2 = "Хорошо, забирайте свои грязные деньги, мерзавцы!";
				link.l2.go = "zpq_sld2_6";
			}
			else
			{
				link.l2 = "У меня их нет...";
				link.l2.go = "zpq_sld2_3";
			}
		break;
		
		case "zpq_sld2_3":
			dialog.text = "Ну что ж, значит такая твоя судьба - умереть в расцвете лет от жадности, потому что теперь слишком опасно оставлять тебя в живых.";
			link.l1 = "Какая самоуверенность.";
			link.l1.go = "zpq_sld2_4";
		break;
		
		case "zpq_sld2_3_1":
			dialog.text = "Хе-хе, значит такая его судьба - умереть от жадности. Но нам это даже на руку - теперь не придётся ни с кем делиться.";
			link.l1 = "И вас жадность погубит...";
			link.l1.go = "zpq_sld2_4";
		break;
		
		case "zpq_sld2_4":
			dialog.text = "Эй, ребята!! А ну надевай мешок е"+ GetSexPhrase("му","й") +" на голову!";
			link.l1 = "Ну, вы сами напросились...";
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
			dialog.text = "Вот и славно. Давай их сюда и проваливай, капитан!";
			link.l1 = "Кха...";
			link.l1.go = "zpq_sld2_7";
			AddMoneyToCharacter(Pchar, -makeint(pchar.questTemp.zpq.sum));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("zpq", "8");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("","а"));
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
