#include "common/initialize.h"
#include "SDL.h"

int main(   
			#ifdef _WIN32 
				int argc, char *argv[] 
			#endif	
		)
{
	runGame();
	return EXIT_SUCCESS;
}
