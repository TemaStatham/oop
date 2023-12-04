#pragma once

#include "CUrlParsingError.h"

class CHttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS
	};

	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
	// написать с учетом чем отличается метод от функции
	Protocol GetProtocolByString(const std::string& str) const;
	unsigned short GetPortByProtocol() const;
	unsigned short GetPortByString(const std::string& str) const;
};

std::string GetProtocolAsString(CHttpUrl::Protocol protocol);
// чем метод класса отличается от обычной ункции
// как код внутри метода класса знает с каким обьектом он работает