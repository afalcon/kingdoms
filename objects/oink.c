#include "/areas/Misc/Bad/c/include/defs.h"
inherit "/std/obj/treasure";

  string adjective;

  string *consonants = ({
    "beautiful",
    "blonde",
    "bored",
    "brown-haired", 
    "cheerful",
    "crazy",
    "crippled",
    "cross-eyed",
    "curious", 
    "cute",
    "dark-haired", 
    "doe-eyed",
    "drunk",
    "fair-haired", 
    "fat", 
    "giggling",
    "gloomy", 
    "greedy-looking", 
    "grey-haired", 
    "grim",
    "handsome",
    "happy",
    "jolly", 
    "majestic", 
    "massive", 
    "medium-sized", 
    "noble", 
    "nosy", 
    "paraplegic",
    "portly",
    "proud", 
    "quiet", 
    "red-haired", 
    "retarded",
    "sad",
    "short", 
    "short-haired", 
    "silent",
    "silly",
    "sinewy", 
    "shy", 
    "slender", 
    "slim", 
    "smelly", 
    "stern", 
    "strong", 
    "stubborn", 
    "stubby", 
    "sturdy", 
    "tall", 
    "thin", 
    "tiny",
    "tired", 
    "white-haired",
    "young", 
  });
  
  string *vowels = ({
    "emaciated",
    "evil-looking", 
    "intelligent",
    "important",
    "overweight", 
    "old", 
    "ugly",
    "unassuming",
    "underweight", 
    "underage",
  });

  string *generic_profs = ({
    "architect",
    "archeologist",
    "artist",
    "bartender",
    "banker",
    "biologist",
    "bum",
    "child",
    "citizen",
    "civil servant",
    "clown",
    "dentist",
    "doctor",
    "drifter",
    "gardener",
    "kid",
    "lawyer",
    "leper",
    "librarian",
    "merchant",
    "mime",
    "miner",
    "painter",
    "pathologist",
    "politician",
    "plumber",
    "psychologist",
    "psychiatrist",
    "psychic",
    "refugee",
    "sculptor",
    "scientist",
    "singer",
    "street cleaner",
    "student",
    "teacher",
    "trader",
    "traveller",
    "tourist",
    "ventriloquist",
    "wanderer",
  });

  string *male_profs = ({
    "actor",
    "builder",
    "brick-layer",
    "construction worker",
    "cowboy",
    "craftsman",
    "farmer",
    "fisherman",
    "gladiator",
    "janitor",
    "man",
    "mountain climber",
    "pirate",
    "preacher",
    "priest",
    "salesman",
    "tailor",
    "waiter",
  });

  string *female_profs = ({
    "actress",
    "cowgirl",
    "dancer",
    "gypsy",
    "model",
    "nun",
    "saleswoman",
    "secretary",
    "supermodel",
    "woman",
    "waitress",
  });

  string *gen_plus_male = generic_profs + male_profs;
  string *gen_plus_female = generic_profs + female_profs;

reset(arg) {
  if (arg) return;
  set_name("randomizer");
  set_alias("bad randomizer");
  set_alt_name("hehe");
  set_short("a bad randomizer");
  set_long(
"This is a bad randomizer.\n"+
"It is used by the Bad coders for the monsters in the domain to give them \n"+
"a little variety.  \n"+
"\n"+
"Here are some commands for you:                                            \n"+
"  name <seed>    - to display a random name.                               \n"+
"  adj  <0|1>     - to display a random adjective.                          \n"+
"  padj <0|1>     - to display an adjective with \"A\" or \"An\" before it. \n"+
"  dadj <0|1>     - to dump all the adjectives in the array.                \n"+
"\n"+
"  [0 == adjectives that start with a consonant]                            \n"+
"  [1 == adjectives that start with a vowel]                                \n"+
"\n"+
"  prof <1|2>     - to display a profession. [male = 1 , female = 2]        \n"+
"  dprof <1|2>    - to dump all <num> profs. [male = 1 , female = 2]        \n"+
"\n"+
"Here are some help docs for you:                                           \n"+
"  help rand_use                                                            \n"+
"  help gimme_a_name                                                        \n"+
"  help gimme_an_adjective                                                  \n"+
"  help gimme_an_adj_phrase                                                 \n"+
"  help gimme_a_prof                                                        \n"+
"  help gimme_a_male_prof                                                   \n"+
"  help gimme_a_female_prof                                                 \n"+
"\n\n"
  );
  set_value(1);
  set_weight(1);
}

