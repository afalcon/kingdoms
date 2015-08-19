#pragma save_binary
#include "/wiz/b/bart/include/defines.h"
inherit "/std/room/room";

object *update = ({ });
string *current_weather;
string room_desc;
int current_state, id_rain, id_hail, id_lightning, id_snow;


// This thing cleans up the list.

remove_zeroes() {
  while (member_array(0, update) != -1)
    update -= ({ 0 });
}


// This function returns the current weather state. 

int query_current_state() {
  return current_state;
}


// This function picks a new weather record.

string *get_new_weather_data(int number) {
  string *tmp;
#include "/wiz/b/bart/include/weather_data.h"
  switch(number) {
    case 0:
      tmp = weather_zero;
      break;
    case 1:
      tmp = weather_one;
      break;
    case 2:
      tmp = weather_two;
      break;
    case 3:
      tmp = weather_three;
      break;
    case 4:
      tmp = weather_four;
      break;
    case 5:
      tmp = weather_five;
      break;
    case 6:
      tmp = weather_six;
      break;
    case 7:
      tmp = weather_seven;
      break;
    case 8:
      tmp = weather_eight;
      break;
    case 9:
      tmp = weather_nine;
      break;
    case 10:
      tmp = weather_ten;
      break;
    default:
      tmp = weather_zero;
      break;
  }
  return tmp;
}


// Returns the message associated with this weather state.

string query_current_weather() {
  return current_weather[4]+"\n";
}

// This function returns a % of the chance that a person will be struck by 
// lightning.

int query_will_you_hit_me(object poorguy) {
  int i, flag;
  object *things;
  if (present("anti_lighting_damn_you_cheater",poorguy)) {
    tell_object(poorguy,"Your special anti-lightning thingy saved your ass this time.\n");
    flag = 1000;
    return flag;
  }
  flag = 10;
  things = all_inventory(poorguy);
  for (i = 0; i < sizeof(things); i++) {
    if (flag) {
      switch(things[i]->query_material()) {
        case "iron": flag = flag - 1; break;
        case "steel": flag = flag - 2; break;
        case "silversteel": flag = flag - 3; break;
        case "silver": flag = flag - 4; break;
      }
      switch(things[i]->query_property()) {
        case "metal": flag = flag - 5; break;
      }
    }
  }
  if(poorguy->query_real_name() == "bart") {
    flag = 1;
  }
  return flag;
}


// This function determines whether a person will be pelted by hail stones.

void pelt_me(object room) {
  int i;
  object *people;
  // !random(2) is the % chance of getting hit by hail stones. [33%]
  if (!random(3) && present_living(room)) {
    people = all_inventory(room);
    for (i = 0; i < sizeof(people); i++) {
      if(!random(4) && living(people[i])) {
        tell_object(people[i],"Oof! You got pelted by hail stones.\n");
        say(CAP(people[i]->query_name())+" got pelted by hail stones.\n");
        set_this_player(people[i]);
        people[i]->reduce_hit_point(25 + random(25));
      }
    }
  }
  else {
    tell_room(room,"Hail stones continue to fall from the sky.\n");
  }
}


// This function determines whether a person will be struck by lightning.

void strike_me(object room) {
  int i;
  object *people;
  if (!random(9) && present_living(room)) {
    people = all_inventory(room);
    for (i = 0; i < sizeof(people); i++) {
      if(!random(9) &&  
         query_ip_number(people[i]) &&  
         !random(query_will_you_hit_me(people[i]))) {
        tell_object(people[i],"Oof! You got struck by lightning!\n");
        say(CAP(people[i]->query_name())+" got struck by lightning.\n");
        set_this_player(people[i]);
        people[i]->reduce_hit_point(50 + random(100));
      }
    }
  }
  else {
    tell_room(room,"A lightning bolt strikes a few feet from where you're standing.\n");
  }
}


// This function returns a string describing the clouds.

