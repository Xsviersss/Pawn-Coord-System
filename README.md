## License

This project is licensed under the MIT License.

## /coord Command

### What does this script do?
The `/coord` command is an admin command used to teleport a player to a specific coordinate position in the game world.

It takes three parameters:
- `x` = X coordinate
- `y` = Y coordinate
- `z` = Z coordinate

Example usage:

/coord 1550.5 -1700.3 13.5

After entering the command, the player will be moved to the specified position.

### How does it work?
The script first checks whether the player has admin permission:

```pawn
if(CheckAdmin(playerid, 1))
    return PermissionError(playerid);

This part prevents non-admin players from using the command.

The admin check system is optional. You can remove or replace this section depending on your server's permission system. The command will still work without it.

The command then uses sscanf to read three float values from the command parameters:

sscanf(params, "fff", x, y, z)

If the coordinates are valid, it executes:

SetPlayerPos(playerid, x, y, z);

which teleports the player to the given coordinates.


---

Installation

1. Copy the command code into your gamemode or script file.


2. Make sure you have the required include:



#include <sscanf2>

3. Add the command callback to your command processor.



Example:

CMD:coord(playerid, params[])
{
    // command code here
}

4. Compile your script using the Pawn compiler.


5. Start your server and test the command:



/coord x y z


---

Requirements

SA-MP Server

sscanf2 include

Command processor (such as zcmd, y_commands, or similar)