init() {
  ::init();
  add_action("do_name", "name");
  add_action("do_adj", "adj");
  add_action("do_padj", "padj");
  add_action("do_dadj", "dadj");
  add_action("do_prof", "prof");
  add_action("do_dprof", "dprof");
  add_action("do_help", "help");
}

do_adj(num) {
  write(gimme_an_adjective(num)+"\n");
  return 1;
}

do_padj(string num) {
  write(gimme_an_adj_phrase(num)+"\n");
  return 1;
}

do_dadj(num) {
  int i;
  
  if (num) {
    write("Adjectives that start with a vowel: \n");
    for (i = 0; i < sizeof(vowels); i++) {
      write(" "+vowels[i]);
    }
    write("\n");
  }
  else {
    write("Adjectives that start with a consonant: \n");
    for (i = 0; i < sizeof(consonants); i++) {
      write(" "+consonants[i]);
    }
    write("\n");
  }
  return 1;
}

do_prof(num) {
  write(gimme_a_prof(num)+"\n");
  return 1;
}

do_dprof(num) {
  int i;

  if (!num || num == "1") {
    write("Male profs: \n");
    for (i = 0; i < sizeof(gen_plus_male); i++) {
      write(" "+gen_plus_male[i]);
    }
    write("\n");
  }
  else {
    write("Female profs: \n");
    for (i = 0; i < sizeof(gen_plus_female); i++) {
      write(" "+gen_plus_female[i]);
    }
    write("\n");
  }
  return 1;
}

do_help(str) {
  if (!str) { return 0; }
  if (str == "gr_use" || 
      str == "gimme_a_name" || 
      str == "gimme_an_adjective" || 
      str == "gimme_an_adj_phrase" || 
      str == "gimme_a_prof" || 
      str == "gimme_a_male_prof" ||  
      str == "gimme_a_female_prof") {
    write(read_file(DOC+str));
    return 1;
  }
  return 0;
}

 
/* the cool stuff begins here */

gimme_an_adj_phrase(int a) {
  if(!a) {
    return "A "+gimme_an_adjective(0);
  }
  else {
    return "An "+gimme_an_adjective(1);
  }
}

gimme_an_adjective(int a) {
  if(!a) {
    adjective = consonants[random(sizeof(consonants))];
  }
  else {
    adjective = vowels[random(sizeof(vowels))];
  }
  return adjective;
}

gimme_a_male_prof() {
  string prof = gen_plus_male[random(sizeof(gen_plus_male))];

  return prof;
}

gimme_a_female_prof() {
  string prof = gen_plus_female[random(sizeof(gen_plus_female))];

  return prof;
}

gimme_a_prof(string a) {
  if (!a) {
    return gimme_a_male_prof();
  }
  if (a == "1") {
    return gimme_a_male_prof();
  }
  if (a == "2") {
    return gimme_a_female_prof();
  }
}

string seed_me() {
  string seed;
  int i;
  seed = (string)gimme_an_adjective(1);
  for (i = 0; i < random(10) + 2; i++) {
    seed += " ";
    seed += (string)gimme_an_adjective(1);
  }
  return seed;
}
  
gimme_a_name(str) {
  int i, valid;
  
  valid = 1;
  if(!str) {
    str = seed_me();
  }
  str = str+seed_me();
  str = crypt(str,1);
  str = lower_case(str);
  for(i = 0; i < strlen(str); i++) {
    if(str[i] < 'a' || str[i] > 'z') {
      str = str[0..(i-1)] + str[(i+1)..(strlen(str)-1)];
      i -= 1;
    }
  }
  i = 4 + random(5);
  if(valid) {
    str = str[0..i];
    return str;
  }
  else {
    return gimme_a_name();
  }
}

do_name(str) {
  if (!str) {
    str = seed_me();
  }
  write(gimme_a_name(str)+"\n");
  return 1;
}

string gimme_a_male_name() {
  string name;

  name = (string) gimme_a_name();
  name += "us";

  return name;
}

string gimme_a_female_name() {
  string name;

  name = (string) gimme_a_name();
  name += "ia";

  return name;
}

