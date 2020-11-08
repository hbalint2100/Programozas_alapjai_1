VSCode-ban való használathoz tedd be a list.h és list.o-t a projekted mappájába, majd menj a taks.json-ba, ahol állítsd be a következőt:
"args": [
                "-g",
                "${file}",
                "${fileDirname}\\list.o",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ]
Ha ezzel megvagy, akkor márcsak includeolni kell a programodban így: #include"list.h".

Egy lista létrehozásához egy Node_i *p = NULL; pointert kell létrehoznod, ekkor teljesen üres listád van.

Ha értéket akarsz hozzáadni a lista végére, akkor az int_add(&p,//vmi int); függvénnyel tudod.
Ha értéket akarsz "lekérni" akkor azt az int_get(p,//elem indexe ugyanúgy mint egy tömbnél); függvénnyel tudod.
Ha a lista méretét akarod meghatározni akkor azt a size(p); függvénnyel tudod.
Ha értéket akarsz módosítani egy x indexű elemen akkor azt az int_set(p,//x. index,//új int érték); függvénnyel tudod.
Ha törölni akarsz egy x. indexű elemet, akkor azt az list_remove(&p,//x. index); függvénnyel tudod.
Ha meg akarod kapni az x.indexű elemet, akkor azt a get_node(p,//x. index) függvénnyel tudod.
Ha törölni akarod a teljes listát, akkor azt a free_list(p); függvénnyel tudod.
