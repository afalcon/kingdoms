#include "/wiz/b/bart/include/defines.h"
#include <levels.h>
inherit "/std/obj/treasure";

#include "/wiz/b/bart/include/nadsat.h"

init_arg() {
  tell_object(this_player(), "Cloned: a little orange tongue.\n");
  return 1;
}

reset(arg) {
  if (arg) return;
  set_name("tongue");
  set_alias("nadsat");
  set_short("a little orange tongue");
  set_long(
"This is a clockwork orange nadsat language filter.\n"+
"It will let you communicate (osay/otell/owiz) in a different language.\n"+
"Only those with orange filters will understand what you say or tell.\n");
  set_value(0);
  set_weight(0);
}

int drop() { return 1; }
int get() { return 0; }

init() {
  ::init();
  add_action("do_osay","osay");
  add_action("do_otell","otell");
  add_action("do_otell","oask");
  add_action("do_owiz","owiz");
}

check_word(str) {
  if(dictionary[str]) {
    return dictionary[str];
  }
  else {
    return str;
  }
}

do_osay(str) {
  int i;
  object *people;
  string *words;
  string original, result;
  if(!str) {
    return 0;
  }
  words = explode(str, " ");
  result = "";
  for (i = 0; i < sizeof(words); i++) {
    result += check_word(words[i])+" ";
  }
  write("You skazat: "+result+"\n");
  say(CTPQN+" skazats: "+result+"\n");
  people = all_inventory(environment(this_player()));
  for (i = 0; i < sizeof(people); i++) {
    if(present("nasdat",people[i]) &&
       this_player() != people[i]) {
      tell_object(people[i],CTPQN+"'s nasdat roughly translates to: \""+original+"\"\n");
    }
  }
  return 1;
}

do_otell(str) {
  int i;
  object target;
  object *people;
  string *words;
  string who, original, result;
  if(!str) {
    return 0;
  }
  if(sscanf(str,"%s %s", who, str) != 2) { 
    write(CAP(query_verb())+" who?\n");
    return 1;
  }
  target = find_living(lower_case(who));
  if(!target) {
    write(CAP(who)+" is not here.\n");
    return 1;
  }
  original = str;
  words = explode(str, " ");
  result = "";
  for (i = 0; i < sizeof(words); i++) {
    result += check_word(words[i])+" ";
  }
  if(this_player()->query_talk_pool() < 5) {
    write("You are low on talk points.\n");
    return 1;
  }
  if(target->query_level() <= MAXMORTAL &&
     this_player()->query_level() <= MAXMORTAL) {
    this_player()->add_talk_pool(-5);
  }
 
  write("You "+query_verb()+" "+target->query_name()+": "+result+"\n");
  tell_object(target, CTPQN+" "+query_verb()+"s you: "+result+"\n");
  if(present("nadsat",target)) {
    tell_object(target,CTPQN+"'s nadsat roughly translates to: \""+original+"\"\n");
  }
  return 1;
}

do_owiz(str) {
  int i;
  object *wizzies;
  object *people;
  string *words;
  string original, result;
  if(!str) {
    notify_fail("Pwiz what?\n");
    return 0;
  }
  original = str;
  words = explode(str, " ");
  result = "";
  for (i = 0; i < sizeof(words); i++) {
    result += check_word(words[i])+" ";
  }

  wizzies = users();

  for (i = 0; i < sizeof(wizzies); i++) {
    if (wizzies[i]->query_level() > MAXMORTAL &&
        wizzies[i]->member_chatline("wiz")) {
      tell_object(wizzies[i], "[Wiz]: "+CTPQN+" skazats: "+result+"\n");
      if(present("nadsat",wizzies[i])) {
        tell_object(wizzies[i], CTPQN+"'s nadsat roughly translates to: \""+original+"\"\n");
      }
    }
  }
  return 1;
}

query_auto_load() {
  return "/wiz/b/bart/objects/tongue:";
}

