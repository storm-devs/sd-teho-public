#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират!","") +"", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting() + "! Добро пожаловать, " + GetAddress_Form(NPChar) + " в таверну рудника Лос-Текес. Еда, выпивка и... девочки - все по умеренным ценам! Меня зовут "+GetFullName(npchar)+" и я всегда к вашим услугам.";
				Link.l1 = "Посмотрим... Я " + GetFullName(pchar) + ". Рад с вами познакомиться, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А-а, это же мой старый знакомый, капитан "+GetFullName(pchar)+"! Рад вас видеть, старина! Рому, девочек?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Налей мне рому, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "Я бы хотел отдохнуть. У тебя есть свободная комната?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Расскажи мне последние новости?","Что новенького в этих краях?","Как течет жизнь на суше?");
				link.l3.go = "rumours_tavern";
				link.l4 = "Нет, ничего не надо, "+npchar.name+". Я просто зашел поздороваться с тобой.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "О, а я-то как рад! Новые лица редкость в нашем городке. Давайте я налью вам рому, поболтаем...";
			link.l1 = "Я здесь впервые, и хотел бы немного больше узнать об этом поселении.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Налей мне рому, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "Я бы хотел отдохнуть. У тебя есть свободная комната?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "А о чем тут узнавать-то? У нас изо дня в день одно и то же: скука, палящее солнце и пыль. Население сплошь состоит из солдат и индейцев. Также у нас всегда можно найти пару-тройку искателей приключений и прочих авантюристов и проходимцев, которых сюда привлекают золотые копи\nЗаходят сюда и джентльмены, капитаны кораблей, вроде вас: продать рабов за золотые слитки или купить драгоценные металлы. Наш интендант - занятный человек, торгует не только золотыми и серебряными самородками, но и какими-то камнями\nПричем не драгоценными - так, ерунда какая-то, но при этом утверждает, что знающему человеку эти булыжники пригодятся. Так что обязательно загляните в наш магазин\nШахта находится в глубине города, у гор. Если хотите - можете посетить и ее, но крайне не рекомендую раздражать охрану, вести разговоры с каторжниками, и, Боже вас упаси, попытаться что-нибудь украсть\nОднако самое лучшее место в городе - это моя таверна. Только здесь можно отдохнуть душой и телом от этого знойного ада!";
			link.l1 = "Благодарю за информацию!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Капитан, по-моему, вам следует остановиться. Не дай Бог беды пьяным натворите. У нас здесь с этим строго - не поможет даже ваш авторитет.";
				link.l1 = "Хм... Пожалуй, ты прав - я уже достаточно выпил. Спасибо за заботу!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Пожалуйста, капитан. Всего за пять песо - пинта моего лучшего черного ямайского рома!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Ну, за твое здоровье и процветание твоего заведения, дружище!","Ну, за тех, кто в море!","Ну, за приумножение благосостояния вашего города!"), LinkRandPhrase("Ну, за ветер добычи, за ветер удачи, чтоб все мы зажили веселей и богаче!","Ну, за то, чтобы ветер всегда был попутным во всех делах!","Ну, за счастье, удачу, радости и... женщин!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.MinentownSex"))
			{
				dialog.text = "Сеньор, вы ведь уже оплатили и комнату, и девочку. Ступайте наверх, она вас уже заждалась.";
				link.l1 = "Хорошо.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Есть. На какой срок вы планируете остановиться?";
			if(!isDay())
			{
				link.l1 = "До утра.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "До ночи.";
				link.l1.go = "room_night";
				link.l2 = "До следующего утра.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Это обойдется вам в десять песо. Не желаете ли девочку заодно к комнате? Всего тысячу песо за свидание.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Нет, девочки мне не надо. Вот, возьми деньги за комнату.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Хорошо. Давай и комнату, и девочку. Вот твои деньги.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Увы, но твоя комната мне не по карману.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "Это обойдется вам в десять песо. Не желаете ли девочку заодно к комнате? Всего тысячу песо за свидание.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Нет, девочки мне не надо. Вот, возьми деньги за комнату.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Хорошо. Давай и комнату, и девочку. Вот твои деньги.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Увы, но твоя комната мне не по карману.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "Это обойдется вам в десять песо. Не желаете ли девочку заодно к комнате? Всего тысячу песо за свидание.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Нет, девочки мне не надо. Вот, возьми деньги за комнату.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Хорошо. Давай и комнату, и девочку. Вот твои деньги.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "Увы, но твоя комната мне не по карману.";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "Поднимайтесь по лестнице наверх, сеньор. Девочка будет ждать вас. Приятного отдыха!";
			link.l1 = "Спасибо, приятель...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.MinentownSex = "true";
			LocatorReloadEnterDisable("Minentown_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("Minentown_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\Minentown_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Minentown_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "Рада вас видеть, белый сеньор. И не смотреть на "+npchar.name+" так, "+npchar.name+" уметь делать все не хуже белых девок из бордель. Ах, сеньор такой симпатичный... Обещать, вы остаться доволен.";
			link.l1 = "Ну что же, малышка, давай посмотрим...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабеж среди бела дня!!! Это что же такое делается?! Ну, погоди, "+ GetSexPhrase("приятель","подруга") +"...", "Эй, ты чего это там копаешься?! Никак, вздумал"+ GetSexPhrase("","а") +" ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез"+ GetSexPhrase("","ла") +"? Да ты вор"+ GetSexPhrase("","овка") +", оказывается! Ну, считай, что ты приплыл"+ GetSexPhrase("","а") +", родн"+ GetSexPhrase("ой","ая") +"...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
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
