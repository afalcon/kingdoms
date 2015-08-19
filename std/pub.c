#include "/wiz/b/bart/include/defines.h"
#include <guild.h>
#include <levels.h>
#define WARE_PATH "/wiz/b/bart/std/"
#define MAX_STRENGTH_PUB 3000
#define MAX_STRENGTH_PLAYER 500
inherit "/std/room/pub_std";

mapping guestlist;
string guild, tmp;

reset(arg) {
  ::reset();
  if(arg) return;
  set_light(1);
  set_short("Pub");
  set_long("You are standing inside a standard pub.\n");
	add_item("menu","It would be easier for you if you read the menu");
  add_property("indoors");
  add_property("no_teleport");
  add_property("no_fight");
  alco_drink = ({ "tequila" });
  ware = alco_drink;
  ware_path = WARE_PATH;
  max_strength_pub = MAX_STRENGTH_PUB;
  max_strength_player = MAX_STRENGTH_PLAYER;
}

buying(str) {
  if(!present("bartender",this_object())) {
    write("We mourn the slain bar tender, so we will not sell anything.\n");
    return 1;
  }
  if(this_player()->query_level() < NEWBIE &&
    this_player()->query_guild() != this_object()->this_guild_pub()) {
    write("The bartender says: We don't serve Non-"+guild+"s here. Go away.\n");
    return 1;
  }
  return ::buying(str);
}

set_guild_pub(string tmp) {
  guild = tmp;
}

query_guild_pub() {
  return guild;
}

this_guild_pub() {
  string tmp;
  switch(guild) {
    case "knight":
      tmp = "/areas/Guilds/Knight/o/Rooms/inner_guild";
      break;
    case "medic":
      tmp = "/areas/Guilds/Healer/o/Rooms/medics_guild";
      break;
    case "assassin":
      tmp = "/areas/Guilds/Assassin/o/Rooms/assassin";
      break;
    case "bard":
      tmp = "/areas/Guilds/Bard/o/Rooms/guildhall";
      break;
    case "cleric":
      tmp = "/areas/Guilds/Cleric/o/Main/cleric";
      break;
    case "mage":
      tmp = "/areas/Guilds/Mage/o/Rooms/guild_hall";
      break;
    case "fighter":
      tmp = "/areas/Guilds/Fighter/o/Rooms/fighters_hall";
      break;
    case "demon":
      tmp = "/areas/Guilds/Demon/o/Rooms/demon";
      break;
    default:
      tmp = "/areas/Guilds/Knight/o/Rooms/inner_guild";
      break;
  }
  return tmp;
}
