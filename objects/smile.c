#pragma strict_types
inherit "/std/obj/treasure";

int id, line_count;

string *lines = ({
 " ",1.0,
 "I've found a way to make you",4.0,
 "I've found a way",4.0,
 "A way to make you smile",4.0,
 "I read bad poetry",2.0,
 "Into your machine",2.0,
 "I save your messages",2.0,
 "Just to hear your voice",2.0,
 "You always listen carefully",4.0,
 "To awkward rhymes",4.0,
 "You always say your name",2.0,
 "Like I wouldn't know it's you",2.0,
 "At your most beautiful",1.0,
 "*doot* *doot* *doot* *doot*",1.0,
 "*doot* *doot* *doot* *doot*",1.0,
 "*doot* *doot* *doot* *doot*",1.0,
 "*doo* *doo* *doo*",1.0,
 "*doot*",1.0,
 "I've found a way to make you",4.0,
 "I've found a way",4.0,
 "A way to make you smile",4.0,
 "At my most beautiful",2.0,
 "I count your eyelashes",2.0,
 "Secretly",4.0,
 "With every one, whisper I love you",2.0,
 "I let you sleep",2.0,
 "I know you're closed eye watching me",2.0,
 "Listening",4.0,
 "I thought I saw a smile. =o)",1.0,
 "*doot* *doot* *doot* *doot*",1.0,
 "*doot* *doot* *doot* *doot*",1.0,
 "*doot* *doot* *doot* *doot*",1.0,
 "*doo* *doo* *doo*",1.0,
 "*doot*",1.0,
 "I've found a way to make you",4.0,
 "I've found a way to make you",4.0,
 "I've found a way",4.0,
 "A way to make you smile",4.0
});

int init_arg(void) {
  tell_object(this_player(), "Cloned: a little blue smile.\n");
  return 1;
}

void reset(int arg) {
  if (arg) return;
  set_name("smile");
  set_short("a little blue smile");
  set_long("=o)\n\n"+
           "Commands: beautiful, nobeautiful.\n");
  set_value(0);
  set_weight(0);
}

int drop(void) { return 1; }
int get(void) { return 0; }

void init(void) {
  ::init();
  add_action("do_beautiful","beautiful");
  add_action("do_nobeautiful","nobeautiful");
}

int do_beautiful(void) {
  if(id) {
    write("Nah-uh.\n");
    return 1;
  }
  id = set_alarm(0.0, 0.0, "play_song");
  write("Kewl.\n");
  return 1;
}

int do_nobeautiful(void) {
  if(id) {
    remove_alarm(id);
    id = 0;
    write("Alrighty.\n");
    return 1;
  }
  else {
    write("Oops.\n");
    return 1;
  }
}

void play_song(void) {
  if (line_count < sizeof(lines)) {
    tell_room(environment(environment(this_object())), lines[line_count]+"\n");
    line_count += 1;
    id = set_alarm(lines[line_count], 0.0, "play_song");
    line_count += 1;
  }
  else {
    remove_alarm(id);
    id = 0;
    line_count = 0;
    id = set_alarm(0.0, 0.0, "play_song");
  }
}

string query_auto_load(void) {
  return "/wiz/b/bart/objects/smile:";
}

