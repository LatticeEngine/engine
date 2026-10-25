#include <iostream>

#include "Core/include/Logger/LatticeLogger.h"
#include "Core/include/LatticeAssert.h"

int main(int argc, char** argv)
{
	lattice::Logger::printMsg(lattice::LogLevel::INFO, lattice::LogCategory::CORE, "Test INFO");
	lattice::Logger::printMsg(lattice::LogLevel::DEBUG, lattice::LogCategory::CORE, "Test DEBUG");
	lattice::Logger::printMsg(lattice::LogLevel::WARN, lattice::LogCategory::CORE, "Test WARN");
	lattice::Logger::printMsg(lattice::LogLevel::ERROR, lattice::LogCategory::CORE, "Test ERROR");
	lattice::Logger::printMsg(lattice::LogLevel::CRITICAL, lattice::LogCategory::CORE, "Test CRITICAL");
	/*LATTICE_ASSERT(1 == 1, lattice::LogCategory::RENDERER, "Test Equals");
	LATTICE_ASSERT(1 == 2, lattice::LogCategory::RENDERER, "Test Debug break");*/
	return 0;
}