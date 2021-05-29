// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "What can I do for you, monsieur? I don't speak with people I'm not acquainted with. If you've stopped by just for a chat, then I'll have to disappoint you, I don't like being bothered with nonsense.";
					link.l1 = "Good afternoon, monsieur Fadey. You, of course, may not be acquainted with me yet, but on the other hand, you know my brother. Allow me to introduce myself - Charles de Maure, brother of Michel de Monper.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "Aha, you again, Charles! What is it this time?";
					link.l1 = "You said that you had been robbed... Have you found the culprits?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "So, Charles? Have you gone to check out that Indian dummy?";
					link.l1 = "I have... That's why I've come back to you.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "Ah, it's you again, my dear friend! Well, have you brought the doubloons for the Indian?";
					if (GetCharacterItem(pchar, "gold_dublon") >= 100)
					{
						link.l1 = "Yes. Here are your hundred doubloons.";
						link.l1.go = "Tichingitu_7";
					}
					else
					{
						link.l1 = "No, I haven't collected the required amount yet.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ha, well it's monsieur de Maure himself! Come in, come in... What brought you to my home?";
					link.l1 = TimeGreeting()+", Fadey. I have come to you on the advice of my brother. He's told me you'd definitely be able to help me find some work.";
					link.l1.go = "trial";
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ha, my good old acquaintance. What brought you here, monsieur de Maure?";
					link.l1 = TimeGreeting()+", Fadey. My brother insisted that I shouldn't speak to you about this, but I couldn't restrain myself... ";
					link.l1.go = "vodka";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "Aha, my old friend!  Come in, come in, "+pchar.name+"! How are things?";
					link.l1 = TimeGreeting()+", Fadey. Pleased to see you. I've actually come to you on business.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". I bet you're eager to discover the results of my soul-saving conversation with the priest?";
					link.l1 = "Of course I am! How did it go?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && GetCharacterItem(pchar, "gold_dublon") >= 250)
				{
					dialog.text = "I keep hearing the chinks in your pockets!";
					link.l1 = "Such attitude, monsieur Fadey! Here is your gold.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "Aha, my old friend! Come in, come in, "+pchar.name+"! How are things?";
					link.l1 = "Hello, Fadey. I have come to you once again for your help.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "Is there something you need, "+pchar.name+"?";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Take a look at what I have here, Fadey. Would I be far off to say it's a Persian sword blade and possibly one of the ones that were stolen from your home?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "I have good news for you. I have one more Persian cavalry sword for you here.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "I have a third Persian cavalry sword. Just as you asked, I came back to you right away.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "I'm here concerning the light armour we talked about.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, I would like to buy some of your ropes.";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, I need your help.";
				link.l1.go = "help";
 				link.l9 = "No, nothing at the moment.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "What can I do for you, monsieur? I don't speak with people I'm not acquainted with.";
				link.l1 = "Oh, I was just dropping by to look who lives here.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			dialog.text = "Ah, so you are good old Michel's brother! That radically changes the situation! Come in, come in, monsieur, have a seat. Maybe a glass of vodka for our acquaintance? I still have a few more bottles left and it would do me great pleasure do split one of them with one of my friends' brother!";
			link.l1 = "Forgive me, monsieur Fadey, but drinking is completely out of the cards. I would prefer to get right to business.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Eh, too bad... Rum is nothing compared to Russian vodka! You don't know what you've lost. Fine, to business then. I'm all ears, Charles.";
			link.l1 = "Monsieur, I suspect that what I'm about to tell you will come as quite unpleasant, but alas, I am compelled!  Michel has told me that you owe him quite high gambling debt. He has also ordered that you hand the money to me, cause my brother is... not able to come see you personally at the moment.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Oh, young man! Of course, I remember everything and I unreservedly admit that I owe your brother. A gambling debt is sacred, every nobleman knows that. But I beg you to understand my position. An unpleasant story happened to me recently - I was robbed in the most impertinent way!\nDamned thieves took everything they could, everything I had earned for the last years, my money and my priceless collection! I simply can't wipe a debt right now\nBut, monsieur de Maure, I don't give up my obligations! I only ask you to meet me halfway. Since I don't have any coin in my possession now anyway, I offer you to accept this excellent rare dagger. Take a look!\nThis is a real masterpiece of arms, a pride of my stolen collection. Besides it was enchanted by Indian shamans and has very strong hidden features. Indians called it the Chief's claw\nI would have never agreed to give it away because I paid a great sum for the dagger, the sum much bigger than my debt, but considering the circumstances I am ready to give it to you. Take it, it's a very good deal for you!";
			link.l1 = "Hm... I'd prefer the money...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "But I really do not have it. Do you really think, my good man, that I would offer you this magnificent hoodoo dagger instead of some pitiful coins? You have to admit, I'm stuck in a rut here. My heart bleeds when I say it. But a gambling debt is a debt of honour, so I'm willing to part with this item, which is very dear to me.";
			link.l1 = "Alright, I agree. Since you don't have any money anyway, I'll at least take this vaunted dagger of yours. I hope I can at least fetch a decent amount of money for it...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'At least'!? No, this is unbelievable! I'm giving away my most prized possession that I would get at least ten times more for in Europe, and you stand there saying 'at least'!? This dagger, young man, if you would like to know, saved one man's life! And he...";
			link.l1 = "And what is its hidden power that you mentioned?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Oh, Charles! I am a Christian, you know, not an Indian shaman. And I have no way of knowing all the hidden properties of this blade. But they exist, I assure you. Put this dagger in your hand and you can feel it by yourself! Take it, take it! How about that! Do you feel anything?";
			link.l1 = "Hm... No. Although it fits the hand very comfortably, not too bad.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "There you go! But that's merely the least of its qualities. If you put this dagger to use in battle I'm sure it will display its might on all cylinders! Well then, are you taking it?";
			link.l1 = "Do I have a choice? I'll take it since you've got such money troubles...";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			dialog.text = "It's a sensible decision, Charles. You won't regret it! Here you go. And make sure to say hello to Michel from me! Tell him to drop by sometimes, of course as soon as he gets an opportunity.";
			link.l1 = "I'll tell him, make no doubts...";
			link.l1.go = "exit";
			link.l2 = "You said that you had been robbed... Have you found the culprits?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2"; 
		break;
		
		case "Sharlie_8":
			dialog.text = "The thing is I haven't. The scumbags cleared out the whole house, ran away with all the silver, gold, my savings from years of back breaking labour, but the worst thing is they swiped my magnificent collection of Eastern swords! There wasn't a collection like that in all of the Caribbean. Very, very remarkable Persian cavalry swords...";
			link.l1 = "Eastern swords, you say? Sounds quite curious. So you're a collector, then?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Well, I like to collect rare things... Listen, Charles, maybe you can help me in the matter of the sword blades...";
			link.l1 = "Help? But how? You mean by catching the thieves?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "Not at all. I'm not particularly interested in the thieves. I would like my Persian  cavalry swords to return back to me. If you find them, I won't just stay in debt, I promise.";
			link.l1 = "Hm. But where should I look for them? Around the Caribbean? Or maybe all around the world?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Well, maybe you'll catch sight of them on the isles with some street merchant, the scumbags couldn't even imagine the value of these cavalry swords and they've surely sold them for peanuts. So if you see the Persian sword blades anywhere, bring them to me. Will you be able to recognize them?";
			link.l1 = "I think I will. Okay, I'll keep my eyes peeled and if I see something that looks like them, I'll definitely bring it to you.";
			link.l1.go = "Sharlie_12";
			link.l2 = "You know, I'm not an expert in fine weaponry. I'm afraid I won't be able to help you. So it would be dishonest of me to give you false hope.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Great! I hope you will be fortunate. And I will make it worth you while. Yes, Charles, can you imagine that I had another robbery attempt recently\nA thief tried to get inside my house just a few days ago\nThat was just too much for me! He didn't escape from me though: I managed to catch him, gave him a good beating and sent to the local prison. I guess they will hang him soon. Good riddance!";
			link.l1 = "You think he's one of the guys that snagged your cavalry swords?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Pity, but it's no use crying for the moon. Yes, Charles, can you imagine that I had another robbery attempt recently\nA thief tried to get inside my house just a few days ago\nThat was just too much for me! He didn't escape from me though: I managed to catch him, gave him a good beating and sent to the local prison. I guess they will hang him soon. Good riddance!";
			link.l1 = "You think he's one of the guys that snagged your cavalry swords?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "Nah, I don't think so. He was interested only in money. Imagine a scarecrow in my room, picking my chests\nAn Indian from some deep jungles, that's ridiculous. Coloured and in costume... You may visit our dungeons and see that jester by yourself if you want, while he still lives.";
			link.l1 = "Hm... Maybe I'll drop by.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Go ahead, have a gaze at the local walking wonders... All right, Charles, it was a nice talk. Are you going back to Martinique now? Happy trails.";
			link.l1 = "All the best, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			dialog.text = "How interesting! I'm listening.";
			link.l1 = "Fadey, I've spoken with that Indian. And I came to you to ask for help to get him out. The desolate heart just wanted something to eat...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Ha-ha-ha, and you believed those fairy tales? Youth...";
			link.l1 = "Fadey, of course I may be younger than you, but even I am in a condition to differentiate when I'm being told the truth and when I'm being lied to. Besides, do you really think a hanging is an appropriate punishment for that kind of a crime?";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Maybe it is! That scoundrel snuck into my home! What would you do in that case? I'm sure you'd just cut him with a sabre, wouldn't you?";
			link.l1 = "No, I wouldn't. Fadey, I'm sure you're just enraged out because of your stolen cavalry sword collection. If it wasn't happened, you'd just give this redskin a leathering and kick him out with a punch in the butt. Am I wrong?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Eh, Charles...You're just like your brother... Fine. We'll do this like businessmen. Since you need this Indian so bad, compensate me for the moral distress for him and I will write a pardon that will, of course, be upheld. Is that fine?";
			link.l1 = "How much?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ha, you're already starting to learn life in the Caribbean, Charles. One hundred fifty gold doubloons.";
			link.l1 = "Fadey, God have mercy...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Alright, alright. One hundred gold doubloons. But that's my final offer. And we're talking about doubloons not pesos. Our banker will surely be able to come up with some amount.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 100)
			{
				link.l1 = "I've got the amount you need right now. Here you go, here are your hundred doubloons.";
				link.l1.go = "Tichingitu_7";
			}
			link.l2 = "All right, I'll go get what you need.";
			link.l2.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "And hurry, Charles! You have ten days...";
			link.l1 = "I'll keep that it mind. Goodbye!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			RemoveItems(PChar, "gold_dublon", 100);
			PlaySound("interface\important_item.wav");
			dialog.text = "Great! Get a hold of him! I'll write a note right now and put my stamp on it, hold on a second... here you go. Give this to the commandant and you can take your Indian with you. Why exactly you need him, I can't wrap my mind around it. What are you gonna do, display him at some fair? Ha ha!";
			link.l1 = "God sees everything, Fadey. Saving a man's life is a noble deed.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "That's a debatable, Charles. What if you save a killer or a rapist?  Anyway, may God be with you. Go to the commandant before your red-skinned friend gets hoisted on the scaffold...";
			link.l1 = "I'm on my way. See you later, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
		break;
		
		case "vodka":
			dialog.text = "You don't say so! By your stern face, I take it you're about to bring me up to speed on some bad news?";
			link.l1 = "Pretty much. I'll be straight: Michel said that you basically fooled me with this 'Chief's claw' thingy and that it's a piece of regular old junk, that you could buy from any street merchant for a couple hundred pesos. By the way, I asked around as far as its price from some street vendors dealing in metalware. They named me exactly that price.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Oh, monsieur de Maure... I'm surely surprised by your brother. These half-wit hucksters can say whatever they want, but him! You tell me, Charles, if somebody brought you an old two hand knight's sword of the king Arthur days and offered you to buy it, what would you give for it?";
			link.l1 = "A two hander? Are you mocking me? What use of it? We're in the middle of the seventeenth century! I wouldn't give anything for it. Not a peso.";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "See! And if you bring such sword to me, I will pay three hundred doubloons for it. Ask why? Because it is a rarity, hard to find in our seventeenth century! You don't understand, yet you judge!\nThe Chief's claw is also a great quality dagger, experts told me that Cortez himself owned it. The Cortez! The one who captured Tenochtitlan! And you are saying that it is a rubbish!\nBesides, I have already told you that it's not just a dagger, it is an enchanted dagger! You are still a newcomer here so you don't know yet what role play magic spells, rituals and curses in the Caribbean! Charles, this is the New World, the homeland of Maya and Aztecs whose knowledge of such things had reached inconceivable heights!\nThis dagger has hidden powers, alas no one just knows what kind of powers. You have a unique, incredible chance to learn it yourself and yet you call it a rubbish!\nIf only I had enough money to cover my debt to your brother, I'd immediately exchange it back for despicable metal... This is a very valuable item and its cost valued not in money...";
			link.l1 = "Alright, alright, Fadey. I believe you. Your arguments are quite convincing and the ardour that you have just performed here is a testament to your sincerity.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Hear, hear! Well said! You've done well, Charles, for not taking offence and coming directly to me for an explanation. I hope now the incident is dismissed?";
			link.l1 = "Yes, monsieur Fadey. Completely. Now, please, allow me to make my bow...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\Russian\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Stop, Charles! I'll be honest, I really like you. Maybe you and I could become friends one day. And why not to make the first step toward that right now? I literally just cooled down two bottles of excellent Russian vodka in spring water down in the cellar. What do you say if you and I split it to your brother's health?";
			link.l1 = "Hm. I'm sorry, monsieur Fadey, but it's already time for me to set out to sea. I'm truly in a hurry!";
			link.l1.go = "vodka_no";
			link.l2 = "You had offered last time and I refused... It would be impolite to refuse again. Fine, Fadey. I am in!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "That's too bad. Compared to vodka, rum is just a rotten, cheap wish wash. But since you're in a hurry, I don't hold you anymore. Good luck, Charles!";
			link.l1 = "Same to you, monsieur Fadey...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "Well, get a load of you! Splendid! Let's have a sit and talk! Have a seat, monsieur, and I'll go get the vodka. Oh, it's gonna be tasty. It's nice and cold!..";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Whoo... Sso, tell m-me, Fadey, h-how does t-that work out? Hic! We've drunk... t-two b-bottles of v-vodka... by the way, how ironic! - you look s-stone c-cold sob-ber and I'm... drunk as a hog. How's t-that, huh?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, enjoy yourself, relax. What's a hog got to do with this? I've got some excellent vodka. Get some sleep and you'll be chipper as a whistle when you wake up. Even your head will clear up. You'll see.";
			link.l1 = "Y-yeah, vodka...it is... it's absolutely magnificent, your vodka. I've never drunk anything like it.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ha! You've got that right! That kind of vodka is made where I'm from, in Russia, and even there not everybody knows how to make it right. I buy only the best. Like this stuff here that you and I have deigned to nip.";
			link.l1 = "B-but tell me, Fadey: h-how c-can you drink s-so much and not get drunk? H-how ya do that, huh? Sh-share the secret with me. M-maybe it'll c-come to use later... Hic!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ha! Well, you can't compare you and me, monsieur. Just look at yourself, skinny as a whip there. Plus, you're not used to it. But anyway, I'll share a few secrets with you about how to drink and still keep yourself together.";
			link.l1 = "P-lease d-do...hic! Monsieur Fadey...";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "Well, if you want to drink and not to get drunk you should follow a few rules. Most importantly, never drink if your stomach is empty. Eat something decent before the libation starts\nSecond, don't forget to eat after every glass. Meat or fish will be the best. Third, don't wash your mouth with the drink, swallow at once\nAlso, having a small - not more than a half pint - shot prior the main libation will prepare you poor body for receiving big doses of alcohol. Don't overdo it, otherwise the effect will be quite the opposite\nFinally, training is the key, drinking moderate amounts of rum or other types of alcohol on a regular basis will make you more resistant to them.";
			link.l1 = "Hm-mm... S-so that's how you do it! I'll d-definitely...hic!.. remember all your ins-structions, Fadey. Th-thank you. And n-now I think it'd b-be a g-good idea for me to g-get some shuteye, cuz I aint f-feelin too hot today.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Get some rest, Charles. We've had a nice evening, you and I! Good luck to you and see you later!";
			link.l1 = "G-goodbye, Fadey!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "What, did he actually say that I would definitely help you?";
			link.l1 = "Well, pretty much. Won't you give a hand to the brother of your longtime friend? It's not like I'm asking for money from you. I'm asking you to present me an opportunity to make it.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. No, I won't turn you over of course. If you wanna feed a man, don't give him a fish, but a fishing pole. Isn't that right, monsieur de Maure? So you need a job... Easy enough. I'll have a chat with a man I know and I'll recommend you to him. And everything else will depend only on how well you do the job.";
			link.l1 = "Wonderful. Who do I need to speak with?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Come by the store tomorrow. A man by the name of Gerard LeCroix will be waiting for you there. He'll give you some work. He'll stay in our colony only until tomorrow evening. See him in time and do the job well. Don't put me in an awkward position.";
			link.l1 = "Deal. Gratitude, Fadey!";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		
		case "guardoftruth":
			dialog.text = "Well, who'd doubt that you're here on business, my friend! I don't have any vodka to offer you at the moment, it's all gone. Tell me what kind of affliction has come upon you now.";
			link.l1 = "A local parish was given a golden pectoral cross with lazurite by a certain privateer for the forgiveness of his sins. It's a unique and valuable item. The trouble is that this cross was stolen from another parish. Not only that, but a priest was murdered during the robbery.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "You don't say so!";
			link.l1 = "Yes. At the moment I am representing the interests of followers of the parish which was robbed and I am attempting to return this item to its legal place.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "A noble deed, and very pious...";
			link.l1 = "But the revered father refuses to return it to me despite all of my arguments that I've made to him. I don't get it. How can one calmly place a stolen item with blood of a holy man on it in a place of God? That's flat out blasphemy!";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "I take it you want me to assist you?";
			link.l1 = "I do! You're quite an influence in Basse-Terre. You're well respected, so perhaps the revered father will listen to your admonitions?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", have you told the story of this cross to our priest?";
			link.l1 = "Of course! I have called to his religious sentiments, to Christian solidarity, to his conscience for God sakes, but he still closes his ears to my pleas.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Hm... Have you tried using any other methods to convince him?";
			link.l1 = "You mean bribing him? No... If he were a banker, or a merchant, or even a governor, I would attempt to solve the issue that way, but a priest!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "My friend, if the priest's ears really are closed to proclamations of conscience, then surely his hands will be open for gold... Or the other way around. I'll help you, I think that keeping such items here is unacceptable. However, it will require certain expenses."
			link.l1 = "Not a big surprise. How much?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Come by tomorrow, "+pchar.name+", for how much I am not yet aware. But you will receive your item, rest assured.";
			link.l1 = "Thank you, Fadey! I won't bother you any further then. See you tomorrow!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Just as I assumed. I've got the cross, "+pchar.name+", and the details... oh forget them... all nonsense and fuss!";
			link.l1 = "How much do I owe you?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Two hundred fifty doubloons. A coverage of my expenses, and of course I'd appreciate a little for my righteous aid...";
			if (GetCharacterItem(pchar, "gold_dublon") >= 250)
			{
				link.l1 = "Right this way, monsieur Fadey! Here is your gold.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "I'll will take the money from a chest in my cabin, wait a bit!";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "Excellent. Here is your item!";
			link.l1 = "Thank you, Fadey. You can't even imagine how much you've done for me!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveItems(pchar, "gold_dublon", 250);
			Log_Info("You've given 250 doubloons");
			GiveItem2Character(pchar, "jewelry34");
			Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "I am always glad to help a kind and more importantly generous friend. Drop by more often. Maybe we'll have some vodka when it's delivered to me from my homeland.";
			link.l1 = "Sure!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Well the oceans have parted! Fill me in. What misfortunes have brought you to me this time?";
			link.l1 = "I don't know whether to call them misfortunes or not, but nevertheless I'm here. Fadey, the first day we met you gave me a rare dagger, the Chief's Claw. Now I know that it previously belonged to a man named Archibald Calhoun. Please, tell me what you know about this man.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Nothing can be kept from you, "+pchar.name+". You see everything through, just like your brother. Yes, I won this dagger in game of dice from Archibald. Who is he? I don't even have a thought myself. We met by chance, we got to talking, drank a little, and he started telling me about some sins of his past that were weighing him down...";
			link.l1 = "What sins?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibald was eating himself over some man who got tortured by the Inquisition to death because of him and over other innocent souls he killed. He was constantly calling himself Judah. Said that God was punishing him for his sins - the Inquisition hunted him\nHe mentioned that Spanish inquisitor Vincento himself wants him dead and sent Spanish mercenaries to chase him everywhere. Then alcohol had won over him and we gambled for this old dagger.";
			link.l1 = "Is that all? You never saw him again?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Archibald's dead! Cursed pirates sent his flute to the bottom of the sea and sent the whole crew to Mictlantecuhtli. Actually, rumours were that it wasn't pirates but Spaniards dressed up as tramps... the Inquisition, "+pchar.name+", that is a serious organization.";
			link.l1 = "Archibald Calhoun is alive. I saw him not that long ago along with some William Patterson. He serves as his first mate.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Oh, you never guess how things unfold! I had no idea! Under the wing of captain Patterson, Archibald can at least catch his breath. He's in good company. The Spanish fear Patterson worse than a plague and they won't dare be scheming any more.";
			link.l1 = "Do you know Patterson?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "That I do, my friend. Who doesn't know that distinguished man! He, just as you, has arrived to the archipelago recently, but has already hammered together an outstanding reputation. Mister Patterson is Colonel Fox's closest friend and well in with Lord Windsor himself, the governor general of all English settlements here. He often visits the governor's palace in Port-Royal.";
			link.l1 = "Got it. Well, thanks for the story, Fadey!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Oh, don't mention it, friend. Come visit me sometime!";
			link.l1 = "Definitely!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Let's have a look, "+pchar.name+"... Oh yeah, it's one of them! Where did you find it, my friend?";
			link.l1 = "It doesn't matter. The important thing is that it has found its way back to you.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "I'll be paid well for your gruelling labour. Three hundred golden doubloons is a dignified reward for your troubles...";
			link.l1 = "Fadey, your kind disposition to me is much more valuable than these three hundred doubloons. Although, of course, I won't reject them. Here is your cavalry sword.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Thank you, my friend! Thank you kindly! For the sword and for you're reasonable words. You're intelligent beyond your years, "+pchar.name+", you speak the real truth, human bonds of friendship surpass the value of gold. But talking about the precious gold, of course, I will pay you in full. Here, take your doubloons.";
			link.l1 = "Gratitude!";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "And talking about the bonds of friendship, yours and mine in particular, "+pchar.name+". I have something that you'll be quite interested in.";
			link.l1 = "Something means vodka?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Vodka is good, but it is not the only thing my country is known for. There is a ware which only Russia produces and I deliver this ware here to trade. Any captain is interested in it, because it is a part of any ship. I am talking about hemp ropes\nThey are immune to a moisture and sea salt. They say that it is the best material for a rigging\nEvery month trade ships deliver me some amount of the ropes. Normally, my storehouse has a few hundreds of coils by the middle of each month. So, "+pchar.name+", I am offering you to buy a batch of fifty coils. Ten doubloons for a coil\nI have only two terms: I will keep your ropes until 20th of every month and you can buy only a whole batch. Fifty coils for five hundred gold. Confidentially speaking, "+pchar.name+", they say that there are places where you can resell the ropes for a much better price, but that's all I know\nThough I am completely satisfied with the current state of my operation. If you find a good merchant then you will have a fine profit.";
			link.l1 = "Got it. That's a great offer, Fadey! I think I'll take advantage of the opportunity you've presented to me. So, every twentieth day of a month, five hundred doubloons for fifty pieces?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecord("Unique_Goods", "2");
			dialog.text = "Correct. Go collect your purchase. But wait, wait, dear fellow! Besides this sword, which you returned to me out of true benevolence, there were two others. I beg you, please, if you find them, bring them back right to me and I will pay you more than a fair share.";
			link.l1 = "Definitely, Fadey. If I find them, I'll definitely bring them back.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Good news for you then. I've got another Persian cavalry sword here.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "Oh, my good friend! You have just swabbed my tears! Let me take a look... yes, this is it, my precious cavalry sword! Here, just as I promised you, three hundred doubloons reward for it.";
			link.l1 = "Gramercy!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Please accept my gratitudes and a modest, but a very useful gift. I don't need it, but you or your ship joiner will find it quite helpful\nHere, look at this fine ring! It's yours now. But it is not just a common ring, it is an enchanted ring. It helps in carpeting and in ship repair. A lot of craftsmen would like to have it, but I have been keeping it for a special occasion. Take it, my friend, I wish it will ease your burden!";
			link.l1 = "I didn't expect that! Thank you very much, Fadey!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "There's only one cavalry sword of my lost cavalry sword collection left to be found. I'm counting on you, "+pchar.name+", and on your luck. If you find it, don't hesitate to hurry back to me.";
			link.l1 = "Definitely! See you soon...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Why should I hurry? The sword is with me.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "Oh, thank God, that I asked exactly you for help, "+pchar.name+". You're a miracle man, my friend! Show me it... Ohooo! It's, it's her. My darling! Precious! Gramercy, fine fellow, I take a bow to you! Here, here's your money. Four hundred doubloons. I won't be stingy.";
			link.l1 = "Thank you, Fadey. Pleasure to be able to help.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_SetStat(pchar, 65, 1); // ugeen 2016
			dialog.text = "My collection is back to me! No one will dare to steal it from me again, I will make sure of that! And I have a very special reward for you, good man: one merchant will bring me an excellent fencing armour from Europe in two weeks. An order of one nobleman, it is a quite unique piece of armour\nSo, if you want, you can buy it for only seven hundreds golden doubloons. I will tell the nobleman that they are still making it.";
			link.l1 = "What's so good about this armour?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "It's very comfortable and durable, yet it still can compete with iron cuirass. You should come back in a couple of weeks and have a look at it. But don't take longer than a month or I'll sell it to the original orderer.";
			link.l1 = "Deal. I'll drop by your house in two weeks.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Yes, It's been delivered already and it's waiting for you. Did you bring the money?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 700)
			{
				link.l1 = "Yes. Here's seven hundred doubloons.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "Damn it. I forgot the money on the ship. I'll bring it in a second!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveItems(pchar, "gold_dublon", 700);
			Log_Info("You've given 700 doubloons");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Yes, my good man! Here, take it. This wicker armour will serve well, I assure you. There's nothing else like it in all of the Caribbean.";
			link.l1 = "Yes, I can see that the armour is good. Thank you! Can't wait to try it on...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "Why do you need to wait? Go ahead. Let's see how it fits.";
			link.l1 = "Will do. See you later, monsieur Fadey!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			dialog.text = "Come in, my dear friend. The merchandise is ready for you to purchase. Five hundred doubloons for fifty pieces.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 500)
			{
				link.l1 = "Everything's as we've agreed on. Take the money.";
				link.l1.go = "ropes_1";
			}
			else
			{
				link.l1 = "Just let me bring the coins from my cabin.";
				link.l1.go = "exit";
			}
		break;
		
		case "ropes_1":
			RemoveItems(pchar, "gold_dublon", 500);
			Log_Info("You've given 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nice doing business with you, "+pchar.name+". I'll order my men to carry over the ropes onto your ship.";
			link.l1 = "Thank you!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "If you still need my product, come back in a month.";
			link.l1 = "Very well, Fadey. See you later!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "What can I do for you, my dear friend?";
				link.l1 = "You are an influential person, Fadey, as far as I know. A friend of the governor, and, as rumours say, you've got connections at the palace. Would you be able to petition the authorities in case I get in trouble with the law?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "How can I help you, my friend?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "I have a problem with the English authorities.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "I've run into trouble with the French authorities.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "I had a huge quarrel with the smugglers.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Sorry, I think I'll handle things myself.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "Oh-ho, good man, who told you that? Everybody lies. But since you are a Michel's brother and a good friend of mine, I can try to fix things for you. Though my connections have limits, I can petition for you only to English and French authorities. I don't do business with the Spanish and the Dutch\nI also warn you that my influence is not enough to redeem considerable faults. I can persuade them to reconsider their attitude towards you in case of slight misconducts or to ease a bit an anger\nAnd only one nation at once, France or England, I can't tear myself apart. Of course, coins also will be required in order to make bribes. Don't hesitate to address me if you find my terms acceptable.";
			link.l1 = "Thanks, Fadey. I'll keep that in mind.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Of course. I sure have heard of your adventures. I'll take care of your dilemma, it's rectifiable. Three hundred golden doubloons and we'll take you out of hot water.";
				if (GetCharacterItem(pchar, "gold_dublon") >= 300)
				{
					link.l1 = "Great! Here's the gold.";
					link.l1.go = "agree";
					iTotalTemp = 300;
				}
				link.l2 = "Then it's just the right time for me to go get the coins.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Of course. I've heard about your troubles. You've tarnished your reputation. However, it is rectifiable. Six hundred gold doubloons and we'll take you out of hot water.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 600)
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Then it's just the right time for me to go get the coins.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Yes, you're in quite a legitimate quandary. I can't completely sort out the situation, however I can soften the burden of your scornful sins. And later at any moment, we'll present a bribe again if you have money and a desire. Seven hundred gold doubloons and we'll smooth out your troubles.";
					if (GetCharacterItem(pchar, "gold_dublon") >= 700)
					{
						link.l1 = "Great! Here's the gold.";
						link.l1.go = "agree";
						iTotalTemp = 700;
					}
					link.l2 = "Then it's just the right time for me to go get the coins.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveItems(pchar, "gold_dublon", iTotalTemp);
			Log_Info("You've given "+iTotalTemp+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Okay, give me about ten-fifteen days. Meanwhile, I'll get an appointment and take care of this and that. It'll all be done in about two weeks. ";
			link.l1 = "Thank you, Fadey! I'll be waiting...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, 10+rand(5), false);
			pchar.GenQuest.FadeyNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			dialog.Text = "Why, my good man? The smugglers are not the worst folk in our world and they can make you a good profit. Fine, I will help you, I know how to grease some wheels... Prepare seven hundred doubloons, no bargaining.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 700)
			{
				Link.l1 = "Very well, Fadey, I agree. Take your gold.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "I don't have that much gold with me now. I will come back later!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Good, I will patch up a quarrel, don't you worry. They will do business with you again.";
			Link.l1 = "Thank you!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, 25);
			RemoveItems(pchar, "gold_dublon", 700);
			Log_Info("You've given 700 doubloons");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
