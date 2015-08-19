// Who-server.
#include <levels.h>
inherit "/std/obj/stdobj";
inherit "/sys/master/level_titles";

int count,tmp, use_more;
string func,if_guild, *wholist;

reset(arg)
{
  if (arg)
  {
    return;
  }
  count = 0;
  "/wiz/b/bart/rooms/void"->load_me();
    move_object(this_object(), find_object("/wiz/b/bart/rooms/void"));
}

short()
{
  return "Bart's who control";
}

long()
{
  write("The count is: " + count + "\n");
}

id(str)
{
  return str == "who" || str == "who control";
}

query_prevent_shadow()
{
  return 1;
}

do_who(str,guild) 
{
  if (guild)
  {
    if_guild = guild;
  }
  else
  {
    if_guild = 0;
  }
  use_more = (str == 0 || (str != "--" && !sscanf(str, "-- %s", str)));
  count++;
  wholist = ({ });
  if (!str || str == "" || str == "--")
  {
    normal();
  }
  else if (str == "-f")
  {
    frozen();
  }
  else if (str == "-w")
  {
    wizards();
  }
  else if (str == "-m")
  {
    mortals();
  }
  else if (str == "-s")
  {
    short_who();
  }
  else 
  {
    notify_fail("Usage: who [--] [-f/-w/-m/-s]\n");
    return 0;
  }
  wholist = ({ });
  return 1;
}

normal()
{
  filter(users(),"print",this_object());
  this_player()->more_list(wholist);
}

wizards()
{
  filter(filter(users(),"iswiz",this_object()),
	 "print",this_object());
  this_player()->more_list(wholist);
}

mortals()
{
  filter(filter(users(),"ismort",this_object()),
	 "print",this_object());
  this_player()->more_list(wholist);
}

frozen()
{
  tmp = 1;
  filter(all_inventory(find_object("/sys/room/freezer")),
	 "print",this_object());
  tmp = 0;
  this_player()->more_list(wholist);
}

iswiz(ob)
{
  if (!ob)
  {
    return;
  }
  return ob->query_level() > NEWBIE ;
}

ismort(ob)
{
  if (!ob)
  {
    return;
  }
  return ob->query_level() <= MAXMORTAL;
}

print(ob,guild) 
{
  if (ob && ob->short() && (!if_guild || ob->query_guild() == if_guild))
  {
    string str = sprintf("%s %s", "["+level(ob)+"]" ,
                 ob->short() + (!tmp ? is_idle(ob) : ""));
    if (use_more)
    {
      wholist += ({ str });
    }
    else
    {
      write(str);
    }
  }
}

level(ob)
{
  // We don't have playernames in the lib. The titles are meant to help our
  // users to recognize a function. A second field telling of a specific arch
  // function may be a good idea, feel free to add such code, Yappo.
  if(ob->query_gender() == 2) {
    switch(ob->query_level()) {
      case 1500:
        return "BARONESS";
        break;
      case 1700:
        return "LADY";
        break;
      case 1800:
        return "DUCHESS";
        break;
      case 1900:
        return "QUEEN";
        break;
      case 3000:
        return "GODDESS";
        break;
      default:
        return level_titles[ob->query_level()];
        break;
    }
  }
  return level_titles[ob->query_level()];
}

is_idle(the_player)
{
  if(query_ip_number(the_player) && query_idle(the_player) > 200)
  {	
    return(" [IDLE:"+(query_idle(the_player)/60)+"m]");
  }
  return("");
}

PL(n,s,e)
{
  return ((n ? n : "no") + " " + s + (n == 1 ? "" : (e ? "es" : "s")));
}

who_top()
{
  int n,mortal,wizards,visiting,arches,gods;
  object *hubba;
  
  hubba = users();
  for(n = 0; n < sizeof(hubba); n++)
  {
    if (hubba[n]->query_level()<NEWBIE)
    {
      mortal++;
    }
    else if (hubba[n]->query_level()<VISITINGARCH && hubba[n]->short())
    {
      wizards++;
    }
    else if (hubba[n]->query_level()<ARCH && hubba[n]->short())
    {
      visiting++;
    }
    else if (hubba[n]->query_level()<GOD && hubba[n]->short())
    {
      arches++;
    }
    else if (hubba[n]->short())
    {
      gods++;
    }
  }
  
  write("\nThere are " +
	PL(mortal, "mortal", 0) + ", " +
	PL(wizards, "wizard", 0) + ", " +
	PL(visiting, "visiting arch", 1) + ", " +
	PL(arches, "arch", 1) + ", and " +
	PL(gods, "god", 0) +
	" currently logged on.  (total: " + sizeof(hubba) + ")\n");
  return 1;
}

guild_abbrev(who)
{
  return who->query_ghost() ? "&" : who->query_test_char() ? " + " :
  who->query_ever_player() ? "*" : " ";
}

short_wizards()
{
  object *obj;
  int gur, check, counter;
  string name, invis;

  obj = users();
  counter = sizeof(obj);
  
  for(gur = 0; gur < counter && obj[gur]->query_level() > MAXMORTAL; gur++)
  {
    if(!obj[gur]->short() || !obj[gur] || !(name = obj[gur]->query_name()))
    {
      continue;
    }
    if (check == 3)
    {
      write(sprintf("[%s] %-12s\n", level(obj[gur]), name));
      check = 0;
    }
    else
    {
      write(sprintf("[%s] %-12s ", level(obj[gur]), name));
      check ++;
    }
  }
}

short_who()
{
  object *obj;
  int gur, check, level;
  string name, invis;

  obj = users();
  who_top();
  write("\nAdmin and coders :\n\n");
  short_wizards();
  write("\n\n\nMortals :\n\n");
  for(gur = 0; gur < sizeof(obj); gur++)
  {
    level = obj[gur]->query_level() ;
    if (level > MAXMORTAL ||
	!obj[gur]->short() ||
	!(name = obj[gur]->query_name()) ||
	name == "logon")
    {
      continue;
    }
    if (check == 3)
    {
      write(sprintf("%2d %1s%-12s\n", level, guild_abbrev(obj[gur]), name));
      check = 0;
    }
    else
    {
      write(sprintf("%2d %1s%-12s ", level, guild_abbrev(obj[gur]), name));
      check ++;
    }
  }
  write("\n");
  return 1;
}
