#pragma strict_types
inherit "/std/obj/treasure";

int cow_voice, id_title, title_count;

string *titles = ({
  "says: Everything's catching on fire",
  "says: I hear the wind blow",
  "says: Hey now everybody now",
  "says: Hey now everybody",
  "says: Hey now everybody now",
  "asks: Who's that standing out my window?",
  "says: I found a new friend underneath my pillow",
  "says: Come on and wreck my car",
  "asks: Aren't you the guy who hit me in the eye?",
  "says: Please pass the milk, please",
  "says: Leave me alone, leave me alone",
  "asks: Who's knocking on the wall?",
  "says: All alone all alone all by myself",
  "asks: What's that blue thing doing here?",
  "says: I'm having a heart attack",
  "says: Fingertips",
  "says: I walked along darkened corridors",
  "says: I don't wan't the world, I just want your half",
  "says: And the truth is, we don't know anything",
  "says: I'm going to see the cow beneath the sea",
  "says: Our only home is bone",
  "says: Life is a placebo masquerading as a simile",
  "says: Purple toupee will show the way when summer brings you down",
  "says: Purple toupee is here to stay after the hair has gone away",
  "yawns as your plane goes down in flames",
  "says: Piece of dirt, that is all I'm standing on today",
  "says: A woman's voice on the radio can convince you you're in love",
  "says: A woman's voice on the telephone can convince you you're alone",
  "says: I find myself haunted by a spooky man named Me",
  "says: I wish that I could jump out of my skin",
  "says: I've floundered in the misty sea, but can't abide it's mystery, I wound up sad, you bet",
  "says: Everyone looks naked when you know the world's address",
  "says: Call the men of science and let them hear this song. Tell them Albert Einstein and Copernicus were wrong",
  "says: Get out of the car",
  "says: Put down the phone",
  "says: Take off that stupid looking hat you wear",
  "says: I'm going to die if you touch me one more time",
  "says: Well I guess that I'm going to die no matter what",
  "says: I put a rock in the coffee in your coffee mug",
  "says: No, I don't want that fat guy around",
  "wants a shoehorn, the kind with teeth",
  "says: People should get beat up for stating their beliefs",
  "says: We are out of furniture",
  "says: Avalanche or roadblock, I was a snowball in hell",
  "says: I look like Jesus, so they say",
  "says: But Mr. Jesus is very far away",
  "says: Kiss me, Son of God",
  "says: Hey Mr. DJ, I thought you said we had a deal",
  "says: I thought you said, \"You scratch my back and I'll scratch your record\"",
  "lives in the nightgown of the sullen moon",
  "says: There's a feeling of boredom of the big whoredom",
  "says: It's not necessary to breathe",
  "says: Forever is a long time",
  "says: I'll sink Manhattan right under the sea",
  "says: When this grey world crumbles like a cake, I'll be hanging from the hope that I'll never see that recipe again",
  "says: And I'm not the only dust my mother raised",
  "says: Hello. Hello. Hello.",
  "says: A claw is a claw and nobody has seen a talking claw",
  "says: There has been a spacecraft sighted flying high above the sky",
  "says: Volunteers! We need volunteers!",
  "says: Have no fear. You will be killed right away",
  "says: I will date a girl from Venus. Flowers die and so will I",
  "says: Yes, I will kiss the girl from Venus for science",
  "says: I'm so brave. I'm so brave. I'll be her love slave",
  "says: Well, the bellhop is funky. The dumbwaiter's a monkey",
  "says: The famous person wears the same size water skis as me",
  "says: She's got three cars, as many years I've lived in this city",
  "says: Her hair is blonde and mine is brown, they both start with a 'B'",
  "says: But when the phone inside her rib cage rings it's not for me",
  "says: When it rains it snows, I wonder why",
  "says: Everything right is wrong again",
  "says: You're a weasel overcome with dinge",
  "says: You need some lo-lo-loving arms",
  "says: Put your hand inside the puppet head",
  "says: The check's in the mail, and I'll see you in church, and don't you ever change",
  "says: A rich man once told me, \"Hey life's a funny thing\"",
  "says: A poor man once told me that he can't afford to speak",
  "says: If there's just two songs in ya, boy, whaddaya want from me?",
  "says: The words I'm singing now mean nothing more than meow to an animal",
  "says: Wake up and smell the cat food in your bank account",
  "says: Don't try to stop the tail that wags the hound",
  "says: D, world destruction",
  "says: Over and overture",
  "says: N, do i need",
  "says: Apostrophe T, need this torture?",
  "says: No one in the world ever gets what they want and that is beautiful",
  "says: Everybody dies frustrated and sad and that is beautiful",
  "says: They want what they're not and I wish they would stop saying:",
  "says: Deputy dog dog a ding dang depadpa",
  "says: Hide away folk family, or else someone's gonna get ya",
  "says: Hammer down",
  "says: Rabbit ears",
  "says: All the people are so happy now, their heads are caving in",
  "says: Some people call em snake-eyes, but to me they look like mice",
  "says: Youth culture killed my dog and I don't think it's fair",
  "says: I don't understand what you did to me dog",
  "says: Sometimes I feel like being wispy",
  "says: And once in a while I feel like being dry",
  "says: Alienation's for the rich and I'm feeling poorer every day",
  "says: Hats off to the new age hairstyle made of bones",
  "says: Hats off to the use of hats as megaphones",
  "says: Speak softly, drive a Sherman tank",
  "says: Laugh hard, it's a long way to the bank",
  "asks: Do you sing like Olive Oyl on purpose?",
  "says: You guys must be into the Eurythmics",
  "says: I'm your only friend, I'm not your only friend",
  "says: But I'm a little glowing friend, but really I'm not actually your friend",
  "says: Make a little birdhouse in your soul",
  "says: Say I'm the only bee in your bonnet",
  "says: My name is blue canary one-word spelled l-i-t-e",
  "says: But I was young and foolish then, I feel old and foolish now",
  "says: I just stood there whistling \"There goes the bride\" as she walked out the door",
  "says: Why they changed it I can't say (People just liked it better that way)",
  "asks: Why did Constantinople get the works?",
  "says: That's nobody's business but the Turks",
  "says: Can't shake the devil's hand and say you're only kidding",
  "says: Person man, person man. Hit on the head with a frying pan",
  "says: She doesn't miss so turn off your smoke machine and Marshall stack",
  "says: Where was I? I forgot the point that I was making",
  "says: Everybody wants a rock to wind a piece of string around",
  "says: Throw the crib door wide, let the people crawl inside",
  "says: Someone in this town is trying to burn their playhouse down",
  "says: Everybody wants prosthetic foreheads on their real heads",
  "says: Someone in this town is trying to burn their foreheads down",
  "asks: Would you mind if we balance this glass of milk where your visiting friend accidentally was killed?",
  "says: Don't say the electric chair's not good enough for king-lazy-bones like myself",
  "says: Minimum wage!!! Ya!",
  "says: I'd like to poison your mind with wrong ideas that appeal to you though I am not unkind",
  "says: I'd like to change your mind by hitting it with a rock though I am not unkind",
  "says: I'd rather be whistling in the dark",
  "asks: Hot Cha where are you?",
  "says: Bullets from a revolver, bullets from a gun. Bullets through the atmosphere, here they come",
  "says: We can't be silent because they might be giants",
  "says: They might be snow, they might be something else in the snow",
  "says: We were once so close to heaven, Peter came out and gave us medals declaring us the nicest of the damned",
});

