#include "log.h"


logger getLogger()
{
	return logger();
}

logger getLogger(const char* filename)
{
	return logger(filename);
}

logger getLogger(const char* filename, const char* prefix)
{
	return logger(filename, prefix);
}

log_message::~log_message()
{
	m_owner.flush(this->m_stream);
}

std::string logger::getEnumType(Logger log)
{
	switch (log)
	{
	case 0:
		return std::string("INFO");
	case 1:
		return std::string("DEBUG");
	case 2:
		return std::string("WARNING");
	case 3:
		return std::string("ERROR");
	default:
		throw std::runtime_error("Incorrect Enum");
	}
}
void logger::flush(const ::std::stringstream& ss)
{
	if (console)
	{
		std::cout << __DATE__ << " " << __TIME__ << ";" << enumInfo << ";" << prefix << " " << "(" << std::this_thread::get_id() << ")" << ":" << ss.str() << '\n';
	}
	else
	{
		std::ofstream out;
		out.open(fileName, std::ios::app);
		out << __DATE__ << " " << __TIME__ << ";" << enumInfo << ";" << prefix << " " << "(" << std::this_thread::get_id() << ")" << ":" << ss.str() << '\n';
		out.close();
	}
}

logger& logger::operator()(Logger log)
{
	enumInfo = getEnumType(log);
	return *this;
}