/* /players/azid/ocean/galley_master.c */
#pragma strict_types
inherit "/std/obj/stdobj";
#define MAXINT 30000
#define MININT -30000
#define RELOADER "/areas/Backbone/Oceans/o/reload"

mixed *galleys = 
({
});

mixed *harbours = 
({ 
    ({1300, 1200,({"/areas/Northlands/NorthPole/o/rooms/n1","North Pole"}),}),  
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
    ({1200, -700,({"/areas/Tropical/Jungle/o/stranger/jungle/entrance",
		   "Jungle"}),}),
    ({1000, -600,({"/areas/Tropical/Jungle/o/daemon/tropic/harbor","Northern jungle"}),}),
    ({1600, -700,({"/areas/Tropical/Cannibal/o/harbour","Cannibal Island"}),}),
    ({500, 800, ({"/players/Citygreed/rooms/harbor1","City of greed",}),}),
    
});
mixed *land =
({
    ({
	({ 1200, 1200,"/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
	({ 1200, 1300,"/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
	({ 1500, 1300,"/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
	({ 1500, 1200,"/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
    }),
    ({
	({ 1100, 1100,"/areas/Northlands/NorthPole/o/rooms/berg2","iceberg"}),
	({ 1100, 1200,"/areas/Northlands/NorthPole/o/rooms/berg2","iceberg"}),
	({ 1200, 1200,"/areas/Northlands/NorthPole/o/rooms/berg2","iceberg"}),
	({ 1200,1100,"/areas/Northlands/NorthPole/o/rooms/berg2","iceberg"}),
    }),
    ({
	({ 1300, 1100,"/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
	({ 1300, 1200,"/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
	({ 1400, 1200,"/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
	({ 1400, 1100,"/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
    }),
    ({
	({ 1600, 1100,"/areas/Northlands/NorthPole/o/rooms/berg3","iceberg"}),
	({ 1600, 1200,"/areas/Northlands/NorthPole/o/rooms/berg3","iceberg"}),
	({ 1700, 1200,"/areas/Northlands/NorthPole/o/rooms/berg3","iceberg"}),
	({ 1700, 1100,"/areas/Northlands/NorthPole/o/rooms/berg3","iceberg"}),
    }),
    ({
	({ 1500, 1000,"/areas/Northlands/NorthPole/o/rooms/berg4","iceberg"}),
	({ 1500, 1100,"/areas/Northlands/NorthPole/o/rooms/berg4","iceberg"}),
	({ 1600, 1100,"/areas/Northlands/NorthPole/o/rooms/berg4","iceberg"}),
	({ 1600, 1000,"/areas/Northlands/NorthPole/o/rooms/berg4","iceberg"}),
    }),

    ({
	({ 4100, -300, "/areas/Northlands/Highlands/o/rooms/b/beach1","yodo"}),
	({ 4100, -200, "/areas/Northlands/Highlands/o/rooms/b/beach1","yodo"}),
	({ 4300, -200, "/areas/Northlands/Highlands/o/rooms/b/beach1","yodo"}),
	({ 4300, -300,"/areas/Northlands/Highlands/o/rooms/b/beach1","yodo"}),
    }),
    
    ({
	({ 4700, -300,"/areas/Northlands/Highlands/o/rooms/b/beach","yodo"}), 
	({ 4700, -200,"/areas/Northlands/Highlands/o/rooms/b/beach","yodo"}), 
	({ 4900, -200,"/areas/Northlands/Highlands/o/rooms/b/beach","yodo"}), 
	({ 4900, -300,"/areas/Northlands/Highlands/o/rooms/b/beach","yodo"}), 
    }),
    ({
        ({ 4300, -500, "/areas/Northlands/Highlands/o/rooms/b/b1","yodo"}), 
        ({ 4300, -400, "/areas/Northlands/Highlands/o/rooms/b/b1","yodo"}), 
        ({ 4700, -400, "/areas/Northlands/Highlands/o/rooms/b/b1","yodo"}), 
	({ 4700, -500, "/areas/Northlands/Highlands/o/rooms/b/b1","yodo"}), 
    }),

    ({
        ({ 2200, 800,"/areas/Northlands/Highlands/o/rooms/r1/rbeach","caledonia"}), 
	({ 2200, 900,"/areas/Northlands/Highlands/o/rooms/r1/rbeach","caledonia"}), 
	({ 3300, 900,"/areas/Northlands/Highlands/o/rooms/r1/rbeach","caledonia"}), 
	({ 3300, 800,"/areas/Northlands/Highlands/o/rooms/r1/rbeach","caledonia"}), 
    }),

    ({
	({ MININT, 200,"/areas/WestLars/Kaniarah/o/Room/Beach/beach3","mainland"}),
	({ MININT, 700,"/areas/WestLars/Kaniarah/o/Room/Beach/beach3","mainland"}),
	({ 0, 700,"/areas/WestLars/Kaniarah/o/Room/Beach/beach3","mainland"}),
	({ 0, 200,"/areas/WestLars/Kaniarah/o/Room/Beach/beach3","mainland"}),
    )},

    ({
        ({ 2800, -200,"/areas/Kordar/Kordar/o/Room/Capital/beach4","kordar"}),
	({ 2800, 500,"/areas/Kordar/Kordar/o/Room/Capital/beach4","kordar"}),
	({ 3600, 500,"/areas/Kordar/Kordar/o/Room/Capital/beach4","kordar"}),
	({ 3600, -200,"/areas/Kordar/Kordar/o/Room/Capital/beach4","kordar"}),
    }),

    ({
	({ 2400, -500,"/areas/Kordar/Kordar/o/Room/Island/smugglers_harbour",
	       "coranian island"}),
	({ 2400, -200,"/areas/Kordar/Kordar/o/Room/Island/smugglers_harbour",
	       "coranian island"}),
	({ 2500, -200,"/areas/Kordar/Kordar/o/Room/Island/smugglers_harbour",
	       "coranian island"}),
	({ 2500, -500,"/areas/Kordar/Kordar/o/Room/Island/smugglers_harbour",
	       "coranian island"}),
    }),

    ({
	({ 800, 500,"/areas/Bird/Aviary/o/room/bird/beach","small island"}),
	({ 800, 700,"/areas/Bird/Aviary/o/room/bird/beach","small island"}),
	({ 1000, 700,"/areas/Bird/Aviary/o/room/bird/beach","small island"}),
	({ 1000, 500,"/areas/Bird/Aviary/o/room/bird/beach","small island"}),
    )},

    ({
	({ 1000, -700,"/areas/Tropical/Jungle/o/stranger/jungle/entrance",
	       "jairman archipelago"}),
	({ 1000, -600,"/areas/Tropical/Jungle/o/stranger/jungle/entrance",
	      "jairman archipelago"}),
	({ 1200, -600,"/areas/Tropical/Jungle/o/stranger/jungle/entrance",
	      "jairman archipelago"}),
	({ 1200, -700,"/areas/Tropical/Jungle/o/stranger/jungle/entrance",
	      "jairman archipelago"}),
    }),

    ({
	({ 1600, -800."/areas/Tropical/Cannibal/o/room2",
	       "small island"}),
	({ 1600, -700,"/areas/Tropical/Cannibal/o/room2",
	       "small island"}),
	({ 1700, -700,"/areas/Tropical/Cannibal/o/room2",
	       "small island"}),
	({ 1700, -800,"/areas/Tropical/Cannibal/o/room2",
	       "small island"}),
    )},
	({ 300, 800,"/players/Citygreed/rooms/beach3","pirates island"}),
	({ 300, 900,"/players/Citygreed/rooms/beach3","pirates island"}),
	({ 500, 900,"/players/Citygreed/rooms/beach3","pirates island"}),
	({ 500, 800,"/players/Citygreed/rooms/beach3","pirates island"}),
    )},

});

object *galleys_obj;
#define SHIPOB 0
#define FROM 1
#define TO 2
#define SPEED 3
#define EVENTS 4
#define GL_SIZE 5


string short() {return "The Galley master2";}

int id(string str) { return str == "master2"||str == "galley master2";}

void
long() 
{ 
  write("This is the Galley master2 controling the galleys of Kingdoms.\n");
}

void
create_object()
{
    setuid();
    seteuid(getuid(this_object()));
    tell_object(this_player(),"I loaded.\n");
    dont_clean_up = 1;
    move_object(this_object(),"/wiz/a/azid/workroom");
}

string *
harbourp(int x, int y)
{
    int i;
    for(i=0;i<sizeof(harbours);i++) {
	if (x==(int)harbours[i][0] && y==(int)harbours[i][1]) {
	    return (string *)harbours[i][2];
	}
    }
    return 0;
}

mixed *
wreckedp(int x_loc, int y_loc, int x_dest, int y_dest)
{
    int i;
    mixed *coast;
    mixed *points;
    mixed point;
    
    points = ({});
    for (j = 0; j < sizeof(land); j++ )
    {
	coast = land[j];
	c0 = coast[sizeof(coast) - 1];
	for (i=0;i<sizeof(coast);i++)
	{
	    c1 = coast[i];
	    if (point = crossing_line(x_loc, y_loc, x_dest, y_dest, c0[0],c0[1],c1[0],c1[1]))
		points += ({ ({ point[0], land[i][2..3] }) )};
	    c0 = c1;
	}
    }
    if (!sizeof(points))
	return 0;
        
    for (point = points[0], i = 1; i < sizeof(points); i++)
	if (point[0] > points[i][0])
	    point = points[i];
    return point;
}

string
nearp(int x_loc, int y_loc, int x_dest, int y_dest)
{
    int i, cs;
    mixed *coast;
    int dx, dy, l;
    mixed *lines;
    
    for (i=0;i<sizeof(land);i++)
    {
	cs = sizeof(coast = land[i]);
	for (j = 0; j < cs; j++)
	{
	    dy = (x2 - x1);
	    dx = - (y2 - y1);
	    l = sqrt(dy*dy + dx*dx);
	    lines +=({ x1 + xd * 100 / l , y1 + xy * 100 / l,
			   x2 + dx * 100 / l , y2 + dy * 100 / l });
	}

    }


    return 0;
}

int
travel_time(int x, int y, int speed)
{
    return sqrt(x * x + y * y) * 2 / (3 * speed);
}

float *
crossing_line(float x1, float y1, float x2, float y2,
	 float x3, float y3, float x4, float y4)
{
    float y12, x34, x12, y34;
    float y13, x13, den;
    float numa, numb;
    
    den = (y12 = y1 - y2) * (x34 = x3 - x4) - 
	(x12 = x1 - x2) * (y34 = y3 - y4);
    numa = (y13 = y1 - y3) * x34 - (x13 = x1 - x3)*y34;
    numb = y13 * x12 - x13 * y12;
    r1 = numa / den;
    r2 = numb / den;
    if ( r1 > 1.0 ||  r2 > 1.0 ||   r1 < 0.0 || r2 < 0.0)
	return 0;
    return ({ r1, r2 });
}

mk_line()
{
}