string query_item_cloud() {
  string desc;
  switch(current_weather[7]) {
    case 0:
      desc = "There are no clouds in the sky";
      break;
    case 1:
      desc = "There are a few scattered clouds in the sky";
      break;
    case 2:
      desc = "Fluffy white clouds cover the sky";
      break;
    case 3:
      desc = "Dark clouds cover the sky";
      break;
    case 4:
      desc = "Very thick, and dark clouds cover the sky";
      break;
  }
  return desc;
}


// This function returns a string describing the rain.

string query_item_rain() {
  string desc;
  switch(current_weather[8]) {
    case 0:
      desc = "It is not raining";
      break;
    case 1:
      desc = "It appears that the rain had just stopped falling";
      break;
    case 2:
      desc = "A very light downpour of rain is falling";
      break;
    case 3:
      desc = "A steady downpour of rain is falling";
      break;
    case 4:
      desc = "A very heavy downpour of rain is falling";
      break;
  }
  return desc;
}


// This function returns a string describing the hail.

string query_item_hail() {
  string desc;
  switch(current_weather[9]) {
    case 0:
      desc = "There are no hail stones falling";
      break;
    case 1:
      desc = "Hail stones are falling from the sky";
      break;
  }
  return desc;
}


// This function returns a string describing the thunder.

string query_item_thunder() {
  string desc;
  switch(current_weather[10]) {
    case 0:
      desc = "You can't see thunder!  You don't hear thunder at this moment";
      break;
    case 1:
      desc = "You hear distant thunder";
      break;
    case 2:
      desc = "You hear nearby thunder";
      break;
  }
  return desc;
}


// This function returns a string describing the lightning.

string query_item_lightning() {
  string desc;
  switch(current_weather[11]) {
    case 0:
      desc = "*Comfort* You don't see any lightning";
      break;
    case 1:
      desc = "You see a spectacular lightning show off at a distance";
      break;
    case 2:
      desc = "You see a spectacular lightning show right above your head";
      break;
  }
  return desc;
}

string query_item_snow() {
  string desc;
  desc = "Snow is falling from the sky";
  return desc;
}

// This function returns a string describing the time of day.

string query_day_description() {
  string desc;
  switch(query_hour()) {
    case 0..4:
      desc = "night";
      break;
    case 5..11:
      desc = "morning";
      break;
    case 12..17:
      desc = "afternoon";
      break;
    case 18..21:
      desc = "late afternoon";
      break;
    case 22..23:
      desc = "evening";
      break;
  }
  return desc;
}


// This function returns a string describing the sun.

string query_item_sun() {  
  string desc;
  if(query_daylight()) {
    if(current_weather[5]) {
      desc = "The sun shines brightly on this ";
      desc += current_weather[1]+" ";
      desc += query_day_description();
    }
    else {
      desc = query_item_cloud()+".  ";
      desc += "You can't see the sun at this moment";
    }
  }
  else {
      desc = "The sun is gone";
  }
  return desc;
}


// This function returns a string describing the moon phases.

string query_moon_stage() {
  string desc;
  switch(query_moonphase()) {
    case 0:
      desc = "new moon";
      break;
    case 1..6:
      desc = "waxing crescent";
      break;
    case 7:
      desc = "first quarter";
      break;
    case 8..13:
      desc = "waxing gibbous";
      break;
    case 14:
      desc = "full moon";
      break;
    case 15..20:
      desc = "waning gibbous";
      break;
    case 21:
      desc = "last quarter";
      break;
    case 22..27:
      desc = "waning crescent";
      break;
  }
  return desc;
}


// This function returns a string describing the moon.

string query_item_moon() {
  string desc;
  if(query_daylight()) {
      desc = "The moon is gone";
  }
  else {
    if(current_weather[6]) {
      if(query_moonphase()) {
        desc = "The moon, which appears to be in its ";
        desc += query_moon_stage();
        desc += " stage, illuminates the sky";
      }
      else {
        desc = "You can't seem to see the moon tonight";
      }
    }
    else {
      desc = query_item_cloud()+".  ";
      desc += "You can't see the moon at this moment";
    }
  }
  return desc;
}


