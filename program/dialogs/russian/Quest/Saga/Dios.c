// Хосе Диос - картограф
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
			dialog.text = "Want something?";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"! Tell me, are you Jose Dios, a cartographer?";
				link.l3.go = "island";
			}
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "Yes, it's me. I don't know you, senor. What do you want from me?";
			link.l1 = "My name is "+GetFullName(pchar)+" and I came here from Jan Swanson. Do you remember him?";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "Ah, senor Swanson! Sure I remember him! Come, make yourself comfortable... How is respected Jan doing?";
			link.l1 = "Thanks, he is doing fine. Senor Dios, I need your help. I want to consult with you about one matter which must be familiar to you due to your job. Jan recommended you as an geography expert of Caribbean region";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "I am listening, senor. What do you want to know about the archipelago's geography?";
			link.l1 = "They say that there is an island or some different kind of formation North-West from Havana, between Cuba and Gulf of Mexico. This island has never been plotted on any map. I'd like to know the trustworthiness of all these gossips.";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "Hm... You have asked the question which is one of the most stirring for me. This place you've mentioned has been attracting the inquisitive minds of geographers for a long time, but nobody have ever been brave enough to explore that region.";
			link.l1 = "Why?";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "Thing is, that the place is some sort of natural anomaly. The probability of storms there is much higher than anywhere else. Perhaps the reason is in the cold sea current, but this is just my hypothesis. A lot of ships have disappeared there and that was enough to make sailors avoid that place, all of the main sea routes are passing far away from that region anyway.";
			link.l1 = "I take it that you also don't know the truth...";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "Exactly, senor. But I have a few historical documents and some material evidences, so I have all rights to suspect the probability of that place's existence.";
			link.l1 = "Can you tell me more?";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "Sure. The most important evidence is the historical document with extracts from the journal of captain Alvarado who has visited the Island in 1620. Quite an interesting story I tell you!";
			link.l1 = "Captain Alvarado? It is the second time I hear that name...";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "I am not surprised. The story of captain Alvarado has been a part of folklore for years. It changed, was filled with rumors, lies and dreams, so here it is - the legend of Justice Island\nBut the paper and the ink cannot be changed, they stay intact for hundreds of years. Here, read this story - perhaps, it will help to unveil something you are looking for.";
			link.l1 = "Thanks! Got anything else?";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "There is a theory that the sea bottom in that area rises high enough to form a vast shoal. I have already mentioned the current. There is also a large accumulation of seagulls and other sea birds according to sailors talks\nAlvorado mentioned names of vessels which were the part of admiral Francisco Betancourt's squadron, the squadron was lost more than fifty years ago. I doubt that this is just a coincidence...";
			link.l1 = "I will return to my ship and read Alvarado's notes carefully. Thank you for your help, senor Dios!";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "You're welcome. Actually I didn't help you at all, you don't have coordinates of the place, so do I. I can't even prove that there is an inhabited land out there. But as far as I understand, you intend to explore this area?\nIf so, then be aware that I will be really grateful for any information, especially if it is provided with a material proof. It seems that you are a wealthy man, but I will find a way to repay you.";
			link.l1 = "Good. Consider that we have a deal, senor Dios. Perhaps my notes will be also read by someone in the future... And someone might write a legend...";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "Why not? Senor "+pchar.name+", I see that you are an active man who travels a lot, so I'd ask you to do something.";
			link.l1 = "Yes? I am listening.";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "You know that I am cartographer. So, I had been drawing maps of the Caribbean archipelago for two years, compiling the admiral's atlas for the Vice King's contest of Nueva Granada. But all twenty four maps were stolen from my house in the most insolent way while I was captured by pirates, the ones senior Swanson saved me from\nI am sure that the attack was organized by my competitors in order to acquire my maps. It's been a long time but I have not seen a single map from my set.";
			link.l1 = "I see. You want me to return your maps.";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "Exactly. Perhaps you will find them during your future adventures. It is easy to recognize them - there is my sign on every of them. I will generously reward you if you are be miraculously able to collect all twenty four maps.";
			link.l1 = "Fine. I will attentively look at every map I'll find at the archipelago. Well, I have to go now. Thank you for an interesting conversation and for the document.";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "A-ah, it is you, senor "+GetFullName(pchar)+"? Got anything interesting to tell me?";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"! Senor Dios, please, take a look at the map I've found. It must be one of your maps according to the sign.";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"! Senor Dios I have good news for you. I was able to collect the whole complect of your unique maps just as you wanted. Here, there are all twenty four maps.";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"! Yes, I have. I was at that mystic place we were talking about.";
				link.l4.go = "LSC";
			}
			link.l9 = "Nothing so far, senor. Just wanted to see how you're doing.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "Show me... (taking a look) Of course! This is one of my maps for the admiral's atlas! Captain, I really ask you to find all of them! I understand that it's almost impossible but still... I don't loose hope.";
			link.l1 = "Don't loose it, senor. I have found this map so there is a chance to find the rest. They are still at the Caribbean.";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "Your optimism really encourages me, senor captain. Perhaps I still have an opportunity to show to don Juan de Cordova who is the best cartographer of the archipelago!";
			link.l1 = "You will be able beat all your competitors-ill-wishers. The maps are really wonderful... Farewell, senor!";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			dialog.text = "I don't believe my ears! Have you really found them? All of them?";
			link.l1 = "Yes. It wasn't easy, but I was lucky enough in this search. Take your maps. They are so wonderful, that I am sorry to part with them.";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			for(i=1; i<=24; i++)
			{
				sTemp = IdentifyAdmiralMapLast();
				if (sTemp != "") RemoveItems(pchar, sTemp, 1);
			}
			Log_Info("You have given the complect of admiral's maps");
			PlaySound("interface\important_item.wav");
			dialog.text = "Incredible! This is just too incredible! To be honest I have never believed that it will happen at all.";
			link.l1 = "Dum spiro, spero, senior Dios. You may face don Cordova now. I am sure, he will value your talents highly.";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "You have my thanks, captain! You don't even realize what a great service you have done for me. As I promised - I will reward you. I also have a gift for you. I think that as sailor you will find it very useful.";
			link.l1 = "You have intrigued me, senor!";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("You have received a ship telescope");
			PlaySound("interface\important_item.wav");
			dialog.text = "Here! There is a ship telescope of my design. It is unique and you won't find anything like that anywhere else. Lens were made in Europe by the most skilful master of Spain. Its case was made by my friend gunsmith. A special tripod will help you to point the device despite of any rolling. You can see everything you need at the ship's deck or at a fort.";
			link.l1 = "Such a wounderful a gift! Thank you, senor Dios.";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "Use it, senor captain. I hope that my telescope will serve you well.";
			link.l1 = "No doubt! I am looking forward to plant it on the deck of my ship and look through it.";
			link.l1.go = "amap_5";
		break;
		
		case "amap_5":
			dialog.text = "You will be surprised, I assure you... Thanks again for my saved maps!";
			link.l1 = "Thank you too, senor. I think that we will meet again. And I have to go now, looking forward to try your gift. Farewell!";
			link.l1.go = "amap_6";
		break;
		
		case "amap_6":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
		break;
		
		case "LSC":
			dialog.text = "Really?! Have you found it? Make yourself comfortable, I think coming conversation will take a while, am I right?";
			link.l1 = "I really have a lot to tell you about the island. But, first, I want you to promise me something. I see that you are a man of honour, so I am sure that you will keep your word...";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "What are you talking about, captain?";
			link.l1 = "There are people living there... and they won't be happy if someone will meddle in their life. I don't think that a possible arrival of some 'research' squadron will be welcomed. So I want you to give me your word of honour that you won't publish any information which can be used to find the Island within ten years after our conversation. You are welcome to publish any information about locals, their life and so on, just don't reveal the location of island.";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "I agree, captain. I give you a word of a nobleman that I won't tell anyone neither the location of the Island nor any information which could harm it's inhabitants within ten years.";
			link.l1 = "Listen to my story then. Write it if you want. So, the Island is made of a lot of wrecked ships which shells are lying on the wide shoal...";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "Incredible! You have told me a very valuable information, captain! Offspring's of admiral de Betancourt are living at the Island! Now we know what happened to his squadron. And there is one less blank spot on the map of the Caribbean archipelago now... Thank you very much for you story, "+pchar.name+"!";
			link.l1 = "See now why have I asked you to be really careful in retelling my information?";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "I see. You can be sure that I will keep my word. Tell me... do you have any material attributes from the Island?";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "I have sailing directions to the Island of Justice. Here, take a look. It allows you to sail a small ship through the reefs and debris and to land safely at the Island. It is impossible to reach the Island without it.";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have any.";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("You have given a sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking) Such an excellent document! It was drawn by a man who is skilled in cartography. Even I couldn't do it better. Incredible! Captain, why don't you give me these sailing directions? Story is a story, but this paper must be shown to the most famous geographers of the Old World!";
			link.l1 = "Sure. That is why I have brought it to you.";
			link.l1.go = "LSC_10";
			link.l2 = "Senor Dios, unfortunately, I need this item for myself. As I have said, it is impossible to bypass the reefs around the Island without it. I'd sacrifice it in the name of the science, but... I am sure that you understand.";
			link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("You received a sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Absolutely. It is your right, though it's a pity... Anyway, thanks for you story! You have done a great service for geographers, cartographer and other curious people.";
			link.l1 = "You're welcome, senor. Well, I have to go now. Farewell.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "What a pity... Anyway, thanks for you story! You have done a great service for geographers, cartographer and other curious people.";
			link.l1 = "You're welcome, senor. Well, I have to go now. Farewell.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "Sure, "+pchar.name+". You have spared a lot of your time for me. Send my regards to senor Swanson!";
			link.l1 = "Good bye, senor Dios.";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "Thank you very much! It was very kind of you. Now we have got not only oral evidences but also material ones... I won't leave you unanswered, captain. I have got a small gift for you.";
			link.l1 = "What kind of gift?";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "I am fond not only of cartography and geography, but also of mathematics and astronomy. It took a year of trying for me to create a universal tool for taking latitude and longitude. And I've made some progress. Here, take a look\nThis is my sextant. I've designed it myself. Problem is, it doesn't work. It requires an extremely accurate chronometer. Even those which were made by the best craftsmen give unacceptable errors over time. Therefore, my tool is worthless\nBut you travel a lot, perhaps you will find a chronometer accurate enough for the sextant to work. Once you find such clocks - you won't need a Boussole, a compass, an astrolabe, sand clocks and crappy chronometers - my tool will replace them all.";
			link.l1 = "Thank you, senor Dios. Let's hope that I will find a chronometer which will make your invention to work. I'd like to have such a device... in working condition. Well, I have to go now. Farewell.";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}