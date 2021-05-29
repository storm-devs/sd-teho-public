// Ришард Шамбон - контрабандист
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "I don't want to talk with you. You attack peaceful civilians with no reasons and provoke them to fight. Get lost!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "Oh! Here you are, pal. And I was thinking about finding you by myself. I need you, friend.";
				link.l1 = "You are suspiciously friendly today, Richard. Well, I am listening.";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "What do you want? To be honest, I am not in a good mood today. Actually I have forgotten when I was in it last time.";
				link.l1 = "Is it really that bad, pal?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Аh, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Want something?";
				link.l1 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
				link.l1.go = "rumours_LSC";
				link.l2 = "I want to ask you a few questions about the island.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Just wanted to know how you're doing. See you!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Bad? No, it is not bad. I am just not in a right mood. So what did you want?";
			link.l1 = "Just wanted to know you. I am a newcomer here, so I am just walking around the Island and getting to know people.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Really? Fine then. I am Richard Shambon. A long time ago I traded some valuable goods and some of them were illegal, but I have been scavenging ship's wrecks, searching for scraps and exchanging them for food and gold for the last nine years.";
			link.l1 = "And I am "+GetFullName(pchar)+", a captain...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "You mean the ex captain, ha-ha?";
			link.l1 = "Well, actually, my ship is at Blueweld now. And I have sailed here on a tartane.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Really? Impossible! And where is your tartane now?";
			link.l1 = "Hm... at the bottom.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "A-ah... And I thought... Whatever, pal, I'd better drink some rum...";
			link.l1 = "Good luck with that. It was nice to talk with you. See you!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Got anything interesting to say?", "Has anything new happened on the island?", "Will you tell me the last gossips?");
			link.l2.go = "rumours_LSC";
			link.l3 = "I want to ask you a few questions about the island.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "And was I different before? Come on, I had bad days, everybody sometimes has them! Tell me, there are gossips among the Island that you are an excellent fighter. Is it true?";
			link.l1 = "I don't know what they say, but I know how to handle a sword if that is what you are asking.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "Got it. I see that those gossips were true... Listen, "+pchar.name+", remember me telling you about the outer ring? And about the valuable stuff you can find there?";
			link.l1 = "You all like to talk about that ring... And you all say the same.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "What else can be said, ha-ha! Fine. I'll get to the point. (lowering his voice) I have found an untouched ship at the outer ring, she is in good condition, which is quite rare\nThe ship is large, a pinnace. She was driven here not long ago, around two months or even less. Others have not found her yet, so there is a chance to make some good money by looting her holds and cabins.";
			link.l1 = "Nice, I am glad for you. But how does it concern me? Do you want to ask me to go there with you?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "Exactly! Listen. The pinnace's bow is damaged. Those damned crabs used a hole to get inside and they built a blasted nest inside. Sneaking inside while they are there isn't an option and I have no idea how to climb up to the upper deck\nI have never been a good fighter and I haven't touched a blade for years, so I won't be able to kill the creatures on my own. That's why I came to you.";
			link.l1 = "So do you propose me to kill all crabs inside that ship, right?";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "Yes. We will have a deal. I will show they way to the ship and you will eliminate crabs. We will share all loot we find there. It's a fair deal - I have found the ship and you will clear it.";
			link.l1 = "No, pal, I am not interested. It's not my style to fight crabs inside a half-sunk ship for some doubtful trophies. Find yourself another risky lad who will pull chestnuts out of the fire for you.";
			link.l1.go = "ring_exit";
			link.l2 = "Interesting... I have been thinking to check the outer ring for a long time. Deal! I will kill crabs.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "Too bad... You've made a mistake. There are a lot of juicy stuff in ships of the outer ring... And no one have been at that ship before. Fine, it's your wish. Farewell...";
			link.l1 = "Bye, pal...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "I am glad that I was right about you, friend. I have got a feeling that we will find a lot of interesting things inside her...";
			link.l1 = "We will see. Do you know how many crabs are there?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "I think about four of five of them... Well, in average.";
			link.l1 = "Works for me. When will we go?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "Let's go there tomorrow, we have to prepare ourselves. Get some antidotes from brother Julian, crab's jaws are poisonous. Caution is welcome. Let's meet tomorrow at eight o'clock in the morning on the 'oblique deck'. Do you know where is it?";
			link.l1 = "I don't. Explain.";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "There is a wreck of an old ship behind the 'San Augustine'. Her bow is underwater and her rear is lifted up high. That is why she is called the 'oblique deck'. You can get there only by swimming. Just start swimming from the place under the bridge and turn around from any side of the 'San Augustine'. We will swim together from there.";
			link.l1 = "Fine. See you tomorrow!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "8 o'clock, 'oblique deck'...";
			link.l1 = "Yes, yes, I remember that...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "Aha, here you are, pal. Ready to make some crab salad?";
			link.l1 = "Sure!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "Very well. Now turn your head to the outer ring and look. See there two ship wrecks stick up from the water?";
			link.l1 = "Hm... Yes, I do.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "Now look between them to the outer ring. See the galleon with a bow pulled up? It's just towards us. Look carefully.";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "I think, I see it... Yes!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "It is our target. Swim straight and don't turn. I will show you the way back when we will reach the outer ring. The entrance to the cargo hold is the hole in ship's bow. Know that I won't enter there until you kill all the crabs.";
			link.l1 = " Yup, we had a deal yesterday, I remember. You will show the ship and I will kill crabs. Let's swim?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "Sure! I will follow you.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "Heh, well done! You have killed all of this filth!";
			link.l1 = "I remember that someone told me about 'four or five' crabs... Remind me, who did that?";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "Pal, I never entered the cargo hold to count them properly. I just looked through the hole. I had no intentions to lie to you.";
			link.l1 = "Whatever. Let's check the cargo hold...";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "Sure! That is why we are here, right?";
			link.l1 = "Exactly! Let's not waste our time...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "Wait a bit, pal, I haven't checked all places I wanted yet. Search better, perhaps you will find more valuables.";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "Nothing special. It is a pity that there are no valuable goods here. There are provisions in barrels and copra in boxes. I have also found a box with expensive wine though. And what do you have?";
			link.l1 = "Nothing interesting too. A few boxes are quite valuable, but the rest is corned beef and copra as you've said.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "Not enough... Let's go upstairs and check the upper deck and cabins.";
			link.l1 = "Let's go.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "Damn it! Just look at that! Damn crab filth got to the deck! And how have they managed to do such a trick?!";
			link.l1 = "Don't be a coward! Stay here, don't move and don't draw their attention. I will deal with those creatures at once...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "Huh! So the tales of your skill in fencing were true! If I was here alone, I'd jump overboard...";
			link.l1 = "Listen, and how did you become a smuggler in past, huh? Or were you running away from everybody?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "Pal, first, I was younger, stronger and more reckless. Second, I am not a mercenary to fight wars - I am a smuggler and we always try to avoid a bloodshed. Third, I always was for sails and the tiller, not for blades and pistols. And finally, years of living here made me soft\nSo don't blame me. Let's check the upper deck. It looks like the ship had been in a serious fight - look at the damage...";
			link.l1 = "You are right. The ship definitely was under the heavy fire. Fine, let's search for something interesting.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "Yeah. And we need to find entrances to the inner rooms.";
			link.l1 = "Deal, let's not waste time. Call me if you see a crab.";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "Nothing valuable again... I have found a few interesting little things and that's all. But it is alright, there are usually no valuable goodies on the decks. The very best must be in cabins. There is an entrance to captain's quarters over there. Let's check it out.";
			link.l1 = "Be careful, who knows what is waiting for us there. Perhaps, I'd better enter there first?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "Let's go, "+pchar.name+". I won't hide behind your back any more. It is a shame that's for sure...";
			link.l1 = "Go on then...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "It looks like I got lucky - neither crabs nor other filth here. And now we will topsy-turvy this cabin, fuck, I swear that I am starting to get angry. I have found only two fucking dozens of doubloons and a few sundries!";
			link.l1 = "Calm down. You were right, all valuables are always stashed in captain's cabin. Let's see what we've got!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "Ha-ha! Just as I thought! I know habits of merchants, they like to make secret stashes and hide there the ship's treasury! Captain of this pinnace was a cunning rogue, but I won't be that easily cheated! Look what I have found! You would never be able to find it without me!";
			link.l1 = "Show me!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "Forty thousand pesos, two chests filled with doubloons, packet of emerald and a bunch of jewels! The owner was quite rich... Fine, at least it will repay our effort, though I was counting to get more stuff. Lets share it fairly.";
			link.l1 = "Excellent, Richard. At least we have made some money!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "Well, and let's keep what each of us have found at the decks for ourselves. Are you okay with that? Have you found anything useful in chests and in cabinets?";
			link.l1 = "A few Indian things, amulets, papers and so on.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "Keep it for yourself. You have done the most risky job after all.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Fine. And I have found something else which such a treasure hunter like yourself might find useful. Here, there were a captain's log lying on the desk. The story which is written there is very sad... but it concerns us in a some way. There is a box hidden in the cargo hold and it is filled with gold! Read it!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Fine. But I have found one more thing - captain's log.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "Fine, I agree with such terms, ha-ha. So what, is it time to return?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "Yes. Don't tell anyone else about the ship, it will be our secret. Sure, we don't need copra, but provision will be useful for us. We won't have to buy it from admiral anymore.";
			link.l1 = "Fine, I agree. I hope, that others won't find the ship soon. Let's go!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "Did you read it?";
			link.l1 = "Not yet...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "So let's read it! We can learn an important information from it. Also it will be interesting to know how did she end up here. Read it!";
			link.l1 = "Hm. Fine, I will read it now...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "Did you read it? What is there?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Well, listen then... The story is very sad... but it concerns us now in some way. Your treasure hunting skills might be able to help us. There is a hidden box filled with gold in the cargo hold! Read it!";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Wait a second. I will read and tell you...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "Really? "+pchar.name+", I am... well, I don't read that good. Tell me what is written there in details, huh?";
			link.l1 = "Short version: this pinnace was crossing the Caribbean Sea from the South Main to the New Spain. Captain got married to the Indian princess of a lower Orinoco tribe. She told him where her people were doing sacrifices...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "The gold nuggets were their sacrifices. Sure, our brave captain has robbed this gold stash with a help of his first mate and quartermaster. They have put it in the cargo hold, in one of boxes and covered it with copra...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "But it seems that the robbery of sacred Indian place was punished. The ship got in dead calm, water supplies were running low, an epidemic of fever started and pirates attacked the ship. Seamen have blamed the Indian girl, a captain's wife, and demanded to throw here overboard. Of course captain refused and a crew started mutiny...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "Captain lost that fight. According to the last notes - he has locked himself with Indian girl in the cabin and tried to shoot enraged sailors who were breaking the door. And there was a storm coming at them... it seems that it has brought the ship here. The end of the story is clear: the girl was shot and the captain was surely killed by rebels.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "Hm. It is really a sad story. But aren't you kidding me? Is there a box with gold in the cargo hold? I don't believe my ears! Which one? Let's go there! I will check every bale, every barrel!";
			link.l1 = "Let's go. I am eager to start searching too.";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "Ha-ha! We have found it! It exists for real! Just look at that huge pile! The whole box! There are five thousand nuggets, not less! I have never seen so much gold!";
			link.l1 = "Congratulations, partner. It seems that our undertaking is successfully ended... What will we do with all of that gold?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "What do you mean? We will divide in half!";
			link.l1 = "Sure we will. Where do you want to keep it? Will you leave it here?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "Ha! Surely, I will hide the gold in my stashes and no one will ever find them. Hiding is the thing I know well! Let's move a half of the gold in this barrel, that would be my share. I will take it away before the sunset.\nYou may do whatever you want with you share. But you'd better move it to your own stashes too. Don't blame me if you'll find your gold missing. I am an honest man, in my way of honesty and I won't dare to take your cut. But others, those who will come here later... they might find it.";
			link.l1 = "Fine. I will decide what to do with my gold. Let's put your share in a barrel...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "Done... Thank you, "+pchar.name+", for coming with me. I couldn't do this without you. Now I should consider building a tartan... to sail away from here... Ah, whatever. I'll think about it later\nI have a work to do - moving the gold to safe places. Farewell, friend, I wish you use your cut wisely!";
			link.l1 = "Bye, Richard. It was a glorious day today. See you!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Questions? Oh, fine, if you really need that...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "How did you get here?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Do you want to leave the Island?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Have you ever been considering to join one of the clans? Narwhals for example?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Is it true that you can find a lot of interesting stuff at the outer ring?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No questions. Pardon...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "For ten years me and my comrades had been sailing from Cuba to the Island on a well equipped tartane. We kept the location of the Island in secret - we were transporting bull carcasses and selling fresh meat for goods and gold from the local ship's holds\nGood times! Provision was always a problem here, bread and salted beef mostly, so they paid us for juicy meat with spicery, which costs a fortune back in Europe! Every single voyage I was making enough money to buy every whore of Tortuga\nBut everything has an end, so had our satisfied life. The weather gone bad - storms got stronger, so sailing to the Island became much more dangerous. Some of my companions have left the business, but not me and a dozen of brave men\nFinally, we were thrown on a reef two miles away from the Island. I still don't get how I managed to swim through the storming sea. That's how I became one of those who I was trading with in past.";
			link.l1 = "Interesting story...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ha! I will get out of here, damn it! But later. What would I do on Cuba? I have got no friends left and my pocket is empty. I will start to build a boat right after I will find a ship with a valuable cargo at the outer ring or a pile of doubloons.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "And why should I? To stand guard like an idiot for every third day and keep people off the San Gabriel? And they don't like to hire new people. They are local natives... And Negros are the same. No, I'd better be on my own.";
			link.l1 = "I see...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Sure! That is what makes the Island and the locals still living. Do you know when parties happen here? When a new ship arrives. But anyway, there are a lot of untouched ships filled with gold and goods at the outer ring\nProblem is that the outer ring is almost impossible to explore, things are messy out there, if you get entangled, slip or fell down badly - you may find yourself in the hole you can't leave on your own. Then you are done. A lot of people died that way.";
			link.l1 = "Hm... Interesting.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("What are you doing there, ah? Thief!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest!", "Decided to check my chests? You won't get away with it!");
			link.l1 = "Damn it!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "What?! Decided to check my chests? You won't get away with it!";
			link.l1 = "Foolish girl!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Listen, you'd better take your weapon away. It makes me nervous.", "You know, running with blade is not tolerated here. Take it away.", "Listen, don't play a medieval knight running with a sword around. Take it away, it doesn't suit you...");
			link.l1 = LinkRandPhrase("Fine.", "Alright.", "As you say...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Listen, I am the citizen of the city and I'd ask you to hold down your blade.", "Listen, I am the citizen of the city and I'd ask you to hold down your blade.");
				link.l1 = LinkRandPhrase("Fine.", "Alright.", "As you say...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Be careful, pal, while running with a weapon. I can get nervous...", "I don't like when men are walking in front of me with their weapon ready. It scares me...");
				link.l1 = RandPhraseSimple("Got it.", "I am taking it away.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}