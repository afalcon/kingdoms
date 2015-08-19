#include "/wiz/b/bart/include/defines.h"
inherit "/std/obj/treasure";

reset(arg) {
  if (arg) return;
  set_name("map");
  set_short("a map");
  set_long("It's a map of Ignoreland.\n");
  set_value(1);
  set_weight(1);
}

init() {
  ::init();
  add_action("do_read","read");
}

do_read(str) {
  if(!str) {
    return 0;
  }
  if(str == "map" || str == "ignoreland map" || str == "map of ignoreland") {
    write(read_file(DOC + "map"));
    say(CAP(this_player()->query_name())+" looks over a map of Ignoreland.\n");
    return 1;
  }
  return 0;
}
