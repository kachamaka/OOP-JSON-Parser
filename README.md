# OOP-JSON-Parser

## Usage

Usage is being kept simple by using the following implemented commands:

open <path> - Opens existing file <br>
close - Closes currently loaded file <br>
save <pretty|raw> - Saves already existing file with optional format [default is pretty] <br>
save search <path> - Saves search result <br>
save search <position> <path> - Saves element from search result on specified position <br>
saveas <path> <pretty|raw> - Saves as new file <br>
new - Creates a new instance with an empty base <br>

print <pretty|raw> - Prints currently loaded JSON's contents with optional format [default is pretty] <br>
print search - Prints search result <br>
print search <position> - Prints element from search result on specified position <br>
search <key> - Searches by key <br>

set <key> <value> - Sets value to property with specified key [set $.path.to.key "value"] <br>
create <key> <value> - Creates new property with specified key and value [create $.path.to.key "value"] <br>
remove <key> - Removes property with specified key [remove $.path.to.key] <br>
move <key1> <key2> - Moves property's contents with key1 to property with key2 [move $.path.to.key1 $.path.to.key2] <br>
cls - Clears console <br>
exit - Exits the program <br>

## Note

When specifying path to property with key, use the following syntax: $.path.to.key.
- $ specifies root object
