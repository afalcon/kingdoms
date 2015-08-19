#pragma strict_types
inherit "/std/obj/stdobj";
#define MININT -30000

mixed *harbours = 
({ 
  ({ 1300, 1200, ({"/areas/Northlands/NorthPole/o/rooms/n1","North Pole"}),}),  
  ({ 4500, -500, ({"/areas/Northlands/Highlands/o/rooms/b/b1","Shodo"}),}),  
  ({ 2500, 800, ({"/areas/Northlands/Highlands/o/rooms/r1/f1","Caledonia"}),}), 
  ({ 800, 600, ({"/areas/Bird/Aviary/o/room/bird/har1","Bird Island",}),}),
  ({ 0, 500, ({"/room/jetty2","Jetty",}),}),
  ({ 0, 300, ({"/areas/Kordar/Kordar/o/Room/Entrance/seaside","Beach",}),}),
  ({ 2400, -400, ({ "/areas/Kordar/Kordar/o/Room/Island/island_harbour", "Small Harbour",}),}),
  ({ 2500, -300, ({"/areas/Kordar/Kordar/o/Room/Island/capital_harbour", "Small Harbour"}),}),
  ({ 2800, 100, ({"/areas/Kordar/Kordar/o/Room/Capital/harbour","Harbour",}),}),
  ({ 1200, -700, ({"/areas/Tropical/Jungle/o/stranger/jungle/entrance", "Jungle"}),}),
  ({ 1000, -600, ({"/areas/Tropical/Jungle/o/daemon/tropic/harbor","Northern jungle"}),}),
  ({ 1600, -700, ({"/areas/Tropical/Cannibal/o/harbour","Cannibal Island"}),}),
  ({ 500, 800, ({"/players/Citygreed/rooms/harbor1","City of greed",}),}),
});

mixed *land =
({
	({ 1250, 1350, 50, 150, "/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
	({ 1150, 1150, 50, 50, "/areas/Northlands/NorthPole/o/rooms/berg2","iceberg"}),
	({ 1150, 1350, 50, 50, "/areas/Northlands/NorthPole/o/rooms/berg1","iceberg"}),
	({ 1150, 1650, 50, 50, "/areas/Northlands/NorthPole/o/rooms/berg3","iceberg"}),
	({ 1050, 1550, 50, 50, "/areas/Northlands/NorthPole/o/rooms/berg4","iceberg"}),
	({ -250, 4200, 50, 100,"/areas/Northlands/Highlands/o/rooms/b/beach1","yodo"}),
	({ -250, 4800, 50, 100, "/areas/Northlands/Highlands/o/rooms/b/beach","yodo"}), 
	({ -450, 4500, 50, 200, "/areas/Northlands/Highlands/o/rooms/b/b1","yodo"}), 
	({ 850, 2750, 50, 550, "/areas/Northlands/Highlands/o/rooms/r1/rbeach","caledonia"}), 
	({ 450, -1500, 250, 1500, "/areas/WestLars/Kaniarah/o/Room/Beach/beach3","mainland"}),
	({ 150, 3200, 350, 400, "/areas/Kordar/Kordar/o/Room/Capital/beach4","kordar"}),
	({ -350, 2450, 150, 50, "/areas/Kordar/Kordar/o/Room/Island/smugglers_harbour","coranian island"}),
	({ 600, 900, 100, 100, "/areas/Bird/Aviary/o/room/bird/beach","small island"}),
	({ -650, 1100, 50, 100, "/areas/Tropical/Jungle/o/stranger/jungle/entrance", "jairman archipelago"}),
	({ -750, 1650, 50, 50, "/areas/Tropical/Cannibal/o/room2", "cannibal island"}),
	({ 850, 400, 50, 100, "/players/Citygreed/rooms/beach3","pirates island"}),
});

string short() { return "The harbor master";}
int id(string str) { return str == "master" || str == "harbor master";}
void long() { write("This is the harbor master of Kingdoms.\n"); }

void
create_object()
{
    setuid();
    seteuid(getuid(this_object()));
    tell_object(this_player(),"I loaded.\n");
    dont_clean_up = 1;
    move_object(this_object(),"/wiz/b/bart/rooms/void");
}

int harbourp(int x, int y) {
  int i;
  for(i=0;i<sizeof(harbours);i++) {
    if (x==(int)harbours[i][1] && y==(int)harbours[i][0]) {
      return 1;
    }
  }
  return 0;
}

int landp(int row, int col) {
  int i;
  for(i = 0; i < sizeof(land); i++) {
    if ((row <= ((int)land[i][0] + (int)land[i][2])) &&
        (row >= ((int)land[i][0] - (int)land[i][2])) &&
        (col <= ((int)land[i][1] + (int)land[i][3])) &&
        (col >= ((int)land[i][1] - (int)land[i][3]))) {
      return 1;
    }
  }
  return 0;
}

string wreckp(int row, int col) {
  int i;
  for(i = 0; i < sizeof(land); i++) {
    if ((row <= ((int)land[i][0] + (int)land[i][2])) &&
        (row >= ((int)land[i][0] - (int)land[i][2])) &&
        (col <= ((int)land[i][1] + (int)land[i][3])) &&
        (col >= ((int)land[i][1] - (int)land[i][3]))) {
      return (string)land[i][4];
    }
  }
  return "";
}