// This function returns a string describing the sky.

query_item_sky() {
  string desc;
  if(query_daylight()) {
    desc = query_item_sun();
  }
  else {
    desc = query_item_moon();
  }
  if (current_weather[8]) {
    desc += ".  "+query_item_rain();
  }
  if (current_weather[9]) {
    desc += ".  "+query_item_hail();
  }
  if (current_weather[11]) {
    desc += ".  "+query_item_lightning();
  }
  if (current_state == 10) {
    desc += ".  "+query_item_snow();
  }
  return desc;
}
  

// This function returns the current season.

string query_season() {
  string season;
  switch(query_month()) {
    case 3..5:
      season = "spring";
      break;
    case 6..8:
      season = "spring";
      break;
    case 9..11:
      season = "fall";
      break;
    default:
      season = "winter";
      break;
  }
  return season;
}


// LAG IS YOUR FRIEND.

void update_room(object room) {
  int count;
  string new_desc, old_desc;
  room->remove_item("snow|sun|moon|sky|cloud|clouds|rain|rains|hail|hails|hail stone|hail stones |thunder|lightning|bolts|bolt|lightning bolts|lightning bolt|lightning show");
  if(query_daylight()) {
    room->add_item("sun",query_item_sun());
  }
  else {
    room->add_item("moon",query_item_moon());
  }
  room->add_item("sky",query_item_sky());
  if(current_weather[7]) {
    room->add_item("cloud|clouds",query_item_cloud());
  }
  if(current_weather[8]) {
    room->add_item("rain|rains",query_item_rain());
  }
  if(current_weather[9]) {
    room->add_item("hail|hails|hail stone|hail stones",query_item_hail());
  }
  if(current_weather[10]) {
    room->add_item("thunder",query_item_thunder());
  }
  if(current_weather[11]) {
    room->add_item("lightning|bolts|bolt|lightning bolts|lightning bolt|lightning show",query_item_lightning());
  }
  if(current_state == 10) {
    room->add_item("snow","Snow covers everything around you, *happy sigh*, awww, what a beautiful sight");
  }
  if (room->query_room_desc()) {
    old_desc = room->query_room_desc();
    new_desc = "On this ";
    new_desc += current_weather[1]+" ";
    new_desc += query_season()+ " ";
    new_desc += query_day_description()+", ";
    new_desc += lower_case(current_weather[3])+"  ";
    room->set_long(new_desc+old_desc);
    count = strlen(new_desc) - 3;
    new_desc = sprintf("%."+count+"s",new_desc);
  }
}


// This function determines whether the weather will become better or worse.

int query_weather_progress() {
  int one, two;
  one = random(1000);
  two = random(1000);
  if (current_state == 0) {
    return 1;
  }
  if (one > two) {
    return 1;
  }
  else {
    return 0;
  }
}


// This function determines whether the previous weather was bad.
// Right now, the weather states which are considered "bad" are:
// Hail = 8, Lightning = 9 and Snow = 10.

int query_did_i_just_have_bad_weather() {
  if(current_state > 7) { return 1; }
  else { return 0; }
}


// This function determines whether a bad weather will occur next.

int query_will_i_have_bad_weather() {
  if (current_state == 7 && query_weather_progress()) {
    return 1;
  }
  else {
    return 0;
  }
}


// This function will determine if there will be a change in weather.

int query_no_progress() {
  if(random(9)) {
    return 1;
  }
  else {
    return 0;
  }
}


void rain_msgs() {
  int i;
  for (i = 0; i < sizeof(update); i++) {
    switch(random(5)) {
      case 0:
        tell_room(update[i],"Rain continues to fall from the sky.\n");
        break;
      case 1:
        tell_room(update[i],"Raindrops fall on your head.\n");
        break;
      case 2:
        tell_room(update[i],"You get drenched by a torrid downpour of rain.\n");
        break;
      case 3:
        tell_room(update[i],"The rain continues to fall from the sky.\n");
        break;
      case 4:
        tell_room(update[i],"The rain comes down hard.\n");
        break;
    }
  }
}


