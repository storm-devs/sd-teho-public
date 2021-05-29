// диалоги Уракана, Канека и прочих индейцев ица
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Is there anything you need?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("Another pale-faced... The great priest will be overjoyed to carve out your heart...","Pale-faced knows how come to Tayasal, but no one leaves our city!","I'm surprised, pale-faced: you still did not go to spirit land... Walk while you can, soon you see your ancestors.");
			link.l1 = LinkRandPhrase("Well, well. We'll see...","Don't scare me, red-skinned warrior. I've seen worse than that.","Go, go. You'll frighten your children.");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("Bless me for this battle with foe, great Cavil!","Great Cavil and great Kukulcan reverence us their presence. Even in ancient Maya this not happen!","We pass legend of great battle of Kukulcan and Cavil our children!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "You are great warrior, pale-faced. We bring your blood to gods. You die with dignity.";
			link.l1 = "Easy there, red-skinned warrior. I'm not gonna let your Kanek bring me as a sacrifice to Kukulcan or anybody else for that matter. Your warriors were not able to capture me and everyone of them has fallen in a battle.";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "Yes, you are a gracious warrior, pale-faced. But you not withstand hundreds Tayasal Itza warriors. However, you say interesting word. How you know about great Kanek and Kukulcan?";
			link.l1 = "Well, let me guess... Since you're not Kanek, then your name is probably Urakan and you're the son of priest Kanek?";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "Your lips speak truth, pale-faced. I am Urakan, and I am surprised.";
			link.l1 = "You're going to be even more surprised when you have a look at this... Look.";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "Oh, gods! If this pale-faced has mask, then that means the time is come... You are the one that Kukulcan has told about. He ordered to bring you to him as soon as you arrive to Tayasal. He knows you come.";
			link.l1 = "Kukulcan?! He's here in Tayasal?";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "Yes, white warrior. Quetzalcoatl come Tayasal. Soon he leaves to bring light our ancestors, great city of Maya.";
			link.l1 = "God damn it! So, HE'S already here...(lowering voice) Urakan, I know everything. I know that you're the one who sent Ksatl Cha with the Guardian of Truth to search for Ksocheatem and the mask of Kukulcan...";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "I see a surprise in your eyes and a doubt, great chief Urakan. You're not happy with Kukulcan, am I wrong?";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "Every Itza warrior happy great Kukulcan come, white warrior. You must stand before Kukulcan. He waits for you many nights. He is great prophet. He knows everything ahead of time. Go to Flying Snake, you have no other path. We not allow you leave Tayasal.";
			link.l1 = "Don't you understand that as soon as Kukulcan leaves through the gates of time, all of you, as well as you personally – will cease to exist? And the best part is that you will be reborn in another image, another body... Maybe a simple warrior. Or maybe a cripple or a beggar...";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "Go, pale-skinned warrior. You find Kukulcan in Great temple of Itza warriors. Go strait on bridge, until you see big pyramid. Go in lower door of temple and approach sanctuary.";
			link.l1 = "All right. I will go to Kukulcan, for I see that we are not to escape this encounter. But I've warned you.";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "Go, white warrior. Kukulcan waits for you.";
			link.l1 = "I'm on my way...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("VOICE\Russian\Complete.wav");
			dialog.text = "It's came true! As soon I see how you fight Kukulcan I know that you are Cavil himself and you come Tayasal to save Itza people from death because of my father and Kukulcan. My father, the great priest Kanek doom Itza people in glory of long dead ancestors Maya\nI am war chief Urakan who protect Itza people for many years. Not a single paleface leave Tayasal alive. Me and my warriors made sure Itza people stay protected and alive for many-many years to come. I don't want to sacrifice all my people.";
			link.l1 = "I knew that, Urakan. And I asked you to help me on the bridge.";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "Nothing hide from eyes of great Cavil. Forgive Urakan that he not understand who you are right.";
			link.l1 = "Don't worry about it, chief. I've defeated the mortal embodiment of Kukulcan, but we have a second important task lying ahead – to close the gates to the past. This unnatural hole in time must be eliminated. Will you help me?";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "What Urakan help you with, oh Cavil?";
			link.l1 = "You sent Ksatl Cha with the Guardian of Truth to search for Ksocheatem and the mask of Kukulcan. So, you know that it can be used to close the gates of time. Did your father tell you of that?";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "Father not speak. I study writings in temple of Knowledge and Wisdom. But much may be unclear Urakan. Maybe, Cavil can understand?";
			link.l1 = "What exactly did you find out?";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "I learn by heart. Writing proclaim: 'When sun arises against rain, and fire between them in triangle, strike Tohil leg against leg and incinerate mask of Kukulcan on alter of time. And seal then Itzamna gates of time until end of days.'";
			link.l1 = "What.";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "Yes.";
			link.l1 = "Jesus... Show me the gates.";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "They are located in the temple Kukulcan. But door there is locked. Only my father can lock and unlock them. When he open door temple Kukulcan, he say: 'Sun come and go, water fall and subside, fire ignite and fade, war and peace interchange, but only heaven is forever. Above time is only heaven.'";
			link.l1 = "Interesting... Let's remember that and see what we can do...";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "I will be here, down below, near alter of time. I suggest you seeing every pyramid and building in Taysal from inside. Find keys. I'll stay here.";
			link.l1 = "If I have any questions of importance, I'll definitely come to you.";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "Can Urakan help somehow great Cavil with advice or action?";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "Take a look at this tablet I found. Judging by the place I found it, it must have had something to do with your father and it's clearly not a regular item...";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "I found another entrance on the top of the Great Temple, but it's sealed. How could I get inside there? Possibly, what I'm looking for might be in there.";
				link.l1.go = "treasure";
			}
			link.l9 = "Nothing right now, Urakan. I'll manage myself...";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "Gods stone plate. My father has several different pieces and he very values them. Ancient Tayasal builders used plate to activate hidden mechanism, to open and close the door, even to do magic rituals\nThey work if put in the right place - that is what my father does. But I am a warrior just like you, don't know how to use them right. Perhaps Cavil know?";
			link.l1 = "We'll definitely get to the bottom of it...";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "This is the door to treasures of Tayasal. There lie riches of Itza Indians. Door inside only my father open and close. No one dare enter to treasures without him. Not even I.";
			link.l1 = "How did your father open the entrance?";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "My father said: 'Any riches have two side. Only he who know these two side enter to treasures of Tayasal.' What this means – I not know. Maybe, Cavil guess?";
			link.l1 = "We'll figure this one out too...";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("VOICE\Russian\Complete.wav");
			dialog.text = "You did it, oh great Cavil! People of Itza now safe. I, Urakan, son of Kanek, assure you that I not put shame on the honor you give me and I protect Tayasal from any invasion of dishonorable pale-faced in your name.";
			link.l1 = "I can well believe it, chief. Well, we can celebrate now: we have put a crimp in the treacherous plans of Kukulcan. He'll never be able to materialize a time revolution again.";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Glory great Cavil! To me and my generation befall great honor see Tayasal two gods. We write about this history for our children. They know about battle of gods in Tayasal! Glory Cavil! Glory!";
			link.l1 = "I need to drink...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "You stand before the Winged Serpent, paleface. Spirit of mighty Kukulcan in human flesh. You lucky to be brother through father of his embodiment as I lucky to be father of mother gave him birth. Great honour. Perhaps that is why you become a strong warrior and still alive\nBut your time run out, paleface. We start new time, time of great Maya. We establish our own power and never let palefaces to come our world. Soon. I, Kanek the priest, go to start the ritual!";
			link.l1 = "Wonderful...";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "Urakan, you heard what our lord said. Submit now!";
			link.l1 = "When great ones battle against each other, it is better for us simple mortals to just stand aside and gaze from a distance, father...";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "What?! Come to your senses, son!";
			link.l1 = "This man is Kukulcan's brother and a great warrior. I see the embodiment of Cavil himself in him! No one besides him could withstand a god like THAT. Don't doddle in the duel of the gods, father! And if you bring offerings to Kukulcan, then my warriors will give their blood to Cavil!";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "Are you in your right mind, Urakan?";
			link.l1 = "Many years I, named after Hurakan, have successfully protected our lands in Cavil's name from the invasion of outlanders. Hundreds of them have fallen under our clubs and no one has left Tayasal. But never in all my life I have seen a warrior so strong and swift as this pale-faced. If he was able to defeat Kukulcan, then he's embodied the spirit of Cavil himself!";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
