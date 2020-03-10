/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature ORANGE_CUBE = vex::vision::signature (1, 3593, 9097, 6345, -2839, -1681, -2260, 1, 0);
vex::vision::signature PURPLE_CUBE = vex::vision::signature (2, 1051, 3067, 2059, 6743, 9523, 8133, 3.6, 0);
vex::vision::signature GREEN_CUBE = vex::vision::signature (3, -8805, -6965, -7885, -4717, -2673, -3695, 3.3, 0);
vex::vision::signature BLUE_TILE = vex::vision::signature (4, -3811, -3155, -3483, 4991, 6665, 5828, 2.5, 0);
vex::vision::signature RED_TILE = vex::vision::signature (5, 4839, 5821, 5330, -409, 143, -134, 2.4, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision VisionSensor = vex::vision (vex::PORT18, 65, ORANGE_CUBE, PURPLE_CUBE, GREEN_CUBE, BLUE_TILE, RED_TILE, SIG_6, SIG_7);
/*vex-vision-config:end*/