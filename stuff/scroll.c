/* /players/azid/ocean/scroll.c */
inherit "/std/obj/stdobj";
id(str) 
{
    return str == "table" || str == "map"|| str == "map table";
}


short()
{ 
    return "A map table";
}
    
long() {
    write("This table has a map carved into it:\n\n");
    cat("/areas/Backbone/Oceans/o/chart");
}

init()
{
    add_action("read_map","read");
}

read_map(str)
{
    if (!id(str))
	return 0;
    cat("/areas/Backbone/Oceans/o/chart");
    return 1;
}

query_value()
{
    return 50;
}
    
query_weight()
{
    return 5;
}
    
get()
{
    return 1;
}
