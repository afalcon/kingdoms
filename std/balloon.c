inherit "/std/obj/treasure";

#define DEST query_dest()
#define DEST2 query_dest2()
#define NAMEDEST query_name_dest()
#define NAMEDEST2 query_name_dest2()
#define DOCKED_TIME query_docked_time()
#define FLYING_TIME query_fly_time()
#define BALLOON_NAME query_balloon_name()
#define ID query_id()

string 	dest = "", 
	dest2 = "", 
	name_dest = "", 
	name_dest2 = "", 
	balloon_name = "";
int 	balloon_id, 
	flying = 0, 
	where_to = 0, 
	fly_time, 
	docked_time;
object 	balloon; 

reset(arg) {
  if (arg) return;
  set_name("balloon");
  set_alias(ID);
  set_alt_name(BALLOON_NAME);
  set_light(1);
  set_short("A "+BALLOON_NAME);
  call_out("launch",DOCKED_TIME);
}

long()
{
  if(present(this_player(),this_object()))
    {
      return write("You are on "+BALLOON_NAME+" ["+NAMEDEST2+" to "+NAMEDEST+"].");
      if(!query_flying() && !query_destination())
        return write("The balloon is docked on "+NAMEDEST+".");
      if(!query_flying() && query_destination())
        return write("The balloon is docked on "+NAMEDEST2+".");
      if(query_flying() && !query_destination())
        return write("The balloon is flying towards "+NAMEDEST2+".");
      if(query_flying() && query_destination())
        return write("The balloon is flying towards "+NAMEDEST+".");
    return write("Type 'jump' to get out of the balloon.");
    }
  if(!present(this_player(),this_object()))
    return write("A "+BALLOON_NAME+" that connects "+NAMEDEST+" with "+NAMEDEST2+".");
}
  
init()
{
  if(!DEST || !DEST2 || !DOCKED_TIME || !FLYING_TIME || !BALLOON_NAME || ! NAMEDEST || !NAMEDEST2 || !BALLOON_NAME)
    {
      write("Illegal balloon.\n");
      this_object()->destroy();
      return 1;
    }
  ::init();
  add_action("climb","climb");
  add_action("climb","enter");
  add_action("jump","jump");
  add_action("jump","leave");
}

climb(str)
{
  if(str== "balloon" || str == lower_case(BALLOON_NAME))
  {
    balloon = present(this_player(), environment(this_object()));
    if(balloon)
    {
      write("You climb in the "+BALLOON_NAME+".\n");
      say(this_player()->query_cap_name()+" climbs in the "+BALLOON_NAME+".\n");
      this_player()->move(this_object());
      this_player()->command("look");
      say(this_player()->query_cap_name()+" arrives.\n");
      return 1;
    }
    write("You are inside the balloon.\n");
    return 1;
  }
  return 0;
}

jump()
{
  balloon = present(this_player(), this_object());
  if(balloon && flying==0)
  {
    write("You jump out of the balloon.\n");
    say(this_player()->query_cap_name()+" jumps out of the balloon.\n");
    if(!where_to) 
      this_player()->move(DEST);
    if(where_to)
      this_player()->move(DEST2);
    this_player()->command("look");
    say(this_player()->query_cap_name()+" arrives from the "+BALLOON_NAME+".\n");
    return 1;
  }
  if(balloon && flying==1)
  {
    write("You can't jump out of the balloon while it's still in the air.\n");
    say(this_player()->query_cap_name()+" tries to jump out of the balloon while it is still in the air.\n");
    return 1;
  }  
}

