#define CITY "Oinkland"
#include "/wiz/b/bart/include/defines.h"
inherit "/std/living/monster";

object thing;
string desc, t;
int adjust;

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_name("soldier");
  set_level(1 + random(10) + random(10));
  if (random(2)) {
    set_gender(1);
  }
  else {
    set_gender(2);
  }
  desc = RAND->gimme_an_adjective();
  set_short("A "+desc+" "+this_object()->query_gender_string()+" soldier");
  set_long(CAP(this_object()->query_pronoun())+ " is one of the many "+desc+" soldiers that partol "+CITY+".\n");
  set_alias(this_object()->query_gender_string());
  set_alt_name(this_object()->query_gender_string()+ " soldier");
  set_race("human");
  set_hp((this_object()->query_level() * 5) + 50 + random(50));
  set_al(0);
  adjust = (this_object()->query_level() * 3 ) / 2;
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
  set_wc((this_object()->query_level() * 5)  + random(50));
  set_new_ac(this_object()->query_level() + 5 + random(5));
  set_unarmed(this_object()->query_level() * 5);
  set_skill("combat", this_object()->query_level() * 8);
  set_skill("longblade", this_object()->query_level() * 7);
  set_skill("shieldbash", this_object()->query_level() * 7);
  set_skill("perception", this_object()->query_level() * (3 + random(5)));
  set_skill("resist", this_object()->query_level() * (3 + random(5)));
  add_money((this_object()->query_level() * 5) + 25 + random(100));
  load_chat(1, 
    ({
      "A soldier yawns.\n",
      "A soldier says: Hey, what's up?\n",
      "A soldier paces back an forth.\n",
      "A soldier trips and falls on "+this_object()->query_possessive()+" face.\n",
      "A soldier slaps you!\n",
      "A soldier says: Hey you, stop picking your nose.\n",
      "A soldier says: Hey you, stop loitering.\n",
      "A soldier looks at you.\n",
      "A soldier smiles happily at you.\n",
      "A soldier bows gracefully before you.\n",
    })
  );
  load_a_chat(5, 
    ({
      "Soldier says: You seem to be losing a lot of blood there.\n",
      "Soldier exclaims: Ouch! That hurts!\n",
      "Soldier asks: Why did I ever take this job?\n",
    })
  );
  thing = clone_object (STD + "sword");
  thing->calculate(this_object()->query_level());
  transfer(thing, this_object());
  init_command("wield sword");
  thing = clone_object (STD + "plate");
  thing->calculate(this_object()->query_level());
  transfer(thing, this_object());
  thing = clone_object (STD + "armour");
  switch (random(6)) {
    case 1: t = "shield"; break;
    case 2: t = "cloak"; break;
    case 3: t = "glove"; break;
    case 4: t = "boot"; break;
    case 5: t = "legging"; break;
    default: t = "helmet"; break; 
  }
  thing->calculate(t, this_object()->query_level());
  transfer(thing, this_object());
  init_command("wear all");
}

