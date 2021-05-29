// Джино Гвинейли - алхимик
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
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "Oh! Good day, sir. How did you get here?";
				link.l1 = "Good day, Gino. Let's get to know each other. I am captain "+GetFullName(pchar)+" and I am here with John's permission. I am going to make it clear - I need your help, but I also can help you.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh! Good day, sir. How did you get here? And where is John?";
				link.l1 = "Well, well... And that's who was always hiding behind this closed door! Interesting... About John... He has gone away. And this house is mine now. But don't worry. Let's get to know each other, who are you and what are you doing here?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "Hello, " + pchar.name + ". Your face tells me that you have found something important. Have you found all components of the Guardian of Truth?";
					link.l1 = "Exactly! I have got all three items with me: the dagger, the map and the compass!";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "Hello, " + pchar.name + ". What happened? You look strange...";
					link.l1 = "I have got something to talk with you about, Gino. It's big.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Yes, I remember, two days has passed and you want to know about the Guardian of Truth, am I right?";
					link.l1 = "Yes, you are! Were you able to dig up anything?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "Have you brought 5 000 pesos, " + pchar.name + "?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "Sure. Here, take the money and buy all you need.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 3, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 4);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 4);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 4);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "Unfortunately, I don't have money now.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "Alas, " + pchar.name + ", I am so sorry - the patient is dead. He suddenly got worse and he passed away very fast.";
					link.l1 = "Too bad... May the God have mercy on his soul!";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "Hello, " + pchar.name + ". Has something happened? You look very worried...";
					link.l1 = "Gino, I have got an unusual ask for you! There is man in fever on my ship. He is delirious and unconscious... can you help him?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = "" + pchar.name + ", I am waiting for the patient. Hurry up, the sooner you will bring him here, then more chances I'll have to save him.";
					link.l1 = "Yes, yes, he will be delivered here at once.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "You have brought him just in time, " + pchar.name + ". Critical conditions, yet there is still a chance\nCaptain, I am running out of ingredients and we don't have time to gather them in the jungles. I have to buy them all from the local herbalists for 5 000 pesos. Can you provide the sum?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "Sure. Here, take money and buy all you need.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 3, false);
					}
					else
					{
						link.l1 = "Unfortunately,  I don't have money now.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесет через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "I have nothing to say now, " + pchar.name + ". I am fighting for the patient's life. There is still some hope. Come and see me later, I suppose that I will be able to tell you something more specific soon.";
					link.l1 = "Fine, Gino, I will be back later.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "I have got news," + pchar.name + ". I won't say that your man is alright, but he lives. The illness is retreating and there is a progress to see. To be honest, I didn't expect that my potions will help him that good.";
					link.l1 = "It is a very interesting information, Gino, but tell me when will I be able to take him? We have a long way to sail and the clock is ticking.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "Good day, captain. Glad to see you.";
					link.l1 = "How is our patient, Gino?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "Good day, captain. How are you doing? Need my help?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "Yes. Gino, I take it that you are an erudite man and perhaps you must even know Latin...";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "I have something different. A small present for you. Here, take a look at this book.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "Yes, Gino. I want to show you this pistol. Have you ever seen anything like it?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "I have brought an example of the charge for my pistol.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "What about charges for the pistol? Got any ideas already?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "Gino I've found an unknown word 'gord' in one captain's log. Do you know what it means?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "Good day, Gino. I am doing fine, no help is needed. Just wanted to check on you and to talk a bit.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "My name is Gino. Gino Gvineili. I am a scientist. My job is to make powders, mixtures and other medicines for mister Murdock. But since he is gone...";
			link.l1 = "Well, I am "+GetFullName(pchar)+". A captain of my own ship. So, you are an alchemist then?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Not only an alchemist, but also a physician. I posses quite a knowledge of medicine. I know many things about healing herbs and I am able to brew mixtures and potions from them. But chemistry is my calling, I do a lot of experimenting and some of my inventions might help such person like you.\nI know Latin, French, English and Italian. My help will be indispensable if you are planning to run a drugstore like mister Murdock did...";
			link.l1 = "Oho! It is not every day you meet such an erudite man. Pharmacy's business is fine for sure, but I am a sailor...hm, that sounds strange even to me... anyway, I am sure that we will become friends, Gino. You can continue living here and do your science things...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "And if I will ever need a help from an alchemist, a healer or a scientist - I will know who to ask... Tell me, why do you always live inside? Don't you even go out?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "I do go outside when I need to buy some ingredients or herbs for my experiments. I like living alone, that is my way. I have dedicated my life to the science and find no interest in ordinary life. Books, writings, test tubes, retorts…\nMister Murdock gave me such opportunity in exchange of helping him to make drugs.";
			link.l1 = "Now you will have even more time, Gino. But you will have to give up some of your experiment's time to me in case I would need your help, deal?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Sure, captain. I will call you captain, "+GetAddress_Form(NPChar)+", if you don't mind? I will leave all my researches in case you will need my practical skills or theoretical knowledge.";
			link.l1 = "Splendid. I am glad that we have understood each other that fast. Don't worry about your board, me or my purser will leave you reasonable sums from time to time.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Thanks, captain. I don't need much... Yes, captain, I have an idea... why don't you learn some alchemy skills? It can be really useful for you.";
			link.l1 = "Hm. As my brother has told me once - don't be squeamish about learning how to do things with your own hands. Sure I want. What can you show me?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Well, certainly, you won't be able to turn iron into gold, it is impossible... yet, but you can learn how to mix ingredients according to instructions and in order to get potions or other useful items as the result. Here, take this bag. Everything that the beginner alchemist will need. Test tubes, flasks, retorts, still, spatulas, glass tubes, burner and so on...";
			link.l1 = "Fascinating!";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("You have received an alchemist's kit");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "You must know a recipe in order to make a potion or an item. Recipes can be bought from merchants or be found anywhere. Once you have studied a recipe, you should collect every ingredient needed and do exactly what is written there\n Use your alchemy tools, find or buy mortar and pestle, look for a crucible, alas, I don't posses an extra one to give you. Herbs, spirits, potions, minerals, garbage - everything will do, providing you have right recipe and tools.";
			link.l1 = "I see. I will try to mix something in my spare time. Thanks, Gino! Can you give me any simple recipe? Something to start with? ";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "I don't have simple ones... but here, take this recipe of an antidote. I suppose that you are able to handle this task. Take it.";
			link.l1 = "Gratitude! I will learn. Goodbye now, Gino! Watch after my house, I fear that I won't visit this place very often so you are welcome to use not only your room, but also the rest of the building.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion3");
			Log_Info("You have received an antidote recipe");
			PlaySound("interface\notebook.wav");
			Log_Info("You need to have Alchemy skill in order to craft your potions, amulets and items!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "Yes, captain, I know the language of ancient Romans. Every scientist, especially a healer or an alchemist, must know Latin. Do you need something of my Latin knowledge?";
			link.l1 = "Yes. Gino, don't consider me as a fool but... well, how to explain...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "Speak as it is, captain. Don't be shy.";
			link.l1 = "Fine. Can you make a list of scholar Latin aphorisms for me? You see, there is... a man who likes to boast of his 'erudition' and sometimes he uses that Latin phrases to show me my ignorance compared to him. Something like... 'pasem-bellum'...";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "'Si vis pacem, para bellum', you mean?";
			link.l1 = "Yes, yes. I want to learn them to beat my arrogant br... my friend.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "There is nothing strange or shameful in your ask, captain. Knowing the aphorisms of ancients which went down in history, makes you an educated man. Here, take this text. It is what you have asked.";
			link.l1 = "Thanks, Gino! Appreciate it! I will read it in my spare time...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("You have given Lavoisier's chemistry textbook");
			dialog.text = "Show me... (reading) Impossible! A 'small present' you say? This book is priceless! Where did you get it?! This is... a real treasure!";
			link.l1 = "I am glad that you like it.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(Reading) Incredible! I have never even heard about that... and this? I don't understand a thing here... but I will, damn it! Oh, soon the work will be boiling in my lab! "+pchar.name+", you don't even realize WHAT have you given to me...";
			link.l1 = "Why don't I? I do. The scientific book for the scientist...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "But who is the author of this miracle? Antoine-Laurent de Lavoisier, France... Never heard of him. But wait! How is it possible! The year of printing is 1789? But how...";
			link.l1 = "I don't know why is that year is written there too. Well, maybe I do. But I won't advice you to think to much over it. The book is useful and that is all what matters.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "It is promising beyond measure and that year must be a printing mistake of some sort... Whatever. Thank you very much, captain!";
			link.l1 = "You are welcome, Gino. It is all yours.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "It is not all, Gino. I want to show you this pistol. Have you ever seen anything like that?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "I am no gunsmith, but I will take a look... no, I have never seen anything like it. And why do you ask?";
			link.l1 = "This pistol is powerful and destructive, but there are special charges needed to shoot it. Nothing else would work. And I have no idea how to make more rounds for it. So I came here for your advice.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "Do you have got at least one round to show me as an example? If you don't, then I fear that I would not be able to help.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "I do. The charge is made of two parts: the round itself with a bullet and this thing which explodes the powder.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "Such a fail! What a shame! Fine, perhaps, I will find more and bring them to you.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("You have given a revolver's cartridge");
			Log_Info("You have given a capsule");
			PlaySound("interface\important_item.wav");
			dialog.text = "Interesting! That looks simple, there is a powder inside, a bullet goes from above, but it looks a bit strange. And this 'thing'... hm. Powder doesn't explode without it, right? Curious... Look, captain, leave all of this to me: the pistol and charges. Come and see me in a month, I need time to deal with it.";
			link.l1 = "Great! Try to understand how it works I really want to shoot this pistol.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "The main problem is to find out what this substance, which explodes powder, is made of. This book will come in handy. I will try.";
			link.l1 = "Fine. Farewell, Gino!";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "Yes, I dealt with the charges to the pistol. I have to give a credit to the book you have presented to me. It wouldn't have worked without it. But I have to warn you, captain, it won't be easy to create rounds and capsules to you weapon.";
			link.l1 = "Capsules?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "It is that 'thing', as you said, which explodes powder. But let's go in a succession. Are you ready?";
			link.l1 = "Yes! I am listening to you very carefully.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "So, first, you need to craft a special bullet. Common bullets won't work. It must have some special conic form. You will have to find a mould for such bullets, the bullet mold as I have called it. Take an ordinary lead bullets, melt them in crucible and pour melted lead in the bullet mold, freeze it and take a ready bullet.";
			link.l1 = "And where can I find such bullet mold?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "I don't know, captain. I am an alchemist, not a blacksmith. Take this bullet as an example perhaps you will find out what to do.";
			link.l1 = "Fine. Go on...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "Then you have to make a container for powder. You inject a bullet there. I have written a nice instruction for you. Read it carefully and give it a try.";
			link.l1 = "Good...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "Now we have got capsules on the row. You will need a very thin copper sheet - craft it yourself of the copper nugget of whatever. Carve circles on it the same size as rounds. Then put inside them a fulminating silver using wax.";
			link.l1 = "A fulminating silver? What is that?";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "I didn't know about it myself, learnt the secret from your book. It is a white powder which can be made of silver, spirit and nitric acid. It explodes from any rubber or shake that is why it serves to fire a gunpowder in your pistol's rounds. An unpleasant thing, it has exploded twice during my tests until I came up with the recipe.";
			link.l1 = "I was lucky to have this book with me!";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "Be strongly careful, this thing is explosive as hell! I could make some amount by myself, but it is too dangerous to store the fulminating silver, it is vital to put it in capsules right after it's creation. I can't craft copper capsules, I am no blacksmith as I've told you once.";
			link.l1 = "Fine. Give me the recipe, I will learn myself.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "You are welcome. Accurately follow the recipe and be careful with an order of process or you will fly sky high with your flasks.";
			link.l1 = "I will be careful.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "Also, take these two flasks. This one has nitric acid inside and this one has spirit. You will be able to make fulminating silver enough for filling about 20 capsules.";
			link.l1 = "Thank you, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("You have received a flask of nitric acid");
			Log_Info("You have received a flask of spirit");
			PlaySound("interface\important_item.wav");
			dialog.text = "Also take your pistol and the example charge. Good luck, captain, in your crafting of charges. I hope that you will stay alive and in one piece.";
			link.l1 = "I will do what I can to protect myself. And, Gino, have I told you that you are genius?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "You are making me blush, captain, I am serious...";
			link.l1 = "Fine. Goodbye, Gino! You are my best alchemist!";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "Gord, gord... Would you tell me more about the captain? Where is he from?";
			link.l1 = "No idea, although he was born somewhere in the North, they called him a Viking sometimes.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "A Viking! Yes-yes, I remember, I've read about this in a history book. Gord is fortified settlement of a free jarl.";
			link.l1 = "A free jarl? Who would be that?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "It's a prince of the Northmen. Free jarls with their war bands used to raid and plunder Europe centuries ago on their ships, Drakkars. You could call them pirates, I suppose. Gords were their bases and homes, places where they could rest, farm and feast.";
			link.l1 = "I see. This gord must be his pirate lair then... Thanks, Gino!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "Fever and delusions, you say, that is intriguing. Deliver him here immediately! I will see what I can do. But I can't promise you anything if his condition is too bad... Is he your officer?";
			link.l1 = "No, thanks God, he is not. Gino, listen, don't ask who he is, just do what you can, it is really important for me!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "All right, bring him in the house to your room. I will prepare some mixtures... perhaps this root will...";
			link.l1 = "I am going to deliver him here immediately!";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			pchar.questTemp.Portugal = "Portugal_wait";
			int iShipType = GetCharacterShipType(pchar);
			ref rShip = GetRealShip(iShipType);
			sTemp = "My_" + rShip.CabinType;
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_9";
			ChangeCharacterAddressGroup(sld, sTemp, "rld", "aloc0");
			LAi_SetStayType(sld);
		break;
		
		case "Portugal_nomoney":
			dialog.text = "Then try to find them as soon as possible I won't be able to heal him without medicines and it might get too late if you will not hurry.";
			link.l1 = "Fine, I will find the money.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Splendid, captain. Now I will deal with preparing mixtures and you'd better leave my patient. Come back here tomorrow.";
			link.l1 = "Fine, Gino. I trust in your mixtures and in your genius.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "Well, I think, that he will be fine in two weeks. I can't promise that he will be able to dance but at least he will stand on his feet himself, that is for sure.";
			link.l1 = "Damn it, I don't have these two weeks! I need... to set sail as soon as possible!";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Captain, I am not a mage and I tell you that the man is too weak for now. I am not sure that he will survive few days on the ship, you can't move him!";
			link.l1 = "Fine-fine, but two weeks, no, even one week is too much!";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Three days... yes, I suppose in three days you may try to sail, but he will need a care, medicines and you will have to do stops.";
			link.l1 = "I have got a doctor, he will take care of him. I will be back in three days and we will take him, it is the most I can afford. We have to move, even with stops...yes, and one more thing - Gino, you are a genius!";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "Thanks, captain. Come back in three days for your friend, but don't bother him until then. He needs a full rest.";
			link.l1 = "Fine, I got it. I will take him in three days.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "He is doing well, but the progress is slow. He can't be taken yet.";
			link.l1 = "Yes - yes, Gino, I remember. Three days...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "No deterioration, but he didn't get better really. He is still unconscious, he doesn't understand where is he and why is he here, though it doesn't seem to concern him that much. He still got fever so I am not sure that taking him aboard now is a good idea.";
			link.l1 = "I can't wait any longer, we have been here for too long already. Pack your mixtures which will help him in voyage and we are leaving. I hope that this bastard is strong enough to survive long enough to face his death sentence...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "Wait, captain! Have I been treating the condemned? What the hell? The huge work was done here, do you have any idea how difficult is it to make the dry powder...";
			link.l1 = "Gino, you didn't need to know that. Don't worry too much, he is a pirate and one of the most terrible of the kind. I have to take him to Curacao for a date with the Company's authorities as soon as possible. Period.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "Fine, you know better. Pirate then... Curacao. Whatever, but listen to me, he will be sleeping most of the time, but the ship's rolling and stuffy heat can backward all process. I recommend to make a stop after a few days of sail and to let your... prisoner to rest on the land. Otherwise there is a risk that they will have to hang a corpse at Curacao... ";
			link.l1 = "Fine, I'll do that. Martinique will do fine, it is almost a half of the way. I hope that the wind will be fair. I am going to take him now and we will leave. Thank you again, Gino.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "You are welcome, captain. Remember that you have four days, well, five but not more. And one last thing... you know, I usually heal people not because I want them be hanged after my treatment. The doctor is responsible for his patients no matter who are they. And I am feeling really bad...";
			link.l1 = "I am sorry for dragging you in all of this, but we had no chance without you. We have to set sail now or the Portuguese's lads will manage to assemble at our doors to meet their boss otherwise.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "Intriguing... And how you can help me? I don't need help and I didn't ask for it...";
			link.l1 = "But you will need it. Listen to me first and then conclude.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "I am all ears.";
			link.l1 = "I have been in Santiago recently... visiting father Vincento. So, he was looking for his missed secretary named... Jesus, why have you gone so pale, Gino?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "You... have you seen the inquisitor? Is he...";
			link.l1 = "Don't worry, Gino. No chance I will give you to him, though that was his order: to find you and to bring you to him. I need acquire some information regarding one Indian of Itza people. Tell me about Tayasal, it's treasures and the 'evil' about it.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "I see that you are well informed. Did father Vincento tell you this?";
			link.l1 = "I got something from him and something from other people. But I'd like to hear you out. You once were his secretary, so you must have been recording a protocol of interrogation, am I right?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "You can't imagine what was he doing to that poor Indian!.. It makes my flesh creep every time I recall that interrogation in my mind.";
			link.l1 = "Still, let's talk about it. Who was that Indian? How did he get to father's Vincento hands?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "He was among the Indians of Itza people who traveled from Tayasal in a search of the Kukulcan Mask - an artefact of ancient Maya god - Kukulcan. Those Indians faced a band of white adventurers lead by Archibald Calhoun - a treasure hunter from Scotland. Only one Indian survived, his name was Ksatl Cha. He had three interesting items on him, I will tell you about them later.\Calhoun had tried to force the prisoner to tell him about treasures, but he kept silence. So the Scot delivered him to Santiago, to father Vincento in exchange for permission to visit Spanish cities during a year. He knew that the inquisitor is very interested in all kinds of local mysteries and legends. Vincento made the Indian talk. He was talking a lot, he told us everything he knew and the information we got out of him shocked the inquisitor himself.";
			link.l1 = "You don't say? And what could make His Grace to tremble?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "I will tell you everything in order. There is an ancient Maya city called Tayasal in the depths of Yucatan's jungles. It is inhabited by the offsprings of Maya - the Itza people. They try to live their lifes according to the rules and traditions of their ancestors. Surely, they don't like the state of the modern world - I mean the dominance of white men.\nThey dream about good old times. And here comes the most interesting part. A bunch of white adventurers accidentally got close to Tayasal and kidnapped a daughter of supreme chief of the Itza people. It happened almost a quarter of century ago\nThis was the last straw and Kanek, the chief, was enraged. He decided to conduct most dangerous and secret rituals of Maya - to summon an Indian god in order to erase all offsprings of white conquerors...";
			link.l1 = "Hm... That must be the demon of which father Vincento was talking about. But how should this Indian god deal with white colonists? To show itself in a form of dragon and burn them all?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Oh, "+pchar.name+", leave these fire monsters tales to the old grannies! Actually, you were not so wrong, but our case is more difficult and serious. Even the Flood won't be able to stop Europe from expanding in the New World. Ten more alive will come to replace one dead. Kanek needed to destroy the possibility of European colonization itself.";
			link.l1 = "Well, it did happen already.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "You are thinking in the right direction, captain... The purpose of the Kanek's rite wasn't only in calling the high being, but also to create the spatio-temporal hole.";
			link.l1 = "What?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Ancients of Maya people possessed quite a knowledge, captain. Kanek found a description of the rite which allows to control the time.";
			link.l1 = "Whoa! Incredible!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Listen. The ultimate goal of the ritual is to alter the past to make the appearance of white men in the New World impossible. In order to do such a thing, they are going to send someone in the past, someone who holds authority, power and ability to change people's fates. But most importantly, such person must posses modern knowledges\nThink about it, "+pchar.name+", what would had happened to Columbus if his caravels were met by Indian fleet of frigates and galleons armed with modern cannons? And hackbut's of white soldiers would be opposed not to bows and spears, but to mortars and muskets?";
			link.l1 = "I suppose that the Americas would not be discovered at all....";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Exactly! And perhaps some Indian 'Columbus' would have discovered Europe...";
			link.l1 = "Interesting, and who Kanek is going to send to the past? One of his naked warriors? I doubt that he will be able to teach his ancestors...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Don't laugh, captain. Kanek wasn't wasting years in Maya's temples reading their writings. An Indian God must be sent to the past in a human form...";
			link.l1 = "Gino, what the nonsense are talking about? Are you....";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Even the Son of our Lord, Jesus Christ, has come to our earth in human form and was born by the human woman, the Holy Virgin Mary...";
			link.l1 = "Jesus, Gino... are you serious?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Sure I am. Ksatl Cha was very persuasive...";
			link.l1 = "But which God Kanek decided to choose for such 'noble' mission?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "The rite was meant to call only the one High Being. The feathered serpent, Quetzalcoatl, Kukulcan...";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "Kukulcan?! I have already had an imprudence to meet with his 'spirit' which is living in statues. Now I see... go on!";
			else link.l1 = "Hm. Interesting. I have already heard that name from father Vincento... go on!";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Kanek decided to summon Kukulcan, since the Itza already had an ancient artifact of this god - the Mask of Kukulcan. One who has the mask is able to go through the portal and only the owner of the mask will be accepted by the ancient Maya as a living god.\nThe priest conducted the ritual, summoned Kukulcan to incarnate in the body of some mortal. He also created a time hole which extracted several random people from the future.\nThe goal of such extraction was to present Kukulcan's incarnation not only knowledge of modern times, but also of the future. But something went wrong and all those people got elsewhere but Tayasal. I never met any of them.\nSeveral portals were created within the archipelago, they were supposed to transport owners of future knowledge and Itza agents all across the area and to Tayasal. But these portals failed their purpose, no one had been ever delivered to Tayasal for the last 25 years...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "Sure... Because these portals transfer captured people only to each other. Incredible!";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "Interesting...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "Have you seen those portals? Tell me!";
			link.l1 = "Maybe later, Gino... I am more interested in your story at the moment. Go on!";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Father Vincento is aware of everything I have told you. This made him worry, of course. If Kukulcan, incarnated in human form, will get to the portal along with the Mask and all the knowledge he gathered… End of times. Apocalypse\nIf the past alters - future does the same thing. Our reality will change, it will disappear, dissolve. You and I may never be born. Or we shall be different. Once Kukulcan reaches the past - we shall seize to exist.";
			link.l1 = "And who is the Kukulcan's incarnation?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Who knows. He might be in anyone who was born a quarter of century ago, when the ritual was conducted. In you, for example… just kidding. But we still have a chance. First, Kukulcan's incarnation is just a mortal person, he can drown, be stabbed, be shot or die of fever. And in such case, no apocalypse will ever happen.\nSecond, it is impossible to reach the past absent the mask, Kanek stashed it very well, maybe too well so it seems. It might be, that even incarnated Kukulcan will fail to find it.";
			link.l1 = "Tell me more.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Some time after the ritual, a group of Spanish conquistadors almost reached Tayasal and almost made it to the treasury. Itza managed to kill them all except one - a strong giant seven feet tall\nKanek was worried that the Mask could be stolen by any stranger, so he decided to protect the relic. He had invented his own ritual, using the ancient Maya's knowledge. He took three items which, as he believed, held power of white men. A dagger which once was a property of Cortez himself and a compass. He also used that dagger to carve out a piece of skin from the back of captured Spanish giant. The man himself was sacrificed on the altar of Kukulcan. Three items were used in the ritual\nAnd from this ritual a new island was born, in the open sea, not far from Yucatan. No one know it's location, but the Mask is stashed there. In order to find it, one must use the dagger, the compass and the piece of skin. Besides, all items from the treasury are cursed, not a single one of them can leave the archipelago.\nAn attempt to do so will cause a storm which will take the ship right to rocks of the island. It is called Ksocheatem. Smart, isn't it?";
			link.l1 = "Maybe too samrt. No arguing on that. But how in the world was Ksatl Cha so well informed? I doubt that Kanek was sharing such knowledge with common warriors...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Thing is, that the current chief of Itza, Urakan, the son of Kanek, had told this warrior everything. He sent Ksatl Cha with a group of warriors to find the secret island and the Mask of Kukulcan. He had given him the Guardian of Truth to do that, it is the name of three items together - the dagger, the compass and the map made of human skin.";
			link.l1 = "The map? And why did Urakan need the Mask? He decided to alter the past himself?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "The skin has contours of the archipelago on it, so they call it the map. Urakan wanted the Mask for a very simple reason - he does not want to destroy the existing reality and to sacrifice his life and lifes of his people for the glory of the ancients.\nThat is why he was going to destroy the Mask at all costs. But Ksatl Cha was captured by Calhoun and... well, you know the rest of the story. He never reached Ksocheatem.";
			link.l1 = "So it is possible to prevent the end of times by finding and destroying the Mask? And where is that... Guardian of Truth now?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "The dagger 'Chief's claw' and the compass 'Arrow of the Way' were left to Calhoun and the skin map 'Of two appearances' is still somewhere in the inquisition. Calhoun used it as a gag to shut the prisoner's mouth. He had no idea what were these items for.";
			link.l1 = "What did you just say? 'Chief's claw'? Damn it, but this dagger is on me right now! Fadey has given it to me as a repayment of his debt to my brother! Take a look!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "Incredible... It really is. I remember it.";
			link.l1 = "Gino, tell me, what exactly does father Vincento know of your story?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "Everything, except information concerning the Guardian of Truth and how to make it give out the location of the secret island with the Mask of Kukulcan. Ksatl Cha told me when we were alone right before I gave him a poison mixture to end his suffering. He died with a smile on his face.\nSurely, I couldn't stay in Santiago any longer. I had serious suspicions that I became a too important and dangerous witness for the inquisitor. Father Vincento always gets what he wants, no matter the cost. Ksatl Cha told him about the treasury in Tayasal.";
			link.l1 = "These treasures were already found by one adventurer named Miguel Dichoso. Have you heard of him?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "No. And where is he now with his treasures?";
			link.l1 = "I want to know it myself. That is why I came to you, I am looking for that Indian gold. Dichoso has taken the treasures to Europe and disappeared with them.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "I will tell you where are the treasures and Dichoso himself.";
			link.l1 = "Gino, you are surprising me. How'd you know that?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "You could already figure this out yourself from my story, captain. The treasures of Tayasal were cursed - not a single item is able to be taken away from the archipelago. Any ship...";
			link.l1 = "... will be caught by the storm and thrown on the island where the Mask of Kukulcan is hidden! I was blind, but now I see. It seems that I know enough to find Ksocheatem, the treasures and the Mask itself!";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "Want to save th world, captain?";
			link.l1 = "I want to find my prodigal brother... Gino, how to make the Guardian of Truth to show a location of the island? You said that you know how!";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "I know the method, but I don't know the details. I won't be able to help you until I have all components of the Guardian.";
			link.l1 = "Hm. We have already got the dagger. Only compass and map are left. Calhoun has the compass and father Vincento has the map...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "Are you going to return to the inquisitor? But how are you going to report about...";
			link.l1 = "I have to convince father Vincento that you are dead, Gino. Only then he will stop his searches. Let's say that you have had a sudden stroke once you saw me. You should give me some item which I will be able to use as a proof of your death.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "Vincento won't believe in heart attack version, but he will do believe if you tell him that I committed a suicide by drinking some poison with a smell of almond. Give him my almanac, he knows that I never part with it.";
			link.l1 = "Fine. Because I need that connection with the inquisitor. He probably knows a lot about our business.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "Be careful with the father Vincento. He is dangerous as a tiger and he runs a game of his own. He won't share neither treasures nor fame with you.";
			link.l1 = "I understand that. Fine, Gino, give me your almanac and try to remember what had Indian told you about the Guardian of Truth, because I want to assemble it. I need to find Ksocheatem, I am sure that I will find there not only the mask and the treasures, but also my dear brother.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "Take it. Good luck, captain!";
			link.l1 = "I am not saying farewells, Gino...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("You have received an almanac");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "Was it hard, captain?";
			link.l1 = "Let's not talk about it... There were too many people willing to get these items. Too many. It seems that I am not the only one who is eager to find mysterious Ksocheatem. ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "I can imagine... By the way, how is father Vincento? Do you communicate regularly with him?";
			link.l1 = "So far I do, but I think that there is no need to do that anymore. I have all components of the Guardian of Truth which means that I own a key to the location of Ksocheatem. I am not eager to report His Grace about my success for some reason.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "Be careful, "+pchar.name+". Father Vincento has hundreds of eyes and hundreds of hands. Very long hands...";
			link.l1 = "I have went through a lot for the last few months and at this moment I am certainly not afraid neither of father Vincento nor of his eyes and hands. Whatever. It is time for us to find Ksocheatem using components of the Guardian. Do you know how to perform that? ";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "Not really. Ksatl Cha was quite vague. I think that the Indian didn't really know how to make the Guardian to work. Leave components to me and I will try to figure that out. Come and see me in two days and perhaps I will see this riddle solved.";
			link.l1 = "Fine, Gino. I count on you. Here, take them.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "You can be sure that they will stay safe and in one piece.";
			link.l1 = "I don't doubt in that. Well, I won't bother you now, Gino. Good luck with your research!";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "Partly. I mean, I have got something, but I don't know how to make it all work for real. Let's try to solve this puzzle together.";
			link.l1 = "Let's try! Give me your ideas.";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Ksatl Cha said something like that: 'The Chief's claw will make the map to reveal itself. The Arrow of the Way will show direction at the appearances.";
			link.l1 = "And what have you managed to do?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "I have guessed how to make the map to 'reveal' itself. Have you taken a look at the map of Two Appearances?";
			link.l1 = "Hm. And was there anything special? Some obscured contours of the archipelago.";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "Take it and have a look again. Be attentive.";
			link.l1 = "Well, let's do that if you insist.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "You haven't taken a look at the map, "+pchar.name+"...";
			link.l1 = "Yes-yes, I will do it now...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "I have. I didn't see anything new. Just some obscured shapes of islands and Main. What am I supposed to see there?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Wait a second. Now you have to make this map to reveal itself. Take the dagger and smoothly touch the map with it's edge. Don't push, we don't need avoid any damage. Take the dagger. And watch it carefully!";
			link.l1 = "Interesting! Let's see...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "Well, do you see any differences now?";
			link.l1 = "Yes. When you touch the map with the dagger two marks of skulls appear and always at the same places...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "At the TWO same places, "+pchar.name+"! That is why it was called as the map of Two Appearances!";
			link.l1 = "And what does it mean?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "A lot, I think... But more puzzles coming next. I take it that these skulls are the appearances of which Ksatl Cha was talking about. So the compass must show the right direction to the Ksocheatem from them. Have you seen the compass, "+pchar.name+"?";
			link.l1 = "Yes. It looks like an ordinary naval compass, but it behaves strange, it's arrow twitches in different directions or starts to turn around with a wild speed.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "I thought that planting the compass on skulls will stop it's arrows and will show some clear direction on the map. To perform that I have planted it on one skull and then to another while touching the map with the dagger.";
			link.l1 = "So what?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "Fruitlessly. The compass didn't change it's behaviour. The arrow is still turning  wildly. It seems that I am doing something wrong. Or I didn't understand Ksatl Cha's words correctly.";
			link.l1 = "So the dagger and the map work and the compass doesn't?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "The Arrow of the Way must be operational for sure, we just don't know yet how to make it work. "+pchar.name+",  you know the archipelago's geography better than I do... Tell me, what places are revealed by the map of two appearances?";
			link.l1 = "Just a second! (taking a look)...Well-well... The appearance on the left is the western Main. The right one looks like Dominica island. Something like that.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "And tell me now: is there... anything remarkable at those places?";
			link.l1 = "What do you mean?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "I am not sure myself... Well, something special?";
			link.l1 = "Gino, don't talk riddles. Explain simply.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "I can only suppose that these skulls show us some real places. The Arrow of the Way doesn't work while planted on the map's appearance perhaps it will work close to the real geographic appearances which were revealed by the map?";
			link.l1 = "Gino, you are a genius! Western Main, Dominica? Skulls are too big to show the exact locations.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+", let's do the following: bring here a paper map of the archipelago, combine it with the map of Two Appearances and mark with crosses the appearances. Perhaps this will give you some suppositions?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "I have got this old map of the archipelago.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "I have got this fine map of the archipelago.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "I have got this excellent map of the archipelago.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Deal. I will bring here a map and we will continue...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "Oh, come on, "+pchar.name+"! This parchment from the time of Columbus is not much better than the skin map. I am sure that there is something better than this rubbish in the world. Bring me another map, younger one!";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "Splendid! Now mark the places of the appearances on it. It will make it easier to build suppositions.";
			link.l1 = "Just in a second, Gino!";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "No way we ruin such a wonderful map with our markings. You will need it yourself, "+pchar.name+". Bring here another map, a bit more modest!";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "Have you brought a map of the archipelago, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "I have got this old map of the archipelago.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "I have got this fine map of the archipelago.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "I have got this excellent map of the archipelago.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Not yet, but I have ordered it already. Soon I will have it and we will continue...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "Done... I have done the markings, but it is still inaccurate information. The first place is somewhere Northwest of Blueweld. The second one is at the centre of Dominica island.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "Any ideas?";
			link.l1 = "No. But I think that we should bring the Arrow of the Way there and watch it's behaviour. Of course, it is like searching for a needle in a haystack, but we don't have any better ideas anyway.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "I agree with you, "+pchar.name+". Will you let me sail with you?";
			link.l1 = "Are you interested to check your suppositions? It would be an honour to have you on my ship's decks, Gino. Pack your things!";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "It won't take much time. I will be ready in a few hours. Here, take Arrow of the Way.";
			link.l1 = "Welcome aboard!";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "Yes-yes, "+pchar.name+", I am preparing myself. I will be ready soon.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "So what, "+pchar.name+", are you lucky in our searches?";
			link.l1 = "We were right. This is it. The Indian idol is one of the appearances.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "Oh! It must be one of those idols which were supposed to teleport people to Tayasal! I was telling you about them, remember? So what, where to the Arrow of the Way is pointed?";
			link.l1 = "It is pointed Northwest. I have marked the direction on a map. Though the drawn line crosses almost the whole Caribbean sea. We have to find another appearance on Dominica to find Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "I am sure that we will find there another idol... do you agree with my hypothesis, "+pchar.name+"?";
			link.l1 = "I do, Gino. Now let's not waste time and start searching.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "So what, "+pchar.name+", have you found anything of interest?";
			link.l1 = "We were right. This is it. The Indian idol is one of the appearances.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "Oh! It must be one of those idols which were supposed to teleport people to Tayasal! I was telling you about them, remember? So what, where to the Arrow of the Way is pointed?";
			link.l1 = "Northwest. I have marked the direction on a map. Though the drawn line crosses almost the whole Caribbean sea. We have to find another appearance at the Main to find Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "So what, "+pchar.name+", have you found the second idol?";
			link.l1 = "Yes. I have drawn the direction which was shown by the Arrow of the Way. Now we know the location of Ksocheatem, it is not the exact location but we know where to search! I will search the whole area where the lines are crossed and I will find that damn island!";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "I am glad to hear so much enthusiasm in your voice. But we have to prepare well for the upcoming expedition, it is unknown what we will face there. I doubt that we will get a welcome reception there...";
			link.l1 = "Are you worrying about something specific or are you just expressing concerns?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "Think about it, "+pchar.name+".. Ksocheatem was created by the Mayan magic performed by Kanek. It is not a natural formation and it has evil and destructive powers on it. It is unknown what is waiting for us there, I doubt that we will find there sun shine, peaceful sea, whores and a calm wind.";
			link.l1 = "Fine, Gino. I will consider your words and prepare myself for the expedition. I will get my ship ready and take care about potions and ammo...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "A very wise decision. Well, shall get back to the ship?";
			link.l1 = "Sure! Let's go!";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "We have arrived, "+pchar.name+"! Uh, the wind is howling!";
			link.l1 = "Yes, Gino, you were right, there is no sun shine to greet us... I don't see any whores either. Actually, it is unknown what is waiting for us here at all.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "Well, such a place you have chosen to land, captain! Just rocks and cliffs everywhere! And how are you going to get inside the island from here?";
			link.l1 = "I didn't see any more suitable bay to land on this island because of this damn storm! Whatever, this is better than nothing. I will manage to find the way within these rocks, it's been worse sometimes. Don't panic, friend!";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "I don't like this island, "+pchar.name+"! It is creepy. An this storm must be attached to the island. This place is doomed that's for sure!";
			link.l1 = "I don't really like this place either, Gino! But this island does exist and which means that the story of Kukulcan is true. We will be all in danger if he will manage to get to Tayasal with the Mask...";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "Try to find the Mask, captain! It is more important than all of treasures in the world! It must be somewhere around! Once we have it, we will destroy Kukulcan's plans and won't let him alter the past!";
			link.l1 = "And how does this mask look like, don't you know?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "No clue! But I think that you will recognize it, it is an ancient Indian artefact, it is hard to be mixed up with something else!";
			link.l1 = "I see. I will keep my eyes open! Fine, Gino, get back to the ship! You don't have to walk around the island, your head is too valuable to risk it!";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "I won't lie, captain, I am a crappy fighter and I don't feel comfortable about this place. Care to hear an advice? Every component of the Guardian is connected to the magic of this island. Ksatl Cha mentioned that the dagger has power over the local inhabitants, I don't know he meant though.\nI will stay aboard. See me there if you need my help.";
			link.l1 = "Good. And now wish me luck, Gino!";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "Good luck, "+pchar.name+"! God favour and preserve you!";
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "aloc0", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "How are you doing, "+pchar.name+"? Need an advice?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "This fucking island is crawling with the undead and damn skeletons are surprisingly tough. I have no idea how to fight them.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "If you go left from the fork you will eventually get the cavern. And where to go next? I fear that the cavern is a deadlock...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "I have found the way inside the wet cavern, you can dive into it's underwater part. But I don't see any exit from there...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "If you go left from the fork you will get to the cavern. And where to go next? I fear that the cavern is a deadlock...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "There is a place in the large cavern where you can dive into the flooded part. But it seems that there is no way out of there...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "It is alright so far, Gino, I am fine.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "Ksatl Cha mentioned the Chief's claw. Try to use it against skeletons, the Indian said that this dagger has power over the inhabitants of Ksocheatem.";
			link.l1 = "I will try for sure!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "And how does this cave look like?";
			link.l1 = "Well, there is a small cave in a rock, it is wet and the water sways in the bottom just like the surf...";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "If the water sways then the cavern has got a connection with the sea and it can't be a deadlock. Search for the passage, it must be there.";
			link.l1 = "On my way...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "If there is a way to the flooded cavern from the main one and if the water sways like a surf in the main cavern then the flood cave has the second passage. Search better but be careful or you will drown.";
			link.l1 = "I am going to dive...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "And how does this cave look like?";
			link.l1 = "Well, it is pretty big with a few caverns, it is wet and there is small lack with the still water...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "If the water is still then the cave doesn't have connection with the sea and it might be a deadlock.";
			link.l1 = "I thought the same. I have been searching there for a long time and there is the only one entrance which is also an exit...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "If the water is still in the cavern then, perhaps, you are right. Search a bit more, but don't be sad if you won't find a thing. It is likely that it is a deadlock.";
			link.l1 = "I see...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", Spanish ships are on us! It is not the best time to talk!";
			link.l1 = "Yes, sure...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "Your happy eyes tell me that you have found what you were looking for.";
			link.l1 = "Yes. Treasures of Miguel Dichoso and the mask of Kukulcan. Now his incarnation will never be able to change the future!";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "Incredible! You are a hero, "+pchar.name+"...";
			link.l1 = "Gino, are you sure that this is enough to stop Kukulcan?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "According to Ksatl Cha - yes. And he was quoting Urakan. His father Kanek was the one who started all this mess. Any doubts?";
			link.l1 = "I have been met at the bay by a guest from the past - Alonso de Maldonado. He was in Tayasal when Kanek was performing the ritual to create the Guardian of Truth. He was dragged into the spatio-temporal hole, yet he stayed alive... Until today.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "He said that I have to shut down the portal itself to protect our world for good. In order to do that I have to destroy the Mask on some altar in Tayasal.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "And you are going to go to Tayasal? This is madness! "+pchar.name+", you have got the mask and the incarnation of Kukulcan won't be able to do anything! And Kanek himself is confident in that! And that is why Urakan has sent Ksatl Cha to find Ksocheatem - to get the Mask and to destroy it.";
			link.l1 = "And what if this Urakan was planning to destroy the mask in Tayasal?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+", only one man has managed escaped Tayasal alive so far and it was Miguel Dichoso. And Maldonado, but he was an exception. Even if the incarnation of Kukulcan will get to the past he will get killed by the ancient Maya!";
			link.l1 = "What if they won't kill him but recognize him?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "So are you planning an expedition to Tayasal?";
			link.l1 = "I don't know, Gino. I really don't...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "Then think about it, why should you do that? You have heard my opinion. It is up for you now..."+pchar.name+", will you take me to St. John's?";
			link.l1 = "Sure, Gino. Let's set sail as soon as possible. I had enough of this horrible island.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "Will we be home soon, "+pchar.name+"? I really miss my flasks and tubes...";
			link.l1 = "Yes-yes, Gino, soon we will be at Antigua.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "I am glad that we are back at last! I can't imagine how you, sailors, spend so much time on your ships...";
			link.l1 = "It is a matter of habit, Gino.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "I will lay on my bed standing on the solid ground with a great pleasure... I hope, "+pchar.name+", that you have spared you head from the idea of visiting Tayasal?";
			link.l1 = "I don't know yet, Gino. To be honest, I am still not sure.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "Destroy the mask of Kukulcan and live with no worry, captain. If you want, we will dissolve the mask in the most powerful acid I have got. I won't be grudge for such a matter.";
			link.l1 = "You know, I will wait for a while. We will always have time to destroy it.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "It's your call. If you decide to spare this world from this artifact - call me then. Gratitude for a wonderful travel, captain!";
			link.l1 = "Any time, Gino. See you around!";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You are a "+ GetSexPhrase("thief, mister! Guards, take him","thief, girl! Guards, take her ") +"!!!", "Just look at that! As soon as I was lost in contemplation, you decided to check my chest! Take the thief!!!", "Guards! Robbery! Take the thief!!!");
			link.l1 = "Damn it!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}