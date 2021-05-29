// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			dialog.text = "What you want, pale-face? Tichingitu have nothing to say to you.";
			link.l1 = "Your name is Tichingitu? Hm. Listen, warrior, I haven't come here to stare at you. I've come here to ask you a question: Why did you intrude into that fatman's house?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Not saying anything? Not smart. You'll be hanged for theft and everything else you've done. Tell me why you committed such an act and maybe I'll be able to help you.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu come to town of pale faces through many many roads, through big water, from great forests and swamps. Tichingitu was tired and wanted to eat. Tichingitu die from hunger. No one want help Tichingitu. They yell, 'Go away, red-skinned dog'. Pub owner kick out Indian like mangy dog. Tichingitu want eat.";
			link.l1 = "God damn it, but why did you come to this settlement from... your forest?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu kicked out of native tribe. Tichingitu get into fight with tribe shaman, shaman tell chief, Shaman curse Tichingitu, Tichingitu leave tribe, far far away from native landing. Tichingitu have no home, no weapon, no nothing.";
			link.l1 = "That's what I call a misfortune. Why did you quarell with your own people?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Shaman of our tribe is an evil man. He say that evil spirit settle into my wife's body. Wife must die. My wife just sick, no spirit settle. I treat wife, shaman kill wife. Tichingitu stand out against shaman, everyone stand out against Tichingitu, Tichingitu leave.";
			link.l1 = "You tried to save your wife? That's why you were kicked out of the village?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Yes, pale-face. Tichingitu have no choice. Either steal or die of hunger...";
			link.l1 = "Well, I say... A noose for a few measly coins stolen by a starving man... Tichingitu, I'll try to help you. I know Fadey, that husky man whose house you snack into. Maybe I'll be able to do something... I'll go talk to the commandant.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu wait. Indian not afraid of death. Shaman curse Tichingitu must die.";
			link.l1 = "Not all is yet lost. I'll try to help...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			dialog.text = "Tichingitu wait. Indian not afraid of death. Shaman curse Tichingitu must die.";
			link.l1 = "Don't be that pessimistic. Your imprisonment has come to an end. I've helped to set you free.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Pale-face joke? Tichingitu free?";
			link.l1 = "No, I'm not joking. They are about to open your cell and let you out. Follow me, I'll lead you out of the jail.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "There you are, free again. Go on, Tichingitu, make sure not to steal anything else or get into any more trouble! You'd better find some Indian village and live with your own kind, I don't think they'd be against accepting you.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu not go. Master save Tichingitu's life. Tichingitu stay. Tichingitu's life belong to master.";
			link.l1 = "Huh? What are you talking about? What master, what life? Don't you understand what I'm saying? You're free! Go!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Indian is in debt, white master. Tichingitu serves you faith and truth. Tichingitu knows how to fight. Tichingitu will die in battle for master. He stay.";
			link.l1 = "Oh Lord! Damn it... What kind of a master am I to you, Tichingitu? I helped you not to turn you into a slave.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu is not a slave. Tichingitu is a free Indian. Tichingitu wants to serve you. Tichingitu knows how to fight, any dog die before come close to the master. Tichingitu knows how to clean and load musket. Tichingitu can shoot musket.";
			link.l1 = "Although... You know, Tichingitu, that's not a bad idea. I need loyal people and you don't seem to be a bad man. Also you know how to shoot a musket too. And what are you going to do alone anyway? You'll end up stealing something else and next time you'll definitely get hanged... All right, you can stay. But remember: life isn't going to be calm with me.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "All right, enough. Go in peace, red-skinned brother. May your gods watch over you!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu not afraid of anything, white master. Tichingitu will be glad to serve you. Tichingitu faithful to the last breath.";
			link.l1 = "All right. Welcome to the crew, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = sti(pchar.rank)*20;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.CanTakeMushket = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu listen to you, captain "+pchar.name+"!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, I'm about to depart to an old Indian village called Tayasal. I won't lie to you it's an extremely dangerous journey and furthermore unusual: through a teleportation idol. You... Will you joing me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, give me a full ship report.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we are docked.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nothing at the moment. At ease!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Ship report? Tichingitu has no report, master. Only weapon and clothes. Tichingitu took no report from nowhere.";
			Link.l1 = "Fine, whatever.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Master, Tichingitu never set foot in a colony without you. 'cause when Tichingitu enters a shop - all think Tichingitu is a thief again. Then, a prison.";
			link.l1 = "Yeah, you probably right. Not that prison thing again. Plus, nobody will ever believe you are a purser.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "What orders you have?";
			if (CheckAttribute(npchar, "IsMushketer"))
			{
				Link.l4 = "I want you to keep distance from the target.";
				Link.l4.go = "TargetDistance";
			}
            Link.l1 = "Hold up here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and don't lag behind!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.bulletNum") && sti(NPChar.chr_ai.bulletNum) > 1)
				{
					Link.l3 = "You need to change the type of ammunition for your firing arm.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choose ammunition type:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, sBullet);
			LAi_GunSetUnload(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "There is change of disposition!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "There is change of disposition!";
            Link.l1 = "At ease.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "How far, captain? Tell Tichingitu how many yards, but not more than twenty.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Captain, forgive Tichingitu but me not understand you.";
				link.l1 = "Sorry, my mistake...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu stand idle, no move. That is what you want, captain?";
				link.l1 = "Yes, precisely so.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu can not stay more than a twenty yards from target. Then he miss.";
				link.l1 = "Fine, keep your distance at twenty yards.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu understand everything. Tichingitu take position you say.";
			link.l1 = "Good.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Tichingit's life is long time become life of my captain. Indian not forget what captain do for Tichingitu. Tichingitu follow him where captain say, no questioning, no hesitation.";
			link.l1 = "Thank you, my friend!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "When will we depart?";
			link.l1 = "A little later. For now we will prepare for the journey.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