void hail_msgs() {
  int i;
  for (i = 0; i < sizeof(update); i++) {
    pelt_me(update[i]);
  }
}


void lightning_msgs() {
  int i;
  for (i = 0; i < sizeof(update); i++) {
    strike_me(update[i]);
  }
}
     

void snow_msgs() {
  int i;
  for (i = 0; i < sizeof(update); i++) {
    switch(random(8)) {
      case 0:
        tell_room(update[i],"Snow continues to fall from the sky.\n");
        break;
      case 1:
        tell_room(update[i],"Tiny snow flakes fall from the sky.\n");
        break;
      case 2:
        tell_room(update[i],"Snow flakes fall on the ground.\n");
        break;
      case 3:
        tell_room(update[i],"The snow continues to fall from the sky.\n");
        break;
      case 4:
        tell_room(update[i],"The snow comes down hard.\n");
        break;
      case 5:
        tell_room(update[i],"It continues to snow.\n");
        break;
      case 6:
        tell_room(update[i],"Snow flakes slowly fall from the sky.\n");
        break;
      case 7:
        tell_room(update[i],"Snow falls on the ground.\n");
        break;
    }
  }
}

    
void repeat_messages(int num) {
  switch(num) {
    case 4..7:
      id_rain = set_alarm(1.0, 10.0, "rain_msgs");
      break;
    case 8:
      id_hail = set_alarm(1.0, 10.0, "hail_msgs");
      break;
    case 9:
      id_lightning = set_alarm(1.0, 10.0, "lightning_msgs");
      break;
    case 10:
      id_snow = set_alarm(1.0, 10.0, "snow_msgs");
      break;
    default:
      break;
  }
}


// This function changes the weather. Based on the current weather
// state, it picks a new weather state and call_outs itself, so that there
// is always one version of the function in the call_out queue. If the new
// state is the same as the old one, then nothing else is done, otherwise
// we update each object of the new state.

void change_weather() {
  int count, i, new_state;
  string new_desc, old_desc;
  remove_zeroes();
  set_alarm(current_weather[0], 0.0, "change_weather");
  if (query_no_progress()) return;
  if (id_rain) { remove_alarm(id_rain); }
  if (id_hail) { remove_alarm(id_hail); }
  if (id_lightning) { remove_alarm(id_lightning); }
  if (id_snow) { remove_alarm(id_snow); }

// No more hail or lightning.
  if (query_did_i_just_have_bad_weather()) {
    current_state = 0;
    current_weather = get_new_weather_data(current_state);
    i = sizeof(update);
    while (i--) {
      tell_room(update[i],current_weather[4]+"\n");
      update_room(update[i]);
    }
    return;
  }
  // Hail and lightning. mwhahaha.
  if (query_will_i_have_bad_weather()) {
    switch(random(3)) {
      case 1: current_state = 8; break;
      case 2: current_state = 9; break;
      default: current_state = 10; break;
    }
    current_weather = get_new_weather_data(current_state);
    set_alarm(1.0, 0.0, "repeat_messages", current_state);
    i = sizeof(update);
    while (i--) {
      tell_room(update[i],current_weather[2]+"\n");
      update_room(update[i]);
      if (current_state == 8) { pelt_me(update[i]); }
      if (current_state == 9) { strike_me(update[i]); }
    }
  }
  // Normal, boring, and safe weather.
  else {
    if (query_weather_progress()) {
      current_state = current_state + 1;
      current_weather = get_new_weather_data(current_state);
      set_alarm(1.0, 0.0, "repeat_messages", current_state);
      i = sizeof(update);
      while (i--) {
        tell_room(update[i],current_weather[2]+"\n");
        update_room(update[i]);
      }
    }
    else {
      current_state = current_state - 1;
      current_weather = get_new_weather_data(current_state);
      set_alarm(1.0, 0.0, "repeat_messages", current_state);
      i = sizeof(update);
      while (i--) {
        tell_room(update[i],current_weather[4]+"\n");
        update_room(update[i]);
      }
    }
  }
  return;
}

