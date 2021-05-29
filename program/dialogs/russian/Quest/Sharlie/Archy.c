// Арчибальд Колхаун
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

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
		
		case "portroyal":
			dialog.text = "Ha, monsieur de Maure!  Welcome to Port Royal!  Do you still remember me?";
			link.l1 = "Hmm...You're mr. Calhoun, aren't you? Henry Calhoun?";
			link.l1.go = "portroyal_1";
		break;
		
		case "portroyal_1":
			dialog.text = "Almost... Archibald Calhoun.";
			link.l1 = "Oh, forgive me, monsieur. Yes, I remember you. We met at Cape Catoche, on the bay. Your captain was with you as well, William Patterson. I recognized his squadron.";
			link.l1.go = "portroyal_2";
		break;
		
		case "portroyal_2":
			dialog.text = "Absolutelly right, captain! Please forgive my cap. He's always rude with people he doesn't know. You've done excellent, blitzing Fort of Diego de Montoya, which we happened to pare our claws over...";
			link.l1 = "It's for the sake of justice, I might add, that without the preliminary preparation displayed by your captain I doubtfully would have even been able to run up to the gains while under fire of the Spanish cannons. Did your commander find what he was looking for?";
			link.l1.go = "portroyal_3";
		break;
		
		case "portroyal_3":
			dialog.text = "Yes. He nuzzled quite deeply in the casemates under the fort and found some kind of archives. He was unspeakably glad. By the way, if you don't mind my asking, what jerked you to attack that fort in the jungle?";
			link.l1 = "After being defeated by me in Saint-Pierre, Don Diego began constructing a scheme and ended up staging an open attack on Cuba. Then he broke off combat and escaped to the hills toward Main. Well, so I decided to get rid of that yellow dog once and for all. So he'd never bedraggle the French again.";
			link.l1.go = "portroyal_4";
		break;
		
		case "portroyal_4":
			dialog.text = "Yep, I heard quite a few legends about captain Charles de Maure's heroics now I've seen it with my own eyes...";
			link.l1 = "Yeah, Iheard a few things about William Patterson's velour as well. You're lucky to have a captain like him.";
			link.l1.go = "portroyal_5";
		break;
		
		case "portroyal_5":
			dialog.text = "Lucky me, that's true. Though he has become such an important man these days, a man of high society, audiences, balls, parades and private parties... You can't lure him out of the governor's palace every time we arrive at Port Royal. Actually he is right there now again\nCaptain Charles de Maure, can you do a favour for the Scottish drunkard? Join my company and let's have a chat! I am sick of these always the same faces and you seem to be a good person to talk with. Come to my place, let's relax and have a barrel of excellent whiskey. I'll buy!";
			link.l1 = "Hm... Tempting, but...";
			link.l1.go = "portroyal_6";
		break;
		
		case "portroyal_6":
			dialog.text = "Oh stop, captain you need to rest sometimes too. I have some fine hors-d'oeuvres by the way, right out of a local merchant's store I'm renting a room right above the store. Whenever you feel like getting a bite to eat or a drink, you just take a walk downstairs and it's ready, haha!  Convenient, isn't it? Come on, let's go!";
			link.l1 = "You've talked me into it!";
			link.l1.go = "portroyal_7";
		break;
		
		case "portroyal_7":
			dialog.text = "Great. Follow me!";
			link.l1 = "...";
			link.l1.go = "portroyal_8";
		break;
		
		case "portroyal_8":
			DialogExit();
			NextDiag.CurrentNode = "portroyal_9";
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6_back", "PortRoyal_store", "goto", "goto2", "GuardOT_ArchyIntoStore", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "portroyal_9":
			LAi_SetSitType(Pchar);
			dialog.text = "See how nice it is here? Nice and cold... Here are some whisky barrels! Bottoms up, captain!";
			link.l1 = "Well, let's drink to our fortuitous meeting and a pleasant acquaintance!";
			link.l1.go = "portroyal_10";
		break;
		
		case "portroyal_10":
			dialog.text = "Delighted!... Ah! You have arrived at the Caribbean recently, right, monsieur de Maure?";
			link.l1 = "Relatively recently... or not so recently. I don't really know how to put it. I feel like I've lived here half my life.";
			link.l1.go = "portroyal_11";
		break;
		
		case "portroyal_11":
			dialog.text = "Oh, I know that feeling... Although I've been here a long time myself. And when I landed on that damn island that William saved me from... Ohoo, it surely feels like I kissed goodbye half my life over there.";
			link.l1 = "Interesting! What island was that?";
			link.l1.go = "portroyal_12";
		break;
		
		case "portroyal_12":
			dialog.text = "Willy is an old friend of mine, we knew each other when I was still breathing a fair air of Scotland... Good times. I was foolish enough to have a quarrel with damned papists and the Inquisitor himself, so he organized troubles for me. I was a trader back then, had my own flute\nEh, that blasted day my ship was attacked by the Spanish dressed as pirates, we fought bravely but they managed to corner us like rats! Even then the old Colhaun didn't lose his head and jumped overboard with a barrel of water and a few planks\nI used the dark and swam away from my ship unseen. Chances of survival weren't very good, but staying on the ship meant no chances at all. Two days later I cast up on the shore of some desert island\nI had been living in the Caribbean for while and never heard of it until then! It is small and completely uninhabited... and I had spent there two years which felt like an eternity. I still don't know how I managed to save my mind intact.";
			link.l1 = "You lived two years on an uninhabited island?";
			link.l1.go = "portroyal_13";
		break;
		
		case "portroyal_13":
			dialog.text = "I sure did, cursed place! Good thing there was fresh water. I nourished myself with crabs, barnacles, fish, and birds. That's why I named it Crab Island. I didn't have any weapon so I mastered the harpoon, spear, and arrow like a savage man! Ohoo! Drink, drink, captain! I don't mind wetting my whistle as well...";
			link.l1 = "Yeah... I don't envy you.";
			link.l1.go = "portroyal_14";
		break;
		
		case "portroyal_14":
			dialog.text = "There you go!  That's exactly what I said when first set my foot on the beach of that large hunk of sand: 'Old Archy, you're situation is not enviable, but it's not hopeless either'! And you know what kept me alive, captain?";
			link.l1 = "A ship passing by the island?";
			link.l1.go = "portroyal_15";
		break;
		
		case "portroyal_15":
			dialog.text = "No! Labour saved me! Labour, faith and a wish to live! I explored the whole island, every corner of it and I was awarded with a chest filled with carpenter's tools, writing accessories and other little things. You know what I said to myself that moment? Pour more, captain, just pour!\nI said: Archie, you must work to keep your mind in place and the God has given you everything to start doing so. Now you see! I had started building a house close to a bay and you know what? It saved me from ill thoughts and gave me a reason to live!";
			link.l1 = "You're a living inspiration, mr. Calhoun. Not every man would be able to do much of anything at all in a situation like that...";
			link.l1.go = "portroyal_16";
		break;
		
		case "portroyal_16":
			dialog.text = "Yes, old Calhaun was born in Scotland for a reason! Right! We are the sons of the mountains - strong, brave and tough, much better than those featherweights from the marshland. Pour more... Right, what I was talking about? Yes! I worked hard a built a decent house for myself. I also started a journal for everyday writings of my misfortunes. I took the journal with me when Willy saved me\nNow I keep it in this table and reread it in a warm, soft bed every time we stay in Port Royal\I wrote everything in it, everything happened to me before and I after I got there. It is one of the reasons I still have my mind with me.";
			link.l1 = "So it turns out that Mr. Patterson picked you up off the island? But how could he have found it? You said...";
			link.l1.go = "portroyal_17";
		break;
		
		case "portroyal_17":
			dialog.text = "Yes, yes, the island is not marked on any map. But Willy, he's old Willy! He can do anything! And he found that god damn island and saved me, for what I will be grateful to the end of my life. Yeah...";
			link.l1 = "Do you like serving mister Patterson? Would you go again on your own resources?";
			link.l1.go = "portroyal_18";
		break;
		
		case "portroyal_18":
			dialog.text = "I'm done with being independent. Willie's young and successful and also I'm a long time friend of his. What else do I need? No, I'll be with Willy until the end of my days, or at least until he kicks me out the next time I get wasted, haha! Speaking of getting wasted, pour it on!";
			link.l1 = "Akh...(drinking) Tell me, Mr. Calhoun. I heard you, uh, used to be a treasure hunter. Is that so or is it just nonsense?";
			link.l1.go = "portroyal_19";
		break;
		
		case "portroyal_19":
			dialog.text = "Who told you that? Well, no sense in trying to hide it. I used to. Didn't turn out well though, such treasure hunting had led me to the blasted Jesuits and to the island. Holy fathers had tortured a man to death because of me, and I myself... oh, let's keep the past in past\nI have paid enough for my sins and I hope to never repeat such in the future. No, Willy won't let that happen, I am sure!";
			link.l1 = "Listen, Archibald. Have you ever heard of a man named Miguel Dichoso?";
			link.l1.go = "portroyal_20";
		break;
		
		case "portroyal_20":
			dialog.text = "I've never heard that name before. Who is he?";
			link.l1 = "Oh, nobody interesting... just a man that likes searching for adventures and treasure. But since you haven't heard about him, we won't talk about him.";
			link.l1.go = "portroyal_21";
		break;
		
		case "portroyal_21":
			dialog.text = "Yes, let's not! Let's talk about old Europe instead! I remember twenty years ago in Scotland...";
			link.l1 = "...";
			link.l1.go = "portroyal_22";
		break;
		
		case "portroyal_22":
			DialogExit();
			AddDialogExitQuest("GuardOT_MCOutFromArchyRoom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
