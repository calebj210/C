All: WaterRand.c WaterFilter.c WaterPack.c
	make WaterRand
	make WaterFilter
	make WaterPack

WaterRand: WaterRand.c
	gcc -std=c99 -Wall -Wextra -pedantic -O1 WaterRand.c -o WaterRand

WaterFilter: WaterFilter.c
	gcc -std=c99 -Wall -Wextra -pedantic -O1 WaterFilter.c -o WaterFilter

WaterPack: WaterPack.c
	gcc -std=c99 -Wall -Wextra -pedantic -O1 -lm WaterPack.c -o WaterPack
