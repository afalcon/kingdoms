#include "/wiz/b/bart/include/defines.h"
inherit "/std/living/monster";

object thing;
string t;
int i;

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_name("mega-soldier");
  set_alias("soldier");
  set_level(1 + random(10) + random(10));
  if (random(2)) {
    set_short("A male mega-soldier");
    set_long("He is a soldier.\n");
    set_alt_name("male");
    set_gender(1);
  }
  else {
    set_short("A female mega-soldier");
    set_long("She is a soldier.\n");
    set_alt_name("female");
    set_gender(2);
  }
  set_race("human");
  set_hp((this_object()->query_level() * 10) + 50 + random(50));
  set_al(0);
  set_wc((this_object()->query_level() * 10)  + random(50));
  set_new_ac(this_object()->query_level() + 10 + random(10));
  set_unarmed(this_object()->query_level() * 10);
  set_skill("combat", this_object()->query_level() * 10);
  set_skill("longblade", this_object()->query_level() * 10);
  set_skill("perception", this_object()->query_level() * 10);
  set_skill("resist", this_object()->query_level() * 10);
  add_money((this_object()->query_level() * 10) + 25 + random(100));
  load_chat(1, 
    ({
      "A mega-soldier struts proudly.\n",
      "A mega-soldier flexes "+this_object()->query_possessive()+" muscles.\n",
    })
  );
  load_a_chat(5, 
    ({
      "A mega-soldier yells: Die! Die! Die!\n",
      "A mega-soldier exclaims: That must hurt!\n",
      "A mega-soldier asks: Are you still alive?\n",
    })
  );
  thing = clone_object (WEA + "std_sword");
  thing->calculate(this_object()->query_level());
  transfer(thing, this_object());
  init_command("wield sword");
  thing = clone_object (ARM + "std_plate");
  thing->calculate(this_object()->query_level());
  transfer(thing, this_object());
  for (i = 0; i < 6; i++) {
    thing = clone_object (ARM + "std_armour");
    switch (i) {
      case 0: t = "shield"; break;
      case 1: t = "cloak"; break;
      case 2: t = "glove"; break;
      case 3: t = "boot"; break;
      case 4: t = "legging"; break;
      default: t = "helmet"; break; 
    }
    thing->calculate(t, this_object()->query_level());
    transfer(thing, this_object());
  }
  init_command("wear all");
}
