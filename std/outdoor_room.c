#include "/wiz/b/bart/include/defines.h"
inherit "/std/room/doorroom";

void my_tell_room(object room, string message, object me) {
  object *people;
  int i;

  people = all_inventory(room);
  for (i = 0; i < sizeof(people); i++) {
    if(interactive(people[i]) && people[i] != me) {
      tell_object(people[i], message);
    }
  }
}

string room_desc;
string who;

query_room_desc() { 
  if (!room_desc) {
    return 0;
  }
  else {
    return room_desc; 
  }
}

set_room_desc(str) { 
  room_desc = str; 
  set_long(str);
  set_alarm(2.0,0.0,"new_desc",this_object());
}

new_desc(object ob) {
  "/wiz/b/bart/rooms/weather_control"->update_room(ob);
}

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_light(1);
  set_short("Outdoor inherit room");
  add_property("no_sun_msg");
  add_property("no_sky_msg");
  "/wiz/b/bart/rooms/weather_control"->add_room(this_object());
}

init() {
  ::init();
  add_action("do_snow_throw","throw"); 
}

add_lamps() {
  add_item("lamp|lamps|street lamp|street lamps",do_lamp());
}

string do_lamp() {
  string desc;
  if(query_daylight()) {
    desc = "The street lamps aren't lit";
  }
  else {
    desc = "The street lamps provide enough lighting to let you see where you're walking";
  }
  return desc;
}

do_snow_throw(str) {
  int i;
  object people, victim;
  string what;

  if(!str) {
    return 0;
  }

  if(sscanf(str, "%s at %s",what,who) != 2) {
    notify_fail("Throw snow at who?\n");
    return 0;
  }

  if(what != "snow" && what != "snowball") {
    notify_fail("You throw "+what+" at "+who+".\n");
    return 0;
  }

  if("/wiz/b/bart/rooms/weather_control"->query_current_state() != 10) {
    write("What?\n");
    return 1;
  }

  who = lower_case(who);
  if(who == this_player()->query_real_name()) {
    write("You smack yourself with a snowball.  Wheeeeeeeeeee!.\n");
    say(CTPQN+" smacks "+this_player()->query_objective()+"self with a snowball.  What a goofball!\n");
    return 1;
  }

  victim = find_living(who);
  if(!present(who,environment(this_player())) || !victim) {
    notify_fail(CAP(who)+" is not here, so you throw the snowball up in the air and catch it with your face.\n");
    return 0;
  }
  people = all_inventory(environment(this_player()));
  for(i = 0; i < sizeof(people); i++) {
    if(people[i] != this_player() && people[i] != victim) {
      tell_object(people[i], CAP(this_player()->query_name())+" throws a snowball at "+CAP(who)+".\n");
    }
  }
  write("You bean "+CAP(who)+" with a wicked snowball!\n");
  tell_object(victim, CAP(this_player()->query_name())+" smacks you with a snowball!\n");
  return 1;
}