launch()
{
  if(!DEST || !DEST2 || !DOCKED_TIME || !FLYING_TIME || !BALLOON_NAME || ! NAMEDEST || !NAMEDEST2 || !BALLOON_NAME)
    {
      this_object()->destroy();
      return 1;
    }
  if(!where_to) {
    tell_room(DEST,"The balloon flies away.\n");
  }
  if(where_to) {
    tell_room(DEST2,"The balloon flies away.\n");
  }
  move_object(this_object(),"/wiz/b/bart/rooms/sky");
  if(!where_to) {
    tell_room("/wiz/b/bart/rooms/sky","Balloon update: "+BALLOON_NAME+" heading for "+NAMEDEST2+".\n");
    tell_room(this_object(),"The balloon flies towards "+NAMEDEST2+".\n");
  }
  if(where_to) {
    tell_room("/wiz/b/bart/rooms/sky","Balloon update: "+BALLOON_NAME+" heading for "+NAMEDEST+".\n");
    tell_room(this_object(),"The balloon flies towards "+NAMEDEST+".\n");
  }
  flying=1;
  if(!where_to) {
    if(environment(this_object())) {
      call_out("destination",FLYING_TIME);
    }
  }
  if(where_to) {
    if(environment(this_object())) {
  	  call_out("start",FLYING_TIME);
    }
  }
}

hang_time()
{
  if(environment(this_object()))
  {
    if(!where_to) {
      tell_room(DEST,"The balloon flies away.\n");
    }
    if(where_to) {
      tell_room(DEST2,"The balloon flies away.\n");
    }
    move_object(this_object(),"/wiz/b/bart/rooms/sky");
    if(!where_to) {
      tell_room("/wiz/b/bart/rooms/sky","Balloon update: "+BALLOON_NAME+" heading for "+NAMEDEST2+".\n");
      tell_room(this_object(),"The balloon flies towards "+NAMEDEST2+".\n");
    }
    if(where_to) {
      tell_room("/wiz/b/bart/rooms/sky","Balloon update: "+BALLOON_NAME+" heading for "+NAMEDEST+".\n");
      tell_room(this_object(),"The balloon flies towards "+NAMEDEST+".\n");
    }
    flying=1;
    if(!where_to) {
      if(environment(this_object())) {
        call_out("destination",FLYING_TIME);
      }
    }
    if(where_to) {
      if(environment(this_object())) {
    	  call_out("start",FLYING_TIME);
      }
    }
  }
}

destination()
{
  if(environment(this_object()))
  {
    where_to=1;
    flying=0;
    tell_room("/wiz/b/bart/rooms/sky","Balloon update: "+BALLOON_NAME+" is now in "+NAMEDEST2+".\n");
    tell_room(DEST2,"A balloon gently lands on the dock.\n");
    move_object(this_object(),DEST2);
    tell_room(this_object(),"The balloon finally reaches "+NAMEDEST2+".\n");
    if(environment(this_object()))
      call_out("hang_time",DOCKED_TIME);
  }
}

start()
{
  if(environment(this_object()))
  {
    flying =0;
    where_to=0;
    tell_room("/wiz/b/bart/rooms/sky","Balloon update: "+BALLOON_NAME+" is now in "+NAMEDEST+".\n");
    tell_room(DEST,"A balloon gently lands on the dock.\n");
    move_object(this_object(),DEST);
    tell_room(this_object(),"The balloon finally reaches "+NAMEDEST+".\n");
    if(environment(this_object()))
      call_out("hang_time",DOCKED_TIME);
  }
}

query_flying() { return flying; }
query_destination() { return where_to; }

set_dest(str) { dest = str; }
query_dest() { return dest; }

set_dest2(str) { dest2=str; }
query_dest2() { return dest2; }

set_name_dest(str) { name_dest = str; }
query_name_dest() { return name_dest; }

set_name_dest2(str) { name_dest2 = str; }
query_name_dest2() { return name_dest2; }

set_docked_time(n) { docked_time = n; }
query_docked_time() { return docked_time; }

set_fly_time(n) { fly_time = n; }
query_fly_time() { return fly_time; }

set_balloon_name(str) { balloon_name = str; }
query_balloon_name() { return balloon_name; }

set_id(str) { balloon_id = str; }
query_id() { return balloon_id; }
 
