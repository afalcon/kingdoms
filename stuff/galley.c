/* /players/azid/ocean/galley.c */
inherit "/std/room/room";
int x_loc, y_loc;
int x_dest, y_dest;
int x_home,y_home;
int true_speed, x_speed, y_speed;
int wrecked, docked;
string *harbour;
object captain;
int hit_points;
string isnear;

reset(arg) {
    dont_clean_up = 1;
  if (!present("galley captain", this_object())) {
    move_object(captain = clone_object("/areas/Backbone/Oceans/o/captain"),
		this_object());
    captain->set_galley(this_object());
  }
  if (!present("map table", this_object()))
    move_object(clone_object("/areas/Backbone/Oceans/o/scroll"),
		this_object());
    if (arg) return;
    set_skip_obvious(1);
    long_desc = "You are standing on the deck of a trading Galley. "
      + "There are about twenty rowers manning rows, and a drum "
	+ "beater awaiting orders from the Captain.\n";
  set_light(1);
  items = ({"rowers","They seem better taken care of than you might expect",
	      "rower","He catches your eye, and stares back at you",
	      "galley","It's pretty small, as far as Galleys go",
	      "rows","The rowers take good care of their rows",
	      "deck","It's perfectly polished",
	      "drum","It looks suspiciously like a wine barrel..",
	      "beater","Seems like a nice enough fellow, except for that scar..",
	      "drum beater","Seems like a nice enough fellow, except for that scar.."
	      });
    call_out("check_place", 30 * 5 + random(30 * 5));
}

id(str) {
  if (this_player()&&environment(this_player())==this_object())
    return items && member_array(str,items) != -1;
  return str == "ship" || str == "galley" || str == "galley ship";
}

short() { 
  if (this_player()&&environment(this_player())==this_object())
    return "Deck of the Galley Ship";
  return "A Galley ship";
}

long(str) {
  if (this_player()&&environment(this_player())==this_object())
    return ::long(str);
  else
    write("This is a fairly small Galley, as far as Galleys go. "
	  + "The gangplank is down, allowing you to board, if you like.\n");
}

init() {
  if (this_player()&&environment(this_player())==this_object()) 
  {
      add_action("out","out");
      add_action("out", "disembark");
      add_action("quit", "quit");
  }
  else
      add_action("board","board");
}

call_id(arg1, arg2)
{
    return arg1->id(arg2);
}

board(str) 
{
    mixed *inv2;
    object *inv;
    int i;
    string sub_str;
    
    inv2 = ({});
    
    if (str && sscanf(str, "%s %d", sub_str, i) == 2)
    {
	if (!id(sub_str)) return 0;
	
	if (i <= 0)
	    return 0;
	inv = filter(all_inventory(environment(this_object())),
		     "call_id", this_object(), sub_str);
	if (i > sizeof(inv))
	    return notify_fail("There are not that many galleys here.\n");
	if (inv[i - 1] != this_object())
	    return 0;
    }
    else
	if (str && str != "" && !id(str)) return 0;
    
    write("You board the Galley.\n");
    this_player()->move_player(" aboard a galley",
			       this_object(),
			       " on the gangplank");
    return 1;
}

out() {
  if (docked) {
      this_player()->move_player(" on the gangplank",
				 environment(this_object()),
				 " from the galley");
  }
  else 
      write("You think there will be a looong swim before you reach land" +
	    " and consider it better to stay aboard.\n");
  return 1;
}

go_home()
{
  x_loc = x_home; y_loc = y_home;
  x_dest = x_home; y_dest = y_home;
  true_speed = 0;
  wrecked = 0;
  docked = 0;
  environment()->exit();
  efun::move_object("/areas/Backbone/Oceans/o/sea");
  environment()->object_enters();
  /* make it go home */
  isnear = "/areas/Backbone/Oceans/o/galley_master"->nearp(x_loc,y_loc);
  
  
  if (harbour="/areas/Backbone/Oceans/o/galley_master"->
      harbourp(x_loc,y_loc)) {
	  environment()->exit();
	  efun::move_object(harbour[0]);
	  environment()->object_enters();
    tell_room(this_object(),"The Captain mumbles: We are docked at "+
	      harbour[1]+".\n");
    tell_room(harbour[0],"A Galley pulls into dock.\n");
    docked=1;
  }
  set_heart_beat(0);
  return 1;
}

