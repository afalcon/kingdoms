#include "/wiz/b/bart/include/defines.h"
inherit "/std/obj/armour";

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_name("jumpsuit");
  set_alias("jumpsuit");
  set_short("an official "+CITIZEN+" jumpsuit");
  set_long("It is a very unique and special jumpsuit, made from fine Kohoutek fabrics. It's the only one of it's kind in the world.\n");
  set_value(200 + random(200));
  set_weight(3);
  set_new_ac(5);
  set_db(0);
  set_type("armour");
  set_material("cloth");
}

