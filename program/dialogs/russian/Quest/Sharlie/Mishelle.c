// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "Welcome, Charles the Voyager! I've heard all about how you defeated those pirates at the East coast of Martinique. Now I'm absolutely positive I wasn't wrong about you, brother.";
				link.l1 = "Sons of bitches caught me in a trap. But they miscalculated. My navigator and my crew came out on top. Although I've got to admit, dear brother, in the beginning... things were looking dim.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				dialog.text = "Good afternoon, Charles. The sight of you brings joy to my heart: you're definitely changing in a good way.";
				link.l1 = "Is that so? And how'd you figure that?";
				link.l1.go = "gambit";//переход на Гамбит
				break;
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "I see. I see that you have news for me Charles! Well, what's the good word? Hopefully nothing grim?";
				link.l1 = "I followed the advice you gave me last time...";
				link.l1.go = "saga";//переход на Сагу
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "Finally you're here... What's the good word, dear brother?";
				link.l1 = "I followed the advice you gave me last time...";
				link.l1.go = "gambit_fale";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "Pleased to see you, Charles! Have you seen Chevalier de Poincy? How did your meeting go?";
				link.l1 = "Yes, dear brother. We've met. And I have two pieces of news for you, good and bad. I'll start with the good. I've taken care of your debt to de Poincy. The bad news is that he won't release you until I fulfil your promise to sort things out with some heretic...";
				link.l1.go = "saga_5";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail") // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "How did you do in La Vega, brother?";
				link.l1 = "Nothing to boast about really. Tyrex's colorful character but his manner of doing business is not for me.";
				link.l1.go = "saga_17e";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "How did you do in La Vega, brother? I heard rumors and to be completely honest I am not feeling happy about them... Charley Prince.";
				link.l1 = "I think I know what were those rumors about. But it is all in the past. I am not working with Tyrex again, this job got too dirty for my taste.";
				link.l1.go = "saga_17f";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "Well, greetings... corsair Charley Prince. Tell me, Charles, how did you fall so low? I can't believe this. My brother who made a squeamish face when I once mentioned plundering a Spanish merchant galleon is now one of the most wanted and dangerous pirate in this region! Even I, sitting deep in this shit, turn red every time your infamousy reaches here. I have cursed the day when I sent you to La Vega. What a shame! A French nobleman has joined pirates and become the worst of them in short time! What now, brother? Are you looking for a vacancy of a pirate baron?";
				link.l1 = "No. I am done with piracy once and for all.";
				link.l1.go = "saga_17g";
				break;
			}
			dialog.text = "What else, Charles? I think we've discussed everything. Time is money, dear brother - make haste!";
			link.l1 = "Yes, yes, off I go...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Mishelle_prisoner":
			dialog.text = "Pleased to see you, brother. I understand, of course, that it'll be hard for you to believe, but I'm happy as hell you're here...";
			link.l1 = "Ha! Look at him! He's happy! So while you were on your high horse with your 'Society', Charles was the embarrassment of the family, a measly artist, a gigolo, and a court knight, huh? And now that you're clapped behind bars by your own comrades, you not only remember your good-for-nothing brother, a street rat, but you're 'happy as hell' to see him too!";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "Charles, you...";
			link.l1 = "I'm not done yet! You had the gall to manipulate our father's feelings to serve yourself. Just so you know, I came to this hell hole in the sweltering heat where the mosquitoes literally chew you to death not for you, but for our poor father!";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "Really? Charles, since when you care about your family? Let's be honest, brother, everyone in Paris knows who is your father. You may carry a family name of de Maure, but you don't want to have de Monper' name dishonoured\nBecause in that case you won't be able to use your lineage in order to tell everyone fictional stories about your heroic deeds, am I right? The doors of the best houses of Paris will be closed for you and they won't let you come closer than a mile to the Louvre\nDo you really believe that your courtesans and mistresses, whose husbands you make cuckolds while they are fighting on the battlefield for our Fatherland, will be happy to cheat on their lords and masters with a brother of a state criminal like myself?\nI guess you have arrived here straight from the bed of some married girl, am I correct? Charles, what is wrong with your face? Did I hit the nerve?";
			link.l1 = "You... You!..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "All right, brother. We've exchanged barbs, that's enough. I agree that I'm not perfect. But you're no angel either. Charles, this really isn't the time to quarrel. We've both got one goal to save the honour and the dignity of the Monper family...no matter what our motives are. Brother, for once in our lives let's change animosity for peace. Deal?";
			link.l1 = "Let's try it out... But can you explain to me what you're being accused for?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "Officially it sounds like the expenditure of the Society's money. In reality, it's much deeper.";
			link.l1 = "So, you've appropriated your organization's money? Well-well...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "I told you those were the official charges. I didn't take a single louis d'or. Here's how it went down... you see, I can't explain everything to you in detail as far as even behind bars I don't have the moral right to disseminate the secrets of our Society.";
			link.l1 = "Please, try to explain, dear brother. I have a right to know, don't you think?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "Fine. I had received the money for a very dangerous and delicate operation which was supposed to shift political balance of the Caribbean. I was acting by direct orders of Philippe de Poincy, he is a general-governor of the French colonies. But the operation was failed despite all my efforts\nDe Poincy had a fit of anger due to the fact that all his long shot plans went broken. He had personally signed an order for my arrest and made sure it was executed. Then he came here and declared that he would accuse me of peculation and treason against the Order, if I or my relatives wouldn't return money spent on the operation.";
			link.l1 = "Here's a fine how-do-you-do. Where is it, this money that as I understand, our family has to pay for your muffs?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "It's spent on preparing the operation. Bribes, organization of expeditions, purchasing all sorts of merchandise and equipment. I had rather large expenses. Just like I said - I didn't take a coin.";
			link.l1 = "And what is the sum that is being requested?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "One million.";
			link.l1 = "Merde! You're kidding, right?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "Do I look like somebody in the joking mood? No, dear brother, this is the bitter truth. We are going to return de Poincy on million pesos.";
			link.l1 = "But god damn it! Our family has nowhere near that kind of money! We couldn't put that much together in twenty years!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "If I wasn't behind bars and restricted by my obligations to the Society, I would make it in six months to a year, a year and a half at the most. Charles, this is the New World. Everything's different here. A motivated, ambitious man can make a fortune for himself here without dedicating his whole life to it like in Europe.";
			link.l1 = "A million in half a year?! Are you off your nut? If you're so sure, then why don't you tell your de Poincy about that? Let him release you. Put your best foot forward...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "Oh, don't talk rubbish, Charles! There's no way Poincy is going to release me from here. If it was that easy, I wouldn't ask you for help.";
			link.l1 = "So I'm the one that's going to make the money for your freedom?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "Not just my freedom. Or have you forgotten? Shall we return back to our conversation about the palaces, balls, and sex with noble whores? Yes, Charles, you're the one that has to do it. If, of course, you'd like to carry on with your meretricious life in Paris like before. You would like that, wouldn't you, brother?";
			link.l1 = "But god damn it, where the hell am I supposed to get it?! You know some old woods where louis d'ors grow instead of leaves?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "The whole New World represents a grove of money trees, yet people are too lazy to lift their dumb heads up and stretch out their hands to the branches. Don't worry, Charles, you can do it. I have been knowing you since our childhood and I would never waste my time persuading father to send you here if you were dumb or lazy\nDespite of your downsides I have mentioned before, you are brave, ambitious, smart, your tongue is hung well enough and you know how to handle a rapier which is an extremely important skill to know here...";
			link.l1 = "Thank you very much. Has my dear brother really deigned to give me praise? And I thought I was nothing but a pitiful artist, a courtier...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "Cut the bullshit. Do you and I have an agreement, or not?";
			link.l1 = "Sorry, brother. It slipped out. I'm just so unused to hearing those words from you. It's like a street whore preaching about saving a soul.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "Let's proceed brother. As I said, you have everything it takes to become successful here. Not only that, you are not alone. I will help you with advice on what to do and how to do it the right way. Listen to me and we're in flying colors. Believe me, there's no replacement for my experience. Are you ready to hold off on the trash talking and finally get to the point?";
			link.l1 = "Yes, it looks like I'm staying here for while... All right. I'm all ears, Michel.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "Yes, brother, you are going to stay here for a while. It's good that you can see that now. So if some courtesane is waiting for your returning back to Paris, I suggest you forgeting about her. But don't feel bad about it, local girls have their own charms\nThough, they like real men, strong and pushy, even rough. So if you are going to fuck some colony girl don't count on poetry, painting discussions or walking under the moon. They won't approve.";
			link.l1 = "All right, brother. Have you been struck by a bolt of windbaggery? Let's get to the point. I'm willing to listen to your advice, but not your foul insinuations.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "Splendid. In order for you to have any kind of success, you need to own a ship. The Caribbean is an archipelago. You did know that, right? Life is intertwined with the sea. A man with his own ship has an endless horizon of earning potential.";
			link.l1 = "But I'm not a sailor!";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "Then, it's time to become one. You've got no other choice anyway. You didn't think of becoming a port office clerk or registering into a garrison, did you? No? Then you'll be a captain.";
			link.l1 = "What a turn of events in my career! And where will I find myself a ship?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "There's an excellent lugger is standing at our shipyard. It isn't big, but it's a very comfortable boat just right for making the first steps to the arena of a sailor. This lugger was built just for me. I placed a deposit of five thousand pesos for her with the help of my friends. Make your way to the local shipbuilder and tell him that Michel de Monper sent you. He'll understand what you're there for.";
			link.l1 = "The ship only costs five thousand? That's kind of weird...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "Brother, are you listening to me? Five thousand is just for the deposit. The lugger's price is around twenty thousand. So you'll have to earn the rest of the money yourself. Besides that, you'll need money to hire a crew and a navigator.";
			link.l1 = "Great! And how will I get it?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "Not big surprise in that. Earn it. How else? There's money lying behind every bush here you've just got to know where to look and not to fear adversity. Walk around the different establishments around here. Have a talk with the people. You're sure to get some kind of work. But be careful, there are much more con artists than there are honest people. If you are not an honest man, you may try to steal something valuable from houses.";
			link.l1 = "But we are nobility, right?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "Titles mean shit here. Work, fight, steal just like anyone else. After you buy a boat, hire a crew. You won't be able to steer the boat in the beginning, so you'll need a navigator. You can talk about all this with the owner of the tavern, he'll help you. And make sure you don't get lost, of course. When you depart to sea, take the course straight to Guadalupe...";
			link.l1 = "What is that? A town?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "It's an island almost two days away from here. Yes, try to acquire a map of the archipelago as soon as you can and learn it like 'Our Father' so you won't look like a moron to everybody that can tell the difference between a town and an island. You're going to have to cruise around the archipelago a lot, so prepare ahead of time.";
			link.l1 = "Hm. Okay. So what do I do on this, uh... Guadeloupe?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "Find a man there by the name Fadey. He has his own house not far away from the pier. Tell him you know me and ask him to repay his debt - he lost quite a hand to me in a game of cards. The money you receive will help to get you on your feet. Use it to get things going.";
			link.l1 = "What do you mean get things going?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "I mean use this money to earn even more money and so on. Trading for example. We will return to this conversation later. Now you should deal with the ship, then sail to Guadeloupe, find that fat Muscovite and beat the debt out of him\nNot literally, of course, Fadey is a very respected man of Guadeloupe and a friend of the local governor himself. So there is no point in quarrelling. On the contrary, try to make friends with him. Get back to me as soon as you have the money. Understood, brother?";
			link.l1 = "Got it. Oh, why....What did I do to deserve this punishment...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "Don't sorrow, Charles. Accept it as an inevitable evil, or...a good. You'll be grateful later to fate that your life has taken this kind of twist. You, brother, finally have the opportunity to do something to prove you're a real man. You'll become a decent human being...";
			link.l1 = "That crap again?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "Brother, I don`t have time for this. I want to skip the boring part and get right to the high seas immediately. The sooner I have a ship, the sooner you will be out of this shithole. Or would you prefer to stay here longer?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "No, no. Don't take it the wrong way... All right Charles, don't waste any time. You know what to do. I'll be waiting for you coming from Guadeloupe as the captain of your own ship with Fadey's money. Good luck, brother. I'm counting on you.";
			link.l1 = "I'll try not to let you down. All right, Michel. Until next time!";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Heh! This 'boring part' might save your life one day... Whatever. There is an easy way to get the money right now\nGo to the local church an talk to abbot Benoit. He is old friend of our father. Tell him about the situation, fall onto your knees and beg to lend you enough coins to buy a ship.";
			link.l1 = "(SKIP TUTORIAL) Much better now! Heading to the abbot.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(START TUTORIAL) Do you want me to begin with raising your debts to even higher levels? You think I am an idiot, brother? I can see you can`t help me at all in this. All of this is on me then.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "Whoa! Looks like I wasn`t wrong about you, brother. Looking forward for your return from Guadeloupe as a captain of your own ship with Fadey`s money. Godspeed!";
			link.l1 = "See you. Have fun here.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "trial":
			dialog.text = "Are you trying to say that was scary? Don't tense up, brother. It's absolutely fine. I didn't feel like much of a hero in my first sea battle either. Nonsense. In a month or two, such encounters are going feel like a common-or-garden event... Have you visited Fadey?";
			link.l1 = "I have... But with this kind of success I might as well have not even done it at all.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. Why is that?";
			link.l1 = "Because he's on the rocks. He has been robbed recently and he has problems with money. He offered me a dagger from his collection instead. He said that it's value and it's greater than the amount of the whole debt. So, I took it...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Fadey? On the rocks? Problems with money? Ha-ha-ha! You've given me a chuckle, dear brother! That god damn Muscovite recognized you as a novice right away and... ah that bugger! Show me the dagger the old man gave you way for his debt.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "Here you go...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "I don't have it with me. To the naked eye it's just a regular dagger. Fadey told me it's incanted by an Indian shaman and called the Chief's Claw.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "Hm. Well, let's see... God judge that pudgy bear. Scrap like that, Charles, you could buy at any local store. He put one over on you, taking advantage of your lack of experience... Here you go, take this piece of steel back. Keep it as a souvenir. You can hang it over your bed in your cabin.";
			link.l1 = "Fucker! Oh, who cares... I'll go back to see him in Guadeloupe and give this greasy scorcher a shake!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "Incanted by a shaman? Chief's Claw? Yeah... It's all clear. God judge that pudgy bear. Scraps like that, Charles, you could buy at any local shop. He put one over on you, taking advantage of your lack of experience... He tried to tell me some kind of fairy tales and I put him right back in his place. So you can hang this claw in your cabin up over your bed as a souvenir...If you haven't tossed it in the rubbish bin yet.";
			link.l1 = "Fucker! Oh, who cares... I'll go back to see him in Guadeloupe and give this greasy scorcher a shake!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "Calm down, dear brother, relax. There's no need for that unless you want to spend a couple of months in Basse-Terre prison. Have you forgotten what I told you? That puffy bear is a friend of Claude Francois de Lyon, the governor of Guadeloupe. As soon as I leave this place, I'll go have a talk with him... a heart to heart. He's not going anywhere.";
			link.l1 = "All right. You'd better deal with him... Looks like I'll be left without the promised start-up funds?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Looks like it, Charles. But keep your head up. The one who has a ship and a head on his shoulders can not do wrong in the Caribbean. And you've got both, don't you?";
			link.l1 = "What are you insinuating? I've messed up with this dagger, so what should I...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Calm down, dear brother! Why are you so jumpy all of a sudden? Keep calm, you'll live longer. I'm not insinuating anything. I didn't even have the thought!";
			link.l1 = "Sorry, Michel. It's just that I'm a little... well try to understand me too!";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "I understand. And I really want to help you! So listen carefully to me. You must gain some experience and at least save up a little bit of money before taking to more serious matters. Rushing into adventures without the needed preparation is pure suicide. I don't want you to get squashed by this place too soon.";
			link.l1 = "Very inspiring. What sort of adventures are you expatiating on, Michel? I've lost track of you for some reason.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Brother, let me remind you that I, or to be more specific, we owe de Poincy a million pesos. Do you really think that you can earn them honestly? Sure, you can trade that much, it is possible if the things will go fortunate for you but trading in the Caribbean is not a peaceful activity either\nAdventures will find you themselves even if you don't want to participate, thing is - will you be ready for them at the moment? It is better to strike first. Si vis pacem, para bellum, Charles...";
			link.l1 = "Again with the fancy words? Speak French, I beg of you...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "It's Latin, dear brother. I said, 'If you want peace, prepare for war'. Take this phrase as a leadership mentality toward action. You can write it down in your logbook and reread it every morning after prayer. There is much you have to learn and a lot left for you to grasp...";
			link.l1 = "All right, that's enough. I've grown tired from your dissertations. Let's get to the point.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "I am specific, you just don't follow yet. Fine. First, you need to get familiar with the archipelago and to get used to your new life as a captain. You will have to work hard to ensure your being and a wage for your crew. There are a lot of ways to make coin\nFreights and taking passengers are the simplest. Merchants in stores may give you freight contracts and passengers will address to you on the streets themselves. You should also consider checking harbor offices, having lugger or any fast ship will allow you to earn good money for a courier's job\nHarbor masters will provide you with very profitable freight contracts once you get yourself a bigger ship. Talk with people, don't boast of your lineage, be friendly and things will go just fine. Visit colony governors, they often offer well paid work\nYou may try trading but in that case you should hire a decent purser. Be careful at the sea, avoid Spanish military squadrons and warships. If you meet a single Spanish trader or an unprotected convoy - you may try to capture them.";
			link.l1 = "What?! Michel, have I lost my hearing? Are you suggesting that I take up the life of a pirate? You, the pride of the Society, a servant of God and the Trinity, propose such a lifestyle to me?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "Oh, Charles... I advice you to get rid of your fastidiousness once and for all, it is not appreciated here. And about the Order... don't be naive, brother. Perhaps, in Europe the Louvre and the Escorial are in peace of some sort but it is a war here. Any Spanish raider will not hesitate to plunder your ship and hang you and your crew to dry up on a yardarm\nTherefore, nobody will blame you for plundering a trade ship of the hostile nation, I assure you. And with a letter of marquee you will even get an official support from the authorities...";
			link.l1 = "I am beginning to understand your life's principles. Just as I understand the methods with which you would be apparently able to 'earn' a million in half a year.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "And you will have to use these methods, Charles. After all, this is supported by the acting authorities openly or not. Even if you will stick with the trading, one day you will be forced to fight pirates or Spanish raiders, because for them you are the booty\nIt is in your best interests to forget your previous views of life. Trust me, brother, you can do a great deal of things not only without loosing a face, but also earning authorities' favour and love of the people.";
			link.l1 = "You never cease to surprise me, Michel. Now you're calling me to become a pirate. What's next?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "Don't overdramatize this, Charles. It's really simple: hunt or be hunted. That's the whole philosophy. I prefer the first and I would like for you to follow in my example. And I tell you not to become a pirate, but to engage in military action against a hostile nation and only when there is a good reason for it.";
			link.l1 = "A benefit, you mean?";
			link.l1.go = "trial_15";
		break;
		
		case "trial_15":
			dialog.text = "You understand it, brother. But enough words. Time to test yourself. See you in three months, but take your time. Come see me only when you feel ready. Earn some decent money, get a better ship, learn the map and get new skills\nBut if you will spend all coming months in taverns and brothels and learn nothing useful in the process... don't even return then. Are we clear, Charles?";
			link.l1 = "Don't worry. I didn't come here for recreation... What after that?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "Later I'll tell you what to do after that. I've put a plan together already. You've got a bright future shining ahead, Charles, if you accurately follow my advice and recommendations.";
			link.l1 = "I would prefer my modest past against such a bright big future...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "Trust me, brother, you will laugh at your worthless past and thank the fate for saving you from it. Be optimistic and positive. You will love this life. You'll see\nYes, one more thing: pay a visit to our mutual friend Fadey and ask him to find you a job. The bear has good connections, I am sure he will find you something. Don't linger or you might miss an opportunity. And please don't let me down.";
			link.l1 = "Moral teachings again...Lord, when will this all end? All right, Michel... Shall I be on my way?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "Wait. A few more tactical advices. If you do a bad turn to any nation and go outlaw, visit the local church and talk to abbot Benoit. Tell him that you are from me. He has connections within both Papists and Calvinists and had helped me a lot with such matters more than once. But be aware that it is neither easy nor cheap, so try to avoid making enemies\nWait, one more thing! We are nobles, but it is foolish to have an aversion to crafting with our own hands, especially here. You can craft a lot of useful items provided you have got needed tools and components... Tell me, brother, how do you load any of your pistols?";
			link.l1 = "Hm. As usual, a bullet and a hinge of gun powder.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "Ha! I didn't expect to hear anything different.";
			link.l1 = "Do you know another way, dear brother?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "Of course. But there are few who do it due to ignorance and plain old laziness. Just by spending several hours of your time, you could make paper shells out of gun powder and bullets. Using them speeds up the reloading time of the gun by two times. Impressed?";
			link.l1 = "Hm. I guess so. It's interesting.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "Take these paper shells crafting instructions, study it in your spare time, and don't be too lazy to apply your new knowledge. Go now. I'll be waiting for you in three months! Good luck, brother!";
			link.l1 = "Thank you... See you later, Michel.";
			link.l1.go = "trial_22";
		break;
		
		case "trial_22":
			Log_Info("Press K for crafting");
			PlaySound("interface\notebook.wav");
			DialogExit();
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "trial";
			pchar.questTemp.Trial = "begin"; // старт промежуточной линейки
			SetFunctionTimerCondition("Sharlie_TrialOver", 0, 0, 10, false); // таймер
			pchar.quest.Sharlie_trial.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_trial.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Sharlie_trial.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 90);
			pchar.quest.Sharlie_trial.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 90);
			pchar.quest.Sharlie_trial.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 90);
			pchar.quest.Sharlie_trial.win_condition.l2 = "Rank";
			pchar.quest.Sharlie_trial.win_condition.l2.value = 3;
			pchar.quest.Sharlie_trial.win_condition.l2.operation = ">=";
			pchar.quest.Sharlie_trial.function = "Sharlie_GambitStage";
			AddQuestRecord("Sharlie", "19");
			// открываем все острова
			for (i=0; i<MAX_ISLANDS; i++)
			{				
				if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
			}
			DeleteAttribute(pchar, "questTemp.Sharlie.Lock"); //снимаем блокировку
			LocatorReloadEnterDisable("FortFrance_store", "reload2", false); // откроем склад магазина
			sld = characterFromId("Benua");
			sld.quest.help = "true";
			npchar.greeting = "mishelle_3";
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 5000;
			// Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.quest.Sharlie_FMQ.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_FMQ.win_condition.l1.value = 4;
			pchar.quest.Sharlie_FMQ.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_FMQ.function = "FMQ_SetConditions";
		break;
		
		case "gambit":
			dialog.text = "I can see you, dear brother. I can see your walk and the expression on your face. Finally that mask of a conceiting young boy has melted off you, which literally drove me insane. Your new life has clearly benefitted you now.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "I can't understand, brother, what to make of your words whether it's praise or insults. But I'll tell you the truth: I am uninterested in what you think about me over there. I have collected the million that is necessary to pay off your debt, so you'll soon be walking free. Where can I find de Poincy?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "I can't understand, brother, what to make of your words whether it's praise or insults. But I'll tell you the truth: I am uninterested in what you think about me over there. I have a heap, not a sea of matters to attend to and I have no time to engage in a dispute with you here and chip words. Do you have anything relevant to say? If not, then I'll be on my way...";
				link.l1.go = "gambit_1";
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "You managed to put together a million? Good job, Charles, just impeccable! But Philippe de Poincy, unfortunately, is no longer at his residence, he's departed on matters of the Society on the secret expedition. So you'll have to bide your time a little on the visit.";
			link.l1 = "Screw you and your secret affairs! I thought I'd be done with all this story and go home, and now...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "And now you've opened up the opportunity to make way much more money and not just that. Brother, the fact that you've amassed the quantity requested by the old fox that's amazing, but I wouldn't be so confident and so calm... De Poincy, is quite the slippery eel, and he's displayed quite a lot of interest in your modest persona, and...";
			link.l1 = "And now you're afraid that a million won't be enough for him?! Or is there something you left out last time?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "I'm not afraid of anything, but I must to warn you that Poincy is not such a simple man. While he is away you have the opportunity to build yourself some stature, so that you could speak with him as equals, not like a lord and a serf. Thus, I persistently call you to follow out my plan, which I will expound to you right now.";
			link.l1 = "All right. No use crying over spilt milk. I'll hold up in this hell hole a little longer. De Poincy isn't going to be cruising around forever. Bring me up to speed on your plan.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "Oh! A commendable reply. I'm glad, Charles, that you've become a man. However, do not be so stern toward you brother. Granted, I have something to tell you. I've been looking forward to us meeting again and have already developed a plan for what you'll do next.";
			link.l1 = "Nice. Then brief me.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "Look. Sure, money plays a big role in the Caribbean, just like anywhere else, but money can't solve everything. A successful man must not only has a heavy purse, but also extensive and different connections, and not to lowlives, but to people who mean something in this world\nIt doesn't matter what nationality or estate they are. Connections can open doors which cannot be opened only with money. As a result a combination of 'money plus connections' gives a man the most valuable thing in the world - power\nYou should consider establishing such connections and you won't be able to do so by doing freights, trading, minor piracy or even gaining favour with governors.";
			link.l1 = "What do you propose?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "There are not that many powerful organizations in the Caribbean. One of them is Dutch West India Company. You can join them. Their headquarters are in Willemstad at Curacao. The Company often hires third-party captains and offers special long-term contracts to the most useful of them\nIf you are lucky you may make a decent career there. I heard that they are experiencing serious troubles now - some English privateer took up arms against the Company and is constantly sinking their ships. They can't do anything about him, he is a navy officer, too tough for them\nThey say that he is somehow connected to the British military intelligence and they are very serious people. So, perhaps, taking side of this captain will be even more profitable for you, but problem is - I don't his name, I only know that Antigua is his operational base\nYou may sail there and ask people around. I also heard about some strange organization which also takes part in this English-Dutch conflict, but I don't know which side they are playing for. All I know that trails lead to Barbados, to Bridgetown...";
			link.l1 = "So you propose me to sign up for service with the Dutch or go search for a shady captain or an even shadier 'organization'?";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "The choice is yours. In any case, you don't have any other means of quickly getting in with people deciding the fate of others on the Caribbean and possessing significant power. I hope you haven't got it in your head that two or three favours for the governor will write you right into the royal navy.";
			link.l1 = "You know, dear brother. I wasn't actually hoping for a military career in the French navy. God forbid I end up like you stuck in a jail cell for some task I didn't manage to carry out... All right, I understood. I think I'll find the General Headquarters of the Dutch Company without much hindrance, but I don't have a clue on how to look for the rest of the parties";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "As for the English privateer, you can ask around in St. John's, Antigua. Someone will definitely be able to tell you. Tell them you're looking for work at English fleet. As for 'the third force', you can talk to the people in Bridgetown about that. Someone there is sure to be connected to this organization.";
			link.l1 = "Is their work going to be compensated at least? The Company, this privateer... Or is it all going to be for the sake of 'connections'?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "Charles, you have surprised me. Dutch West Indian Company operates with sums a king would envy. The privateer, I told you about, had plundered so many Dutch ships that he must already be overflowed with wealth. And the serious people don't just have a lot of money. They have a shitload of money\nWorking for them will always guarantee you a sweet piece of pie. People like them always play big. And if you are smart, you can always play your own game and make even more.";
			link.l1 = "All right. I'll think it over and decide what my best bet is. Do you have any other instructions?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "Yes. You should learn how to use navigation tools. Alas, a lot of navigators can orientate only by compass and stars and can not estimate the coordinates. And this is critical\nSo. Use a boussole to estimate the latitude. It is a quite rare tool and you won't find it in stores, but you can craft it yourself using two common items - a compass and an astrolabe. Here, take an instruction\nEstimating longitude is a bit more tricky. You will need a rated chronometer. You can make the one from a usual ship chronometer by adjusting it with a special sand glass. Problem is, that such tool works efficiently only for a month before the error becomes too inadmissible\nA chronometer always requires the resetting. Sand glasses can be bought in the office of Dutch West India Company. I also bought there chronometers. Here, take this instruction.";
			link.l1 = "Thank you. I'll get to studying right away.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "Try to acquire all these tools as soon as possible. All experienced and respected captains operate with  the latitude and the longitude. You will be considered a man far from seamanship until you know what those numbers mean\nWell, come back to boast as soon as you find success in the matters we have discussed recently. Godspeed, Charles!";
			link.l1 = "Thank you, dear brother. I feel it'll surely come in handy!";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
		break;
		
		case "gambit_fale":
			dialog.text = "And what do you have to boast of?";
			link.l1 = "Nothing for now. I've found all three organizations and tried to work with them, but no cigar it all blew up in fumes literally on the first stage. It's like fate's rigged against me...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "The rumors are true then... Dear brother, fate is not rigged against you. It's called a dull brain and crooked hands. You've disappointed me. Go back to France, you have nothing to do here.";
			link.l1 = "But how...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "It's not your business anymore. I'll deal with it by myself. I have other people more capable to help fix my problem. I'm afraid that confiding in you would hold me here till the end of my days. Anyway. Get out of here, go back to your courtesans.";
			link.l1 = "Fine, go to hell...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "I've got nothing to talk about with you. Go.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered a 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become the close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered a 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "And? Come on, dear brother, don't pull it along. What's the good word? Some rumours have whispered their way to me of your ardent industriousness, but I wanted to hear it all from you.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";	
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Excellent! Great job, Charles! I didn't doubt in you for a minute! You'll go far, dear brother... Busying yourself like that and laying down relationships with such important people of course, I didn't expect that. Congratulations!";
			}
			else
			{
				dialog.text = "Don't be upset, Charles. If it didn't work out there's nothing you can do about it. We'll use other means of achieving the results we need.";
			}
			link.l1 = "What do we do now, Michel? Is it time to pay a visit to chevalier de Poincy? I feel quite prepared for a conversation with him.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "Have you already managed to put together the required sum of one million pesos?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Yes, I currently possess the required sum.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "No, I don't have that amount of money yet.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "Excellent! Then I won't be sitting in this casemate much longer... Be on your way to Capsterville, it's on Saint Christopher, and request an audience with de Poincy. He should be at the governor palace where he resides. Beyond that, just judge based on the situation and remember: Poincy is slick, very slick... I've got a bad feeling that this whole shebang isn't going go down so easy. Go, brother, and be careful!";
			link.l1 = "I'll keep your precautions in mind, Michel. Don't fret, I wasn't born yesterday either. Off I go to the old fox. See you later!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "No point in talking to de Poincy then. He won't even let you in. Find the money, my brother, you are quite experienced already so it won't be much of a problem. Sail to Capsterville on Saint Christopher as soon as you have it\nThe Chevalier must be in his governor's palace. Ask for an audience and they will let you in. Then see for yourself and be careful: Poincy is sly, very sly... Something is telling me that this story won't end just like that.";
			link.l1 = "I'll keep your precautions in mind, Michel. Don't fret, I wasn't born yesterday either. Off I go to the old fox. As soon as I put the money together, I'll go right to the old fox. See you later!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "Nom d'une pipe! That's exactly what I was afraid of. Poincy has been hot on your heels for a long time, Charles. That's why he's paid such an interest in you! You've built yourself quite a reputation in the Caribbean and so he's decided to use you to fulfil assignments that went down the pan...";
			link.l1 = "I get the feeling, Michel, that you were well aware and you just didn't want to inform me before. It's turning out all too smooth... The money first, now your work... That doesn't happen by chance.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Charles, don't search for some secret message where it doesn't exist. If only you just gave Poincy the money the very first day you got here... Well, I mean, let's say you had them. The Chevalier wouldn't have asked you for anything more. But now that he's paid an interest in you and seen how easily you've settled in here and what you've been able to achieve, he's decided to exploit your talents.";
			link.l1 = "Right... because your talents are no longer satisfactory to him, right? Merde! All right. I see I'm in a dead end here. Who is this heretic? How can I find him?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "No need to search for him! He never leaves Tortuga and stays under protection of bastions he built and muskets of loyal Huguenots, who serve as soldiers in his garrison. Therefore, every soldier is loyal to him. He meant Francois Levasseur, the governor of Tortuga\nThe Spanish still can't pluck him out of there and de Poincy seriously believed that I will be able to do so alone without any support from the navy, because starting a civil war would be a wrong political misstep due to the close location of Santo Domingo garrison\nThe old scum is too worried about his clean career and a coming pension to risk like that. Nevertheless, Levasseur has gone too far and represents a danger to the crown\nDe Poincy, who appointed Levasseur to his current position himself, considers this fearsome Huguenot a personal enemy and is eager to replace him with Maltese chevalier de Fontenet, my immediate superior under whose command I have arrived here from Malta.";
			link.l1 = "Glorious! First, make a million, then assassinate the governor of Tortuga. What will my next assignment be? Organize a conspiracy in the Escorial? Shit! I'm not surprised you messed that thing up. Wiping off the governor isn't like pinching Spanish merchants. I hope you had some kind of plan when you swore to pull the chestnuts out of the fire for this couple?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "To be completely honest, I didn't have any plan since I was going to leave the service anyway and return to our family mansion in case of success of my risky venture. Personally, I don't give a damn about de Poincy's problems\nSurely, he would become much more flexible as soon as he saw the Indian gold... Well, currently he holds all the trump-cards against us. I will stay here as long as Levasseur is the governor of Tortuga.";
			link.l1 = "And why wouldn't the Maltese led by de Fontenay with their sights set on the governor's seat charge Tortuga themselves?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Imagine that. The order declares a war to Louis. Don't be absurd! Such scandal is completely not an option. Only a private individual can capture Tortuga. A pirate, or a Catholic adventurer like you\nAfter that he can surrender the island under control of the new governor de Poincy will send. Such performance will look perfectly from the point of view of big-time policy.";
			link.l1 = "So there's a point in negotiating with pirates?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Problem is that Levasseur has authority among a lot of pirates of the Brethren and beyond. He allows them to hide behind Tortuga's batteries and sell what they have plundered freely for a cut of the booty\nHe used to share with de Poincy, but he is not sharing now. So the pirate ships will protect Tortuga and its garrison which makes the storm of the fort even more difficult.";
			link.l1 = "Do you think this matter is a lost cause?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "There is always a solution, little brother. It is not just always lying on the surface. Not all pirates are in sympathy with Huguenots of Tortuga. I know at least two authoritative pirates who consider Levasseur a traitor and a scum. I am talking about some Steven Dodson also known as the Shark and the legendary baron of Mosquitoes Bay, Jan Swanson\nI don't know where to find the Shark, I have heard rumours that something wrong had happened to him and he had to leave his base at Isla Tesoro. But you can always find Swanson in Blueweld. He is a significant figure there.";
			link.l1 = "Do you suppose that this... Swanson will help me?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "He will if you help him. Things don't go well enough for him and the man could use loyal talented people. You will need to prove him your utility first before having a serious conversation. You will find a way to do so when you get there. I find it hard to give advices from here\nI take it that you have decided to go on, Charles, since you keep asking questions?";
			link.l1 = "You see, Michel, I just gave away a heap of my own silver to de Poincy. I assembled it through blood, sweat, and tears! I'm not sure you'd even have risked a single louis d'or for me if I were in your shoes.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "Charles...";
			link.l1 = "Don't interrupt me! It would be stupid right now to return back to father with empty hands. The problem still isn't solved, you're behind bars and under threat of being convicted under betrayal of the Society. Poincy wouldn't hesitate to tarnish the Monper name, if I don't carry out his 'request'. It was written all over his face. So I will be off to Blueweld to find a way to approach Swanson. In the meantime, you think about what else you've 'forgotten' to tell me. For example, this is the first time I've heard from you about some Indian gold, that you brought de Poincy.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "There are things better to stay hidden. You are right, I didn't tell you everything I know. Perhaps, one day I will tell you more, but not before you deal with Levasseur, it would be a useless knowledge for now\nI have no doubt that your touching care of me is caused only by the wish to save the honour of our family. By saving me, you are saving yourself in the first place and a possibility of visiting the best houses of Paris in the second. Am I wrong?";
			link.l1 = "I'm afraid it is no longer so, brother. You were right. These past months spent in the Caribbean have changed every fibre of me and my entire outlook. And I'm sure it's for the better. I don't really need those Paris salons anymore and will be able to go on one day without the name Monper. De Maure isn't any worse...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "";
			link.l1 = "And now the only thing that actually hurt me is that fact that your shame will leave a mark on our old father. He doesn't know the true status quo and what's truly going on here. Also, as you correctly stated, the patrimony must be restored from its ominous state. And the million paid for your freedom has significantly eased my treasury, so it will clearly require filling.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "You have excellently grasped all of life's lessons, Charles. I am truly happy for you. And I'm glad that you did go ahead and accepted de Poincy's request instead of sailing home to France. I hope everything turns out well for you and that you will be able to carry out what I was not able to do myself.";
			link.l1 = "I'm afraid I have no choice. I am alone since my first day in the Caribbean. See you later, Michel. I think our next meeting will include an order of your release.";
			if (GetDLCenabled(DLC_APPID_3)) link.l1.go = "saga_17a";
			else 							link.l1.go = "saga_17";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "Wait a minute! Before you go to Jan Swanson, make sure to pay a visit Marcus Tyrex - the Keeper of the Code. He is a ruler of La Vega on Hispaniola. He has a limitless authority among pirates and the Spanish fear him to the death.";
			link.l1 = "Could he help me with our matter?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "Doubt it. I can't really tell which side he is on, most likely he stands for himself only. You will need the Shark and Swanson anyway but at this moment - Tyrex is the most powerful pirate out here. They elected him as the Code Keeper for a reason. You shouldn't ignore such a figure. It could prove useful to get know pirates better before you meet Swanson. You may even make yourself a name among them...";
			link.l1 = "And yet again, we are back to the pirate talk. No way I am getting away from it, huh? Very well. I will pay him a visit.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "To be a pirate and to do business with them it's a totally different game, brother. I hope you will see the difference. Go to La Vega and ask Tyrex for a job. If you two will not get along - screw him and get back to me.";
			link.l1 = "Very well, Michel. See you!..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
		break;
		
		case "saga_17e":
            dialog.text = "At least, you have tried. You had an opportunity to 'get familiar' with an infamous pirate baron. Nevermind. Go to Jan Swanson, he is in Blueweld. Try to make him your ally or our dealing with Levasseur will turn in a bloodshed.";
			link.l1 = "Fine. I am on my way.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "Glad you had stopped, brother. I once told you that it's a totally different game - to be a pirate and to do business with them. And you have lost your way. I hope you will not do the same mistake with the Shark and Swanson. Do the job but keep the distance from it. You are a French nobleman after all so be above them. Now go to Jan Swanson, he is in Blueweld. Try to make him your ally or our dealing with Levasseur will turn in a bloodshed.";
			link.l1 = "Fine. I am on my way.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "I am very glad to hear it if you are telling a truth. But can I really trust a word of a pirate who burns cities, even Spanish, and murders civilians including women?";
			link.l1 = "Stop.. I am really sorry for what I was doing during my time with Tyrex. I have seen the hell with my own eyes, brother... No, it's done! I am done with piracy and no way I am setting a foot in La Vega again. I will do everything it takes to restore my good name.";
			link.l1.go = "saga_17gx";
		break;
		
		case "saga_17gx":
            dialog.text = "You will have to put a great effort in it, bother. Do you remember what I had told you once? That it's a totally different game - to be a pirate and to do business with them. You... Forget it, I hope you will not do the same mistake with the Shark and Swanson. Do the job but keep the distance from it. You are a French nobleman after all so be above them. Now go to Jan Swanson, he is in Blueweld. Try to make him your ally or our dealing with Levasseur will turn in a bloodshed.";
			link.l1 = "Fine. I am on my way.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
		break;
		
		case "Base_fight":
			dialog.text = "Now it is not the right time for conversation, brother! The enemy is in our refuge!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			if (pchar.model == "Sharle_6") sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "You're right on time, dear brother! I'm so happy to see you! These forsaken Castilians have completely taken over Saint-Pierre already. I thought that we were done for sure! "+sTemp+"";
			link.l1 = "We're not out of the woods, yet the city is clear, but the scumbags are sitting back in the fort and there is a huge squadron headed by a battleship. But I do bring you quite delightful news: Michel, you're free!";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "I don't believe my ears! Can it truly be? Freedom?!";
			link.l1 = "Levasseur is dead, Tortuga is now headed by your ex commander, and the old fox Poincy has removed all his charges against you. From now on, nothing threatens our good name.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "I doubted until the last minute... You have surpised me, Charles, and succeeded where I suffered a distressful fiasco.";
			link.l1 = "Audaces fortuna juvat, brother... As you can see, I know Latin too now. Where is a key from your cell?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "The keys to my casemate should be at the orderly officer's desk. Look well for them there. Maybe they've fallen onto the ground and skidded of somewhere...";
			link.l1 = "I'll go find them and I'll be back!";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "Freedom at last! Oh, how long I have waited!";
			link.l1 = "You can't even imagine how long I've awaited this second... Michel, do we have people capable of fighting?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "What have you got in mind, Charles?";
			link.l1 = "The threat presented by the Spanish is not liquefied yet. I want to knock them out of the fort and then join forces to attack the squadron both from land and from sea! By using the cannons from the bastion I will be able to tussle with the battleship!";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "We've got manpower. A large portion of knights have left to protect the governor's palace. We'll definitely be able to find someone in the city... I'll put together all the people I can find. See you beyond the city gates!";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "Here it is brother, our army. All the people I was able to find. Now much in the matter of numbers, but we will fight for our Fatherland! We'll knock these fucking intruders clear out of the fort! The element of surprise will help us - they are not expecting our attack. Onward!";
			link.l1 = "Dulce et decorum est pro patria mori! Onward!";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "It's done, brother! The fort is ours!";
			link.l1 = "It's a pity that took such a hit in the battle with the Spanish squadron... but it is still quite capable of leading a battle.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "I'll play my part. We'll load the cannons and deal the enemy a hefty blow! But only after we see your squadron approaching, or else the man-of-war will quickly blast us into sawdust.";
			link.l1 = "Get the people together, Michel! I'm immediately moving out back to the shore!";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "Charles, remember: the most dangerous part of the squadron is the man-of-war Try to take her out first. We'll also concentrate fire on her with what's left of the fort's battery.";
			link.l1 = "All right, brother. Perhaps, I should capture her.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "Judging by the circumstances, I'm not the one who should teach you. Now we should stop wasting our time!";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "Gloria victorious! Congratulations with you victory, brother! You were great! The Spanish are completely destroyed!";
			link.l1 = "I hope that'll teach them to think twice before attacking French colonies.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "Now tell me, Charles: what is your past life worth... compare to this one?";
			link.l1 = "Don't remind me...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "Do you remember what I told you during our first meeting here? 'You will love this life', that's what! Yes, and a huge thanks to you, brother, for your help. Without you I'd likely have never managed to escape the confines of that underground base.";
			link.l1 = "Don't mention it, Michel. You are my brother after all and I was obliged to help you.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "Just look at you, brother, I am impressed: so much strength in eyes, confidence in moves, stature in posture... and where did that shitty artist and court jester go? Indeed! You have overcome all my boldest expectations, truth to be said, I never thought that you would become... this\nIt even... scares me a bit. Because you will stop at nothing in order to achieve the goal. You are good, too good...";
			link.l1 = "For some reason I'm having trouble understanding you once again. Are you unhappy with me again?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "No! What are you talking about?... Not at all! I was just channelling my excitement.";
			link.l1 = "All right. So, what will you do next, brother? Will you continue serving the Society? Or will you return to our patrimony? Yes, and I almost forgot: you promised to tell me about one thing.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "About what exactly?";
			link.l1 = "About your service for de Poincy. About some Indian gold that you were going to bring him. About everything that preceded your imprisonment. There's a lot you haven't managed to tell me, Michel, riding me blind pretty much. So...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "Brother, I remember what I said perfectly. I will tell you everything. But not in the middle of burning city!\nWe both have a lot of things to do now. You need to settle your squadron, to fix and to get ships ready, me and the governor should organize and calm down the locals\nWe will discuss everything tomorrow morning with a glass of good French wine. Trust me, brother, I have big plan. A really big. But not now. Come tomorrow at nine a.m. to abbot Benoit. I will spend a night at his place, he is an old friend of mine.";
			link.l1 = "Alright, Michel. It's settled then. I'll be looking forward to our tomorrow conversation.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_7":
			dialog.text = "No need for goodbyes, Charles!";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with a brave captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while such brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("VOICE\Russian\sharlie\mishelle-04.wav");
			dialog.text = "So we meet again, "+pchar.name+". Despite my warnings, you still went searching for me and your searches have brought you far far away...";
			link.l1 = "Michel?... For some reason I'm not surprised. Has Miguel Dichoso returned to Tayasal for another heap of treasure? Hm-hm-hm. Yes, I have been seeking a meeting with you, dear brother. I was just dying to have a look into your shameless eyes. On top of that, your assassination attempt on me in the graveyard crypt was the icing on the cake. But first, tell me, how should I call you? Michel de Monper or Miguel Dichoso?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "These names are no longer of any importance anymore, "+pchar.name+". It's all in the past, which will very soon disappear even from history. Now is the moment of truth, which I've been inching towards a long quarter of a century since I first made it on the land...";
			link.l1 = "What?!! This... this cannot be!!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "Yes, "+pchar.name+". I see by your face that you understand who I am, but you can't believe it. I am the one you've aspired to meet over the past months. The one, into the battle with whom the representative of your God,the Inquisitor from Santiago, have blessed you.";
			link.l1 = "Kukulcan?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "I agree, "+pchar.name+", that it is difficult to believe. Life is more complicated and more surprising than any fairy tale...";
			link.l1 = "I was ready for anything, but... my brother!";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "Brother? Only by father's blood. We have different mothers, "+pchar.name+". Know that my mother was a daughter of Kanek, named Shochikezhal. She was abducted by French capers under the command of famous Nicolas Gotier after she foolishly left Tayasal. They had decided to sell her to slavery. A man named Serge Benoit was among them\nAshamed of his captain's deed he had left him, took the veil and now you know him as abbot Benoit. Henri de Monper, our father, he was a navy officer back then. He bought Shochikezhal and took her to France where she gave birth to me. That is also when you were born too, "+pchar.name+". Your mother died giving birth and our father declared that his lawful wife had given birth to twins\nShochikezhal, my mother, had become a wet-nurse for both of us. You were fed with milk of Indian woman of Itza people, "+pchar.name+"! Later you grandmother by mother's line decided to took you for education and you were given the name of your mother - de Maure.";
			link.l1 = "How did you find all that out?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "Wouldn't you think, brother, that I should know more than people do? Also, our father has told me a lot and I am aware of a lot... It's just as they say by the seat of my pants.";
			link.l1 = "Now it's all coming clear... And what happened to your mother? Why I have never seen her?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "She died saving my life. In a little over a year after my birth, I ended up close to death due to a disease. My mother, the daughter of an Itza priest, conducted a secret Maya healing magic ceremony over me. I got better, but this ceremony was accompanied by some...destructive side effects in a form of thunder and a tropical hurricane, Shochikezhal was denounced and accused of sorcery and burnt on the fire of the Inquisition...";
			link.l1 = "And you got better...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "Other than the healing, this ritual gave me other abilities as well, in addition to opening connection to the world of the gods. And you already know the rest. As you are already supposed to know, I will bare the light of knowledge and experience of the white race into the past and pass it onto the people of Maya. History will be rewritten and you, whites, will not dominate this world. I will make sure of it.";
			link.l1 = "So your whole life studying at the best naval academy, serving in the army and the Maltese Order was all basically an accumulation of military experience?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "Exactly. When I realized that I knew enough, I arranged that I would be commanded to the Caribbean. I talked Philippe de Poincy into creating a base on Martinique. Next, I had to make my way to Tayasal. It wasn't exactly a simple task for me, for this physical vessel remains mortal and the portals on the Caribbean weren't working correctly.";
			link.l1 = "And you became Miguel Dichoso...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "Dear brother, I got this nickname on the battlefields of Europe. I also met there Ramon de Mendoza y Riba. You think that life is made of chances? No, not at all, every chance is an unknown regularity. A lot had been done for the sake of my return to Tayasal. I had to live two lives. Michel de Monper and Miguel Dichoso, I also had to make sure people believe them to be different people\nI had to pirate on a so called service for de Poincy in order to gain his trust, favour and money. I had to murder Blaze Sharp, a leader of pirates, as a favour for Ramon de Mendoza, in order to get soldiers for the expedition\nI had tempted both of them with tales of Tayasal's treasures. I have received seven hundred and fifty thousand silver from de Poincy's treasury and sold the Spanish military frigate to pirate Dodson. And then the expedition happened. I had returned back to Tayasal only to suffer a failure...";
			link.l1 = "I understand... While you were but a five years old boy chasing the butterflies in our father's patrimony, Kanek the great priest, frightened by Don Alonso de Maldonado's invasion into Tayasal, securely hid the Kukulcan mask which is so vital to travelling into the past... beg pardon, I meant YOUR mask.";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "Yes, Kanek had outsmarted himself there. He performed the most difficult ritual, the ritual even the ancients didn't dare to do. He hid the mask on the fresh made deserted island and managed to lose the key to Ksocheatem - so called Guardian of Truth\nI had to play smart. The ritual prevented any ship, carrying protected items from Taysal's treasury aboard, from leaving the Caribbean by throwing such vessels at the shores of Ksocheatem. I intended to use that. I took enough treasures to appease Mendoza. I also took a special item protected by the ritual\nThe ship with this item aboard would be doomed to be delivered right to Ksocheatem, right to my mask. So I went to the sea coast and let Mendoza know about myself.";
			link.l1 = " So, you left Tayasal by yourself?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "You mean without Mendoza's soldiers? Sure. All Spanish were slain here, in Tayasal. Itza had brought treasures to the shore themselves and I told Mendoza that the soldiers were ambushed by Miskito people. He believed it, since he was interested in gold not in people\nI planned to set up the ship with treasures under the cannons of the 'Gryffondor', but it all went much better: the baron decided to send the treasures to Spain under my watch. That was the best variant possible, I only had to wait until the ship crosses the invisible border of the Caribbean\nTurned out that captain had different orders.  I found out that a special boarding unit was supposed to mutiny as soon as we reach Atlantic ocean, kill the crew and all officers. Then the captain had to return Indian gold back to Mendoza\nSuch a fine specimen of white race isn't he, brother? I had to risk it, I didn't know when the mutiny was supposed to start. But it all went according to the plan: the storm had hit us as soon as the 'Santa Quiteria' reached the East of Tobago island. The frigate got carried away back to the Caribbean toward Ksocheatem\nThen I had suffered the biggest failure of my life - a wave washed me of the ship and later I found myself at Le Marin Cove of Martinique. Fishermen had found me and took me to Le Francois. But de Poincy's men captured me while I was coming back to life at Cesar Craig's place. The 'Gryffondor' didn't find 'Santa Quiteria' at the place I defined. The Chevalier got furious as soon as he learnt that the Indian gold is gone as well as the money taken from the Order's treasury and his own savings\nHe had me arrested. He couldn't kill me though, he didn't want to. He wanted gold. Gold! That is the only thing your people want! You will do anything to get it... I was in a terrible position: I had no mask with me and I was in a cell with not a single coin in my pockets\nThat was when I summoned you. Yes-yes, dear brother, you were supposed to free me, so I could do what I was born to. And you did an extraordinary work. It seems that the Itza milk you suckled did you some good.";
			link.l1 = "What I'm interested in, is what you were counting on when you escaped Saint-Pierre then? What was your plan?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("VOICE\Russian\sharlie\mishelle-05.wav");
			dialog.text = "You were my plan all the way, brother. Kukulcan can read people's hearts. The letter I left for you at abbot's was supposed to make you act. I was right about you. I had been watching your progress ever since you had a first meeting with the Inquisitor of Santiago. You did everything for me. You have crafted the Guardian of Truth. You have eliminated the competitors. You have found Ksocheatem\nI was there, following you. Though I didn't expect you get in Tayasal. You have overcome all my expectations. And with your help, I will do what I was born to. The reason why I was born in a mortal flesh.";
			link.l1 = "There's just one little hole in your reasoning, dear brother. You don't posses your mask, you are nothing without it. I have it. And I'm not burning with the desire to give it away to you. I'd more likely blow it to shreds rather than let it end up in your hands.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "You can't change what's predetermined by fate. I will not allow you to damage my artifact. I can feel it... It's with you. And you are here, in my temple, within my full power! You will not leave this place ever. It's time for your final test, dear brother, to see what you worth in a battle against Kukulcan!";
			link.l1 = "I suppose that your mortal body still can bleed!";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "Ha! I feel bad about you, Charles. This is really sad. But you deserve a chance to fight the God. Even if it's pointless. I'll tell you later, if you survive the first act.";
			link.l1 = "I suppose that your mortal body still can bleed!";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "It seems your powers depart from you, great Kukulcan...You may be strong, but your body is yet mortal!";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "I think that will be enough of an entertainment. You are truly a master swordsman and a great fighter, I would even dare to say a greatest warrior of your time, but this battle you have lost, "+pchar.name+"...";
				link.l1 = "We're just...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "Enough, dear brother. You cannot withstand the power of Kukulcan when he's together with his artifact! I have allowed you to stay alive for so long just to watch what you have really been able to achieve.";
			link.l1 = "Fuck... That last blow... But what artifact do you speak of? The mask? It's with me!";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "Poor, poor captain "+GetFullName(pchar)+"... You have come this far, survived all dangers, slain so many strongest enemies only to be defeated in the end!.. The jade mask you found inside a metal box close to the wrecks of the 'Santa Quiteria' at Ksocheatem is a fake! It is just an ancient mask from Taysal's treasury. It is NOT THE MASK OF KUKULCAN!\nI had personally taken it from here after my failed expedition, it is guarded by the ancient ritual, this mask was the reason why the storm had the Santa Quiteria carried away to Ksocheatem. It also had a second purpose. It was supposed to fool anyone who came there for my TRUE artefact.";
			link.l1 = "But... Where was the real mask then?! I had searched all over Ksocheatem!..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "You hadn't, "+pchar.name+". My artifact was lying on the opposite side of the island from the 'Santa Quiteria' in a securely guarded sanctuary. The road there leads through underground caverns. It's complicated to find and not obvious to the in exquisite eye of a mortal. There it is! Take a good look at it, one final look...";
			link.l1 = "It can't be!";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "You survived and won a lot of battles, brother. But you've lost this one, "+pchar.name+"...";
			link.l1 = "And what now?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "I will travel directly into the tenth century, seven centuries back. This will be enough for the Maya civilization to reach unshakable military and scientific prowess over the white race.";
			link.l1 = "And what will happen to our world? Will it disappear?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "No. It will change. Perhaps, there will be a place for you, but you will remember nothing of what happened in this world. Some of those who was born here will never be born there, the opposite is also correct. The dead will come back to life and and the living will die, one way or another, everyone will reborn. Suum cuique, to each his own, "+pchar.name+"\nDon't be afraid, little brother. You will never realize what has happened and you will naturally embrace the new reality. Only I, Kukulcan, will keep memories... But enough! Kanek has already prepared everything for the ritual\nYou will follow me, "+GetFullName(pchar)+", and you will witness the last moments of this reality's existence which you were so eager to preserve.";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "The gates of times are opened! Rejoice my children as you stand in close to the greatness! We will create the new world, the world with no place for the pale invaders!\nFarewell, "+pchar.name+", and be ready to accept your new fate, whatever it is. Suum cuique!";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "This battle still isn't over, mortal. You are considerably worn out and I still have reinforcements coming! You will still give up my artifact. Either that or I'll take it from your dead body, it makes no difference to me...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "Urakan! I order you to kill this man immediately!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "Urakan! Didn't you hear me? I repeat: I order you and your warriors to capture and kill this man!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "Urakan! What the hell? Kanek! Repeat my order to your fucking son!!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "You betray your people, Urakan! You have quailed in the face of such eminent transformations! Warriors, I order you to capture and put to death not only this man who calls himself my brother, but Urakan the traitor!";
			link.l1 = "Warriors, in the name of Cavil and Hurakan I order you stand as you are if you value your life! Not one of you will survive a fight against Cavil! Let the gods decide themselves who of them is the strongest on the Earth!";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "This day is just gettig better and better. You didn't expect such course of actions, right, brother? The gods must decide themselves who is the strongest of them. And everyone will get what they deserve, Michele. Suum cuique! To each his own...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
