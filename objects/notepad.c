#pragma strict_types
inherit "/std/obj/treasure";

string *messages = ({ });

int restore_me() {
  restore_object("/wiz/b/bart/save/notepad");
  return 1;
}

int save_me() {
  save_object("/wiz/b/bart/save/notepad");
  return 1;
}

int init_arg() {
  tell_object(this_player(), "Your notepad is ready for scribbling.\n");
  set_alarm(1.0, 0.0, "restore_me");
  return 1;
}

void init() {
  if(environment(this_object())->query_real_name() != "bart") {
    write("No way, you are too ugly.\n");
    this_object()->destroy();
  }
  add_action("do_messages","messages");
  add_action("do_add","add");
  add_action("do_del","del");
}

int drop() { return 1; }
int get() { return 0; }

void create_object() {
  set_name("notepad");
  set_alias("pad");
  set_short("a little blue notepad");
  set_long(
"Commands:\n"+
"  messages       \n"+
"  add <message>  \n"+
"  del <num>      \n"+
"\n\n");
}

int do_messages() {
  int i;
  if(sizeof(messages) < 1) {
    write("Your notepad is empty.\n");
    return 1;
  }
  write("Your messages:\n");
  for(i = 0; i < sizeof(messages); i++) {
    write("  "+(i+1)+". "+messages[i]+"\n");
  }
  save_object("/wiz/b/bart/save/notepad");
  return 1;
}

int do_add(string str) {
  if(!str) {
    notify_fail("Syntax: add <message>.\n");
    return 0;
  }
  messages += ({ str });
  write("Message added.  Total: "+sizeof(messages)+"\n");
  save_object("/wiz/b/bart/save/notepad");
  return 1;
}

int do_del(string str) {
  int num;
  if(!str) {
    notify_fail("Syntax: del <num>.\n");
    return 0;
  }
  sscanf(str,"%d",num);
  if(!num || num - 1 > sizeof(messages)) {
    notify_fail("Error: invalid message number.\n");
    return 1;
  }
  messages -= ({ messages[num-1] });
  write("Message "+str+" deleted.  Total: "+sizeof(messages)+"\n");
  save_object("/wiz/b/bart/save/notepad");
  return 1;
}

string query_auto_load() {
  return "/wiz/b/bart/objects/notepad:";
}

