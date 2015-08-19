#pragma strict_types
inherit "/std/obj/treasure";

status listen;
status game;
object it;

int init_arg(void) {
  tell_object(this_player(), "T A G  on!!!\n");
  return 1;
}

void create_object(void) {
  set_name("tag");
  set_alt_name("bartslovelygameoftag");
  set_short("a little blue tag");
  set_long(
"---------------------\n"+
"     Tag commands:   \n"+
"---------------------\n"+
"  tagon              \n"+
"  tagoff             \n"+
"  tagstart           \n"+
"  tagtalk <message>  \n"+
"  tagwho             \n"+
"---------------------\n");
  set_value(0);
  set_weight(0);
  listen = 1;
}

int drop() { return 1; }
int get() { return 0; }

void init() {
  ::init();
  add_action("do_tagon","tagon");
  add_action("do_tagoff","tagoff");
  add_action("do_tagtalk","tagtalk");
  add_action("do_tagwho","tagwho");
  add_action("do_tagstart","tagstart");
}

int do_tagon(void) {
  listen = 1;
  write("You decide to listen to the Tag channel.\n");
  return 1;
}

int do_tagoff(void) {
  listen = 0;
  write("You decide to stop listening to the Tag channel.\n");
  return 1;
}

int do_tagtalk(string str) {
  int i;
  object *who;
  object tag;
  who = users();

  if(!str) {
    notify_fail("Speechless?\n");
    return 0;
  }

  for(i = 0; i < sizeof(who); i++) {
    tag = present("bartslovelygameoftag",who[i]);
    if(tag && tag->query_listening()) {
      tell_object(who[i],"[Tag] "+this_player()->query_name()+" says: "+str+"\n");
    }
  }
  return 1;
}

int do_tagwho(void) {
  int i;
  object tag;
  object *who;
  who = users();

  write("---------------------------------\n");
  write("           Tag Players           \n");
  write("---------------------------------\n");

  for(i = 0; i < sizeof(who); i++) {
    tag = present("bartslovelygameoftag",who[i]);
    if(tag) {
      if(tag->query_listening()) {
        write("[*]    "+capitalize(who[i]->query_real_name()));
      }
      else {
        write("[ ]    "+capitalize(who[i]->query_real_name()));
      }
      if(present("thissillypersonisit",who[i])) {
        write("     [IT]\n");
      }
      else {
        write("\n");
      }
    }
  }
  write("---------------------------------\n");
  return 1;
}
 
int do_tagstart(void) {
  int i;
  object *who;

  game = 0;
  who = users();
  for (i = 0; i < sizeof(who); i++) {
    it = present("thissillypersonisit",who[i]);
    if(it) {
      game = 1;
    }
  }
  if(!game) {
    it = make("/wiz/b/bart/objects/it");
    move_object(it,environment(this_object()));
    write("You happily start a game of tag.\n");
    this_object()->do_tagtalk("I'm IT!!!\n");
    return 1;
  }
  else {
    write("You can't start a tag game. Someone is already IT.\n");
    return 1;
  }
}

status query_listening(void) {
  return listen;
}

string extra_look(void) { 
  return environment(this_object())->query_name()+" is a legendary TAG player";
}

string query_auto_load(void) {
  return "/wiz/b/bart/objects/tag:";
}

