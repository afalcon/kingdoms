#define CITY "Oinkland"
#include "/wiz/b/bart/include/defines.h"
inherit "/std/living/moving_monster";

object thing;
string desc, occ, name, type;
int adjust;

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_level(1 + random(10) + random(10));
  desc = RAND->gimme_an_adjective();
  if (random(2)) {
    set_gender(1);
    name = RAND->gimme_a_male_name();
    occ = RAND->gimme_a_male_prof();
  }
  else {
    set_gender(2);
    name = RAND->gimme_a_female_name();
    occ = RAND->gimme_a_female_prof();
  }
  set_name(name);
  set_short(CAP(name)+" the "+desc+" "+occ);
  set_long(
CAP(name)+ " the "+desc+" "+occ+" is a person in your neighborhood.\n"+
CAP(this_object()->query_pronoun())+"'s a person that you meet, when you're walking down the street.\n"+
CAP(this_object()->query_pronoun())+"'s a person that you meet each day.\n");
  set_alias(occ);
  set_alt_name(desc+" "+occ);
  set_race("human");
  set_hp((this_object()->query_level() * 7) + 50 + random(50));
  set_al(0);
  adjust = this_object()->query_level() * 3;
  this_object()->set_str(adjust);
  this_object()->set_dex(adjust);
  this_object()->set_int(adjust);
  this_object()->set_con(adjust);
  this_object()->set_siz(adjust);
  this_object()->set_res(adjust);
  this_object()->set_elo(adjust);
  this_object()->set_mem(adjust);
  this_object()->set_dic(adjust);
  this_object()->set_qui(adjust);
  set_wc((this_object()->query_level() * 9)  + random(50));
  set_new_ac(this_object()->query_level() + 9 + random(9));
  set_skill("combat", this_object()->query_level() * 9);
  set_skill("unarmed", this_object()->query_level() * 9);
  set_skill("perception", this_object()->query_level() * (3 + random(5)));
  set_skill("resist", this_object()->query_level() * (3 + random(5)));
  add_money((this_object()->query_level() * 7) + 25 + random(100));
  load_chat(1, 
    ({
      CAP(name) + " smiles at you.\n",
      CAP(name) + " looks at the sky.\n",
      CAP(name) + " looks at the sky.\n",
      CAP(name) + " looks at the clouds.\n",
      CAP(name) + " looks at you.\n",
      CAP(name) + " taps you on the shoulder.\n",
      CAP(name) + " shakes your hand.\n",
      CAP(name) + " pushes your nose and BEEP\a.\n",
      CAP(name) + " tells you: Hey, baby.\n",
      CAP(name) + " slaps you!\n",
      CAP(name) + " spits on the ground.\n",
      CAP(name) + " bonks you on the head.\n",
      CAP(name) + " pats you on the head.\n",
      CAP(name) + " sins.\n",
      CAP(name) + " screams loudly.\n",
      CAP(name) + " says: Everybody wants a rock to wind a piece of string around.\n",
      CAP(name) + " says: Everybody wants prosthetic foreheads on their real heads.\n",
      CAP(name) + " says: I'm kinda depressed, this job just isn't working out.\n",
      CAP(name) + " says: Boy it sure is a nice day today, isn't it?\n",
      CAP(name) + " asks: How long have you been in town?\n",
      CAP(name) + " says: I hope you enjoy your stay here.\n",
      CAP(name) + " says: Ack.\n",
      CAP(name) + " says: Ack, I think I'm in love with you.\n",
      CAP(name) + " says: I wish it would rain all the time.\n",
      CAP(name) + " says: Damn, I need to find a bathroom fast.\n",
      CAP(name) + " says: I need some beer.\n",
      CAP(name) + " says: I think I'm lost.\n",
      CAP(name) + " asks: Do you know where the hospital is?\n",
      CAP(name) + " asks: Do you know where the mansion is?\n",
      CAP(name) + " asks: Do you know where the market is?\n",
      CAP(name) + " asks: Do you know where the cathedral is?\n",
      CAP(name) + " asks: Do you know where the park is?\n",
      CAP(name) + " asks: Do you know where the theater is?\n",
      CAP(name) + " asks: Do you know where the school is?\n",
      CAP(name) + " asks: Do you know where the library is?\n",
      CAP(name) + " asks: Do you know where the toilet is?\n",
      CAP(name) + " asks: Do you know where the carnival is?\n",
      CAP(name) + " asks: Do you know where the arena is?\n",
    })
  );
  load_a_chat(5, 
    ({
      CAP(name) + " says: You ungrateful little sh*t.\n",
    })
  );
  if (!random(3)) {
    thing = clone_object (STD + "weapon");
    thing->calculate(this_object()->query_level());
    transfer(thing, this_object());
    init_command("wield "+lower_case(thing->query_name()));
  }
  if (!random(3)) {
    thing = clone_object (STD + "armour");
    switch (random(6)) {
      case 1: type = "shield"; break;
      case 2: type = "cloak"; break;
      case 3: type = "glove"; break;
      case 4: type = "boot"; break;
      case 5: type = "legging"; break;
      default: type = "helmet"; break; 
    }
    thing->calculate(type, this_object()->query_level());
    transfer(thing, this_object());
    init_command("wear all");
  }
  set_time_slice(20);
  set_walking();
}

