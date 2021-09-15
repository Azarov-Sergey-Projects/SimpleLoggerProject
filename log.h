#pragma once
#include <string>
#include <thread>
#include <fstream>
#include <iostream>
#include <sstream>

const enum Logger
{
	INFO,
	DEBUG,
	WARNING,
	ERROR
};

class logger;

class log_message
{
public:
	log_message(log_message&& rhs)
		: m_owner(rhs.m_owner)
		, m_stream(std::move(rhs.m_stream))
	{}

	template<class T>
	log_message(logger& owner, T&& value)
		: m_owner(owner)
		, m_stream()
	{
		this->m_stream << std::forward<T>(value);
	}

	~log_message();

	template<class T> 
	log_message& operator<<(T&& value)
	{
		this->m_stream << std::forward<T>(value);
		return *this;
	}
private:
	logger& m_owner;
	std::stringstream m_stream;
};

class logger
{
public:
	friend class log_message;

	template<class T>
	log_message operator<<(T&& value)
	{
		return log_message(
			*this, std::forward<T>(value)
		);
	}
	logger(){}
	logger(const std::string& filename,const std::string& prefix) :fileName(filename), prefix(prefix)
	{
		console = false;
	}
	logger(const std::string& filename):fileName(filename)
	{
		console = false;
	}
	logger& operator()(Logger log);
	std::string getEnumType(Logger log);

private:
	void flush(const ::std::stringstream& ss);
	std::string enumInfo="INFO";
	std::string prefix;
	bool console = true;
	std::string fileName;
};




logger getLogger(const char* filename);
logger getLogger();
logger getLogger(const char* filename, const char* prefix);