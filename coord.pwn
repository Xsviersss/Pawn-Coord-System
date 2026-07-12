CMD:coord(playerid, params[])
{
    if(CheckAdmin(playerid, 1))
        return PermissionError(playerid);

    new Float:x, Float:y, Float:z;

    GetPlayerPos(playerid, x, y, z);

    SendClientMessage(playerid, -1, "Your Coordinate Is:");
    SendClientMessagef(playerid, -1, "X: %.4f | Y: %.4f | Z: %.4f", x, y, z);

    return 1;
}