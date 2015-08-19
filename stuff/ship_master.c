/* /players/azid/ocean/galley_master.c */
inherit "/std/obj/stdobj";
#define MAXINT 30000
#define MININT -30000
mixed *galleys;
mixed *harbours;
mixed *land;
mixed *near;
object *galleys_obj;

short() {return "The Galley master";}
id(str) { return str == "master"||str == "galley master";}
long() 
{ 
  write("This is the Galley master controling the galleys of Kingdoms.\n");
}
reset(arg) {
  int i;
  object g;
  if (arg) return;
  galleys = 
  ({
    ({4500,-500}), 
    ({0,500}),
    ({0,300}),
    ({800,600}),
    ({2400,-400}),
    ({2500,-300}),
    ({2800,100}),
    ({1600,-700}),
  });
  harbours = 
  ({ 
    ({4500, -500,({"/areas/Northlands/Highlands/o/rooms/b/b1","Shodo"}),}),  
    ({2500, 800,({"/areas/Northlands/Highlands/o/rooms/r1/f1","Caledonia"}),}), 
    ({800,  600,({"/areas/Bird/Aviary/o/room/bird/har1","Bird Island",}),}),
    ({0,  500,({"/room/jetty2","Jetty",}),}),
    ({0,  300,({"/areas/Kordar/Kordar/o/Room/Entrance/seaside","Beach",}),}),
    ({2400,  -400,({ "/areas/Kordar/Kordar/o/Room/Island/island_harbour",
		      "Small Harbour",}),}),
    ({2500,  -300,({"/areas/Kordar/Kordar/o/Room/Island/capital_harbour",
		     "Small Harbour"}),}),
    ({2800,  100,({"/areas/Kordar/Kordar/o/Room/Capital/harbour","Harbour",}),}),
    ({1600, -700,({"/wiz/s/stranger/jungle/entrance",
		       "Jungle"}),}), 
			  
  });
  land =
  ({
    ({ 4100, 4300,-300,-200,"/areas/Northlands/Highlands/o/rooms/b/beach1","yodo"}),
    ({ 4700, 4900, -300 -200,"/areas/Northlands/Highlands/o/rooms/b/beach","yodo"}), 
    ({ 4300,4700,-500,-400, "/areas/Northlands/Highlands/o/rooms/b/b1","yodo"}), 
    ({ 2200,3300,800,900,"/areas/Northlands/Highlands/o/rooms/r1/rbeach","caledonia"}), 
    ({ MININT, 0, 200, 700,"/areas/WestLars/Kaniarah/o/Room/Beach/beach3","mainland"}),
    ({ 2800, 3600, -200, 500,"/areas/Kordar/Kordar/o/Room/Capital/beach4","kordar"}),
    ({ 2400, 2500, -500, -200,
	"/areas/Kordar/Kordar/o/Room/Island/smugglers_harbour","coranian island"}),
    ({ 800, 900, 500, 600,"/areas/Bird/Aviary/o/room/bird/beach","small island"}),
    ({ 1500, 1600, -700, -600,"/wiz/s/stranger/jungle/entrance",
	"jairman archipelago"}) 
  });

  galleys_obj=allocate(sizeof(galleys));
  move_object(this_object(),"/sys/admin/room/admin_room");
  for (i=0;i<sizeof(galleys);i++) {
    move_object(galleys_obj[i]=clone_object("/areas/Backbone/Oceans/o/galley"),
		"/areas/Backbone/Oceans/o/sea");
    galleys_obj[i]->set_homei(galleys[i][0],galleys[i][1]);
    galleys_obj[i]->go_home();
  }
}

harbourp(int x,y)
{
  int i;
  for(i=0;i<sizeof(harbours);i++)
    if (x==(int)harbours[i][0] && y==(int)harbours[i][1]) {
      return (string *)harbours[i][2];
    }
  return 0;
}

wreckedp(int x,y)
{
  int i;
  for (i=0;i<sizeof(land);i++)
    if (x > land[i][0] && x < land[i][1] &&
	y > land[i][2] && y < land[i][3])
      return (string)land[i][4];
  return 0;
}

nearp(int x,y)
{
  int i;
  for (i=0;i<sizeof(land);i++)
    if (x > land[i][0] - 100 && x < land[i][1] + 100 &&
	y > land[i][2] - 100 && y < land[i][3] + 100 )
      return (string)land[i][5];
  return 0;
}

restart()
{
  int i;
  destruct(find_object("/areas/Backbone/Oceans/o/galley"));
  for (i=0;i<sizeof(galleys_obj);i++) {
      if (galleys_obj[i])
        destruct(galleys_obj[i]);
    move_object(galleys_obj[i] = clone_object("/areas/Backbone/Oceans/o/galley"),
		"/areas/Backbone/Oceans/o/sea");
    galleys_obj[i]->set_homei(galleys[i][0],galleys[i][1]);
    galleys_obj[i]->go_home();
  }
}


angle(xt, yt, x1, y1, x2, y2)
{
    return arctan2(x1 - xt, y1 - yt) - arctan2(x2 - xt, y2 - xt);
}

/*

ks = (yt - yb) / (xt - xb);
kl = (y2 - y1) / (x2 - x1);

ms = yb - ks * xb || yt - ks * xt;
ml = y1 - kl * x1 || y2 - kl * x2



((ms - ml) / (kl - ks) - xb) / (xt - xb) > 1
((ms - ml) / (kl - ks) - x1) / (x2 - x1) > 1

    [ (ms - ml) / (kl - ks),
      (kl * ms - ks * ml) / (kl - ks) ]



(ms - ml) / (kl - ks) - xt <= 0 &&
(ms - ml) / (kl - ks) - xb >= 0
