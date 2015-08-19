#pragma strict_types
inherit "/std/obj/treasure";

int id, line_count;

string *lines = ({
  "<guiro intro>",3.5,
  "Your eyes are burning holes through me.",6.0,
  "I'm gasoline.",3.5,
  "I'm burning clean.",6.5,
  "Twentieth century go to sleep.",4.8,
  "You're plasticine.",4.0,
  "That is obscene.",4.0,
  "That is obscene.",3.0,
  "You are the star tonight.",3.0,
  "You shine electric, outta sight.",3.8,
  "Your light eclipsed the moon tonight.",5.8,
  "Electrolite...",3.8,
  "You're outta sight.",8.2,
  "If I ever want to fly.",5.0,
  "Mulholland Drive.",4.0,
  "I am alive.",6.3,
  "Hollywood is under me.",5.0,
  "I'm Martin Sheen.",4.0,
  "I'm Steve McQueen.",4.0,
  "I'm Jimmy Dean.",2.8,
  "You are the star tonight.",3.0,
  "You shine electric, outta sight.",3.6,
  "Your light eclipsed the moon tonight.",5.8,
  "Electrolite...",3.8,
  "You're outta sight.",6.2,
  "<more guiro>",30.0,
  "If you ever want to fly.",5.0,
  "Mulholland Drive.",4.0,
  "Up in the sky.",6.0,
  "Stand on a cliff and look down there.",6.5,
  "Don't be scared...",3.0,
  "You are alive.",3.0,
  "You are alive.",3.0,
  "You are the star tonight.",3.0,
  "You shine electric, outta sight.",3.8,
  "Your light eclipsed the moon tonight.",5.8,
  "Electrolite...",3.8,
  "You're outta sight.",8.5,
  "Twentieth century go to sleep.",6.0,
  "Really deep.",3.5,
  "We won't blink.",5.0,
  "Your eyes are burning holes through me.",6.5,
  "I'm not scared.",4.0,
  "I'm outta here.",4.0,
  "I'm not scared...",4.0,
  "I'm outta here.",7.5
});

int init_arg(void) {
  tell_object(this_player(), "Cloned: a little blue electrolite.\n");
  return 1;
}

void reset(int arg) {
  if (arg) return;
  set_name("electrolite");
  set_short("a little blue electrolite");
  set_long("\"That is obscene.\n"+
           " That is obscene.\"\n"+
           "\n"+
           "Commands: lite, nolite.\n");
  set_value(0);
  set_weight(0);
}

int drop(void) { return 1; }
int get(void) { return 0; }

void init(void) {
  ::init();
  add_action("do_lite","lite");
  add_action("do_nolite","nolite");
}

int do_lite(void) {
  if(id) {
    write("Nah-uh.\n");
    return 1;
  }
  id = set_alarm(0.0, 0.0, "play_song");
  write("Kewl.\n");
  return 1;
}

int do_nolite(void) {
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
  return "/wiz/b/bart/objects/electrolite:";
}

