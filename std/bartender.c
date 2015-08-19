#include "/wiz/b/bart/include/defines.h"
#include <levels.h>
#include <guild.h>
inherit "/std/living/monster";

object thing;
string name;
string guild;

reset(arg) {
  ::reset(arg);
  if (arg) return;
}

set_guild(string hmm) {
  guild = hmm;
  name = RAND->gimme_a_male_name();
  set_name(name);
  set_short(CAP(name)+" the bartender");
  set_long(CAP(name)+" is the new bartender of the "+CAP(guild)+"'s Tavern.\n");
  set_level(1);
  set_alias("bartender");
  set_alt_name("std_bartender");
  set_gender(1);
  set_race("human");
  set_hp(50);
  set_al(0);
  set_wc(50);
  set_new_ac(9);
  set_skill("combat", 9);
  set_skill("unarmed", 9);
  set_skill("perception", 5);
  set_skill("resist", 5);
  add_money(25);
  load_chat(1, 
    ({
      CAP(name) + " says: I don't know what to say?\n",
      CAP(name) + " asks: Want some more alcohol?\n",
      CAP(name) + " says: Alcohol makes people smarter.\n",
      CAP(name) + " asks: Who needs brain cells?\n",
    })
  );
}

init() {
  if(this_player()->query_level() < NEWBIE &&
     this_player()->query_guild() != this_object()->this_guild_pub()) {
	  write(CAP(name)+" says: We don't serve Non-"+guild+"s here. Go away.\n");
	  say(CAP(name)+" looks at "+CTPQN+" and says: We don't serve Non-"+guild+"s here. Go away.\n");
    return 1;
  }
  else {
    if(this_player()->query_level() < NEWBIE) { 
      write(CAP(name)+ " says: Welcome, fellow "+guild+"!\n");
	    say(CAP(name)+" looks at "+CTPQN+" and says: Welcome, fellow "+guild+".\n");
    }
    else {
      write(CAP(name)+ " smiles happily at you.\n");
      write(CAP(name)+ " says: Welcome to the "+CAP(guild)+"'s Tavern, "+CTPQN+".\n");
	    say(CAP(name)+" bows to "+CTPQN+".\n");
    }
  }
  ::init();
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
