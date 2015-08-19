// Stolen from Nightmare...hehe.
// Bart changed the buggy mapping thingy into an array.

#include "/wiz/b/bart/include/defines.h"
#define FISH ([ "mackeral":3, "blue fish":5, "flounder":12, "marlin":20, "swordfish":30 ])
inherit "/wiz/b/bart/std/outdoor_room";

mapping fish;
string *fishermen;
int s_f, g_f, max_catch, chance, caught, max_fishing;

int stop_fishing(string str);
void catch_anything(string who);
void still_fishing(string who);
void caught_something(string who);
void give_player_a_fish(string who, string fish_name, int strength);
int pole_breaks(int wt, string who);
void snap(string who);

reset(arg) {
  ::reset();
  if(arg) return;
  set_short("Fishing room");
  set_long("This is the inheritable fishing room.\n");
  add_exit("/wiz/b/bart/workroom","work");
  fishermen = 0;
  set_max_fishing(2);
  set_chance(20);
  set_max_catch(3);
}
  

init() {
  ::init();
  add_action("go_fish", "fish");
  add_action("dropped_the_pole", "drop");
  add_action("stop_fishing", "stop");
}

bad_tell_room(object room, string message, object fisherman) {
  int i;
  object *other;
  other = all_inventory(room);
 
  for(i = 0; i < sizeof(other); i++) {
    if(query_ip_number(other[i]) && other[i] != fisherman) {
      tell_object(other[i],message);
    }
  }
}

int go_fish() {
  object ob;

  if(!fishermen) {
    fishermen = ({ });
  }
  ob = present("fishing_pole", this_player());
  if(!ob) {
	  notify_fail("You really need something to fish with!\n");
	  return 0;
  }
  if(ob->query_broken()) {
	  notify_fail("You cannot fish while your "+ob->query_name()+" is broken!\n");
	  return 0;
  }
  if(member_array(this_player()->query_real_name(),fishermen) != -1) {
	  notify_fail("You are already fishing!\n");
	  return 0;
  }
  if(max_fishing <= sizeof(fishermen)) {
  	write("The area is simply too crowded with people fishing right now.\n");
	  say(CTPQN+" is unable to find a spot to fish.\n");
	  return 1;
  }
  if(!ob->query_bait()) {
	  notify_fail("Don't you dare to fish without a bait!\n");
	  return 0;
  }
  if(!this_player()->query_intoxication()) {
	  notify_fail("What good is fishing without being intoxicated?\n");
	  return 0;
  }
  write("You cast your "+ob->query_name()+" into the water and start fishing.\n");
  say(CTPQN+" casts "+this_player()->query_possessive()+" "+ob->query_name()+" into the water.\n");
  fishermen += ({ this_player()->query_real_name() });
  g_f = set_alarm(10.0, 0.0, "catch_anything", this_player()->query_real_name());
  return 1;
}

int dropped_the_pole(string str) {
  if(!fishermen) return 0;
  if(member_array(this_player()->query_real_name(),fishermen) < 0) return 0;
  if(stop_fishing("fishing")) return 0;
  else {
	  write("You cannot drop it!\n");
	  return 1;                /* Why would this happen? */
  }
}

int stop_fishing(string str) {
  if(!str || str != "fishing") return 0;
  if(!fishermen) {
  	notify_fail("You are not fishing!\n");
	  return 0;
  }
  if(str == "fishing") {
    if(member_array(this_player()->query_real_name(),fishermen) == -1) {
      write("You are not fishing!\n");
      return 1;
    }
    fishermen -= ({ this_player()->query_real_name() });
    write("You stand up and pull in your line.\n");
    say(CTPQN+" gives up on fishing for now.\n");
    remove_alarm(s_f);
    remove_alarm(g_f);
    return 1;
  }
  return 0;
}

void catch_anything(string who) {
  int bait, class;

  if(!who) return;        /* how in hell did this happen? */
  if(!present(who)) {
    fishermen -= ({ who });
    return;
  }
  if(member_array(who,fishermen) < 0) return;
  bait = present("fishing_pole",present(who))->query_bait();
  class = present("fishing_pole",present(who))->query_pole_class();
  if( (caught == max_catch) || (random(101) > chance+class+bait) ) {
  	still_fishing(who);
  }
  else { 
    caught_something(who);
  }
}

void still_fishing(string who) {
  tell_object(present(who), "You pull in your line and cast again, hoping for better luck this time.\n");
  bad_tell_room(this_object(), CAP(who)+" pulls in "+this_player()->query_possessive()+" line and then casts again.\n", present(who));
  s_f = set_alarm(10.0, 0.0, "catch_anything", who);
}

void caught_something(string who) {
  string fish_name;

  if(!fish) fish = FISH;
  fish_name = m_indexes(fish)[random(m_sizeof(fish))];
  tell_object(present(who), "Suddenly you feel something tug at your "+present("fishing_pole",present(who))->query_name()+"!\n");
  tell_object(present(who), "You see a "+fish_name+" fighting on your hook!\n");
  bad_tell_room(this_object(), "Something tugs at "+CAP(who)+"'s line!\n", present(who));
  bad_tell_room(this_object(), CAP(who)+" has hooked a "+ fish_name+"!\n", present(who));
  give_player_a_fish(who, fish_name, fish[fish_name]);
}

void give_player_a_fish(string who, string fish_name, int strength) {
  object this_catch;

  if(!pole_breaks(strength, who)) {
  	this_catch = make("/std/healing/food");
	  this_catch->set_name(fish_name);
	  this_catch->set_alias("fish");
 	  this_catch->set_short("a "+fish_name);
	  this_catch->set_long("A smelly "+fish_name+" caught by "+who+"!\n");
    this_catch->set_strength(strength);
	  this_catch->set_value(0);
    this_catch->set_weight(1);
	  transfer(this_catch,(present(who)));
  }
  else {
    snap(who);
  }
  present("fishing_pole",present(who))->unbait();
  caught ++;
  fishermen -= ({ who });
}

int pole_breaks(int wt, string who) {
  int max_wt, class;

  class = present("fishing_pole",present(who))->query_pole_class();
  max_wt = (class - 1) * (class - 1);
  if(max_wt < wt) return 1;
  else return 0;
}

void snap(string who) {
  present("fishing_pole",present(who))->break_pole();
  tell_object(present(who), "The fish is so big, it breaks your "+present("fishing_pole",present(who))->query_name()+"!\n");
  bad_tell_room(this_object(), CAP(who)+" catches a fish so big that it breaks "+present(who)->query_possessive()+" "+present("fishing_pole",present(who))->query_name()+"!\n", present(who));
}

void set_max_fishing(int x) {
  if(x>10) x=10;
  max_fishing = x;
}

int query_max_fishing() { return max_fishing; }

void set_chance(int x) { 
  if(x > 20) x=20;
  chance = x;
}

int query_chance() { return chance; }

void set_max_catch(int x) { max_catch = x; }

int query_max_catch() { return max_catch; }

void set_fish(mapping borg) { fish = borg; }

mapping query_fish() { return fish; }

void add_fish(string nom, int x) {
  if(!fish) fish = ([]);
  fish[nom] = x;
}