set_homei(int x,y) {
  x_home=x;y_home=y;
  return;
}
set_desti(int x,y) {
  x_dest=x; y_dest=y;
  return;
}
set_loci(int x,y) {
  x_loc=x;y_loc=y;
  true_speed = 0;
  wrecked = 0;
  docked = 0;
  environment()->exit();
  efun::move_object("/areas/Backbone/Oceans/o/sea");
  environment()->object_enters();
  isnear = "/areas/Backbone/Oceans/o/galley_master"->nearp(x_loc,y_loc);
  
  
  if (harbour="/areas/Backbone/Oceans/o/galley_master"->
      harbourp(x_loc,y_loc))
    {
	  environment()->exit();
	  efun::move_object(harbour[0]);
	  environment()->object_enters();
    tell_room(this_object(),"The Captain mumbles: We are docked at "+
	      harbour[1]+".\n");
    tell_room(harbour[0],"A Galley pulls into dock.\n");
    docked=1;
  }
  set_heart_beat(0);
  return;
}

set_speedi(int s)
{
    if (s >= 0 && s <= 50)
    {
	true_speed = s;
	if (s)
	    set_heart_beat(2);
	else
	    set_heart_beat(0);
    }
}

set_dest(string str) {
  if (!str || str == "" ) return 0;

  sscanf(str, "%d %d", x_dest, y_dest);
  write("Destination set to  X: "+x_dest+"   Y: "+y_dest+"\n");
  say((this_player()->query_name())+
	    " tells the Captain to change course.\n",this_player());
  calculate_vectors();
  return 1;
}

set_speed(string str) {
  if (!str || str == "") return 0;

  if (sscanf(str, "%d", true_speed) != 1) return 0;
  if ((x_loc != x_dest) || (y_loc != y_dest)) {
    if (true_speed > 50) {
      write("The Captain tells you: I shall not beat rowers that hard!\n");
      say("The Captain stops the Galley and glares at "
	  + (this_player()->query_name()) + ".\n",this_player());
      true_speed = 0;
    }
    else if (true_speed < 5) {
      write("The Captain tells you: We shall never get there.\n");
      say("The Captain stops the Galley and glares at "
	  + (this_player()->query_name()) + ".\n",this_player());
      true_speed = 0;
    }
    else {
      write("Speed set to: "+true_speed+"\n");
      say((this_player()->query_name())+
	  " asks the Captain to change"
	  + " speed.\n",this_player());
      docked = 0;
      environment()->exit();
      efun::move_object("/areas/Backbone/Oceans/o/sea");
      environment()->object_enters();
    }
    calculate_vectors();
  }
  else if (true_speed != 0) {
    write("The Captain mumbles: You want move in circles?\n");
    say("The Captain looks at "+(this_player()->query_name())
	+ " quizzically.\n",this_player());
    true_speed=0;
  };
  set_heart_beat(2);
  return 1;
}

report() {
  write("Location,    X : "+x_loc+"   Y : "+y_loc+"\n");
  write("Destination, X : "+x_dest+"   Y : "+y_dest+"\n");
  write("Speed : "+true_speed+"\n");
  say((this_player()->query_name())+
      " asks the Captain for a report.\n",this_player());
  if(docked)
      tell_room(this_object(),"The Captain mumbles: We are docked at "+
		harbour[1]+".\n");
  else if (isnear = "/areas/Backbone/Oceans/o/galley_master"->nearp()) {
    write("The Captain tells you we're close to " + isnear + ".\n");
    tell_room(this_object(),"The Captain gets a worried look to his face.\n");
  }
  return 1;
}

