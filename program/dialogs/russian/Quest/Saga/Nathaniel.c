// Натаниэль Хоук - пиратский барон Марун-Тауна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("VOICE\Russian\saga\Nataniel Hawk-02.wav");
			dialog.text = "Ah... who are you, damn it?.. Khe... (severe cough with hoarseness) Damn weakness...";
			link.l1 = "Greetings, Nathaniel. You are Nathaniel Hawk, aren't you?";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "Yes, it is me, if I can still call myself that name. I once was Nathaniel Hawk but now I am just a bag of shit. Fuck that statue! It's drunk all the lifeblood out of me.";
			link.l1 = "I am familiar with the feeling...";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "How could you, lad, if you don't even realize what I am talking about? A-kha... Do you even know how it feels to turn into a half dead old man from being healthy and strong within a minute?\nI've seen a lot of things, I thought that ancient Indian temple killed my ability to get surprised, but this... I had to see it coming! The blasted statue looked the same as the old idol which opened the door to the temple!";
			link.l1 = "Fine, Nathan, let's have a talk. Let me introduce myself, I am "+GetFullName(pchar)+". First, I understand you very well because I came here the same way you did - using the Kukulcan portal.";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "Really?! And why are you looking fine? Or has that... Kukulcan harmed only me?";
			link.l1 = "Snake Eye, Miskito shaman, who helped you to escape, has given a very strong potion to me. I have drunk it as soon as I was thrown to the San Augustine. It totally healed me. I am sure that Snake Eye can help you too. You just need to get to him.";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "Ah, that Indian! A potion? And why didn't he give it to me too?";
			link.l1 = "He said that there was no time. You had been chased and the only thing he could do is to show you the way to escape - the portal.";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("VOICE\Russian\saga\Nataniel Hawk-01.wav");
			dialog.text = "Escape? Oh... Don't you see my current condition? I can't even hold a saber. How can you call it an escape? Thank God, there are still good people in this world. Ole, God bless him... Do you know Ole?";
			link.l1 = "Yes. Actually he told me about you, he told me how he fed you with rats and how you keep being drunk, bottle after bottle...";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "I will die faster than the lighted candle if I don't drink rum. It is the only thing which is keeping me alive. Rum...";
			link.l1 = "Are you still feeling that bad? Same as after teleportation?";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "Well, not just like that... But not really better. Yes, pal, explain now why did you need to see old Nathan? Why the hell did you come here, on this old, rotten tub? To chat with me?";
			link.l1 = "Actually, yes. You won't believe me, but the reason why I have gone all that way through teleportation was to find you. I work for the Brethren of the Coast and I represent Jan Swanson.";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "Damn it... Forest Devil? Argh... Did you come to finish me? Or didn't you? You are too talkative for an assassin. Please - no tortures. If you were ordered to get something from me - I will tell everything myself, I have got nothing to hide.";
			link.l1 = "What do you mean? A-ah, I see. You, just like Danielle, decided that Swanson has arranged that ambush on you in a selva. I assure you that Jan didn't do it. On the contrary, he is on your side and he worries a lot about your disappearance.";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "Really? I am damn glad to hear that. And I have already been thinking... but who did it? My detachment was destroyed in minutes. They were waiting for us. They even had ship cannons! They mowed down half of my men with grapeshot and then they were just finishing us with their muskets...";
			link.l1 = "To be honest, I don't know details, but I am sure that Jackman is behind all of this. Too many coincidences, first Blaze, then you... Jackman wants to seize power and he eliminates everyone who stands in his way. He rules Maroon Town now instead of you.";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "Jackman? Bastard! Eh...the Brethren has become separated for the last years, it all was different before. Zachariah has gone crazy on his religion matters, Tyrex doesn't give a fuck about anything and Barbazon is only interested in doubloons. It was all different twenty years ago...";
			link.l1 = "How did they capture you? Tell me more.";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "There is nothing special to tell! As I said, those bandits planned the whole thing. They were acting neatly, they were coordinated and clearly they were following someone's orders. They could have killed me a hundred times, but they haven't. They wanted me alive. They took me to an abandoned mine and locked me inside one of the huts. 'Until the boss arrives' they said\nI thought that Swanson was the boss, but it seems that Jackman is in charge. I don't know what he wanted from me though, but I am sure, I wouldn't live long after having a chat with him.";
			link.l1 = "I have no doubt in that. Swanson is sure that Jackman has killed Blaze Sharp... How were you able to escape?";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "That Indian Snake Eye somehow managed to sneak inside the mines. As far as I understood the Miskito don't like bandits. Anyways, Snake Eye had arranged my escape for some reason. He dug a tunnel to me, got inside, cut my ropes and we ran away to the jungles\nHe wanted to take me to his village, to the Miskito. But it looks like Jackman wanted me badly, a big hunt was organized. They were close on our heels. Snake Eye did his best to fool them, but they always managed to find our trail. They had good pathfinders, no doubt\nWe were close to the village when they had finally found us. My belly was empty for two days and I was completely wasted, I had also damaged my leg badly. It was midnight and I still remember how bright was the star over the statue... Snake Eye said that my only chance was to make it to the idol and touch it\nI thought that the man was mad, but you know what they say about catching at a straw. I hobbled to the statue, touched it... and then crazy things started to happen!";
			link.l1 = "You may not continue, I know what has been happening there.";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "I had found myself inside a wet hold of some wrecked ship. I was half dead. Couldn't walk, only to crawl. Every minute my condition was getting worse. Ole shown up just in time. He poured in me some Caribbean crap tasted mixture, a mix of an antidote and a healing essence. Then he gave me rum\nI got better immediately. Then he found and used an old log to move me here. I've been living here for some time, don't know for sure how long, I've lost the time count.";
			link.l1 = "It will be alright, Nathan. Me and Swanson have great plans and your role in them is very significant. You must return to your position in Maroon Town and we will deal with that scum Jackman.";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "Maroon Town? And how exactly do you imagine this would work? Look at me, I am a rum soaked wreck! Worthless... No, the years of my authority at Maroon Town are gone forever. I am trapped on this bloody ship cemetery. How long will I last? A month, two, a year?\nAnd then I will end up lying on these rotten planking and Ole will throw what is left of Nathaniel Hawk to the sea. The worst part is that I won't see my Dannie again. Eh, it's over, pal.";
			link.l1 = "Don't be that pessimistic. I will get you out of here.";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "Will you get me out of here? And how are you going to leave this place? There are no ships. Do you want to build a raft?";
			link.l1 = "No. I will leave this place the same way I came here. I know where is the statue... well, roughly. I will find it and then I will be back for you and Shark Dodson. We will get you to Snake Eye after that. He will heal you.";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "What did you say? Shark Dodson? Is Steve also here? Such a strange place...";
			link.l1 = "Yes, he is here. He is a 'governor' of this island so to speak. I have asked him about you but he doesn't know a thing.";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "And he shouldn't. I don't want him to see me in that condition. You said that the shaman will heal me... I barely believe it. You have mentioned Dannie... Did you see her?";
			link.l1 = "Yes. She has found me herself in Blueweld. She has eavesdropped on my conversation with Svensson and understood that Jan had no intention to kill you and he is working against Jackman. She went on my ship as an officer to help me to find you.";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "Eh, my dear Dannie! She hasn't changed... As reckless as always... You can't even imagine how badly I want to see and hug her now! I thought a lot while lying here. See, pal, you start to see things in a different light when you are close to death. I have spent so little time with my wife!\nSea raids, Brethren's official businesses, ruling Maroon Town. And she always supported me in everything: stayed alone for weeks, had quarrels with other pirates while I was gone, commanded our ship... My Dannie is the best woman in the world! And I... I should have said that I love her more often!\nI remember the day we decided to be together! Actually, that was the day I first met and fought supernatural things. It all happened because of that blasted idol which looked like the statues. Don't you mind to hear a story? It is quite interesting.";
			link.l1 = "And why not? Tell me!";
			link.l1.go = "story";
			link.l2 = "Nathan, we don't have time for pleasant memories. You will tell me about it later, when we will be sitting at Miskito village with a bottle of wine.";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "It was twenty five years ago... I was young, ardent and restless. The Caribbean was my playground. I already knew Dannie back then. I liked her, I really did and the feeling was mutual. But we often fought, quarreled and gibed at each other. Silly youth... I believe that we were a great entertainment for the respected sailors back then!\nSo. Somehow Dannie and I got involved in the same story. We had found a map of Khael Roa, they told us that it was the place to find Indian gold. We also had a strange golden idol, a smaller copy of the top part of the statues\nThe idol was dangerous, it sucked vitality from those who carried it. We needed that cursed item in order to get to the treasury inside the temple. But we had no idea how to use it properly. Dannie and I sailed to the island. There was an ancient temple, covered with grass and trees. Once we entered, we had found ourselves inside a huge labyrinth\nWe managed to find the right way and reached the central internal part of the labyrinth. We thought that it was a dead end, but when the desperation started to win a victory over us, we saw a strange platform with a small socket in it and a picture. I put the idol in it and...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "The stone platform went a few inches down and one of the walls turned out to be a secret passage. The idol was left inside the platform, I failed to pull it back. Finally we had reached a giant hall. Such a beautiful sight!\nThe most magnificent structure I've ever seen. Carvings on the walls, huge statues... We had searched the whole hall, but found no sign of treasures.";
			link.l1 = "Heh, sure, that often happens to people like us. A lot of effort and no result in the end...";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "It wasn't for nothing. After all, we entered a throne hall with a giant statue of a bird in the end of it. There was a mystic light near the statue, it looked like the light above the idol at midnight. We came closer and saw a beautiful flying sphere. I swear, I am telling the pure truth!\nIt was real, but in the same time it wasn't. While I was thinking, Dannie - oh, that reckless devil, touched the sphere. It started to glow even brighter and had finally turned into a small item in her hands...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "It seemed that we had committed a sacrilege. The temple went alive: all around us were moving, walls were shaking and started destroying. It was like we had awoken all Indian demons and they had stiked all of their anger back on us...";
			link.l1 = "Wow!";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "It is hard to believe, I know. But...";
			link.l1 = "I'd call you a liar half a year ago. But I have been living long enough in the Caribbean so I don't have any reasons to mistrust you. Go on. How did you survive?";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "We ran away from the temple and were lucky enough to get to our ship. I have ordered to raise anchors, we wanted to escape from that place as soon as possible.";
			link.l1 = "Heh! So you have only found some odd artifact instead of treasures? Nice and equivalent replacement, he-he... And did you find out how to use it? Or was it useless?";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "Wait a bit. It wasn't over yet. Dannie had the artifact and as soon as we have decided to go at the cabin to study it, the sky went dark and the ship showed up. Oh God! It was...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// вот тут делаем развилку, в зависимости прошел ли игрок Калеуче
		case "story_7":
			dialog.text = "... Van der Decken himself!!";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Van der Decken? Hm...";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "And who is he?";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "Haven't you ever heard about Flying Dutchman?";
			link.l1 = "And who hasn't heard about Flying Dutchman! I have already met with one Dutchman and sent it's captain to the bottom of the sea. He was just an ordinary pirate who has decorated his ship with some masquerade trash like algaes and torn sails.";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "Yes, it was Van der Decken himself, captain of the Flying Dutchman!";
			link.l1 = "Interesting. Please, go on. How have you pulled through?";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "Eh-heh, friend... You sunk some jester and I am talking about the real Flying Dutchman. The huge warship. God save you from meeting it in the open sea. Its captain Van der Decken and his crew were once cursed to sail across the sea forever and restless\nI remember its torn black sails, the crew of dead men with their blades ready and the captain himself - a creepy skeleton wearing a black cocked hat... Jesus...";
			link.l1 = "Is it true?";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "I can swear on the Bible that I am not lying... The meeting with 'Flying Dutchman' means only death. She's powerful, very powerful, one volley of her guns can sink a heavy frigate and it's crew... how are you supposed to fight the undead?";
			link.l1 = "But you have survived that mess!";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "It is all thanks to my lovely Dannie and the Indian artifact which we have taken from the temple. I have ordered to get ready to fight, but I knew that it was an end of the line. 'Flying Dutchman' was sailing to us and I was seeing her dreadful crew and Van der Decken himself. The ship had started to aim her cannons at us but...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "Dannie raised the artifact and let it fly. I have no idea why. She said something about her female intuition... The artifact turned back into a glowing sphere, exploded, critically damaged the ghost ship and demoralized its crew. I ordered to open fire\nFirst volley made them shudder. We performed another attack and shot their rotten hull again before they recovered from the artifact's influence and returned fire...";
			link.l1 = "But you had to fight them anyway?";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "I had. And I swear it was the toughest fight in my life. Their damn tub was barely keeping on the water, but they were still able to destroy half of my hull before we sent them sky high by blowing up their powder chamber.";
			link.l1 = "So did you sink it? Did you sink the Flying Dutchman?";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "Yes, damn it! I did!..";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "The damn ship went down. The sun was shining again and the sky went clear. We were happy... you can't even imagine how. We had beaten the death itself. Moments like that bring people together. And we did the thing which we had to do long time before - we embraced, kissed, said that we love each other and sworn to stay together forever.";
			link.l1 = "And you are together...";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "Yes, we are. Me and Dannie got married and I have never regretted it. You won't find a better wife and sister in arms.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "So now I know who's that mysterious captain who had sunk the 'Flying Dutchman'... A real hero!";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "So are you the heroes then? You have sunk the famous ghost ship. Wait! You said that the 'Flying Dutchman' is still flying... How can it be possible if she is lying at the bottom?";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "Eh, pal, you don't know a thing... You can sink Van der Decken, but you can't kill him. The curse upon him and his crew is too strong, much stronger than a death...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "A hero I might be, but Van der Decken cannot be killed. The curse hanging over him, his crew and his ship is stronger than death...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "Every time you drown the ship, its crew repair their ship, get her up and continue their eternal sail.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "I know, Nathaniel, I know. Still, Flying Dutchman will no longer trouble anyone.";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "Well, you know, this sounds like a fable. To repair the parted and scuttled ship...";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "People have seen the ship many times after we have sunk it... You decide to believe it or not.";
			link.l1 = "And where is that island with the temple where did you get an artefact from?";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "It is uncharted and it is located somewhere in the east of the Caribbean sea. I left a map of the island in Maroon Town and as you understand I can't get there now. And to be honest I don't want to. The only thing I remember is its name - Khael Roa...";
			link.l1 = "Such an interesting story. I'd like to find that island!";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = "Oh, I won't advise you... I ain't going to see it again.";
			link.l1 = "I'd like to visit it anyway... Fine, thank you for your interesting story! Now I know more about your wife. You both are the living legend!";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = "What are you implying, buddy? Haven't I just tell you that he can't be killed?";
			link.l1 = "Nathaniel, I visited Khael Roa. And I was in the temple of the Chavins, where you, Danielle and some old man had been a quarter of century ago. The artifact you had taken from the temple back then, was called 'orb of the rising sun'. It was that thing that drew the attention of 'Flying Dutchman'. Its captain had fondness for Chavins artifacts.";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "You were at Khael Roa? But that just can't be! Are you telling me the truth?";
			link.l1 = "I swear. Just as you told me about the labyrinth and the statue of the giant bird, I immediately realized, what was that place. Caribbean shaman Tuttuathapak told me about your adventures. It was him who directed me to that island. It is located to the east of St. Christopher. It's very small, shaped like a ring. There are rocks all around and a small cove inside. And there is just one overgrown path leading to a temple, which is build in the form of a pyramid.";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "Yes! This is Khael Roa. And why did you go there?";
			link.l1 = "To remove the curse of the Caleuche... well, of the 'Flying Dutchman'. Actually, her name was 'Flying Heart', and the name of her captain was 'Balthazar de Cordes'. Fifty years ago he was cursed by Yum Cimil, an Indian God of Death. I took the jade skull of Yum Cimil, which had been stolen from the temple by that Balthazar some time ago, and put it back on the pedestal in front of that condor statue...";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "...by returning the skull I have removed the curse of the Caleuche. And since I had two other Chavins amulets with me, she attacked me tight at the island, just like it had happened to you back then. But without the curse Balthazar was no longer immortal, just as Tuttuathapak said. So... the 'Flying Dutchman' is no more. I personally took care of her.";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "Thunder and lightning! I am astounded! You.. You're not kidding old Nathan, are you? No, I see it in your eyes that you are telling the truth! You're a real hero!";
			link.l1 = "A hero or not, but I've surely seen my fair share of the adventures, just as you have. Well, surely we'll talk about the past times many more times, cause now we have a common subject.";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "Are you going to leave me now, friend?";
			link.l1 = "Yes, Nathan. Please, hold on until my return. Take care. And the most important, stay alive until I am back and everything will be alright. Brethren of the Coast need you, Danielle needs you.";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "Is Dannie in your crew now? I beg you, watch over her. She hasn't change since her youth, she is still a daredevil and she will not hesitate to go into hell. Tell her that I love her very much...";
			link.l1 = "Sure I will. We will return together for you, I promise you that, Nathan. Hold on, and keep up. Ole will take care of you. See you soon!";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "Ah, it's you, "+pchar.name+". Haven't leave the Island yet?";
			link.l1 = "Don't worry, Nathan, all is going according to the plan. Rest.";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("VOICE\Russian\saga\Nataniel Hawk-03.wav");
			dialog.text = "Danielle!.. Dannie! My Dannie!..";
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "Thank you, my friend. Thank you for everything and especially for my Dannie...";
			link.l1 = "You are welcome, Nathan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = "Look who's just dropped in! It's "+GetFullName(pchar)+"  himself! Come in, come in, friend! How are you?";
			link.l1 = "I am fine. And you, Nathan? I see that there is no gloom left. You look good. Snake Eye has done really well!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Yes, your shaman is a miracle-worker. I feel even better than I was before that damn teleport! I feel like I am ten years younger! "+pchar.name+", I owe you a great deal. I am impressed: you were helping the complete stranger, passed the cursed portal, grabbed me from the death's hands, returned my wife!\nAnd even more! You brought us our ship and our home back. You are now our best friend. Forever. If you'll ever need something - you know who to ask! Maroon Town will always provide you with protection, support and a sanctuary in case you need it\nThe whole village will fight for you if you are in danger. During the peaceful times you will find here friendship, best rum, soft bed and a fine rest. Dannie and I will make sure of it.";
			link.l1 = "Thank you, baron! I am sincerely glad to see you in a good health and... with Dannie.";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "I've been expecting your visit, "+pchar.name+", and I have prepared a gift - a rare and powerful weapon. One day, perhaps, you will need to take down numerous enemies in one shot and this hand mortar will help you to do that. 'Sclopetta' fires special grenades so I've also prepared an instruction how to make them. Here, take it.";
			link.l1 = "Excellent weapon! Thanks!";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("You have received a hand mortar");
			Log_Info("You have received a grenade instruction");
			PlaySound("interface\important_item.wav");
			dialog.text = "Come and see us more often, "+pchar.name+"! Dannie and me will always be glad to see you any time.";
			link.l1 = "It will be a pleasure for me. Expect to see me soon!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "Ah, my friend "+GetFullName(pchar)+"! Come in, come in, captain! How are you? Need any help?";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "Nathan, I've come to you on a very important business. Do you remember you told me on the Island of Dead Ships, how you and Dannie sneaked into an Indian temple and then sunk the 'Flying Dutchman'?";
				link.l2.go = "caleuche";
			}
			link.l1 = "Thanks, I am fine. Just wanted to see you both.";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "Of course, I do.";
			link.l1 = "I need to get to that island with the temple. I need it very badly. You said you had a map of it. Can you tell me the coordinates?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Oh, friend, this is a very dangerous undertaking, you know... The temple of Khael Roa is cursed. If you only knew who dwells its corridors...";
			link.l1 = "At the moment it is inhabited by monsters much more terrifying compared to those you've seen back then. And still I will go there.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "I will not forgive myself if you perish there. "+pchar.name+", I beg you: abandon this venture! Besides, it's where the 'Flying Dutchman' has been seen very often...";
			link.l1 = "I have already encountered it, and I know how to outrun it. Nathan, please, give me the coordinates of Khael Roa and tell me everything you know about that temple, besides that it's inhabited by the undead Indians.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Oh well... I cannot turn you down, but... You have no idea, what me and Dannie experienced there! Khael Roa is located east of Antigua. I found its map right when I got back to Maroon Town, it's there... (looking) The coordinates: 19 degrees 32' North, 62 degrees 25' West.";
			link.l1 = "I'll write it down in my journal… Thanks, Nathan!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "You can thank me later. Now the details. Island of Khael Roa is a ring of rocks with a cove inside. Seek for the passage between the crags - it's fairly deep there. In the cove, you should cast anchor and disembark at the beach. Look for an old path heading deeper into the island - there's only one there. It will lead you to an Indian pyramid - this is the temple you seek.\nThe island itself is quiet, but the temple is being crawled with abominations of all sorts. The entrance is located at the top of the pyramid. There will be three passages inside; you should take the middle one. Then you walk down the corridor and there will be a platform with four entrances-exits. This is where the temple creatures attacked me for the first time, so you should be careful\nThen there is a labyrinth. It's very complex, and I surely can't remember the right route. And there is a multitude of foul creatures in there. You must kill them all, then walk up to a hall with two entrances, six columns and a platform with nine stone slabs. This is the vestibule of the sanctuary. Its stone wall is closed, and I have no idea how you're going to open it.\nThere is some kind of mechanism, but I swear to God that I have no clue how it functions! I had an idol key. I inserted it into the central slab, and the door opened. But you don't have such an idol, so you'll have to figure out, how this mechanism functions.";
			link.l1 = "Alright, I'll do my best to figure it out. What about the sanctuary?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "The sanctuary is a huge hall with a very high ceiling and large stone stairs. You cannot use them - they are too old and fallen apart for the most part. But the builders of the temple, as it seems, were also great sorcerers. There are portals, like those of Kukulcan, they will take you from one place to another.\nYou will recognize them easily - they look like colored swirls. There will be two portals on the first floor, but one of them is a trap, so be careful! The correct portal will take you to the second floor. There you must find another portal to go even higher, and then right to the heart of the temple!\nThere, at the great statue of the bird, was that magical artifact, which me and Dannie taken with us. And I already told you, what had happened next.";
			link.l1 = "I will remember it. Thank you, Nathaniel. You helped me greatly.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Take care, "+pchar.name+". The labyrinth and the halls of the temple are full of dangers. Just one wrong move and you're sure to stay there forever.";
			link.l1 = "Praemonitus praemunitus, friend. I was forewarned, that means, I am forearmed. I have to go now. See you!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Good luck, "+pchar.name+"!";
			link.l1 = "Thanks!";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}