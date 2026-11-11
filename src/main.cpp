#include "Logging/Logger.h"
#include "LatticeAssert.h"

int main(int argc, char** /*argv*/)
{
	LATTICE_LOG_DEBUG(Core, "Test DEBUG");
	LATTICE_LOG_INFO(Core, "Lattice {}.{}.{} starting", 0, 1, 0);
	LATTICE_LOG_WARN(Core, "Test WARN");
	LATTICE_LOG_ERROR(Core, "Test ERROR");
	LATTICE_LOG_CRITICAL(Core, "Test CRITICAL");
	LATTICE_LOG_INFO(Core, "same");
	LATTICE_LOG_INFO(Core, "same");
	LATTICE_LOG_INFO(Core, "same");

	LATTICE_ASSERT(argc > 0, Core, "argc must be positive");
	return 0;
}
