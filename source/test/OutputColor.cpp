#include "OutputColor.hpp"

std::ostream& testFailed(std::ostream& stream)
{
	stream << "\033[38;2;255;40;0m";
	return stream;
}
std::ostream& testSucceed(std::ostream& stream)
{
	stream << "\033[38;2;0;240;0m";
	return stream;
}
std::ostream& testEntry(std::ostream& stream)
{
	stream << "\033[38;2;180;180;180m";
	return stream;
}

std::ostream& testTitle(std::ostream& stream)
{
	stream << "\033[38;2;0;180;255m";
	return stream;
}