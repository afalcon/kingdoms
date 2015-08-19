#include "/wiz/b/bart/include/defines.h"
inherit "/std/obj/treasure";

int pole_class;
 
int query_bait();
int query_pole_class();
int query_broken();
int break_pole();
void unbait();
int broken;
int bait;
 
void init() {
  add_action("bait_it","bait");
  add_action("do_look","look");
}
 
reset(arg) {
  if(arg) return;
  set_name("stick");
  set_alias("fishing_pole");
  set_long("A bamboo stick with a piece of string connected to the end.\nAt the end of the string is a hook.  What a primitive looking fishing tool!\n");
  set_value(20);
  set_weight(2);
  broken = 0;
  bait = 0;
}
 
do_look(string str) {
  if(str == "at hook") {
    if(!bait) {
      write("Perhaps you could bait this with something?\n");
      return 1;
    }
    else {
      write("It has bait on it.\n");
    }
  }
  else {
    if(str == "at string") {
      write("A string with a hook at the end.\n");
      return 1;
    }
    else {
      return 0;
    }
  }
}
 
short() {
  if(!broken) {
    if(!bait) {
      return "A bamboo stick";
    }
    else {
      return "A bamboo stick (baited)";
    }
  }
  else { 
    return "A bamboo stick (broken)";
  }
}

int set_pole_class(int num) {
  pole_class = num;
}

int query_pole_class() {
  if(!pole_class) {
    return 2;
  }
  else {
    return pole_class;
  }
}
 
int query_bait() {
  return bait;
}
 
int bait_it(string str) {
  string pole, the_bait;
  object hmm;
  if(!str) return 0;
  if((sscanf(str, "%s with %s", pole, the_bait)) !=2) return 0;
  if(pole != "stick" && pole != "hook") return 0;
  if(!present(the_bait,this_player())) {
    write("You do not have any "+the_bait+" to bait your stick!\n");
    return 1;
  }
  if(!(present(the_bait,this_player())->query_bait())) {
    write("You can't use that as bait!\n");
    return 1;
  }
  if(!bait) {
    bait = (100-(int)present(the_bait, this_player())->query_strength())/7;
    write("You bait your hook with "+the_bait+".\n");
    say(CTPQN+" baits "+(string)this_player()->query_possessive()+" stick.\n");
    hmm = present(the_bait, this_player());
    hmm->destroy();
    return 1;
  }
  else {
    write("You already have bait on your hook!\n");
  }
  return 1;
}

void unbait() {
  bait = 0;
}
 
int query_broken(){
  return broken;
}
 
int break_pole() {
  set_value(10);
  broken = 1;
}
 
