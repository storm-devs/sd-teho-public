void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "That is defenetly a bug. Can you please inform Jason about when and how that happend.";
			link.l1 = "Will do.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Why have you come to my hut, white man? Tuttuathapak not think you his dear guest.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2"))
			{
				link.l1 = "Hail to you, great shaman Tuttuathapak. I have come to you to seek your help and advice. Please accept this musket as a token of my goodwill.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Hail to you, great shaman Tuttuathapak. I have come to you to seek your help and advice.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Tuttuathapak not help white man. White men bad men. They kill and conquer Indians, make Indians slaves. Tuttuathapak give white man no advice. You leave now.";
			link.l1 = "Hm...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) sTemp = "mushket1";
			else sTemp = "mushket2";
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have given: "+XI_ConvertString(sTemp)+"");
			dialog.text = "You know what give Tuttuathapak, white man. Tuttuathapak accept your gift. He will speak. What advice you seek of me?";
			link.l1 = "I heard that you'd come from a distant place in the South. I have an Indian amulet, and one knowledgeable man told me that you might know how it can be used.";
			link.l1.go = "Tuttuat_2";
		break;
		
		case "Tuttuat_2":
			dialog.text = "Show me the amulet.";
			link.l1 = "Here you go, great shaman.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking at the amulet)... Your friend tell the truth, white man. This amulet belong my people, great Indians Chavin. Cursed blasphemous palefaced cur defile the shrine and take it here. Tuttuathapak punished that hound.";
			link.l1 = "You deprived him of his mind, I take it?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "White man surprise Tuttuathapak with his knowledge. Yes, I devour the mind of that scurvy cur. He and his filthy man get they due.";
			link.l1 = "I see... Tell me, shaman, what is this amulet used for? Perhaps it can protect one in battle or ward against evil magic?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "This amulet of no use to you, white captain. You cannon use it power. Only great shamans of our tribe know how awake it.";
			link.l1 = "Hmm... So, it turns out that I took such a long journey in vain. But, perhaps, you can awaken the power of this amulet, great shaman? Certainly we could come to an agreement...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "Even if I wake amulet, you not hold its power for long. But I offer you deal, white man.";
			link.l1 = "What kind of deal?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Three amulets like this was taken from our shrine. They have different powers, but if they are bring together, they be much more powerful. Find all three amulets and bring them to me, and I reward you. I give you power you can hold forever.";
			link.l1 = "I don't quite understand... What kind of power you're talking about?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "You know all in right time. Find and bring me all three amulets. They be in Caribbean. Seek and find. You tell them easily - they look alike. Go, white man. Tuttuathapak wait and ask spirits help you.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Go, white man. Find two more amulets.";
				link.l1 = "I have already found them, great shaman. Here, take a look.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Go, white man. Find other two amulets.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "You here again, white man? You look like you meet fierce jaguar in the jungle.";
			link.l1 = "Worse, great shaman. As I had put to sea, I was attacked by a ship manned by the undead! Their captain was totally invincible. First he took the amulet from me and almost killed me - I barely survived. And then they sank my ship.";
			link.l1.go = "Tuttuat_12";
		break;
		
		case "Tuttuat_12":
			dialog.text = "Bad news, white man. The Caleuche goes on for the kill again.";
			link.l1 = "The Caleuche? That undead captain called his ship the Flying Heart. So, you knew about the ghost ship and you didn't warn me about it? If I knew that this sailing nightmare was hunting for the amulet, I'd never...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Tuttuathapak see white captain is upset. White captain must calm down.";
			link.l1 = "Calm down?!";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Yes. Calm down and not shout. Tell me - you still want to receive great power from me, which stay with you forever?";
			link.l1 = "Well, sure I do. But I don't have the amulet anymore.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "I teach you how take amulet from captain of the Caleuche. It be not easy. But if you do it, you take his ship as your prize, find valuable treasure, win glory with your people and receive reward from me.";
			link.l1 = "Goddammit! I'd gladly destroy that shrivelled monster! But how can I defeat him, if he cannot be harmed neither by the sword, nor by the bullet?!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "You ready listen to me, white captain?";
			link.l1 = "Yes, I am, great shaman.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "When my father be a young warrior, white men came to my land on the ship the Flying Heart. They went to mountains. Legend say, a shrine of our ancestors is hidden there. Shrine of jaguar warriors. White men find shrine and gold and defiled ancient sacred thing. They take away great treasure of Chavins - the jade skull of  Yum Cimil, god of death and patron of jaguar men\nWhite men came to their ship. They decide to return to take more gold, but as the sailor step on dry land, he die in horrible pain. Yu Cimil cursed the captain and his crew. They become immortal, but they cannot step on land anymore. They sail many-many winters, half a century by your calendar. That's how the Caleuche emerged.\nTheir bodies wither, they flesh rotten, but they still live. If you hack an arm or leg off, it grow back. It you slice them into, they again become one. If their ship go down, they fix it underwater, and it sail again.";
			link.l1 = "Just great...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " The Caleuche terrorize sailors. It attack without reason and spell certain doom. It is no frequent guest in Caribbean. It likes sailing at the shores of my motherland. Methinks, he want to remove curse. But he will never lift it.";
			link.l1 = "Why? What needs to be done to lift the curse?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Jade skull. It must return to shrine of Yum Cimil, temple of jaguar warriors. There are several temples. Elders of my tribe say there be one on a small island in the Caribbean. That's why the Caleuche sailed there. Once skull be at temple, spell of Yum Cimil breaks, and they become mortal and not heal wounds anymore.";
			link.l1 = "Ha! More likely, they aren't going to return the skull! Why would they, if they're immortal and invincible? And besides, they simply cannot bring it back, if they aren't allowed to step on land, right?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "They don't have skull. Captain throw it away in my ancestor land, when return form the shrine of jaguar men. Jade is no gold, white man not need it, he could not take beautiful green gem in skull eyes. And he throw it away. One sailor picked it up, and he not be touched by curse\nWhen sailor see what the Caleuche crew has become, he flee. He came to our village. My father saw that sailor and skull of Yum Cimil. And then white man go North along the coast ant take skull with him.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				link.l1 = "A jade skull with green gems in the eye sockets? Holy fuck... I... I have held it with my own hands! And I've sold it to some Portuguese... Merriman, or something like that... Yeah, that's what he said - the skull of Yum Cimil! He wanted it really badly! He paid half a million pesos for it!";
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "A jade skull with green gems in the eye sockets? So that is what I'll need to find? But that sailor could have perished in the selva fifty years ago, and the skull might be lost forever!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "Me know the skull is in Caribbean. The Caleuche be here not by chance. For the last six moons it often seen at the island. In former times it be not there for many winters. Captain of the Caleuche can feel the artifact of jaguar men. That's how he find you and your ship.";
			link.l1 = "Alright, then. So, what do I need to do?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "Skull must be here, in Caribbean. Caleuche be here not by chance. For the last six moons it often seen at the island. In former times it be not there for many winters. Captain of Caleuche can feel the artifact of jaguar men. That's how he find you and your ship.";
			link.l1 = "Alright, then. So, what do I need to do?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "You must find skull of Yum Cimil. You must find two amulet of which we spoke. Without them you cannot do anything. Amulet give you power to stand against jaguar men.";
			link.l1 = "Stand against jaguar men? What are you talking about?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "Temple where you must bring jade skull, is on a desert island in the Caribbean. It guarded by jaguar men. They are undead. Without amulet you not pass them. Jaguar men in life were a fierce warrior, and after death become almost invincible. They are given strength by Yum Cimil himself.";
			link.l1 = "Undead? Again? Lucky me...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Why so surprised, white captain? Yum Cimil is a god of death, jade skull give power over dead and alive. Caribbean. It guarded by jaguar men. Without amulet you not pass them. With amulet you can enter temple, leave skull there, then find the Caleuche, defeat her captain and take amulet he took from you.";
			link.l1 = "And why does the captain of the Caleuche need these amulets?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Methinks he want go to temple of jaguar men and he thinks amulet help him. But I can be wrong. Still, the Caleuche is always attracted by artefacts of my land. She sailed near island where temple of jaguar men is, and she sailed at shores of my motherland.";
			link.l1 = "And where is that island?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "First you find skull of Yum Cimil and amulets. Then we talk about island.";
			link.l1 = "Okay. Can you give me a hint, where to look for the jade skull?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "Me know not. But it's here, in the Caribbean. And amulets, too. Ask. Seek. Find.";
			link.l1 = "Heh... Alright, I'll try.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "And you be careful, white captain. The Caleuche feels Chavins items. When you have amulet, she well seek you. If she finds you, flee and quickly. If she gets you, you're a dead man.";
			link.l1 = "This cursed ship is insanely fast! It's about twice as fast as any ship I have ever seen.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "The Caleuche is cursed - that's why she's so fast. Hard to escape. You must have ship which can outrun the Caleuche. Or you end up dead. When you find amulet, bring it to me. Not take amulet on ship.";
			link.l1 = "I already got it. Thanks for your tale, great shaman. It's time for me to go now.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "Me be asking spirits to help you and save you from the Caleuche.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking) Yes, it's the one. Second Chavins amulet. You good. You need find yet another amulet.";
			link.l1 = "I remember that, shaman. Soon you will have it.";
			link.l1.go = "Tuttuat_34";
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Go, white man. Find one more amulet.";
				link.l1 = "I already have it, great shaman. Here, take a look.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Go, white man. Find one more amulet.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking) Yes, it's the one. Third Chavins amulet. You good. You found all amulets to pass dead jaguar warriors, servants of Yum Cimil.";
			link.l1 = "Now as I understand, I will need the jade skull?";
			link.l1.go = "Tuttuat_37";
		break;
		
		case "Tuttuat_37":
			dialog.text = "You speak true. Jade skull of Yum Cimil. You must take it to Chavins temple. Then the Caleuche lose its power for good.";
			link.l1 = "Tuttuathapak, please, tell me, where to look? Any thoughts?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "No. You think where you last seen jade skull. Whom you gave it to. Start seek there.";
				link.l1 = "Alright, great shaman. I'll do everything I can.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "A white warlock interested in skull of Yum Cimil. He seek for it. He come even our village. I heard warlock live in a house on Dutch island. Seek warlock on Dutch island, and you may know something.";
				link.l1 = "Alright, great shaman. I'll do everything I can.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul")) sTemp = "I'll start with visiting Curacao - there I've sold the jade skull to Joachim Merriman.";
			else sTemp = "Tuttuathapak told me, that a 'white warlock' showed interest in the jade skull, and adviced seeking for him on Dutch islands. Who might that be?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
		break;
		
		case "Tuttuat_40":
			dialog.text = "Go, white man. Find jade skull of Yum Cimil.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "I have it here, great shaman, take a look.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "Go, white man. Find jade skull of Yum Cimil.";
			link.l1 = "I am afraid I will not be able to do it. I have found the warlock, but in the last moment he slipped away with the skull. I have absolutely no idea, where he can be now.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "This is very bad, white man. Now you not pass the temple and not defeat the Caleuche. Me give you no gift. Now you leave.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "You leave now, white man.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(looking) Yes, it's the one. Very beautiful. And very frightening.";
			link.l1 = "Sure... But what's more interesting - I crossed the entire Caribbean sea from Cuba to Dominica, and the Caleuche never tried to attack me, when I had this skull. And when I was carrying amulets to you, it constantly ran me down.";
			link.l1.go = "Tuttuat_46a";
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Methinks, the Caleuche is afraid of skull. I have no other explanation. Perhaps Yum Cimil make jade skull very dangerous to the Caleuche - in addition to curse. Perhaps that's why captain wanted so much taking three amulets of my people. To gain wisdom how to control spell of Yum Cimil.";
			link.l1 = "So, as long as I have the jade skull on board of my ship, I can have no fear of the Caleuche's attacks?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Exactly, palefaced one. You see it for yourself.";
			link.l1 = "Very good! So, I can take command of a large ship, hire decent crew and prepare a nice welcome for that walking dead, when the spell is lifted from him, without fear that he'd intercept me earlier...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...about that spell, by the way - where should I take the jade skull to?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "You must take it to Chavins temple and finish your journey. I want tell you a story. You ready listen, white man?";
			link.l1 = "My ears are always open for your wisdom, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "As legends of my ancestors say, long ago, when palefaced men not yet come to our land, great chieftain of the Chavins build a very-very large canoe and send it with a warrior party to land of many islands. The son of great chieftain led them, and there also was one of the high shamans. In the land of many islands they found a desert land and founded a settlement and build great temple of Yum Cimil, which only our great ancestors could build\nMessengers returned with good news, but no one seen neither chieftain son, nor shaman nor the warriors anymore. Legend had it that they left there to live, bud the wisest of shamans talked to spirits and told that no people lived there anymore, and that Yum Cimil ruled this land\nLand of many islands is the Caribbean, white man. Temple of Yum Cimil is on island where no white men nor Indians live. Only servants of Yum Cimil, the Chavinavi, still guard temple corridors.";
			link.l1 = "And where is that island?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "I take it it's small and to north of village somewhere in that great water you call ocean.";
			link.l1 = "Hmm... To the North of Dominica at the ocean border? Goddammit - it's a very large area in the sea! How am I supposed to find a small island there, if no one had heard about it?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "I cannot tell better. But I know yet another story. You could hear it from your brothers. About twenty winters ago white man find that island. With a woman and old man he enter temple of Yum Cimil and take away a powerful artifact - the orb of rising sun. At shores of island pale-faced captain be attacked by the Caleuche\nPalefaced be smart. He blind captain and crew of the Caleuche with rising sun. Curse of the Caleuche weakened, and captain sank it, but orb of rising sun dissolve. If you find that palefaced man, he tell you where the island is.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ha! I think I know that pale-faced man... The stories sounds too similar. So, the Caleuche was sunk?";
			else link.l1 = "Hmm... So, the Caleuche was sunk?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Yes, but curse protect them from death. They fixed it and continued on their eternal journey.";
			link.l1 = "Alright, got it. But what will I do in the temple? Where should I put the skull? How can I beat the jaguar warriors guarding it? If they are the Chavinavi like those summoned by that witcher Merriman, it'd be foolish to go there alone - each of them is as strong as ten soldiers.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "They are not. Chavinavi summoned by white witcher with skull are weak. Much weaker than those summoned by Yum Cimil himself. You never harm them, and they kill you with one blow.";
			link.l1 = "Hold on - and how that pale-faced man managed to enter the temple and steal the artifact?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "Before that first palefaced enter temple, it be guarded by spirits of dead ancestors. Palefaced was strong warrior and he beat them. When he steal orb of rising sun, Yum Cimil was furious. He send fire and brimstone on palefaced man and almost destroy temple, but he run away with artefact. Now Yum Cimil summoned invincible jaguar warriors to guard temple.";
			link.l1 = "Glorious! And how will I sneak in, then?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "I help you, white man. I give you two Chavins amulets you bring me. Me talk to ancestor spirits and empower amulet. When you do it, you can fight jaguar warriors like common soldiers, though very strong. Amulet protect you and give you weapon power to harm Chavinavi of temple.";
			link.l1 = "Are you sure that the amulets will help?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "Me know. Me talk to ancestors. Me great shaman. You trust me. You take two amulets. One protects. Other empowers weapon. One amulet you must use. Which one - you choose. If you no wear amulet, you perish to jaguar warriors\nAnd you remember that on midnight Yum Cimil bring back to life all warriors you kill. You must figure the time to not fight they twice.";
			link.l1 = "I see.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "You take amulets. Here they are. You remember that they power has limits. It wane in one moon. You remember me say that you not hold they power? Only great shaman of our tribe can hold it.";
			link.l1 = "I remember. So, I only have one moon? One month?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Yes. When you come to temple Yum Cimil, you must find shrine and a great statue of condor in it. This is the most important part of temple. Here you put jade skull of Yum Cimil, and curse be lifted from the Caleuche. When he attack you again, you defeat him like ordinary man. Then you bring me amulet he take from you.";
			link.l1 = "Condor? What is it?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "Condor is a great bird which live in the mountains of my home. In memory of home ancestors build statue of condor in shrine.";
			link.l1 = "Okay, I'll search for it...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "You be careful. Many dangers lurk in temple beside jaguar warriors.";
			link.l1 = "What dangers?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "I don't know for sure. You see by yourself. It can be a trap. Or a confusion. Enter shrine is hard. Entrance be sealed, and you must find way open it. My ancestors be not only great warriors and shamans, but great builders, too.";
			link.l1 = "Heh! Sounds frightening, but let 'em all come! I will not waste time. I am setting sail at once!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Go, white warrior. Me shall summon spirits help you against jaguar warriors and the Caleuche.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			Log_Info("You have received two amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "But I have a clue: it seems that white captain, who had visited the temple of the Chavins, is none other than my good friend Nathaniel Hawk. I remember him saying that he had a map of that island in Maroon Town. Guess I will pay Nathan a visit.");
			}
			else AddQuestUserData("Caleuche", "sText", "That's a huge area in the sea, but I have no choice. I'll have to scour it entirely.");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "My talk with spirits. You were on the island in temple of Yum Cimil. You find the  Caleuche and amulet?";
				link.l1 = "You're right, great shaman. I have found the island, entered the temple and left the jade skull inside.";
				link.l1.go = "Tuttuat_63";
			}
			else
			{
				dialog.text = "Go, white warrior.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Tuttuathapak, you see... I didn't take the skull to the temple in time, and your amulets lost their power.";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "You lifted curse from the Caleuche. She find you thereafter?";
			link.l1 = "Yes. We met right at the island. I engaged in combat with her and came out victorious. Now I have all three amulets. Here, take them.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "You big and strong warrior, palefaced one. Tuttuathapak not like white men. But me respect brave and skillful warrior. You did very well. You rid seas of the Caleuche. You bring me three amulets. Me reward you.";
			link.l1 = "You promised something about 'power that I will be able to hold'?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "You speak true. I'll give you that power. None in Caribbean know secret of plant I know. Listen to me, palefaced one! In my home, there be medicinal plant. We call it Manga Rosa. You hear about that plant?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Yes. I held it in my hands. Gypsies show great interest in it. And one of them, healer Amelia, can even...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "No idea...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "Me hear of herbalist Amelia. She not know much. She not know the secret of Manga Rosa. Only great shaman from my homeland, from where Manga Rosa be taken here, can use its full power.";
			link.l1 = "What power?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "This herb grow in my homeland, but it occurs in the Caribbean, too. It's a light-green tall plant, with leaves like palm with fingers spread, and nice smell. You will know it instantly and not confuse it with nothing. Me know secrets of this plant. I can extract power from it.";
			link.l1 = "What power?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "Me can make potions of Manga Rosa. Very strong potions. None but me in the Caribbean can make those. My potions make man forever stronger, faster, smarter, keen-eyed, handsomer and luckier. I brew for you three potions.";
			link.l1 = "Very interesting!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "You great warrior, so you first need potion to make you sturdier and quicker. And you choose third potion after I make first two. But you must bring me Manga Rosa to make them - I have none.";
			link.l1 = "Where should I look for Manga Rosa?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "Manga Rosa is rare herb in Caribbean. It grows where peoplу walk not a lot. Stupid people pick it, dry it and smoke it. It is very stupid. NO SMOKE IT! Seek jungle and coves, secluded places where silly people not thread. Look carefully. For each potion I need five stems of Manga Rosa.";
			link.l1 = "Alright, great shaman. I'll come back to you once I have enough Manga Rosa.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Go, white warrior. Bring me Manga Rosa. You not regret it. My potions are best. Me tell spirits help you in your search.";
			link.l1 = "Thank you! See you!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "You bring five stems of Manga Rosa for potion?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Yes. Here are five plants that you need.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Not yet, great shaman. My search continues...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "Very good. Come tomorrow, once sun goes down. I will brew you potions which will increase your reaction and dexterity.";
					link.l1 = "Alright, shaman. I'll come tomorrow in the evening.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Very good. Come tomorrow, once sun goes down. I will brew you potions which will increase your endurance.";
					link.l1 = "Alright, shaman. I'll come tomorrow in the evening.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Very good. What is your potion to choose? Potion of strength, keen vision, intelligence, beauty or luck?";
					link.l1 = "Potion of strength.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Potion of keen vision.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Potion of intelligence.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "Potion of beauty.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "Potion of luck.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  It make your movements faster, and you better fight with fine light weapons.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  It make you more hardy in long journeys, and you better fight with sharp sabers.";
				dialog.text = "Potion ready, pale-faced warrior. You take it."+sTemp+"";
				link.l1 = "Thank you, great shaman.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "It's not ready yet, white man. Come later. Not disturb me.";
				link.l1 = "Fine...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "Me brew for you all potions I promised. You become stronger. You happy?";
				link.l1 = "Yes, great shaman. That was indeed a worthy reward.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "You find five more stems of Manga Rosa, you bring them to me. I make you another potion.";
				link.l1 = "I will bring you more of it. See you!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				GiveItem2Character(pchar, "kaleuche_amulet1");
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				GiveItem2Character(pchar, "kaleuche_amulet2");
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "Come tomorrow, as usual. I brew you potion to make you stronger, and you better fight with big axe.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Come tomorrow, as usual. I brew you potion to make your eyes keen, and you better hit with fiery weapons.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Come tomorrow, as usual. I brew you potion to make you smarter, and you better hide from enemies.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Come tomorrow, as usual. I brew you potion to make you handsomer, and you better persuade people.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Come tomorrow, as usual. I brew you potion to make you luckier, and you have good fortune.";
			link.l1 = "Fine.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "Me glad that you like my art, art of great shaman.";
			link.l1 = "Say, Tuttuathapak, what did you need these three amulets for? Just curious...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "You already feel the power of these two amulets. Spirits will help me give them power, and all three amulet together give great shaman wisdom and enlightenment of my ancestors, great Chavins.";
			link.l1 = "I see. Alright, thanks once again for your excellent potions. You're truly a great shaman. It is time for me to go now. Farewell, Tuttuathapak.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Farewell, white warrior. You no longer seek me. Me go to seclusion, grasp wisdom of my ancestors. May spirits help you in your journeys!";
			link.l1 = "...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("You have given amulets");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "You make me sad, pale-face. Me perform ritual with spirits to give power these amulets, and you waste it. Me sad. You go now. Tuttuathapak nothing more to say you.";
			link.l1 = "Now that was really unlucky... Oh, well. Farewell, shaman.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Types\skel.wav");
			dialog.text = "It's all in vain, sailor. You will not best me. And all my men lying on the deck will put together their bones and rise again before dawn. We cannot be killed, for death abandoned us.";
			link.l1 = "Goddammit! Are you dead or alive? More likely still alive - the dead are usually lying quietly and not swinging swords. But who are you and why did you attack my ship?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			PlaySound("Reef\reef_01.wav");
			dialog.text = "I am Balthazar de Cordes of the Flying Heart. Pitiful cowards, who don't know anything about me, call me Van der Decken, captain of the Flying Dutchman. But it doesn't matter. What matters is that you have an amulet on you, which I'll take now. I need it! I feel it! The great amulet of the Chavins, one of the three, will finally be mine! Kneel before me, mortal!";
			link.l1 = "Go fuck yourself, corpse!";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			PlaySound("Types\skel.wav");
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			dialog.text = "I can't believe it! It's been so long ago when I have last seen my own blood and felt pain...";
			link.l1 = "This time you have lost, Balthazar de Cordes. I know your story. The jade skull has been returned to the temple of Chavins, and the curse of Yum Cimil no longer hangs upon you or your crewmen. You will no longer bring your sailors back to life.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Oh, so you're considering yourself a redeemer, perhaps? No! Balthazar de Cordes will sell dearly whatever little has left of his life!";
			link.l1 = "The last journey of the Flying Heart ends here, at Khael Roa. And you will not lift your ship from the seabed, like you did twenty five years ago.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			dialog.text = "Hawk! Twenty five years have passed, but I still remember it like it was only yesterday. The radiance of that orb which blinded us and split my ship. That was the first and the last defeat of the Flying Heart and Balthazar de Cordes... So let's cross the swords, captain! Death in battle is light and welcome!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "Finally, you woke up, captain... How do you feel?";
			link.l1 = "Goddammit, what happened? My head is splitting...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "When we entered the captain's cabin, you were lying on the floor still. The guys picked you up and dragged you to our ship - and just in time, since the dead men lying on the deck began to rise again\nMost Holy Virgin and all the Saints! We quickly cut the lines and tried to sail away, but a salvo from their ship quickly turned our old tub into splinters. And then they hoisted sails and were gone in blink of an eye\nOur ship sank, and everyone who managed to survive, have reached the shore in a boat. We took your captain's chest with us. There should be a lot of valuable things, right?";
			link.l1 = "A lot, indeed. Thanks, pals, I'll remember that.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "We dragged you into the boat and then brought you to the shore. You were almost dead...";
			link.l1 = "I am indebted to you. How long had I been lying there, unconscious?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "For an entire day. We washed and bound your wounds, gave you medicine and poured some rum into you. You should get well soon.";
			link.l1 = "I surely will not die this time. Although I don't feel really well...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "That's for sure... Was it the Flying Dutchman, cap? Why did they attack us? And why didn't they shoot at us before the boarding, but sank the ship with just one only volley later?";
			link.l1 = "Their captain needed the amulet, about which I had talked to Tuttuathapak, an Indian shaman. That's why they haven't sunk us immediately, but as their leader took the amulet, they quickly disposed of us... What a nightmare! A ship manned by the dead! Impossible to believe...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Yeah, now it was our turn to encounter the Flying Dutchman. When I have the chance, I'll go to church, light the candle for my miraculous delivery, and pray to our Lord...";
			link.l1 = "Me too, I guess. But first I'll go back to that village. I need to tell Tuttuathapak everything about it. That accursed ship attacked us because of the amulet! I hope that red-skinned devil has some ideas, why in hell those living dead might have needed it.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Alright. But be careful, cap - your wounds have barely healed.";
			link.l1 = "I will be careful, I promise. Thanks for not abandoning me!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "What are you talking about, cap! We'd go to the world's end for you and fight thousands of undead!";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "Hey! I haven't yet collected enough snake skins to sell them to you, so piss off!";
			link.l1 = "Hmm... Are you Fergus Hooper?";
			link.l1.go = "fergus_1";
		break;
		
		case "fergus_1":
			dialog.text = "No, my name is Tuttuathapak, and I will curse you, if you don't get lost at once. So you'd better hurry, or you will...";
			link.l1 = "...lose my mind, burn my own ship, and my sailors will kill me and take all my belongings. Right?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Arrgh... What the hell, who are you!? How did you...";
			link.l1 = "We have a common friend, Fergus. He's a lighthouse keeper, and his name is "+GetFullName(sld)+". He told me about you and sent me to seek you out. By the way, I personally know shaman Tuttuathapak, so your joke didn't work, sorry. Listen, I am not looking for trouble. I want to buy something from you, and it's not the snake skins.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "Oh, so you know my old friend! How is he? Didn't he die of boredom in his lighthouse yet? Please, sit, sailor, have a drink with me!";
			link.l1 = "I am sorry, Fergus, I really don't have much time. Listen, I need that Indian amulet, one of those which your late captain took from the Main with Tuttuathapak. I will pay a good price for it, and you will get rid of a dangerous trinket.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "And what's so dangerous about it? I haven't seen any harm from it so far.";
			link.l1 = "That's because you're no longer sailing the seas. I used to have a similar amulet until recently. A ghost ship is hunting those things.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Are you kidding, buddy? Perhaps, knowing Tuttuathapak has taken its toll on you? Be careful, cap, that red-skinned devil will devour your mind...";
			link.l1 = "Believe me or not, but I am telling the truth. I wouldn't believe it myself, it I didn't see it with my own eyes, I can swear on the Book. I barely survived after that encounter with the Caleuche.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "The Caleuche?";
			link.l1 = "Well, the Flying Dutchman. Whatever. Just sell me that amulet. It's of no use to you anyway, I know.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "That's right. This is just a useless trinket, although quite a beautiful one. Listen, I would have sold it to you without more ado, but you see - I don't have it anymore. It was stolen from my hut among other things, while I was hunting out in the jungle. That happened rather recently, about a month ago. Sorry, but there is nothing I can help you with.";
			link.l1 = "And who stole it?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Are you seriously thinking that I'd be sitting here if I knew, who cleaned out my home? There's a gang of thieves and brigands working outside Belize, and they have informers in town. Well, at least that's what the commandant is thinking. I am positive that it was them.";
			link.l1 = "The commandant knows about the bandits and still does nothing?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Whether he is doing something or not, I don't know. The only thing I know for sure is that my things are gone, and your precious amulet with them. Try to seek out these bandits - perhaps you'll find it in their pockets. It is unlikely that they managed to sell it - merchants have no need for such things.";
			link.l1 = "Alright, I'll go see the commandant. Good luck, Fergus!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "Hey! What do you need? I don't expect any guests. Get lost!";
			link.l1 = "Why so rude, friend? I just wanted to ask...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "Have not you heard? Get out, or I'll kick you out the door!";
			link.l1 = "Hmm... Well, perhaps you're the person I am looking for? You seem way to nervous, buddy...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Thinking yourself too clever, aren't you? Once again: either you get lost right now, or I am calling the guards, and they'll throw you behind bars!";
			link.l1 = "Throw me behind bars? How very interesting. You know, now I am almost positive that I have found whom I was looking for. Alright, I agree. Let's call the guards, and then we'll walk to the commandant's office together. I've just been there, so I remember the way... Guards! GUARDS!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Screw you! I'll run you through!";
			link.l1 = "Oh! Well, you may try!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "Hey, traveller! Welcome, welcome... Supper, lodging - everything for your money. So, get ready to turn your pockets inside out!";
			link.l1 = "Not so fast, my good man. I have business with you.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "Business? Ha-ha! Your only business is to give me all your silver and gold!";
			link.l1 = "Shut up already. I brought you a letter from Belize you've been waiting for. The messenger couldn't get on with the guards and entrusted the affair to me.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "Show me!";
			link.l1 = "Here...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(reading) Hm... That's surely strange... How did you get involved?";
			link.l1 = "I told you, they seized your guy, so I took his job. He promised money and a warm welcome from you...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "A warm welcome? Alright, pal. We'll warm you up, feed you, give you money and all that stuff - but you, too, will have to prove us that you're not a guards' hound. We've got a score to settle\nA merchant has recently arrived to a nearby cove; apparently, he wants to sneak into the city with his wares past the customs office. But we will still exact the duty from him. We are lawful folk. You'll come with us. Do you know which end of the sword goes where?";
			link.l1 = "And will I get a share of this duty?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Sure - if you're brave in battle and if you stay alive. But don't expect a cakewalk - the merchant is not alone, he has an escort. Well, time to go - our prey is close. Boys! Prepare your weapons, we're heading out!";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "I see you're no coward. Well done! You have earned your share. How would you like it? Cash? Merchandise?";
			link.l1 = "Cash.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Merchandise.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Here you go! And this purse is for delivering the letter.";
			link.l1 = "Thanks! That's how I like it!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Here you go! Just don't drink yourself to death, ha-ha-ha! And this purse is for delivering the letter.";
			link.l1 = "Thanks! That's how I like it!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "You look like a decent fellow to me. How about another score? It's about that letter you had delivered to me.";
			link.l1 = "Sure.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "Then come to the cave. There are two of them. Go to the jungle to the point we had last met, then take the left path. We gather in three days at the entrance to the cave, from midnight to one. Got it? If you're a good boy, we'll accept you into our gang. But keep in mind - if you blab anything out in the town, you're done. I have a long arm.";
			link.l1 = "Stop scaring me already. I got it. I will be quiet as a fish. Wait for me in three days. I love easy money!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "Alright, pal. Now get lost before the guards come here. We're leaving as well.";
			link.l1 = "See you around, pal...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "What! I take it you decided to appropriate some of our property? You will not get away with it, you filthy worm!";
			link.l1 = "Whom did you just call a worm, scum?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "Hello, colleague! What has brought you here?";
			link.l1 = TimeGreeting()+", mynheer Jackson. I am glad to finally find you.";
			link.l1.go = "reginald_1";
		break;
		
		case "reginald_1":
			dialog.text = "'Mynheer Jackson', ha-ha! Well, to be honest, soon I am going call myself that too. I am working for this damned Company without a break... but they pay well, very well!.. So, what brings you here?";
			link.l1 = "Our common acquaintance, keeper of the lighthouse, told me that you had an ancient Indian amulet. I guess you never made any use of it, and I need it really badly. I want to buy it from you.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "Oh, you mean that fancy trinket, of which I had inquired that retired bosun? Yeah, friend, you were right, it actually never came in handy.";
			link.l1 = "How much do you want for it?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "You see, there's a problem... Let me explain. I don't have it with me. Since I never found a use for it, I left it in my chest on the shore, among my other belongings.";
			link.l1 = "Oh, that explains that you still... well, never mind. Let's just head to that chest of yours, and I'll buy the amulet from you. Simple as a pie. Where do you have it?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "It's not exactly that simple. My chest is located on Barbados, in the lighthouse tower, and it's safely locked, so that no one could take advantage of it in my absence. And I am really sorry, but I cannot go with you to Barbados, according to my contract with the Dutch, I have to sail between Philipsburg and Port Royal and stick exactly to the schedule. And Barbados is nowhere near that route.";
			link.l1 = "And what can we do? I really, really need that amulet!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Hmm... Well, there is one option. I give you the key to my chest, and you sail to Barbados on your own. But you will have to compensate me all stuff which is in it. I am sorry for the distrust - but you must understand. I've never seen you before.";
			link.l1 = "How much?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Five hundred golden coins. No less.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 500)
			{
				link.l1 = "You've got it! Here's your gold.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Hmm... I don't have that many doubloons with me.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "Then come see me again once you've raised the money. If you found me once, you'll find me again. I am going to sail between St. Martin and Jamaica for quite some time yet.";
			link.l1 = "Alright, deal.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
		break;
		
		case "reginald_9":
			dialog.text = "You again, friend? Have you raised 500 coins?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 500)
			{
				link.l1 = "Yes. Here's your gold.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Not yet, but I am working on it.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			Log_Info("You have given 500 doubloons");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "gold_dublon", 500);
			dialog.text = "Great! And here is your key. And I have a request: after you take everything what's in, please leave the key in the lock. I would hate to commission a new lock and a key for it.";
			link.l1 = "Alright.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "Then good luck to you, friend! Bon voyage!";
			link.l1 = "And the same to you, mynheer Jackson.";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "questTemp.Caleuche.Garpiya");
			DeleteAttribute(pchar, "questTemp.Garpiya");
			GiveItem2Character(pchar, "kaleuche_key"); 
			AddQuestRecord("Caleuche", "20");
			// сундук со схроном
			i = Findlocation("Mayak2");
			Locations[i].models.always.locators = "lighthouse_Blocators";
			locations[i].private1.key = "kaleuche_key";
			locations[i].private1.key.delItem = true;
			locations[i].private1.items.kaleuche_amulet3 = 1;
			locations[i].private1.items.pistol9 = 1;
			locations[i].private1.items.indian_6 = 1;
			locations[i].private1.items.map_barbados = 1;
			locations[i].private1.items.map_part2 = 1;
			locations[i].private1.items.jewelry22 = 5;
			locations[i].private1.items.jewelry17 = 6;
			locations[i].private1.items.jewelry12 = 3;
			locations[i].private1.items.jewelry16 = 2;
			locations[i].private1.items.jewelry20 = 7;
			locations[i].private1.items.jewelry53 = 11;
			locations[i].private1.items.mineral25 = 1;
			locations[i].private1.items.mineral21 = 1;
			locations[i].private1.items.mineral22 = 5;
			locations[i].private1.items.mineral26 = 1;
			locations[i].private1.items.mineral10 = 1;
			locations[i].private1.items.mineral3 = 10;
			pchar.quest.caleuche_amulet3.win_condition.l1 = "item";
			pchar.quest.caleuche_amulet3.win_condition.l1.item = "kaleuche_amulet3";
			pchar.quest.caleuche_amulet3.function = "Caleuche_ThirdAmuletFind";
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			dialog.text = "Hello, captain "+GetFullName(pchar)+". Glad to welcome you in Willemstad.";
			link.l1 = "Hello, Father. I don't remember you. Do we know each other?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "I made inquiries about you, once your ship has put in. And I think I can ask you for assistance.";
			link.l1 = "Very interesting. And why me?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Because you've done a lot for the Republic of Free Provinces. You're in good standing with the Company and you are friends with the governor. I have already appealed to several instances and was rebuked, but I do hope that a noble person such as you would not turn down a humble request of the servant of our Lord.";
			}
			else
			{
				dialog.text = "Because you are not in service of our governor; you're not working for the Company and you have no dealings with our military - otherwise you most likely would just brush me aside like an annoying fly, since I have already appealed to several instances and was rebuked.";
			}
			link.l1 = "Fine, then. What's the nature of your request?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "There is a house opposite to the governor's residence. A lady who lived there was renting a room in it to one very suspicious type, not the local, and not the Dutchman. Well, our father superior, Father "+sld.name+", has recognized him\nIt was Joachim Merriman, a Portuguese, accused by the Inquisition of witchery and dealings with unholy powers. He hid himself from the Inquisition in the New World. You know, Spaniards often accuse those out of favour of heresy and witchery in order to burn them at the stake, but... In this case they were right. Merriman is a warlock\nSo, he'd been living in Willemstad for some time, and then he disappeared as suddenly as he had emerged. And after some time the woman who rented the room to him, was never seen going out of the house. Never! And she was never seen anywhere ever since\nAnd at nights citizens can occasionally see red-blue lights flashing in the windows of the second floor and hear strange sounds. Father "+sld.name+" appealed to the commandant. He sent a patrol of four soldiers, they searched the house, but have found nothing: neither the landlady herself, nor anyone else, nor anything suspicious at all\nBut these strange things continue happening. The landlady's never shown up, and this hellish light can still be seen there at nights. Besides, two beggars have recently gone missing. I heard them over talking at the parvis - they knew that there were no owners in the house, and so they decided to lodge there. No one has seen them thereafter.";
			link.l1 = "And, I take it, you want me to go into that house and check out, what's happening there?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Exactly, noble sir. Please help the Holy Church. The commandant says that we're imagining things, since his patrol never found anything. The government thinks the same. Commoners simply don't care, because they don't see it as a clear threat to them.";
			link.l1 = "Hmm... And I will need to go there at night?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Yes, mynheer. It's quiet there during daytime. Please, I beg you. Father "+sld.name+" will thank you and reward you for your service. Once you've been to that den during the night, please tell him what you find there. I assure you, our misgivings are well-grounded.";
			link.l1 = "Alright. I'll think about it.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Thank you, captain. I hope you don't turn down my humble request. Please, do it in the name of our Lord and our faith. Go with my blessings.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul")) sTemp = "visit the house of my old acquaintance Joachim Merryman, where, allegedly, strange things are happening at nights. I still remember that glitter in Merryman's eyes, when he was looking at the skull, and I feel frightened. I am not really fond of the idea to visit his former abode in the night.";
			else sTemp = "visit the house across the residence, where some Joachim Merryman had been renting a room. Apparently it is that warlock, of which Tuttuathapak was talking about. According to the monk, strange things are happening in this house in the night. I really feel uncomfortable about visiting the warlock's former home.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "Hold on, buddy. You'd better not go there, if you cherish your life.";
			link.l1 = "And what's the deal?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Trust me, you don't want to know. But there is Death himself around the corner, and I can swear on the Book that you won't came back alive.";
			link.l1 = "Well, if you say so, I will not tempt fate. Thanks for the warning.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "You're welcome. Stay clear of that path.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "Stay clear of that path, buddy.";
			link.l1 = "Yeah, I remember...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Are you sure you want to go there?";
			link.l1 = "Absolutely. "+sld.name+", father superior of the church in Havana, sent me here. I must determine what's happening there, and take adequate measures.";
			link.l1.go = "cavehunter_6";
		break;
		
		case "cavehunter_6":
			dialog.text = "What's happening there? I'm afraid you'd be quaking with fear once you've seen what's happening there with your own eyes.";
			link.l1 = "You mean the walking dead?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Yes. And you better believe my words.";
			link.l1 = "I do. I have already encountered that unholy thing in Willemstad and destroyed it. And I will now go there and destroy all filth in that cave.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "Are you going to go there alone? You're a dead man, buddy. You have no idea just how many of those things are there. Well, go, if you must, and I'll go to the church to light a candle for the peace of your soul.";
					link.l1 = "Don't be too quick to bury me. I've seen worse.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "Just the two of you? I am afraid you won't get far. You have no idea just how many are there. It's a suicide.";
					link.l1 = "You just don't know us well, friend. Step aside, and we will cleanse this unholy den.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "Just the three of you? You must be seasoned fighters if you dared to do it. But I am still afraid that you will not manage. You have no idea just how many are there in the grotto.";
					link.l1 = "You just don't know us well, friend. Step aside, and we will cleanse this unholy den.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "You guys are no cowards, I see. But you have really no idea, how many of them are there. In such an affair every man counts. Screw this, I'll come with you and I will shoot that filth with my musket!";
					link.l1 = "You're a brave soul, friend. I will not turn down your help. Let's go!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "Let's go! Death to the filthy undead!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Now that was quite a massacre! Who could have thought that so many dead were hiding in this place! Well, at least we can rest... Please tell about it that father superior of yours, who had sent you here. I do hope that the Inquisition is going to get down to this after your report. Dealing with the undead is on their own ground, after all.";
			link.l1 = "I'll definitely tell them. Thanks you for the help, buddy. You're a real soldier! Good luck!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Stand where you are! This place is off-limits!";
			link.l1 = "Ehh... And what is in there?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "A dangerous warlock was found there. Only the holy fathers and soldiers accompanying them can enter.";
			link.l1 = "I see. Was the warlock arrested?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "I am not authorized to answer such questions, senor. It is time for you to leave.";
			link.l1 = "Alright, I got it. Good luck!";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("VOICE\Russian\TopChavinavi-01.wav");
			dialog.text = "Hold still, human! You're in the very heart of the temple, and you have gone too far to turn back.";
			link.l1 = "Who are you?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "I am the chieftain of the Chavinavi, the keeper and guardian of this sacred place. You're not the first to enter this temple, but only two men and one woman entered it and left alive before you. That is the only reason I condescend to speaking with you. Why have you come here, pale-face?";
			link.l1 = "I have brought an ancient relic here, the jade skull. Fifty years ago it was taken from an Indian temple deep in the mainland. I was going to find the shrine and return the relic to your god.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "It is strange to hear such words from one of your kind. I don't believe you. You, pale-faced ones, are always coming to take something, but never to give anything back.";
			link.l1 = "I do not lie. By returning the skull I will lift the curse laid upon the captain of the ghost ship terrorizing the Caribbean sea, which will make him mortal again, and I will rid the world of him for good.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "How do you know that our God shall lift that curse, pale-face? Does our God talk to you?";
			link.l1 = "No. I came here on advice of a shaman by the name of Tuttuathapak. As he said, the skull is the key to the curse, and this is the only temple in the Caribbean. An you know what - I think that he indeed can converse with the spirits of the past. Perhaps even with you, chieftain of the jaguar warriors.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "Your words surprise me, pale-face, but I still cannot trust you completely. Yet, if you came to this temple to return our relic, surely our shaman must have told you about this place, its creation, its history and denizens\nIf so, you will easily answer all my questions. Then I will admit that you had been sincere with me, allow you to pass and, moreover, reward you.";
			link.l1 = "Then ask!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			PlaySound("VOICE\Russian\TopChavinavi-02.wav");
			dialog.text = "I am the chieftain of the Chavinavi, the jaguar warriors. Thousand years ago I was human; now I am carrying out my sacred duty in these chambers. Which god commands me?";
			link.l1 = "Mictlantecuhtli.";
			link.l1.go = "question1_l";
			link.l2 = "Kukulcan.";
			link.l2.go = "question1_l";
			link.l3 = "Yum Cimil.";
			link.l3.go = "question1_r";
			link.l4 = "Inti.";
			link.l4.go = "question1_l";
			link.l5 = "Kauil.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "Before your pale-faced people came, this entire land, from the great snow in the north to great plains in the south, belonged to us, brothers of one family...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "Before your pale-faced people came, this entire land, from the great snow in the north to great plains in the south, belonged to us, brothers of one family...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "What Indian tribe erected this temple?";
			link.l1 = "Inca.";
			link.l1.go = "question2_l";
			link.l2 = "Chavins.";
			link.l2.go = "question2_r";
			link.l3 = "Maya.";
			link.l3.go = "question2_l";
			link.l4 = "Aztec.";
			link.l4.go = "question2_l";
			link.l5 = "Arawac.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "Our people progressed, learning wisdom, and subjugated new forests, plains and islands. People, who had built this temple, arrived from the woodlands across the Great Water...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "Our people progressed, learning wisdom, and subjugated new forests, plains and islands. People, who had built this temple, arrived from the woodlands across the Great Water...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "Who led the party of those glorious pioneers?";
			link.l1 = "Great chieftain.";
			link.l1.go = "question3_l";
			link.l2 = "Great priest.";
			link.l2.go = "question3_l";
			link.l3 = "Son of the great chieftain.";
			link.l3.go = "question3_r";
			link.l4 = "Son of the great priest.";
			link.l4.go = "question3_l";
			link.l5 = "The party had no leader.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "The Indians, valiant warriors and travellers, always loved and revered their homeland, even after settling in a new place. As a token of their love for their home they built a statue of the temple in the form of a bird the symbol of their home. It's behind me...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "The Indians, valiant warriors and travellers, always loved and revered their homeland, even after settling in a new place. As a token of their love for their home they built a statue of the temple in the form of a bird the symbol of their home. It's behind me...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "What is the name of that bird?";
			link.l1 = "Albatross.";
			link.l1.go = "question4_l";
			link.l2 = "Eagle.";
			link.l2.go = "question4_l";
			link.l3 = "Vulture.";
			link.l3.go = "question4_l";
			link.l4 = "Roc.";
			link.l4.go = "question4_l";
			link.l5 = "Condor.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "Years of prosperity have passed and faded, like the flame of the lamp, and life abandoned the island. Only the temple was left to stand there as a reminder of the great power of ancient Indians. The last shaman left on a pedestal a holy solar orb, which gave power to the courageous and punished the wicked. It was taken by the man who'd been there before you.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "Years of prosperity have passed and faded, like the flame of the lamp, and life abandoned the island. Only the temple was left to stand there as a reminder of the great power of ancient Indians. The last shaman left on a pedestal a holy solar orb, which gave power to the courageous and punished the wicked. It was taken by the man who'd been there before you.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "What was the name of that sacred orb?";
			link.l1 = "Orb of the shining sun.";
			link.l1.go = "question5_l";
			link.l2 = "Orb of the sunrays.";
			link.l2.go = "question5_l";
			link.l3 = "Orb of the midday sun.";
			link.l3.go = "question5_l";
			link.l4 = "Orb of the rising sun.";
			link.l4.go = "question5_r";
			link.l5 = "Orb of the setting sun.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("VOICE\Russian\hambit\Chavinavy.wav");
				dialog.text = "Wrong answers indicate that you lied to me, white man! You have come with evil intentions! You managed to sneak past the guardians of the temple and the shrine, you figured out how the mechanism of the door worked - but you still won't escape a mortal combat with me. Prepare to die, pale face!";
				link.l1 = "Well, if you insist - let's see, what great warrior you are...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "Your knowledge of my people and my temple do you credit, pale-face. Now I believe you. Go and fulfil that what you came here for. Place the holy relic on a pedestal in front of the condor, where the orb of rising sun used to reside\nThen return to me. Your worship of Yum Cimil and the decision to voluntarily return that which had been stolen by your brothers must be rewarded.";
				link.l1 = "Thank you for your trust, great chieftain.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("VOICE\Russian\hambit\Chavinavy.wav");
			dialog.text = "Wrong answers indicate that you lied to me, white man! You have come with evil intentions! You managed to sneak past the guardians of the temple and the shrine, you figured out how the mechanism of the door worked - but you still won't escape a mortal combat with me. Prepare to die, pale face!";
			link.l1 = "Well, if you insist - let's see, what great warrior you are...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "treasure_alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("VOICE\Russian\Complete.wav");
			dialog.text = "You have done what you promised, paleface. I am glad that you were not the liar like most of your brothers. I will keep my word, too. Here, take this gift from me - the symbol of jaguar warriors' might. Yum Cimil himself empowered this pelt with a bit of his strength.";
			link.l1 = "Wow! It is so beautiful!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "This is not a simple pelt. Once you wear it, you will gain the strength of the jaguar warrior. The power of your weapon which breathes fire and fires lead, will increase dramatically, and you will be able to litter the battlefield with the corpses of your enemies\nBut no mortal can hold the power, which was put into this pelt by Yum Cimil. Once you release it, it shall accompany you only until next midnight, and then it will fade. Take care of it, pale-face, and don't waste its power on a petty skirmish.";
			link.l1 = "Thank you! I will only use it, when I am totally overwhelmed by enemies.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "Now go. And warn your brothers against encroaching on the serenity of these sacred chambers. The jaguar warriors show no mercy for the pale-faces and will give them no quarter.";
			link.l1 = "Farewell, chieftain.";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			sld = ItemsFromID("KhaelRoa_item");
			sld.groupID	= ITEM_SLOT_TYPE;
			sld.ItemType = "ARTEFACT";
			sld.Type = ITEM_AMULET;
			sld.time = 2;
			sld.price = 5000;
			sld.Weight = 10.0;
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}