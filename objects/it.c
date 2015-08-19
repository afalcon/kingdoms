#pragma strict_types
inherit "/std/obj/treasure";

string old;

void create_object(void) {
  set_name("thissillypersonisit");
  set_value(0);
  set_weight(0);
}

int drop() { return 1; }
int get() { return 0; }

void init() {
  ::init();
  write("You're IT!!!\n");
  add_action("do_tag","tag");
}

int do_tag(string str) {
  object who;
  who = find_player(lower_case(str));

  if(!str) {
    notify_fail("Tag who? You goofball.\n");
    return 0;
  }
  if(!who) {
    notify_fail(capitalize(str)+" isn't logged on, dude.\n");
    return 0;
  }
  if(who == this_player()) {
    notify_fail("Cheater! You can't do that anymore. Hee hee.\n");
    return 0;
  }
  if(!present(who,environment(environment(this_object())))) {
    notify_fail(capitalize(str)+" isn't here right now, dude.\n");
    return 0;
  }
  if(!present("bartslovelygameoftag",who)) {
    notify_fail(capitalize(str)+" is not a TAG player. What a pooper!\n");
    return 0;
  }
  if (old == who->query_real_name()) {
    notify_fail(capitalize(str)+" just tagged you...you can't tag "+who->query_objective()+" back, dude.\n");
    tell_object(who,capitalize(this_player()->query_name())+" tried to tag you back, what a goofball!\n");
    return 0;
  }

  write("You wap "+who->query_name()+" on the back of the head and yell: \"YOU'RE IT!!!\"\n");
  say(this_player()->query_name()+" waps "+who->query_name()+" on the back of "+who->query_possessive()+" head and yells: \"YOU'RE IT!!!!\"\n");
  old = this_player()->query_real_name();
  move_object(this_object(),who);
  return 1;
}

string extra_look(void) { 
  return environment(this_object())->query_name()+" is IT";
}

