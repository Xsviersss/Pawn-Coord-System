#include <sscanf2>                  //by Y_Less fixed by maddinat0r & Emmet_

CMD:coord(playerid, params[]) 
{
    if(CheckAdmin(playerid, 1))
        return PermissionError(playerid);

    new 
        Float:x,
        Float:y,
        Float:z;

    return ((sscanf(params, "fff", x,y,z)) && (SendSyntaxMessage(playerid, "/coord <x> <y> <z>")) || (SetPlayerPos(playerid, x,y,z)));
}
