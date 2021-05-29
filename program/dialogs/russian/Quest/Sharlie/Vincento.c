// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "Pax vobiscum! So, at last I see in my abode the French captain, a brave soldier and, I hope, a loyal and trustful servant of the Holy Roman Catholic Church. Come in, my son, take a sit.";
				link.l1 = "Greetings, Your Eminence. My path to here was long and difficult. Per astera at astra...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "So, my son. I can see in your eyes that you have news for me. Tell me. You have my full attention.";
				link.l1 = "I've found your old assistant, Your Grace...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "Have you brought me some news from San Jose, my son?";
				link.l1 = "Yes, Your Grace. I have dug up something concerning the fate of Miguel Dichoso's frigate. As soon as the ship approached an open ocean, she was immediately captured by storm and taken back to the Caribbean sea...";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "God bless your deeds, my son... What can I do for you?";
				link.l1 = TimeGreeting()+", Your Grace. Do you have any news pertaining to our affair?"
				link.l1.go = "guardoftruth_17";
				break;
			}
			dialog.text = "Is there something you wanted, my son?";
			link.l1 = "No, nothing, father.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "A path of virtue is always difficult and thorny, my son. But the aim that is achieved fully rewards a righteous man for his works...";
			link.l1 = "I agree, reverend father. I have fully completed your errand: you already have the privateer, who stole the precious item from you, now I return to the parish of Santiago everything that was stolen: the ostensory, the cross, and the censer. Here, take them.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "I truly thank you for your faithful service to the church and your successful aid to the perish of Santiago, my son. Your works mustn't be left unrewarded. The parishioners have collected an offering for a benign, courageous warrior and I gladly give it to you. Here you are.";
			link.l1 = "Thank you, your reverence... What a surprise.";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("You've received a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Faithful service to the church is always encouraged on my part, "+pchar.name+". I hope that I've received a dedicated warrior on your side for the good and the protection of faith in Christ, for there is a serious threat looming above us...";
			link.l1 = "What are you speaking of, holy father?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "My son, maybe it will be you who stands out in the struggle against evil for many signs have indicated that.";
			link.l1 = "What signs?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Many, my son... And one of them is your desire to help in searching for the gold of the Indian pagans of Tayasal, for that which is conserved in those treasure chests is exactly what represents danger to the whole Christian world.";
			link.l1 = "Would you be able to enlighten me a little on this gold, reverend father? The history of it's disappearance I've already heard about, but the details... and what kind of a threat do you speak of?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "Listen to me, my son, yet know that everything you are about to hear is only for your ears. Long before Miguel Dichoso took pagan treasures out the ancient Indian city, I had a captive Indian of Itza people interrogated according to my mission in the Caribbean. The Itza people are offsprings of Maya\nHe was the source we had learnt from about Tayasal and about the terrible blow evil powers were going to be delivered to the Christian world. Consequences would be horrible. I have done everything I could to stop the catastrophe, I informed Escorial and Vatican\nThey had listened and sent here don Ramon de Mendoza y Riba, who has established his base at Providence and started to search Tayasal. Though this cabaliero had different motivations rather than preventing the catastrophe\nThat is why God turned aside from him, all his actions were futile and lead only to pointless deaths of Spanish soldiers. I wrote to Escorial asking to discharge de Mendoza due to his incompetence and it was satisfied, but...";
			link.l1 = "Miguel Dichoso has come.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Oh, Mother of God! Kukulcan again... ";
			else sTemp = "Hm... ";
			dialog.text = "Exactly, my son. With help of this venturer, a former mercenary, that Tayasal was found along with the treasures of the ancient Maya. However, the baron's joy was brief - the treasures disappeared along with Dichoso. It's likely that along with all the gold ingots and ornaments, Miguel took with him an ancient source of evil in our world, an artifact of an esteemed ancient Maya pagan deity called the Kukulcan mask...";
			link.l1 = sTemp+"But what evil do you speak of, Your Grace? How do you know about it?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "It's an evil bearing death to all Christians of the Caribbean, the New World, and possibly the Old World as well. The end may be quite sudden and no one will even realize what happened. And there are signs of this ending everywhere already!";
			link.l1 = "What signs? I don't understand...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "My son, are you really that blind that you don't even notice them? They've come about a quarter century ago already...";
			link.l1 = "I would like to meekly mention, Your Grace, that the course of my life is enumerated at exactly this length of time, so my ignorance is fully justified... ";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "I understand, "+pchar.name+". Didn't you notice strange things happening across the archipelago as soon as you had arrived here from Europe? Don't you find it strange that witchcraft, black magic and other rituals have much bigger strength here than in the other parts of the world? Pagan amulets, enchanted by Indian shamans possess a real power any man can experience\nChristian alchemists have mastered art of crafting enchanted items, they don't realize that they are serving the darkness by doing so. Don't you feel this unnatural, godless existence of something... obscure?";
			link.l1 = "You're right, father. I was surprised by that at first, but now I suppose I've just got used to it... It's the New World!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "But it wasn't always like that. The darkness I am speaking of came here about twenty five years ago and with every day it gains more and more power. That means only one thing: it has already come, it is among us, and it is at work...";
			link.l1 = "Who are you talking about? Who is this mysterious 'it'?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "The sworn enemy of all Christians  Basically a demon desiring the destruction of all the principles of the Christian world.";
			link.l1 = "Are you speaking of the Antichrist?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "Maybe. But it doesn't matter what name the beast bears. The important is what it is going to do. I am here to stop it. But we've got a bit carried away. You, as a man of action, would probably prefer to get to the knitty gritty and skip the extensive discourse?";
			link.l1 = "I've found out a lot of new and important things from you, Your Grace. I'm ready to listen on.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "You're courteous and well brought up, my son. That's a good thing. Now back to reason you conferred with me for. Our collective goal is to find the treasures of Tayasal taken by Dichoso, for it is among them - we will likely be able to find a weapon which will allow us to resist in the battle against evil.";
			link.l1 = "But can it be that Dichoso has already left the Archipelago and is sitting right now in the Old World with all the gold?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "No. I have a proof that these treasures are still here in the Caribbean. You don't need to know about it yet, you should just trust me. Besides, I think that Dichoso was lying to the baron\nHis story about ruined Tayasal doesn't match the results of interrogation of the Indian. I have also found out the fact that Dichoso was the only survivor a very suspicious.";
			link.l1 = "I take it that Don Mendosa believes that as well, since he organized the attack on Saint-Pierre trying to find Dichoso?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "The baron's actions should not concern you, my son. He is motivated by the greed of gold and personal gain and that serves as a terrible companion when things come down to a battle with evil and saving the world...";
			link.l1 = "Do you have any leads on where we should search for the treasure and Dichoso himself?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "I think about it every minute, my son, but I don't have anything specific to tell you. But there is a man, who will help us, a man of science from Genoa, I brought him here with me. He witnessed an interrogation of the Indian Itza and, most likely, things he had heard shocked him\nThe evil captured him. The Lord had granted him a talent of physician, but he used it in the dark way of black magic. He had talked to the captive Indian several times without my permission and then disappeared. We must save this lost soul...";
			link.l1 = "Am I supposed to find this man?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Yes, my son. It is the first step to finding the treasure and the weapon against evil. He can inform us of a lot.";
			link.l1 = "Who is this man?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "His name is Gino Gvineili. A young man aged thirty. A talented physician and an alchemist. As I said, he studies a black magic and the magic in general. According to my most actual information, he is hiding somewhere in English colonies\nUse this knowledge, my son, and find alchemist and physician Gino. If you managed to find a sea bandit who had stolen church utensils, then you will also manage to find my runaway secretary and bring him here. Do it, my son! I bless you.";
			link.l1 = "I see, Your Grace. I won't waste another minute. See you later!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "I had almost betrayed myself by a shout of surprise. Father Vincento ordered me to find and bring him a physician and an alchemist Gino Gvineili. The Gino who occupies a room at the second floor of my house in St.John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "I must find some Gino Gvineili, who hides somewhere in English colonies. He is a physician and an alchemist. Where a man like him can hide?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "I didn't doubt that I would hear you say exactly that, "+pchar.name+". Now my confidence is further strengthened that you have been sent to me by the agency of Providence itself. Where is that wretched, wanton son?";
			link.l1 = "I'm afraid you're not going to like what you're about to hear, but I don't have a choice. Your assistant is dead.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "God save his soul and forgive him for his heavy sins... How did it happen, my son?";
			link.l1 = "I've found Gino on Antigua. He was hiding out there in one of the old buildings that was constructed under the laboratory. He didn't submit to my persuasion to depart on his own good will. After hearing your name and having seen that I was prepare to use force, he took some vial of transparent liquid out of the folds of his long garment and depleted it in an instant...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "And then something horrible happened: he turned red, then he turned dark blue, he fell on the floor, started jerking around in a spasm and in one minute let his spirit free, and the strong smell of almonds filled the room.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gino... Poor slave of God... He even spent the last minute of his life in sin the committed suicide. I will pray for his soul...";
			link.l1 = "After your assistant stopped shaking around, I searched his habitation and found this folio there. Could it possibly be of interest to you or maybe help us in our searches? There are some futuristic notes of some kind here...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("You've given the almanac");
			PlaySound("interface\important_item.wav");
			dialog.text = "This an almanac of poor Gino. He had been writing there notes about all of his explorations. Give it to me, my son, I will study what is written in it. Perhaps, we will find a clue\nThough you didn't deliver Gino Gvineili to my abode, I am satisfied of your efforts, my son. Now let me tell you some news.";
			link.l1 = "You have my attention, Father Vincento.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "I have acquired an information that Trinidad island was the last place where they saw Dichoso's frigate. I also know an approximate time - first half of April 1654\nGo to Trinidad and try to learn anything about the frigate's fate: where was she heading, what plans did captain have, anything. I understand that it has been too long and people's memory has limits, but... a drowning man catches at a straw.";
			link.l1 = "I'll do everything in my power.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Let me see your credentials. I'll enter in permission to visit the colony of San Jose.";
			link.l1 = "Here.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "There... That will be all. Don't forget to hoist the Spanish flag on your ship. Step forward and take my blessings, my son!";
			link.l1 = "One moment, Your Grace. Might I ask you a question?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Yes, of course. What would you like to know?";
			link.l1 = "During our last meeting, you spoke of an Indian that had informed you about Tayasal. I've thought a lot about it... Tell me, did that pagan have anything on him? Objects of some kind, writings, or anything of the sort? This may prove to be useful.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "No special items, my son. A loincloth, primitive jewellery, a bamboo pipe with some herbs and a piece of rough leather used as a gag\nAll of those were sent to baron Ramon de Mendoza y Riba. But I assure you, there were nothing worth of interest.";
			link.l1 = "I see, Father Vincento. Thank you for your input. Till next time!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "May the Almighty give us his blessings... What ended up happening to Miguel Dichoso? Did you find out?";
			link.l1 = "Alas, I did not. The last thing the witness informed me of was that the Santa Quiteria was taken by storm in the direction of the Martinique. It is not known for sure whether the ship was salvaged or it perished. But I have suspicions that Miguel Dichoso did make it out alive.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "What made you decide that, my son?";
			link.l1 = "The key is that the frigate was hidden somewhere in the direction of Martinique. And very recently a gallant caballero by the name of Diego de Montoya, one of Don Ramon de Mendosa's himself, attacked Saint-Pierre with the goal of finding Miguel Dichoso who was supposedly hiding there.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "So, the baron thinks Dichoso went into hiding with the French...";
			link.l1 = "I know well Sent-Pierre and governor Jacques Dyel du Parquet, Your Excellency. Nobody knew a Spanish named Miguel Dichoso there. Can you tell me how to find Diego de Montoya? I'd like to speak with him about Dichoso.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Are you sure he'd be willing to speak with you, my son? I don't think he would. Unless you want talk swords and pistols.";
			link.l1 = "May it be that your name might loosen his lips?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Oh, "+pchar.name+". I doubt that the baron's henchman would be willing to make an agreement with you. Giving him an order to arrive in San Diego for a hearing with me might be an option, but I'm not so sure Diego would be perfectly sincere with me.";
			link.l1 = "What action shall we fortake now, father?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Leave me for a little while, my son. I need to process what you've told me and also put together all the facts that I'm already aware of. At that point, I'll tell you what our next move is. Drop by later on.";
			link.l1 = "Yes, Your Grace. Will do. I'll check up on periodically...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "God bless your deeds, my son... What can I do for you?";
			link.l1 = "Do you have any news, Your Grace?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Not at the moment, my son. Don't despair though. My people and I are working on it. Drop by later.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Yes, my son. I have some information about Miguel Dichoso. It wasn't in vain that I believed Dichoso to be still alive and on the archipelago. And Don Diego de Montoya was right. We've received a proof from a man who knew Miguel Dichoso by his face that this caballero was seen in the pirate settlement Le Francois on Martinique right in April 1654 after the disappearance of the Santa Quiteria...";
			link.l1 = "So, the frigate did crash at the shores of this island?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Slow down, my son. We don't have any information about any ship wrecking at that time by Martinique yet. And the frigate is not a lugger. It's destruction surely would have attracted some attention.";
			link.l1 = "May it be worth searching the shore waters and the beaches in order to find what is left of the ship?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "My son, don Diego de Montoya has already done all of this with no result. But keep listening. My sources at Providence report that the baron is sure that the Santa Quiteria is still sailing across the Caribbean sea though under a different name\nThat is why he is hunting Miguel Dichoso that desperately. According to his words, the Santa Quiteria was seen not far from Isla Tesoro and she has been recently seen under the English flag escorted by a military squadron.";
			link.l1 = "This is all so strange. They claimed that withstanding a storm of such scale would be impossible... And now the ship is sailing under the English flag. The two facts don't fit. What made the baron decide that it was Santa Quiteria? Is she really so unique?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Yes, she is. This frigate was built using the latest technology in Europe, she has an extraordinary exterior, and her speed characteristics are most excellent. That's what my source told me.";
			link.l1 = "And she is called Santa Quiteria now?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "That, unfortunately, I do not know... Go head off to Isla Tesoro, "+pchar.name+", and try to find something out about Dichoso's frigate. We might manage to find her former captain that way as well.";
			link.l1 = "Consider it done, Your Grace!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "I'm glad you decided to meet me, my son...";
			link.l1 = "Hello, Your Grace. After meeting with Don Alonso de Maldonado I didn't even think I'd see you again.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Don Alonso de Maldonado had broken my direct orders. I had strictly forbidden him from confronting you, my son, I knew how it would end up for him. His mission was to escort you to Tayasal, he had been there before\nBesides, his squadron and a unit of Spanish soldiers were supposed to act as an assault force against Itza pagans. Driven by a self-will and a desire for revenge, Alonso acted unworthily\nHe had not only failed an expedition to Tayasal and doomed soldiers and ships entrusted him, but also planted the seeds of distrust and anger towards me in your heart. I assure you, my son, I am completely at your side.";
			link.l1 = "I'd like to believe that.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Rest assured, "+pchar.name+". I, a loyal and dedicated servant to our lord Jesus Christ and a representative of his church, am motivated by one thing: to stop the end of the world from coming, which lies in the hands of a demon embodied in an Indian. I suspected it right away and only now I have become completely sure: you have been chosen by the Lord as His weapon in the battle against evil!";
			link.l1 = "But what makes you decide that, father Vincento?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "You've managed to do something that neither I with the help of my assistants, nor Baron Mendosa and Don Diego nor anybody else has been able to do. You've managed to find the damned island and seek out Kukulcan's artefact on it. Haven't you?";
			link.l1 = "Yes, I truly have taken Kukulcan's mask.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "And would you truly affirm that it happened as an accident? My son, the Almighty has led you onto this path! He has fortified your hand in battles, directed your feet onto the correct path, and protected you during times of danger! You are the penetrating sword that will save the Christian world!";
			link.l1 = "Ehem... Father Vincento, but the mission has basically already been accomplished. I have the mask and that means that Kukulcan's embodiment cannot enter into the past...";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "You're mistaken, my son. The demon may cross that gates, no matter if he has this mask or not. It will be easier for him to carry out his dark deeds with this artefact during this passing time. The only thing that can stop him is the destruction of the gates.";
			link.l1 = "Don Alonso has told me the same thing...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "And he was right! In the name of our Lord Jesus Christ, I call you to the battle against evil, my son! You cannot refuse the great mission that has been set on you. We are all now depending on you, my son.";
			link.l1 = "Your Grace, I really feel...kind of awkward...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Your modesty always suits you well, my son. Enter into this battle for the sake of your loved ones, for the sake of all Christians... and for your own sake, because if the demon emerges victorious, you will perish along with everyone else.";
			link.l1 = "I suppose you've convinced me, Father Vincento. I had hesitated on my situation to crusade into Tayasal, but now I no longer have doubts. What can you help me with?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Only two men knew how to get to Tayasal: Alonso de Maldonado and Miguel Dichoso. Don Alonso is dead. And Dichoso... They told me that he was recently seen in Sharptown of Isla Tesoro. Perhaps, he is still there. You should find Dichoso and persuade him to be your guide\nThrough gold or through force, but you must make this man to bring you to Tayasal. There you will find the gates of evil and there you will seal them.";
			link.l1 = "And what about the shock troops?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "These shock troops were under the command of Alonso de Maldonado. Alas! I don't have the chance to assemble another troop of Spanish soldiers. You'll have to do it with the help of your men, my son. But I will give you whatever help I can.";
			link.l1 = "What help?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Father Adrian will come to this chapel in five days. He will bring you holy amulets which help warriors of Christ in fight. He will also provide you with all kinds of potions. As for me, accept this blade, my son\nThis is a sword of the Temple Knights, a formidable weapon of our ancestors. Only the best warriors had an honour of owning it. Take it, possess it with a pride, and crush enemies of our faith with a name of God on your lips!";
			link.l1 = "Thank you! The sword is absolutely amazing. I'm speechless...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("You've received the Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "God bless you, "+GetFullName(pchar)+", in the sacred battle. I embower you with the holy cross. May God watch over you and may he never leave you, not in your searches, not on your path, and not in your battle. Amen.";
			link.l1 = "Amen!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "And now be gone, my son. Seek out Miguel Dichoso and make your way to the pagan city with his aid. Do not forget about Father Adrian, he will equip you with charms and remedies. And now it's time for me to return back to Santiago. Goodbye, my son.";
			link.l1 = "Goodbye, Father Vincento...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
