inherit "/std/obj/treasure";
 
reset(arg) {
  if(arg) return;
  set_name("cake");
  set_alias("birthday cake");
  set_short("a birthday cake");
  set_long(
"It's a birthday cake with 21 candles burning brightly.\n"+
"The frosting reads:  HAPPY BIRTHDAY STORMIE!!!\n"+
"\n");
  set_value(1);
  set_weight(1);
}

init() {
  ::init();
  add_action("do_eat","eat");
  add_action("do_blow","blow");
}

do_eat(string str)
{
  if(!str)
  {
    return 0;
  }
  if(str == "cake" || str == "birthday cake")
  {
    write("You picture yourself eating the cake....Hmm...Yummy!\n"+
          "Hey silly! If you ate it, no one will see it...then no one"+
          "will know it's Stormie's birthday.\n");
    say(this_player()->query_name()+" drools a little.\n");
    return 1;
  }
  return 0;
}

do_blow(string str)
{
  if(!str)
  { 
    notify_fail("Blow what?\n");
    return 0;
  }
  if(str == "candle" || str == "candles" || str == "out candle" ||
    str == "out candles" || str == "out the candles" || str == "out the candle")
  {
    if(this_player()->query_real_name() == "firestorm")
    {
      tell_room(environment(this_player()),"Firestorm blows out the candles.\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"               B O O M!\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"\n");
      tell_room(environment(this_player()),"The candles light up again. Hah! trick candles!\n");
      return 1;
    }
    write("Are you Firestorm? I don't think so!\n");
    say(this_player()->query_name()+" is a goofball...(tried to blow out the candles.\n");
    return 1;
  }
  return 0;
}
