#include "/wiz/b/bart/include/defines.h"
#include <levels.h>
inherit "/std/obj/treasure";

status pigtalk = 0;

init_arg() {
  tell_object(this_player(), "Cloned: a little blue pig.\n");
  return 1;
}

reset(arg) {
  if (arg) return;
  set_name("pig");
  set_alias("piglatin");
  set_alt_name("piglatinlanguage");
  set_short("a little blue pig");
  set_long(
"This is the prototype piglatin language filter.\n"+
"It will let you communicate (psay/ptell/pwiz) in a different language.\n"+
"Only those with little blue pigs will understand what you say or tell.\n");
  set_value(0);
  set_weight(0);
}

int drop() { return 1; }
int get() { return 0; }

init() {
  ::init();
  add_action("do_psay","psay");
  add_action("do_ptell","ptell");
  add_action("do_ptell","pask");
  add_action("do_pwiz","pwiz");
}

do_psay(str) {
  int i;
  object *people;
  string letter, word, original, result, last;
  if(!str) {
    return 0;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))];
    word = word+letter+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    word = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    word = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    word = str[1..strlen(str)-2];
  }
  word = word+letter+"a";
  word = lower_case(word);
  result += word;
  write("You mumble: "+result+""+last+"\n");
  say(CTPQN+" mumbles: "+result+""+last+"\n");
  people = all_inventory(environment(this_player()));
  for (i = 0; i < sizeof(people); i++) {
    if(present("piglatinlanguage",people[i]) &&
       this_player() != people[i]) {
      tell_object(people[i],CTPQN+"'s piglatin roughly translates to: \""+original+"\"\n");
    }
  }
  return 1;
}

do_ptell(str) {
  int i;
  object target;
  string letter, last, result, original, who, word;
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
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))];
    word = word+letter+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    word = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    word = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    word = str[1..strlen(str)-2];
  }
  word = word+letter+"a";
  word = lower_case(word);
  result += word;
  if(this_player()->query_talk_pool() < 5) {
    write("You are low on talk points.\n");
    return 1;
  }
  if(target->query_level() <= MAXMORTAL &&
     this_player()->query_level() <= MAXMORTAL) {
    this_player()->add_talk_pool(-5);
  }
 
  write("You "+query_verb()+" "+target->query_name()+": "+result+""+last+"\n");
  tell_object(target, CTPQN+" "+query_verb()+"s you: "+result+""+last+"\n");
  if(present("piglatinlanguage",target)) {
    tell_object(target,CTPQN+"'s piglatin roughly translates to: \""+original+"\"\n");
  }
  return 1;
}

do_pwiz(str) {
  int i;
  object *wizzies;
  string letter, last, result, original, who, word;
  if(!str) {
    notify_fail("Pwiz what?\n");
    return 0;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))];
    word = word+letter+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    word = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    word = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    word = str[1..strlen(str)-2];
  }
  word = word+letter+"a";
  word = lower_case(word);
  result += word;

  wizzies = users();

  for (i = 0; i < sizeof(wizzies); i++) {
    if (wizzies[i]->query_level() > MAXMORTAL &&
        wizzies[i]->member_chatline("wiz")) {
      tell_object(wizzies[i], "[Wiz]: "+CTPQN+" mumbles: "+result+""+last+"\n");
      if(present("piglatinlanguage",wizzies[i])) {
        tell_object(wizzies[i], CTPQN+"'s piglatin roughly translates to: \""+original+"\"\n");
      }
    }
  }
  return 1;
}

query_auto_load() {
  return "/wiz/b/bart/objects/pig:";
}

