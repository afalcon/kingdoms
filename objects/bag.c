#include <levels.h>
inherit "/std/clone/bag";

init_arg() {
  tell_object(this_player(), "Cloned: a little blue bag.\n");
  return 1;
}

reset(arg) {
  if (arg) return;
  set_name("bag");
  set_value(0);
  set_weight(0);
}

short() {
 return "a little blue bag";
}

long() {
  write("This is a little blue bag.\nType \"bag <name>\" to bag someone.\n");
  return 1;
}

int drop() { return 1; }
int get() { return 0; }

init() {
  if(environment(this_object())->query_level() < NEWBIE) {
    write("A little blue bag says: Hehehe.\n");
    this_object()->destroy();
  }
  add_action("do_bag","bag");
  add_action("do_back","back");
  add_action("do_look","look");
}

do_bag(str) {
  object bagged;
  if(!str) {
    notify_fail("You goofball!\n");
    return 0;
  }
  str = lower_case(str);
  if(str == "bart") {
    write("You goofball!\n");
    return 1;
  }
  bagged = find_player(str);
  if(!bagged) {
    write("Can't find "+capitalize(str)+", dude.\n");
    return 1;
  }
  else {
    transfer(bagged, this_object());
    write("Moved "+capitalize(bagged->query_real_name())+" to a little blue bag.\n");
    say(this_player()->query_name()+" stuffs "+capitalize(bagged->query_real_name())+" in "+this_player()->query_possessive()+" little blue bag.\n");
    return 1;
  }
}

do_back() {
  if(this_player()->query_last_room()) {
    transfer(this_player(),this_player()->query_last_room());
  }
  else {
    transfer(this_player(),"/areas/Lars/Lars/o/Rooms/church");
  }
  write("Ok.\n");
  return 1;
}

do_look() {
  if(present(this_player(),this_object())) {
    write("Hehe, don't get mad, get bagged.\n");
    write("Type \"back\" to get back to your previous room.\n");
    return 0;
  }
  return 0;
}

query_auto_load() {
  return "/wiz/b/bart/objects/bag:";
}

