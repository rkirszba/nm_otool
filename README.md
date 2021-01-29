# nm_otool
📚 nm and otool commands recoding

## Description
The project is to recode two commands that parse Mach-o files binary files: nm and otool

## Use
```
make
./ft_nm [options] <input files>
./ft_otool [optinos] <input files>
```

### ft_nm options
```
-g     Display only global (external) symbols.
-j     Just display the symbol names (no value or type).
-n     Sort numerically rather than alphabetically.
-o     Prepend file or archive element name to each output line, rather than only once.
-p     Don't sort; display in symbol-table order.
-r     Sort in reverse order.
-u     Display only undefined symbols.
-U     Show only defined symbols.
```

### ft_otool options
```
-d     print the data section.
-t     print the text section.
```
