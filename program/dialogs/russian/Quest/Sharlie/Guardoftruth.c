// диалоги НПС по квесту 'В поисках Стража Истины'
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
			dialog.text = "How can I help you?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("VOICE\Russian\Ransack_1.wav");
			dialog.text = "What do you want? Another interrogation?";
			link.l1 = "Senor, what's your name?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "Oh, what the hell do you care who you're gonna hang or shoot to death? I was cautious enough to fall right into your claws, and...";
			link.l1 = "Senor, I repeat. State your name. I cannot talk to a person without knowing what his name is.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+". Are you happy with my answer? And who do I have the pleasure of speaking with?";
			link.l1 = "My name is "+GetFullName(pchar)+". Have you never heard of me before?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "No, god damn it! I'm not required to know the whole...";
			link.l1 = "Enough. Let's do this without insults and try to behave like civilized people. You're fate will depend on what you are able to inform me. If you tell me at least something interesting I'll petition for your release at my disposal and you'll be able to escape the gunfire and the noose waiting for you right now.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Well, I'm ready. What would you like to find out, sir?";
			link.l1 = "Who has organized such a large-scale attack on St.Pierre and why?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "The order was given from Ramon de Mendosa y Riba, the main commander of the Providence Island garrison. They've set a squadron on foot. The goal is seizing the material valuables of the French colony.";
			link.l1 = "What was your immediate task in assaulting the city? Personally yours?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "I am the commander of a striking force. Our task entailed taking control of the fort and providing a safe landing for the descent into the city. Also my squad took part in attacking the city itself.";
			link.l1 = "Were you informed of the valuables located in the city? Of the amount and quality contained?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "We didn't have any exact information, but Baron de Mendosa y Riba claims that there is silver stored in the underground of the fort and that the port arsenals have strategic raw materials: ironwood and ship silk.";
			link.l1 = "Did you find those valuables?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "No. We didn't find one or the other. The arsenals were filled with normal colonial merchandise and beneath the fort was gun powder, weaponry, and ammo. But we didn't have enough time to conduct a thorough search, for the French reinforcements came roaring in and we were compelled to engage in battle.";
			link.l1 = "Didn't you find it strange not to find valuables there?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "I did, but I don't usually discuss orders.";
			link.l1 = "Listen to what I'm about to tell you: Fort St.Pierre has never stored any silver and the arsenals have never stored ironwood and silk. A now think well, officer, before answering, if your answer does not please me, I'll turn around and walk away leaving you in your own fate... quite a sorrowful fate.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "I'm all ears.";
			link.l1 = "I don't believe that the only goal of the onslaught was simply robbery. St.Pierre is a far away and not-so-rich colony to send a squadron here lead by a battleship. Surely you or your commander or anyone else had additional orders or directions. Which exactly were they given? Think well before answering...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "You're gonna keep quiet? All right. Think for a second, I'll wait.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Senior, the rest of my fate is going to depend on my reply?";
			link.l1 = "Correct.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "I've got something... But you must swear to me that you'll take me out of here and later hold me for ransom to Spain.";
			link.l1 = "If you tell me something worthy of attention, I swear you'll be delivered on board of my vessel and you will escape execution.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "All right. Don Diego de Montoya has instructed assault companies that they must in a mandatory manner find and take captive a man by the name Miguel Dichoso, who is located somewhere in St.Pierre under protection of the authorities.";
			link.l1 = "Continue. Who is Diego de Montoya?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "The immediate chief of the expedition. He's been able to flee after arriving of your squadron...";
			link.l1 = "Who is he, this Don Diego?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "I only know that he's an authorized representative of Baron de Mendosa y Riba, his right hand, and critical tasks agent.";
			link.l1 = "Interesting... And who is this Miguel Dichoso, that apparently this whole uproar was organized for? Gotta be some big shot?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Do you remember your oath, senior?";
			link.l1 = "Yes. And I confirm that if you continue telling your story that you'll be delivered as an important witness to my vessel and later...well, I'll find a way to send you to a Spanish settlement. But not until you inform me of everything that I might be interested in.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Miguel Dichoso is a former brother-in-arms of the baron, however they say that he betrayed him. Senior de Mendosa y Riba wants him alive, so we were given an order to not kill Dichoso by no means.";
			link.l1 = "Is Dichoso Spanish?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Yes. Don Diego de Montoya has given an approximate description and required that everyone looking like Dichoso had to be delivered directly to him. But in the time that we've spent in the city, we haven't even had time to search for Miguel.";
			link.l1 = "Did you know Dichoso personally?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "No. There were people in my platoon that knew him by sight. All of them are dead.";
			link.l1 = "What type of betrayal did Dichoso commit toward your Don Mendosa that he decided to send a whole squadron after him. Are you informed of that?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "In a matter of speaking - yes. The baron has arrived to the Caribbean from Europe quite recently. His was supposed to secure the safety of Spanish ships with treasures aboard but instead he started to search for Indian gold. He decided that one ancient Maya city exists somewhere deep in Yucatan's jungles - Tayasal, the city filled with gold\nThe baron had sent several expeditions to find the city but all of those were vanquished utterly in the wild selva. No doubt, they were slaughtered by the martial Itza people who live there\nEventually his ongoing failures and the pointless death of soldiers caused inquisitor Vincento's discontent, he informed Madrid about the situation. They forbidden to search the mythic city. That's when Miguel Dichoso had shown up\nThey organized another expedition which surprisingly was a success, they had found ruins of the ancient Indian city and a pile of gold with jewellery. But they were attacked by the Mosquitoes on the way back\nAll except Miguel died, Indian weapons were covered by some local poison, even a small scratch leads to the certain death in a few days. Dichoso returned back to Providence with treasures\nWhat a fuss! The baron was unspeakably happy, he sent urgent letters to Madrid and to father Vincento to Santiago, no doubt that he wanted to piss holy father off. Then the military frigate was prepared to deliver treasures to the Old World. Dichoso volunteered to escort it.";
			link.l1 = "And, of course, he didn't deliver the gold?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Right! The frigate disappeared without a trace along with the entire cargo and the crew, including Dichoso, not making it back to Spain. The baron was simply infuriated because he once again embarrassed himself in front of the Escorial to the joy of Father Vincento. It's like he...basically... Well, Miguel Dichoso became the bee in his bonnet...";
			link.l1 = "Isn't it possible that the frigate could've just got caught in crossfire and drowned? Or that it was captured by pirates?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "The baron did claim in the heat of the moment that he waa sure Dichoso betrayed him. I don't know the details. Then Don Diego de Montoya came around, who as I understand informed the baron that Miguel Dichoso may be in St.Pierre.";
			link.l1 = "Hm. Interesting. Those Indian treasures again. It all looks kind of suspiciously tied to them... So, they didn't find Dichoso?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "No. And I won't be surprised if he wasn't even here. The baron is just obsessed with the thought of capturing Dichoso that he believes in even the most farfetched fantasies.";
			link.l1 = "Tell me, "+npchar.name+", how did Don Mendosa find out about this... uh... Tayasal? He didn't dream it, right? Were there some facts or anything else?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "Father Vincento was the one that told of the alleged existence of Tayasal and the Indian treasures. Where he found out about that I have no idea. It was right after his dispatch that Don Ramon Mendosa arrived here, to our allotment...";
			link.l1 = "That's interesting. Father Vincento came up with the theory of Tayasal's existence by himself, informed Spain by himself, and of course began throwing monkey wrenches into the barons plans, informing him of his failures...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "Well you should know these reverend fathers... He didn't inform Madrid of this for no reason. He was pursuing some kind of benefit, but the baron's arrival apparently wasn't part of his plans. Anyway, I don't know anything about it. I've never had the desire to deal with the Inquisition.";
			link.l1 = "All right. You've given me a lot of interesting information, "+npchar.name+", and I'm taking you out of here. You will come to use for me later. But for now... let me think for a little bit and analyse what you've told me...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("VOICE\Russian\Ransack_2.wav");
			dialog.text = "So what do you say? Will you follow through with your promise?";
			link.l1 = "I always keep my promises. Today's your lucky day, "+npchar.name+". You're going with me to Cuba, to Santiago. I'll tell you more in depth about it when we arrive. But for now welcome on board. You'll be accompanied into the port and delivered to my ship.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "My gratitude, captain. I'm glad you're a man of your word.";
			link.l1 = "You can express your gratitude later. Right now you're departing as a passenger, but on hold: don't take it amiss, but I still need you.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "Don't take any trouble, captain. I give you my word that I won't make any attempts to escape.";
			link.l1 = "God spares the cautious. See you on the boat.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("VOICE\Russian\Serve_senior.wav");
			dialog.text = "Captain, what  the goal of your arrival at the Spanish island? Only to leave me here? I don't dare even hope for that...";
			link.l1 = "That's exactly right. To leave you here. Although the reason for my arrival here is somewhat more profound than it seems. But that no longer concerns you. I'll let you go right now without any ransom, but only in the condition that you will swear two things to me.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "What exactly?";
			link.l1 = "The first is I'll give you a typed letter and you have to deliver it to the Inquisitor of Santiago, Father Vincento, personally. If he asks who it's from and how you got it, tell him the truth...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "The second is that you will not undertake actions of trying to find me and attack my ship at least for a week. Agreed?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "Is that all?";
			link.l1 = "Yes, that's all. Fulfil my conditions and you're free to go.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "I swear to you, senior, that I'll deliver the letter to Father Vincento personally and also that I will not undertake actions of any kind that may provoke aggression of Santiago's garrison against you. Rest assured, I will keep my word. I am Spanish and I respect strong and noble adversaries.";
			link.l1 = "All right, Don "+GetFullName(npchar)+", I accept your oath and I am letting you go right now. Here, take this letter for the Inquisitor. You are now free.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Farewell, senior. I hope we will never meet again on the battlefield. I swear I would be extremely displeased.";
			link.l1 = "Farewell...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "Oh, what a lucky meeting! Hello, monsieur "+GetFullName(pchar)+"! I see you've become a welcome guest in Santiago. Are you working for the Holy Inquisition?";
			link.l1 = "Greetings, senior "+npchar.name+". I thought we'd never see each other again. Of all things! No, I've just stopped by to visit Father Vincento. And what about you? Serving in Santiago now?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "After you freed me from arrest, I was definitely compelled to stay in Santiago... but as you can see, I've kept my word: no pursuits aimed at you...";
			link.l1 = "That's commendable that you ended up to be a man of your word.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Listen, captain, don't you mind to have a glass of rum, to our meeting, so to speak? I never thought that I would ever offer that to a Frenchman, but you are an exception.";
			link.l1 = "Of course! I don't mind rinsing my mouth with some rum. Let's go to the tavern.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Eh, well, bottoms up!";
			link.l1 = "What are we drinking to, senior officer?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Let's drink to something neutral, but that concerns us both. For example, to gallant and successful service to one's nation! We've all got our own!";
			link.l1 = "And let's drink also to our authorities coming to an agreement someday with each other and that the French and the Spanish cease the feud on the archipelago.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Well said, captain! Let's drink!";
			link.l1 = "Hum... (drinking)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Aha! Not too bad booze in this local tavern...";
			link.l1 = "I agree. Tell me, did you take it on the chin on service for your captivity in St.Pierre?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "No. The disarray is all put behind me. It is a soldier's service after all.";
			link.l1 = "And where's your commander... what his name... Diego, right? How did the fruitless expedition look on him? Did he get demoted?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "Oh, no! Our dear Diego de Montoya is unsubmergible while he's got Don Ramon de Mendosa y Riba behind him. By the way, Don Diego was in San Diego just yesterday. He arrived from San Jose.";
			link.l1 = "You don't say? Intriguing! Good thing we didn't meet. I'm afraid that affair might have finished in calling a duel, ha ha!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Don Diego has no time for you now, captain. He's got bigger fish to fry that risking his life on a duel. He's come up with some scheme along with the baron in West Main. He put together a squadron in Havana and is looking to sail back to the motherland any day now.";
			link.l1 = "Are you on his crew too?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "No. Tomorrow I'm departing to the San Juan garrison, which is in Puerto Rico. I'm no longer in good mark on Providence with Don Mendosa.";
			link.l1 = "Well, then let's drink to your new area of service and may there be nothing but happy times awaiting you there.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Thank you, monsieur. All kinds of good wishes to you to as well. Oh and, I think it's time for me to go. I'll finish this drink and then take off.";
			link.l1 = "Happy trails, senior "+npchar.name+". Maybe we'll meet each other again some day during more peaceful time.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("VOICE\Russian\other\OZGi-01.wav");
			dialog.text = "Just as I told you, Don Diego: the fish swallowed the entire bait... Oh, looks like we meet again, monsieur. Unfortunately, not in a peaceful setting as you wished.";
			link.l1 = ""+npchar.name+"? Well! I didn't expect this. For some reason, I thought you were an honest, noble soldier. It turns out I was wrong.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "What makes you wrong? I kept my word, but I didn't swear to eternal friendship with you. Nothing's changed, monsieur. You are still an enemy to Spain and my personal enemy. This isn't Santiago, there's no Father Vincento here, and his paper isn't going to help you...";
			link.l1 = "Oh, it's like that? I happen to think that sipping rum together and having a friendly conversation, meanwhile pursuing a goal of luring me into a trap is pretty underhanded, don't you think, senior "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "You dare call me underhanded, you frog eater?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("VOICE\Russian\other\OZGi-02.wav");
			dialog.text = "Hey, you! Yeah, yeah. You! "+GetFullName(pchar)+"?";
			link.l1 = "Right on, pal. It's me.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "I've got a letter from an important person. You already know who it is.";
			link.l1 = "I know, I know. Give it here.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "There you go. How about a few coins for my trouble?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Take a little silver. You've earned it honestly.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "You trying to put one over on me, pal? You were already paid for the delivery.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Thanks, buddy. Nice dealing with a generous person.";
			link.l1 = "All right, get lost, and don't rattle your tongue about went down here.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "The Havana wolf is your pal...";
			link.l1 = "Huh? You still here...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "Welcome on board of the 'Admirable', captain "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"! Surprising. Do you know me?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Who in the French colonies hasn't heard about the captain named "+GetFullName(pchar)+", the one that knocked the pants of that Spanish squadron led by that battleship attacking St. Pierre and killed the whole enemy descent! You're pretty much a national hero!";
			link.l1 = "Oh, come on. 'A hero'... I'm just a soldier that was fulfilling his duties to France.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Could a lot of soldiers do what you did, huh, captain?.. Eh, I would like to treat you to some rum in the tavern, but alas: the captain has forbidden giving so much as a drop of rum to the sailors and I don't want to be the bad example...";
			link.l1 = "Hm... So you're not a captain?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "Do I look like a captain? Hoho! No, I'm just boatswain Serge Degas. Our captain, Gaius Marchais, spends all day in the tavern, meanwhile we've been lying out waiting for some 'merchants' caravan. Cap owes an allowance to the sailors, and to us to, and the whole team is completely out of it... ";
			link.l1 = "What's wrong? The Spanish vanilla caravan not showing up to get it's feathers picked?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "No way! Our captain made an end of piracy after he had captured this galleon. You see, he heard that a trade caravan sailing to Europe will make a stop at Guadeloupe soon and they will be buying vanilla. So he filled our holds with vanilla to the top in Bridgetown! Thought that he would be able to sell it three hundred pesos for a crate, yeah, fat chance!\nThere is no caravan exists of course and selling vanilla here would be a waste. So here we are, waiting for the 'merchants', I am sure they will show up here one day three years later... Captain sits in the tavern whole day, bothering everyone and returns to the ship only to have a nap. Now he is ready to sell for two hundred pesos only to break even\nAll money was invested in the cargo. One day the crew is going to tie him and sell vanilla for cheap just to cover the debts... I swear I can see it coming.";
			link.l1 = "Aye... and what's eating your captain?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Well, if a job is worth doing, it's worth doing well. He's a terrible merchant. It would've been a different matter if he shipped freights as well, but he wanted to feel himself like a merchant stapler. May an anchor fills his ass...";
			link.l1 = "I understood you, Serge. Don't worry, someday your... caravan will show up.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Oh, I don't believe in miracles, captain. Maybe we'll meet again someday and sip some rum... Eh, hot coppers!";
			link.l1 = "Good luck, pal...";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Eh, captain, I sure would like a sip of rum!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("VOICE\Russian\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Ho! Don't you happen to be from the merchant ship? No? Oh, my apologies. Of course, not... My mistake.", "I'm not in the mood, monsieur, so find yourself somebody else to talk to.", "Ah, you again? For crying out loud?!", "Ahem...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Don't worry about it, buddy. It happens.", "Have some rum, captain. It should make easier your troubles a bit...", "Don't be nervous, buddy. It's bad for your health.", "All right, all right. I'm leaving.", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("VOICE\Russian\citizen\convict-03.wav");
			dialog.text = "A argh... Mm... What the hell, what is this?..";
			link.l1 = "Quiet, buddy... Don't make noise...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("VOICE\Russian\citizen\convict-02.wav");
			dialog.text = "Huh? What? Fuck!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("VOICE\Russian\EvilPirates07.wav");
			dialog.text = "Aaah! Who are you? What do you want from me?";
			link.l1 = "If you shout, I'm gonna calm you down with a knuckle duster, savvy? Where's that ornament you grabbed with you when you boarded this ship?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "What ornament? I don't know what you're talking about! This is my ship!";
			link.l1 = "Your ship? Until not that long ago she was called 'Santa Margarita' and sailed under a Spanish flag... I'm asking you, where are those ornaments? The gold ostensory, the cross with lazurite, and the gold censer? What did you do with them? You didn't sell them, did you?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "I don't believe my ears... you're Spanish? Oh, no... you're not Spanish! It's even worse! You've sold out to those vile Castilians! For what are they buying Frenchmen's souls at these days? I won't tell you anything. You won't get your hands on those spiritual gems!";
			link.l1 = "Won't you tell me? Ah, to hell with you. This isn't the best place for interrogation... We're gonna put a gag in your mouth to keep you from squealing and then we're going into my cock boat... you'll talk anyway buddy. Oh, you'll talk!";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "You Spanish accomplice! You better...";
			link.l1 = "Silence, old dog... Yes. Follow right behind me on your own feet or I'll knock you cold and drag you across the deck by your feet.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "How can I help you, sir?";
			link.l1 = "How are things, captain? What brings you to Basse-Terre? As I understand, you're a Spaniard albeit under the Dutch flag?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "What's the problem, sir? Yes, I'm Spanish. That's easy to guess by the name and type of my ship, but I am here on a legal basis. I have a license from the Dutch West India Company, so...";
			link.l1 = "Don't get into a fuss, senior! That's actually really good that you're Spanish... Tell me, are you here for import or export?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "I have brought merchandise from Havana and sold it at a local store. Now, I am awaiting profitable freight to avoid going home with an empty boat.";
			link.l1 = "Good damn it! Senor, I've got a business proposition for you. You could earn decent money if you help me. Shall we discuss it? What's your name by the way?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Carlos. Captain Carlos Guevara. What's your offer?";
			link.l1 = "I need to purchase a batch of vanilla and send it to Cuba, to a man named "+pchar.questTemp.Guardoftruth.LMname+", this is the watchman of the Santiago lighthouse. However, I've got serious problems doing that. First of all, no store has the amount of vanilla that I need...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "Second of all, I must immediately depart to St. Christopher and I don't know how long I'll have to be there. I'm losing money, understand? God damn shame!";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "I understand. That happens, senor. You can't make all the money of the world. So what do you want from me?";
			link.l1 = "Look over there. See that galleon? She's got cargo loads of vanilla that I need dearly. The trouble is the captain of the galleon has drum it up in his stupid head that a caravan will arrive here soon that is going to buy his cargo at a profitable price, at almost three hundred pesos...";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Yes, a lot of naive people walking around these days...";
			link.l1 = "Naive is bad enough. But they're flat out stupid! I offered buying his vanilla at two hundred ten pesos and he won't even fetch two hundred in a store. And can you believe it: he told me to step off! He said we'd only sell it at two hundred fifty!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Ha ha ha! People are stupid as can be...";
			link.l1 = "Yes! That's basically what I told him. Of course he got mad... but I really needed that vanilla! Senior, I'm not a merchant, but you as I see, are a real pet master. And you have a capacious carack...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Talk this damned fool into selling you the cargo. He's definitely not going to sell it to me. I'm willing to pay two hundred ten pesos per box. If you knock the price down, leave the difference to yourself. And for that I'll freight your boat to Santiago";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "How much are you willing to pay for the freight?";
			link.l1 = "How much do you want?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "Santiago is pretty far away...thirty thousand pesos.";
			link.l1 = "What.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "All right, it's on my way anyway...Twenty five thousand and not a peso less.";
			link.l1 = "I agree. The captain of the galleon's named Gaius Marchais. He spends all day in the saloon. I hope, you manage to convince him.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "I've had business with weirder people before... I'll tell him all the details about who's making the rumours about the caravans and why, who were supposedly going to buy the merchandise at sky-high prices.";
			link.l1 = "So, we've got a deal?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "We've got a deal if you have the money to pay for the merchandise and the freight.  Do you have it with you? Show the money to me.";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Here you go. Have a look. This should be enough. No hocus pocus.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "It's on my ship. I'll go get it!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Have you brought the money?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Here you are. Take a look. This should be enough. No hocus pocus.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "I'm bringing it right now!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Wonderful. I love doing business with sensible partners. Come back "+sTemp+" by ten in the morning and I think by that moment your client will 'come to fruition'.";
				link.l1 = "Great! See you later!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Wonderful. I love doing business with sensible partners. I'm off to the shore. Come back in three hours. I think by that moment your client will 'come to fruition'.";
				link.l1 = "Great! See you later!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Senor, I remember well. Don't worry, we'll make your deal with that tough cookie.";
			link.l1 = "Okay...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "All is settled just like you wanted, senor. The poor man was extremely happy that I considered buying his vanilla. He even had his hands shaking while I was counting out an advance. We will load the cargo tomorrow at Capster Beach in the midday in order to avoid any unwanted attention from harbour official\nI will sail immediately to Santiago as soon as I have the cargo on board. I will help your partner with unloading. Anything to tell him?";
			link.l1 = "Yes. Here's a letter. You say the deal will be at Capster Beach tomorrow at noon? All right. I won't be far off just in case at the headland, inaccessible to the island...";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You've handed off the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "You can trust me, senor. I'm an honest man. Besides, I have no desire to quarrel with you. But if you'd like to watch, it would be easier on me.";
			link.l1 = "Wonderful. I'm glad. Then I'll watch over the deal tomorrow and as soon as you take off, I'll go about my business.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Captain, I assure you: I won't let you down and I'll fulfil the conditions of our contract in full.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("Hiic! C-capt-tain, f-finally has g-given us our allowances! Yahoo!","And I j-just s-started... Hic!","Face against the table... body under the fence... yo-ho! And a bottle of rum!");
			link.l1 = LinkRandPhrase("Yup... Aha.","Gotcha... Time to wrap things up with the rum, don't you think?","It's tough...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("VOICE\Russian\EvilPirates01.wav");
			dialog.text = "Stop! What are you doing? Alarm! Enemy on dock!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Haw haw! You've come for Rollie the Cap's treasure too? We've been looking and looking and looking and we just couldn't find it. I wish at least one of these imbeciles would guess to swim behind the waterfall onto the ledge!";
			link.l1 = "You're one of Colonel Fox's men, aren't you?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "Suppose I have ties to the sea foxes. You don't need to know more, there's no point. You don't need any kind of knowledge right now. You've found my treasure, which we now owe you a huge thanks for...";
			link.l1 = "Oh, you're not a sea fox, more like a sea dog... or jackal. What suits you better?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "Oh, look. We've got a wise guy on our hands!";
			link.l1 = "Shall we check the sharpness of these cavalry swords, jackal?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", senor. How can I help you?";
			link.l1 = "Hello. Are you Donna Belinda de Ribero?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Yes, I am. With whom do I have the honour to speak?";
			link.l1 = "Captain "+GetFullName(pchar)+", madam. But, don't be put off but my nationality - at the moment I'm fulfilling an assignment from the Right Reverend, Inquisitor of Santiago, Father Vincento.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "How interesting! I've heard that the Society of Jesus is encompassed by the broadest variety of people, of all classes and nationalities, yet still till this day I hadn't ever come across one up so close before. What can I do for you, senor?";
			link.l1 = "You possess an object that the Right Reverend is very interested in, a golden ostensory, an ecclesiastic calix that you've acquired recently in a usurer's shop in Willemstad.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "You're well-informed, senor. Anyway, knowing who you are, this shouldn't surprise me. Yes, I acquired this valuable ostensory, it certainly shouldn't lat in a merchant's shop among of stolen things which were got at the cost of people's tears and grief.";
			link.l1 = "Do you have the calix, madam?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Yes. I wanted to bring it as a gift to our church, but so much as come upon me here... I couldn't... oh, I'm sorry...";
			link.l1 = "Am I seeing tears, madam? Have my words brought sorrow to you? Please, forgive me.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Oh, please, senor... Let's return to our conversation. As I understand, Father Vincento needs this ostensory? You would like me to give it to you?";
			link.l1 = "This precious calix was intended for the Santiago perish, but it was captured by a pirate and sold to a usurer with several other churchware objects. My task is to return that which was stolen back to where it belongs. Of course, I will fully compensate your expenses.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Oh, don't... Do you really think this money means that much to me? I bought it to give it to the Holy Church and I wouldn't hesitate to hand this calix over to its representative, not to mention a member of the Society of Jesus serving Father Vincento. But... maybe, you won't leave me in my troubles?";
			link.l1 = "You are a noble woman, madam. What troubles bother you? How may I help you?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "You want to help me? Oh, senor...I wouldn't dare to ask a Jesuit brother himself for help...";
			link.l1 = "Tell me. What's the matter?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Can you promise me, as a representative of the Holy Church that no one will ever find out what I'm asking you for?";
			link.l1 = "I give you my word, senora.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Fine. I trust you. My very close friend Esteban Sosa has got in trouble, he was captured by bandits and they demand a ransom of one hundred thousand pesos. I don't possess that much money and only managed to collect a half of the sum. I can't ask for anyone's help in such matter\nBesides I worry for my... friend and fear the worst, they may have him killed as soon as they get the money to make sure that he won't tell a commandant about them. Perhaps you, a brave captain and a brother of Jesus Order could persuade the bandits to accept the sum I have and make sure he stays alive...";
			link.l1 = "When and where will the exchange take place?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "Their ringleader nicknamed Bartie the Knacker said he'd be waiting for Esteban's ransom every night from eleven p.m. to midnight at the cave entrance in the jungle...";
			link.l1 = "Those are unusual conditions...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "Apparently they understand that I can't put the whole sum together quickly, so they've stated the issue that way... but I can't find such money, I'll never be able to!";
			link.l1 = "Don't cry, madam. I'll try to help you. A brother of the Society of Jesus would never leave a righteous woman in peril.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "I wouldn't dare depend on that...But, captain, Bartie the Knacker also said that if the envoy doesn't come alone or if I go to a commandant, he'll immediately kill the hostage...";
			link.l1 = "I'll keep that in mind.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Here, take this. It's fifty thousand. Talk those scums into taking at least this. Tell them I don't have a single peso more! Bring Esteban back! And I'll gladly give you the ostensory for Father Vincento.";
			link.l1 = "I'll do everything I can, madam. Let's hope for the best.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "May God help you in it, courageous captain!";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "Do you have any news, captain?";
			link.l1 = "Not yet. Just wait, senora. I won't let you down.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "Do you have any news, captain?";
			link.l1 = "Yes, seniora. And I'm afraid, you won't be happy.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Tell me, don't keep me waiting! Did you meet with the bandits?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Here, take your fifty thousand back. I didn't need them. Here, take this ring also. It's familiar to you, I believe?";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Here, take this ring. It's familiar to you, I believe?";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "It... yes, it's familiar. What's with Esteban?";
			link.l1 = "I met with the scumbags in the cave. Bartie the Knacker and Esteban Sosa are the exact same person. He staged the kidnapping to get some money out of you. He told me about your... connection. He also said that he would not like to see you anymore. That's how this abomination started. I took a ring of his as a proof.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "This... yes, yes I know it. What's with Esteban?";
			link.l1 = "I met with the scumbags in the cave, where they attacked me, tied me up, and took your money. Bartie the Knacker and Esteban Sosa are the exact same person. He staged the kidnapping to get some money out of you. He told me about your... connection. Esteban let me go and gave me this ring as proof. He said that he would not like to see or know you anymore.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a good lesson, but I didn't kill him out of respect to you.";
			dialog.text = "God almighty! I don't believe my ears! Why does all this happen to me, why?! What did I do for him to....";
			link.l1 = "Senora, I'm begging you, don't kill yourself over this. This scum isn't worth a single tear of yours. "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift for your courage.";
			dialog.text = "Oh... I'll try to calm down. Senor, I must thank you for your help. Here, take your ostensory. "+sTemp+" May God save you.";
			link.l1 = "Thank you, senora. Don't worry: no one will find out about what happened in the cave. The brothers of the Society of Jesus always keep their word. Now please, it is time for me to go.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("VOICE\Russian\other\OZGi-04.wav");
			dialog.text = "Stop right there, buddy!";
			link.l1 = "I'm standing right here.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "Did you bring the money?";
			link.l1 = "Silly question. Why else do you think I would've come here?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "What are you a smart alec, baffle brains? Off you go into the cave, Bartie's been waiting for you.";
			link.l1 = "You served on guard before? You've got that kind of attitude... Anyway, I'm on my way.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("VOICE\Russian\other\OZGi-03.wav");
			dialog.text = "I had to wait for you a long time... Do you have the money with you?";
			link.l1 = "Is that you, Bartie the Knacker? You don't look like an obscene bandit to me...";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Why do you care how I look like? Do you have the goddamn money?";
			link.l1 = "Where's the hostage?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "You'll get your hostage. Come on, give me the coins. Don't make me mad.";
			link.l1 = "Bartie, do I look like an idiot? Until I see Esteban Sosa alive and kicking, you're not gonna see a peso. Where is he?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "Oh, you're diggin your heels in, eh? All right, we're gonna teach you a good lesson... Guys, let's tear this shit eater a new whole!";
			link.l1 = "Bastard!..";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("VOICE\Russian\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "All right, here, enough dancing for you? Where's Esteban Sosa? Come on, tell me or I'll be submerging your head under water until you open up!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "No... Don't hurt me. I am Esteban Sosa.";
			link.l1 = "What?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Yeah, yeah. I'm no Bartie the Knacker. I'm just...";
			link.l1 = "You are a waste of life! So, you decided to just suck a hundred thousand out of Belinda by 'kidnapping' yourself?";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "You understand me, man to man. Belinda...She's really got me browned off with her love. Even her husband has started getting suspicious about it...";
			link.l1 = "Well, how about that! So you're lovers?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Not anymore. I just ran away from her.";
			link.l1 = "And you decided to take some coins for the road, eh? Understood. Well, what should I do with you now? Drown you in this marsh just as you tried to kill me?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "I didn't want any blood, I swear!";
			link.l1 = "Is that why you sicked your cutthroats on me?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "We were just going to shake your pockets, that's it!";
			link.l1 = "By shooting me? Buddy, I should string you up on the butt of my ship's sail yard while I'm at it. But out of respect to the good woman that had the misfortune of getting involved with you, I will not do that. I'll take you to her and let her decide what to do with you...";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "No, anything but that! I'm not going to Cumana!";
			link.l1 = "You'd rather stay in this cave forever?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Spare me, senor! Let me go and I'll just sail away from here and never come back to Cumana again! I'm not going to wait for Belinda's husband to gank me in a duel or send an assassin for me...";
			link.l1 = "Fine. For the sake of Senora Belinda, I'm not going to bring you to her. But don't think for a second that this is all gonna get kept secret. She'll find out the pathetic piece of shit she got tied up with in this life. What kinds of things do you have that she'd be able to recognize?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Here. This turquoise ring here. She gave it to me herself.";
			link.l1 = "Splendid. Give it here and get out of my sight!";
			link.l1.go = "barty_15";
		break;
		
		case "barty_15":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "You've got what we need, buddy...";
			link.l1 = "Hm. Really.... And what would that be?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "I don't even know myself, pal. I've just been ordered to take your stuff, absolutely everything you have on you. Are you gonna give it away by yourself or you're gonna kick and scream?";
			link.l1 = "Amusing. Looks like you've got no idea who you're dealing with. I eat sleazeballs like you for breakfast by the tens.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "You're a joker boy, aren't you frog eater? Well then, let's find out what colour your blood is!";
			link.l1 = "The same colour as yours, idiot... Did you visit a school?";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Haw haw, buddy, all right... Turn out your pockets on the double! If you're a goody two-shoes, you'll stay in one piece. Well?";
			link.l1 = "Again! You even came all the way over here... Who hired you, god damn it?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "None of your business. Thrash about and we're gonna swipe stuff from your dead body. How does that prospect sound?";
			link.l1 = "How's the prospect of you being the dead body?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "Awaiting orders, captain!";
			link.l1 = "Move through the jungle toward San Antonio cape. Take the trail left and keep going straight. Keep your heads down and get ready for an ambush on the shore. Be ready. I'll be going there by sea. How long will it to take you to relocate?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "We'll be there in six hours, captain!";
			link.l1 = "Good. Move!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наемник Патерсона
		case "housemercen":
			dialog.text = "Tenacious bastard! He's still alive... We should've put some more gun powder in. All right, I'll finish you, son of a bitch...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
