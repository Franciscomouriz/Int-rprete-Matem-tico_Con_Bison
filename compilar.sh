flex --header="flex.yy.h" flex.l
bison -d bison.y
cp ./CP/bison.tab.h .
cp ./CP/flex.yy.h .
make
