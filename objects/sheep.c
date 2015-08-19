#include "/wiz/b/bart/include/defines.h"
#include <levels.h>
inherit "/std/obj/treasure";

status sheeptalk = 0;

init_arg() {
  tell_object(this_player(), "Cloned: a little blue sheep.\n");
  return 1;
}

reset(arg) {
  if (arg) return;
  set_name("sheep");
  set_alias("sheeplatin");
  set_alt_name("sheeplatinlanguage");
  set_short("a little blue sheep");
  set_long(
"This is the prototype sheeplatin language filter.\n"+
"It will let you communicate (ssay/stell/swiz) in a different language.\n"+
"Only those with little blue sheep will understand what you say or tell.\n");
  set_value(0);
  set_weight(0);
}

int drop() { return 1; }
int get() { return 0; }

init() {
  ::init();
  add_action("do_ssay","ssay");
  add_action("do_stell","stell");
  add_action("do_stell","sask");
  add_action("do_swiz","swiz");
}

do_ssay(str) {
  int i;
  object *people;
  string last, letter, original, result, tmpword, word;
  if(!str) {
    return 0;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))/2];
    tmpword = word[(strlen(word))/2..(strlen(word))];
    word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))/2];
  tmpword = str[(strlen(str))/2..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    tmpword = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    tmpword = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    tmpword = str[1..strlen(str)-2];
  }
  word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a";
  word = lower_case(word);
  result += word;
  write("You mumble: "+result+""+last+"\n");
  say(CTPQN+" mumbles: "+result+""+last+"\n");
  people = all_inventory(environment(this_player()));
  for (i = 0; i < sizeof(people); i++) {
    if(present("sheeplatinlanguage",people[i]) &&
       this_player() != people[i]) {
      tell_object(people[i],CTPQN+"'s sheeplatin roughly translates to: \""+original+"\"\n");
    }
  }
  return 1;
}

do_stell(str) {
  int i;
  object target;
  string letter, last, result, original, tmpword, who, word;
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
    word = word[1..(strlen(word))/2];
    tmpword = word[(strlen(word))/2..(strlen(word))];
    word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))/2];
  tmpword = str[(strlen(str))/2..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    tmpword = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    tmpword = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    tmpword = str[1..strlen(str)-2];
  }
  word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a";
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
  if(present("sheeplatinlanguage",target)) {
    tell_object(target,CTPQN+"'s sheeplatin roughly translates to: \""+original+"\"\n");
  }
  return 1;
}

do_swiz(str) {
  int i;
  object *wizzies;
  string letter, last, result, original, tmpword, who, word;
  if(!str) {
    notify_fail("Swiz what?\n");
    return 0;
  }
  original = str;
  result = "";
  while(sscanf(str,"%s %s", word, str)) {
    letter = word[0..0];
    word = word[1..(strlen(word))/2];
    tmpword = word[(strlen(word))/2..(strlen(word))];
    word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a ";
    word = lower_case(word);
    result += word;
  }
  letter = str[0..0];
  word = str[1..(strlen(str))/2];
  tmpword = str[(strlen(str))/2..(strlen(str))];
  last = ".";
  if(str[strlen(str)-1] == '?') {
    tmpword = str[1..strlen(str)-2];
    last = "?";
  }
  if(str[strlen(str)-1] == '!') {
    tmpword = str[1..strlen(str)-2];
    last = "!";
  }
  if(str[strlen(str)-1] == '.') {
    tmpword = str[1..strlen(str)-2];
  }
  word = tmpword+"r"+word+"s"+letter+"t"+tmpword+"a";
  word = lower_case(word);
  result += word;

  wizzies = users();

  for (i = 0; i < sizeof(wizzies); i++) {
    if (wizzies[i]->query_level() > MAXMORTAL &&
        wizzies[i]->member_chatline("wiz")) {
      tell_object(wizzies[i], "[Wiz]: "+CTPQN+" mumbles: "+result+""+last+"\n");
      if(present("sheeplatinlanguage",wizzies[i])) {
        tell_object(wizzies[i], CTPQN+"'s sheeplatin roughly translates to: \""+original+"\"\n");
      }
    }
  }
  return 1;
}

query_auto_load() {
  return "/wiz/b/bart/objects/sheep:";
}

