/* /players/azid/ocean/captain.c */
inherit "/std/living/monster";
#define G environment(this_object())
string my_attacker = "";

reset(arg) {
    ::reset(arg);
    if (arg) return;
    set_name("captain");
    set_alt_name("galley captain");
    set_short("Galley Captain");
    set_long("This is the Captain of the Galley you're on. You can tell "
	     + "him where you want to go, and how fast, and he'll see to it "
	     + "that the rowers get you there. Type info for the commands "
	     + "that he understands. (He knows very little English)\n");
    set_level(12);
    set_race("human");
    set_wc(15);
    set_new_ac(30);
    set_db(20);
    set_skill("combat",10);
    set_skill("unarmed",10);
    set_skill("perception",93);
    set_skill("resist", 90);
}

init() {
    add_action("info","info");
    add_action("set_dest","destination");
    add_action("set_speed","speed");
    add_action("report","report");
    if (this_player()->query_real_name() == my_attacker)
	attacked_by(this_player());
}
 
info() {
  write("destination (x) (y) : set your destination point.\n");
  write("speed (x) : sets your speed.\n");
  write("report : reports your status.\n");
  say((this_player()->query_name())+" asks the Captain something.\n");
  return 1;
}
 
set_dest(string str)
{
    if (!attacker_ob || !present(attacker_ob, G))
	return G->set_dest(str);
    else
	write("The Captain is to busy fighting.\n");
    return 1;
}
set_speed(string str)
{
    if (!attacker_ob || !present(attacker_ob, G))
	return G->set_speed(str);
    else
	write("The Captain is to busy fighting.\n");
    return 1;
}
report()
{
    if (attacker_ob && present(attacker_ob, G))
	write("The Captain is to busy fighting.\n");
    else
	return G->report();
    return 1;
}

hit_player(dam, type)
{
  int *loc = G->query_loc();

  my_attacker = this_player()->query_real_name();
  if ("/areas/Backbone/Oceans/o/galley_master"->
      harbourp(loc[0],loc[1]) &&
      find_call_out("move_away") == -1)
    call_out("move_away", 2);
  G->set_speedi(0);
  return ::hit_player(dam, type);
}
reduce_hit_point(dam)
{
  int *loc = G->query_loc();

  my_attacker = this_player()->query_real_name();
  if ("/areas/Backbone/Oceans/o/galley_master"->
      harbourp(loc[0],loc[1]) &&
      find_call_out("move_away") == -1)
    call_out("move_away", 2);
  G->set_speedi(0);
  return ::reduce_hit_point(dam);
}
attacked_by(ob)
{
  int *loc = G->query_loc();

  my_attacker = this_player()->query_real_name();
  if ("/areas/Backbone/Oceans/o/galley_master"->
      harbourp(loc[0],loc[1]) &&
      find_call_out("move_away") == -1)
    call_out("move_away", 2);
  G->set_speedi(0);
  return ::attacked_by(ob);
}

static move_away()
{
    int *loc = G->query_loc();
    int x_loc = loc[0];
    int y_loc = loc[1];

    if ("/areas/Backbone/Oceans/o/galley_master"->wreckedp(x_loc + 50, y_loc + 50))
    {
	G->set_loci(x_loc - 50, y_loc - 50);
	G->set_desti(x_loc - 50, y_loc - 50);
    }
    else
    {
	G->set_loci(x_loc + 50, y_loc + 50);
	G->set_desti(x_loc - 50, y_loc - 50);
    }

    tell_room(G,"The galley departs from the harbour.\n");
}
second_life()
{
    int *loc = G->query_loc();

    write_file("/areas/Backbone/Oceans/o/KILLS", ctime(time()) + ": " +
	       this_player()->query_real_name() + " killed the Captain");
    if ("/areas/Backbone/Oceans/o/galley_master"->harbourp(loc[0], loc[1]))
	write_file("/areas/Backbone/Oceans/o/KILLS", " and is stuck");
    write_file("/areas/Backbone/Oceans/o/KILLS", ".\n");
    
    return ::second_life();
}
