VSCode-ban való használathoz tedd be a list.h és list.o-t a projekted mappájába, majd menj a taks.json-ba, ahol állítsd be a következőt:
"args": [
                "-g",
                "${file}",
                "${fileDirname}\\list.o",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ]
Ha ezzel megvagy, akkor márcsak includeolni kell a programodban így: #include"list.h".