string *current_titles = titles;

int init_arg(void) {
  tell_object(this_player(), "Cloned: a little blue cow.\n");
  return 1;
}

void reset(int arg) {
  if (arg) return;
  set_name("cow");
  set_short("a little blue cow");
  set_long("It's a random title changer.\n"+
           "-----------\n"+
           " Commands: \n"+
           "-----------\n"+
           " moo   -- activate title changer.\n"+
           " nomoo -- de-activate title changer.\n"+
           " smoo  -- toggle title change notifier.\n");
  set_value(0);
  set_weight(0);
}

int drop(void) { return 1; }
int get(void) { return 0; }

void init(void) {
  if(environment(this_object())->query_real_name() != "bart") {
    write("A little blue cow says: Moo. Make yer own little blue cow.\n");
    this_object()->destroy();
  }
  ::init();
  if(this_player()->query_real_name() == "bart") {
    add_action("do_moo","moo");
    add_action("do_nomoo","nomoo");
    add_action("do_moo_sound","smoo");
  }
}

int do_moo(void) {
  if(id_title) {
    write("Nopers.\n");
    return 1;
  }
  cow_voice = 1;
  set_alarm(0.0, 0.0, "change_title");
  write("Yeppers.\n");
  return 1;
}

int do_nomoo(void) {
  if(id_title) {
    remove_alarm(id_title);
    id_title = 0;
    write("Done.\n");
    return 1;
  }
  else {
    write("Oops.\n");
    return 1;
  }
}

int do_moo_sound(void) {
  if (cow_voice) {
    write("Cow voice off.\n");
    cow_voice = 0;
    return 1;
  }
  else {
    write("Cow voice on.\n");
    cow_voice = 1;
    return 1;
  }
}

void change_title(void) {
  object bart;
  bart = find_player("bart");
  if (bart) {
    title_count = random(sizeof(current_titles));
    bart->set_title(current_titles[title_count]);
    bart->set_pre_title(0);
    bart->set_alignment(0);
    if (cow_voice) {
      tell_object(bart, "Cow "+current_titles[title_count]+".\n");
    }
    current_titles -= ({ current_titles[title_count] });
    if (!(sizeof(current_titles))) {
      current_titles = titles;
      tell_object(bart, "Cow tells you: Re-shuffling titles.\n");
    }
    id_title = set_alarm(20.0, 0.0, "change_title");
  }
}

string query_auto_load(void) {
  return "/wiz/b/bart/tools/cow:";
}

