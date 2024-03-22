#include"MapObject.h"
#include"ObjectTextureManager.h"
#include"GameControl.h"
#include<iostream>


Map* Map::instance = 0;




int encodeMap1[map_height][map_width] = {
	{295,296,297,298,299,286,271,271,271,239,271,271,271,271,271,271,271,271,271,271,271,271,271,271,271,291,291,486,487,488,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{314,315,316,317,318,286,4,4,257,258,311,0,714,715,716,717,718,707,708,709,0,0,311,406,407,408,409,505,506,507,476,477,478,479,480,638,639,640,0,309,0,780,781,782,783,784,790,791,792,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{333,334,335,336,337,286,4,4,276,277,311,0,733,734,735,736,737,726,727,728,0,0,311,425,426,427,428,524,525,526,495,496,497,498,499,657,658,659,0,309,0,799,800,801,802,803,809,810,811,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{295,296,297,298,299,286,4,4,0,0,311,0,752,753,754,755,756,745,746,747,0,274,311,444,445,446,447,543,544,545,514,515,516,517,518,676,677,678,0,309,0,818,819,820,821,822,828,829,830,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{314,315,316,317,318,287,4,4,368,369,311,0,771,772,773,774,775,764,765,766,0,0,311,463,464,465,466,0,0,0,533,534,535,536,537,695,696,697,0,309,0,837,838,839,840,841,847,848,849,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{333,334,335,336,337,287,4,4,291,291,291,291,368,369,0,0,0,0,0,0,0,291,291,291,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,309,0,366,367,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{295,296,297,298,299,287,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{314,315,316,317,318,287,4,4,12,13,14,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{333,334,335,336,337,287,4,4,31,32,33,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,287,4,4,50,51,52,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,287,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,287,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,287,324,325,324,325,324,325,324,325,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{352,353,354,355,356,352,353,354,355,356,352,353,354,355,356,352,353,354,355,356,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{371,372,373,374,375,371,372,373,374,375,371,372,373,374,375,371,372,373,374,375,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{390,391,392,393,394,390,391,392,393,394,390,391,392,393,394,390,391,392,393,394,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,26,27,28,29,49,6,240,241,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,45,46,47,48,49,6,259,260,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,64,65,66,67,49,6,278,279,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,49,49,49,49,49,6,240,241,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,49,49,49,49,49,6,259,260,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,49,49,49,49,49,6,278,279,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,49,49,49,49,49,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,49,49,49,49,49,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,49,49,49,49,49,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,49,49,49,49,49,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{49,49,49,49,49,49,49,49,49,49,49,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{291,291,291,291,291,291,291,291,291,291,291,291,291,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{105,105,105,105,105,105,105,105,105,105,105,105,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{105,105,105,105,105,105,105,105,105,105,105,105,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{105,105,105,105,105,105,105,105,105,105,105,105,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{105,105,105,105,80,81,82,83,84,85,105,105,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{105,105,105,105,99,100,101,102,103,104,105,105,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{105,105,105,105,118,119,120,121,122,123,105,105,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{105,105,105,105,105,105,105,105,105,105,105,105,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{105,105,105,105,105,105,105,105,105,105,105,105,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{105,105,105,105,105,105,105,105,105,105,105,105,309,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

};



int encodeMap2[map_height][map_width] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,486,487,488,0,0,0,0,295,296,297,298,299,0,0,0,234,567,568,0,558,559,560,561,410,411,412,413,414,5,5,5,5,5,5,5,5,5 },
	{0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,505,506,507,0,0,0,0,314,315,316,317,318,0,0,0,0,586,587,0,577,578,579,580,429,430,431,432,433,5,134,135,136,137,138,139,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,524,525,526,0,0,0,0,333,334,335,336,337,0,0,0,0,605,606,0,596,597,598,599,448,449,450,451,452,5,153,154,155,156,157,158,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,543,544,545,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,615,616,617,618,467,468,469,470,471,5,172,173,174,175,176,177,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,230,231,232,233,234,235,0,0,0,0,0,5,191,192,193,194,195,196,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,58,59,60,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,242,243,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,77,78,79,5,5,5},
	{0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,261,262,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,96,97,98,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,280,281,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,115,116,117,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,58,59,60,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,77,78,79,5,5,5},
	{0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,96,97,98,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,115,116,117,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,246,247,0,0,0,0,0,0,0,0,0,0,5,5,5,58,59,60,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,217,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,265,266,0,0,0,0,0,0,0,0,0,0,5,5,5,77,78,79,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,217,238,239,0,0,0,0,0,0,0,0,0,0,0,217,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,284,285,0,0,0,0,0,0,0,0,0,0,5,5,5,96,97,98,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,217,257,258,0,0,0,0,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,115,116,117,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,217,276,277,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,236,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,49,49,49,49,49,49,49,49,0,5,5,5,5,5,5,5,5,5},
	{23,24,25,26,27,28,29,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,49,49,49,0,0,0,0,0,0,0,0,0,0,0,0,49,49,49,49,49,49,49,49,49,49,49,49,5,5,5,5,5,5,5,5},
	{42,43,44,45,46,47,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,0,0,0,0,49,49,49,49,49,5,5,5,5,5,5,5,5},
	{61,62,63,64,65,66,67,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,49,49,49,49,49,49,49,49,49,49,49,49,0,0,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5},
	{49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5},
	{49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5},
	{49,49,49,49,49,49,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,246,247,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5},
	{49,49,49,49,49,49,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,265,266,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5},
	{49,49,49,49,49,49,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,284,285,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5},
	{49,49,49,49,49,49,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5},
	{49,49,49,49,49,49,49,291,291,291,291,291,291,291,291,291,291,291,291,291,291,291,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,12,13,14,5,5,5},
	{49,49,49,49,49,49,49,714,715,716,717,718,710,711,712,713,707,708,709,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,31,32,33,5,5,5},
	{49,49,49,49,49,49,49,733,734,735,736,737,729,730,731,732,726,727,728,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,511,511,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,50,51,52,5,5,5},
	{49,49,49,49,49,49,49,752,753,754,755,756,748,749,750,751,745,746,747,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,68,69,5,5,5,5},
	{49,49,49,49,49,49,49,771,772,773,774,775,767,768,769,770,764,765,766,230,231,232,233,234,235,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,105,105,105,87,88,105,105,105,105},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,15,105,105,105,106,107,105,105,105,105},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,15,105,105,105,125,126,82,83,84,85},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,15,105,105,105,99,100,101,102,103,104},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,15,105,105,105,118,119,120,121,122,123},
	{300,301,302,303,304,300,301,302,303,304,300,301,302,303,304,300,301,302,303,304,300,301,302,303,304,300,301,302,303,304,352,353,354,355,356,352,353,354,355,356,357,358,359,360,361,357,358,359,360,361,357,358,359,360,361,238,239,238,239,238,239,238,239,300,301,302,303,304,300,301,302,303,304,300,301,302,303,304,240,241},
{319,320,321,322,323,319,320,321,322,323,319,320,321,322,323,319,320,321,322,323,319,320,321,322,323,319,320,321,322,323,371,372,373,374,375,371,372,373,374,375,376,377,378,379,380,376,377,378,379,380,376,377,378,379,380,257,258,257,258,257,258,257,258,319,320,321,322,323,319,320,321,322,323,319,320,321,322,323,259,260},
{338,339,340,341,342,338,339,340,341,342,338,339,340,341,342,338,339,340,341,342,338,339,340,341,342,338,339,340,341,342,390,391,392,393,394,390,391,392,393,394,395,396,397,398,399,395,396,397,398,399,395,396,397,398,399,276,277,276,277,276,277,276,277,338,339,340,341,342,338,339,340,341,342,338,339,340,341,342,278,279}


};


Map::Map() {
	/*ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/map/dirt.png", "dirt", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/map/grass.png", "grass", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/map/water.png", "water", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/map/rock.jpg", "rock", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/map/wood.jpg", "wood", GameControl::getInstance()->getRenderer());*/
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/tileset map.png", "tileset", GameControl::getInstance()->getRenderer());


	int z = 1;
	for (int i = 0; i < tileset_height; i++) {
		for (int j = 0; j < tileset_width; j++) {
			mp[z] = std::make_pair(j * 32, i * 32);
			z++;
		}
	}


	std::cout << "load map\n";
}

void Map::changeMap(int idMap) {
	if (idMap == 1) {
		LoadMap(encodeMap1);
	}
	else if (idMap == 2) {
		LoadMap(encodeMap2);
	}
}



void Map::LoadMap(int arr[map_height][map_width]) {
	for (int row = 0; row < map_height; row++) {
		for (int col = 0; col < map_width; col++) {
			map[row][col] = arr[row][col];
		}
	}
}


void Map::DrawMap() {
	/*int type = 0;
	for (int row = 0; row < map_height; row++) {
		for (int col = 0; col < map_width; col++) {
			type = map[row][col];
			if (type == 1) {
				ObjectTextureManager::getInstance()->drawTile("dirt", col * 32, row * 32, 32, 32, GameControl::getInstance()->getRenderer());
			}
			else if (type == 2) {
				ObjectTextureManager::getInstance()->drawTile("grass", col * 32, row * 32, 32, 32, GameControl::getInstance()->getRenderer());
			}
			else if (type == 4) {
				ObjectTextureManager::getInstance()->drawTile("water", col * 32, row * 32, 32, 32, GameControl::getInstance()->getRenderer());
			}
			else if (type == 3) {
				ObjectTextureManager::getInstance()->drawTile("rock", col * 32, row * 32, 32, 32, GameControl::getInstance()->getRenderer());
			}
			else {
				ObjectTextureManager::getInstance()->drawTile("wood", col * 32, row * 32, 32, 32, GameControl::getInstance()->getRenderer());
			}
		}
	}*/



	for (int row = 0; row < map_height; row++) {
		for (int col = 0; col < map_width; col++) {
			ObjectTextureManager::getInstance()->drawTile("tileset", col * 32, row * 32, mp[map[row][col]].first, mp[map[row][col]].second, 32, 32, GameControl::getInstance()->getRenderer());
		}
	}
}