heart_beat() {
  object wreck_place;
  string near;
  if (wrecked == 1) {
    set_heart_beat(0);
    return;
  }
  if(true_speed == 0) {
    set_heart_beat(0);
    return;
  }
  calculate_vectors();
  if ((x_dest != x_loc) || (y_dest != y_loc)) {
    if (true_speed != 0) {
      x_loc += x_speed;
      y_loc += y_speed;
    }
  }
  else true_speed=0;
  
  if(near = "/areas/Backbone/Oceans/o/galley_master"->nearp(x_loc,y_loc)) 
  {
      if(!isnear) 
      {
	  tell_room(this_object(),"The Captain mumbles: We close to " +
		    near + ".\n");
	  isnear = near;
      }
  }
  else
      if(isnear)
      {
	  tell_room(this_object(),
		    "The Captain says: We move away from " +
		    isnear + ", again.\n");
	  isnear = 0;
      }
  
  if ((x_loc == x_dest) && (y_loc == y_dest)) {
    true_speed = 0; x_speed = 0; y_speed = 0;
    tell_room(this_object(),"The Captain says: We are at destination.\n");
    set_heart_beat(0);
    if (harbour="/areas/Backbone/Oceans/o/galley_master"->
	harbourp(x_loc,y_loc)) {
	    environment()->exit();  
	    efun::move_object(harbour[0]);
	    environment()->object_enters();
      tell_room(this_object(),"The Captain mumbles: We are docked at "+
		harbour[1]+".\n");
      tell_room(harbour[0],"A Galley pulls into the dock.\n");
      docked=1;
    }
    return;
  } 
  
  if(wreck_place =
     "/areas/Backbone/Oceans/o/galley_master"->wreckedp(x_loc,y_loc))
      {
	  object *inv;
	  int i;
	  tell_room(this_object(),"the Captain screames: Abandon ship!!\n");
	  /* over board code */
	  inv = all_inventory(this_object());
	  tell_room(this_object(),
		    "You jump out into the ocean....\n\n\nAfter what seems "
		    + "an eternity, you wake up, coughing up sea water.\n");
	  for(i=0; i < sizeof(inv); i++) {
	      if(!(inv[i]->id("galley captain"))
		 && !(inv[i]->id("map table"))) {
		     move_object(inv[i],wreck_place);
		 }
	      set_heart_beat(0);
	      wrecked=1;
	      remove_call_out("go_home");
	      call_out("go_home",600);
	  }
      }
}

calculate_vectors() {
  int x_dif,y_dif;
  int distance,increments;
  if (true_speed == 0) {
    x_speed=0;
    y_speed=0;
    return;
  }
  x_dif = x_dest - x_loc; y_dif = y_dest - y_loc;
  distance = ftoi(sqrt(itof(x_dif * x_dif + y_dif * y_dif)));
  if (distance == 0) 
      {
	  x_speed = 0;
	  y_speed = 0;
	  return;
      }
  
  x_speed = (2 * true_speed * x_dif) / (3 * distance);
  y_speed = (2 * true_speed * y_dif) / (3 * distance);

  if ((x_dif - x_speed) * x_dif < 0) x_speed = x_dif;
  if ((y_dif - y_speed) * y_dif < 0) y_speed = y_dif;
  
  return;
}

damage_me(arg)
{
    hit_points -= arg;
}

query_speed() { return true_speed; }

query_loc() { return ({x_loc, y_loc}); }

query_dest() { return ({ x_dest, y_dest}); }

start_move() { set_heart_beat(2); }
void
check_place()
{
    object *inv = all_inventory(this_object());
    int i;
    
    if (!environment())
	return;
    if (find_call_out("check_place") == -1)
	call_out("check_place", 30 * 5 + random(30 * 5));

    if (wrecked || !captain)
	return;

    for(i = 0; i < sizeof(inv); i++)
	if (query_ip_number(inv[i]))
	    return;

    if (environment() == find_object("/areas/Backbone/Oceans/o/sea") ||
	(sizeof(filter(all_inventory(environment()),
		       "chk_galley", this_object())) > 1 &&
	 x_loc != x_home && y_loc != y_home))
	go_home();
    
    return;   
}

int
chk_galley(object ob)
{
    return file_name(ob)[0..26] == "/areas/Backbone/Oceans/o/galley#";
}

void
destroy_object()
{
    destruct(present("galley captain"));
    destruct(present("map table"));
}

int
quit(string str)
{
    if (!captain || captain->query_attack() == this_player())
	this_player()->set_optional_login_room(file_name(this_object()));
    return 0;
}

int
query_ok_to_login()
{
    return !wrecked;
}