// Special thingy so it will work like an outdoor_room.
set_room_desc(str) {
  room_desc = str;
}

query_room_desc() {
  return room_desc;
}

// The reset function. Whew! Thought you'd never see it, huh?

reset(arg) {
  ::reset(arg);
  if (arg) return;
  set_new_light(1);
  set_short("The weather room");
  set_room_desc( 
"\n"+
"\n"+
"Welcome to the weather control room.\n"+
"\n"+
"Here's some commands: \n"+
" 1.  info       -- gives the current weather info.\n"+
" 2.  states     -- shows all the weather states.\n"+
" 3.  list       -- lists all the rooms affected by the weather.\n"+
" 4.  newlist    -- updates all the rooms affected by the weather.\n"+
"\n"+
"Type help weather for more information\n"
);
  set_long(query_room_desc());
  add_property("indoors");
  add_exit("/wiz/b/bart/workroom","east");
  set_alarm(5.0, 0.0, "do_start_me");
}


do_start_me() {
  current_state = 3;
  current_weather = get_new_weather_data(current_state);
  set_alarm(1.0, 0.0, "change_weather");
  set_alarm(1.0, 0.0, "repeat_messages", current_state);
  set_alarm(1.0, 0.0, "add_room", this_object());
  return 1;
}


init() {
  ::init();
  add_action("do_help","help");
  add_action("do_info","info");
  add_action("do_states","states");
  add_action("do_list","list");
  add_action("do_newlist","newlist");
}


do_help(str) {
  if (!str) { 
    return 0; 
  }
  if (str == "weather") { 
    write(read_file(DOC+"weather_room_help")); 
    return 1;
  }
  return 0;
}


do_info() {
  write("Current weather state: "+current_state+"\n");
  write("Current season:        "+CAP(query_season())+"\n");
  write("Current hour:          "+query_hour()+" ("+query_day_description()+")\n");
  write("Sun:                   "+query_item_sun()+".\n");
  write("Moon:                  "+query_item_moon()+".\n");
  write("Moon Phase:            "+CAP(query_moon_stage())+".\n");
  write("Clouds:                "+query_item_cloud()+".\n");
  write("Rain:                  "+query_item_rain()+".\n");
  write("Hail:                  "+query_item_hail()+".\n");
  write("Thunder:               "+query_item_thunder()+".\n");
  write("Lightning:             "+query_item_lightning()+".\n");
  if(current_state == 10) {
    write("Snow:                  "+query_item_snow()+".\n");
  }
  else {
    write("Snow:                  None.\n");
  }
  return 1;
}


do_states() {
  write(read_file(DOC+"weather_states"));
  return 1;
}

  
do_list() {
  int i;
  remove_zeroes();
  for (i = 0; i < sizeof(update); i++) {
    write(i+". "+file_name(update[i])+"\n");
  }
  return 1;
}


do_newlist() {
  int i;
  remove_zeroes();
  for (i = 0; i < sizeof(update); i++) {
    update_room(update[i]);
  }
  return 1;
}


do_restore_me() {
  restore_object("/wiz/b/bart/rooms/weather_data");
  return 1;
}


do_save_me() {
  save_object("/wiz/b/bart/rooms/weather_data");
  return 1;
}

add_room(object ob) {
  if(member_array(ob, update) < 0) {
    update += ({ ob });
  }
  remove_zeroes();
  return 1;
}

remove_ship(object ob) {
  if(member_array(ob, update) < 0) {
    update -= ({ ob });
  }
  remove_zeroes();
  return 1;
}

