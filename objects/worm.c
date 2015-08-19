#include "/wiz/b/bart/include/defines.h"
inherit "/std/obj/treasure";
 
reset(arg) {
  if(arg) return;
  set_name("worm");
  set_alias("the_bait");
  set_short("A worm");
  set_long("Use it for bait.\n");
  set_value(2);
  set_weight(1);
}

query_bait() { return 1; }
