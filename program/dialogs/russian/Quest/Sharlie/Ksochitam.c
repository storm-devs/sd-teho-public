// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Is there something you want?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "You... will still.... Have... to die. He will come... and kill you... as he has killed all of us... as he killed everyone here...";
			link.l1 = "What? Who are you? Who are you talking about?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "He is huge... he's invulnerable... he kills... he will kill you. I must kill you... if I kill you, you won't become like us... you don't understand... you'll die by his sword... you'll turn into what we are... Like everyone on Santa Quiteria...";
			link.l1 = "No way!";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Страж маски Кукулькана
		case "guardmask":
			PlaySound("VOICE\Russian\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "I've been waiting for you for so long!..";
			link.l1 = "Erm!.. Stunning!... That's quite a skeleton!";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "I see it... I feel it... You've brought me... my freedom...";
			link.l1 = "What are you talking about? What are you?!";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "I am the Guardian of Ksocheatem, the Keeper of the mask of Kukulcan... and your eminent death!..";
			link.l1 = "...";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("VOICE\Russian\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Stop...";
			link.l1 = "And why should I do that, huh? Are you out of breath, bonebag?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "No. You won't be able to kill me, not ever. Not even with that magical dagger. Our duel may last a long, long time until you completely run out of strength and die.";
			link.l1 = "Is that so? And why is it that you can't strike me?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "You're a courageous, strong warrior and you wield the Chief's Claw. I'm obliged to let you live, for he or she who possesses this dagger, who dares to stand against me in battle receives what he comes for.";
			link.l1 = "Who are you? Who are you really, Guardian?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "They used to call me Alberto Cascos. I was a soldier in Alonso de Maldonado's squad. We had found the ancient Tayasal, but they caught us and sacrificed us. Because of my hight and my strength pagan Kanek turned me into the Guardian of Ksocheatem, the keeper of Kukulcan's mask. Everyone who ever stood on Ksocheatem were found by me and slaughtered by my hand and then turned into undead\nChief's claw dagger was used to carve a map of this place from my flesh. I will watch for the mask's safety forever and restless, until I hold the dagger in my hands.";
			link.l1 = "Do you need the Chief's Claw?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "Yes. Since you need the mask. Give me the dagger. I'll find my long-awaited peace and you'll receive the mask. I swear to you that you'll be able to take it with you and leave Ksocheatem alive.";
			link.l1 = "I accept your offer, Guardian. I've seen the mask on that pedestal behind the baptistry fountain. Is that it?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "It is. This is the mighty artefact of Kukulcan himself, the flying snake. After we finish the conversation, you can walk over and take it.";
			link.l1 = "Well, I hope you hold to your word, Guardian...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "I've sworn...";
			link.l1 = "Then take the Chief's Claw. I hope it will bring tranquillity to your soul.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the Chief's Claw");
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			dialog.text = "Oh, how long I have waited for this moment! Now I can finally leave... But as a farewell gift, I would like to pass on a particle of my powers to you. This will be the last present that Alberto Cascos will ever give.";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "Now it's time for me to leave. Don't take your time, without its Guardian and the Kukulcan mask, the island will soon disappear forever.";
			link.l1 = "There's nothing to regret. One hellhole less in the world... But wait, Guardian! You've been in Tayasal! Please, tell me what that place is.";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "It's an old Maya city. Its appearance has been conserved since the time the people used to still reside there. Majestic temples, high pyramids... Now, the Itza tribe live there, claiming to be the direct descendants of the Maya. They try to mimic them in every way in religion, culture, and their way of life.";
			link.l1 = "How can I get there?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "Our commander knew the way, Alonso de Maldonado. We just followed him through the jungle. I only remember that we disembarked at Mosquito bay, north of Cape Perlas, and moved deep into the selva to the West.";
			link.l1 = "What's noteworthy in Tayasal?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "Everything is noteworthy there. Absolutely everything. But we were interested in nothing, but the Maya treasures. And we found them. And we paid for them, especially me. But now, I'm finally free!";
			link.l1 = "What do I need to know before heading to Tayasal?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "Itza people possess great strength and wit. They hate white people no matter what their nationality and will destroy any outsider invading their territory. Simple Itza warriors will not engage in any sort of communication, but Kanek or his son Urakan, if they see the mask... they might. If you manage to get to Tayasal alive, you'll see by yourself. But will you be able to leave it...";
			link.l1 = "Does Kanek offer up all white people coming to Tayasal as a sacrifice?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "I would suppose so. But that might not include the man who bears the Kukulcan mask.";
			link.l1 = "All right. I'll be counting on that.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "Farewell, soldier. I hope you will use the power of the mask for the right purpose.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
