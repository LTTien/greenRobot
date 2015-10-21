#include "serialCortex.h"

task main()
{

StartTask(serialRxTask);

while(true){
	wait1Msec(1);
}

}// end program main
