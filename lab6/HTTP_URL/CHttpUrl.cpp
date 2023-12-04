#include "CHttpUrl.h"

using namespace std;

const unsigned short HTTP_PORT = 80;
const unsigned short HTTPS_PORT = 443;

const int PORT_MIN = 0;
const int PORT_MAX = 65535;

constexpr int PROT_REGEX_INDEX = 2;
constexpr int DOMAIN_REGEX_INDEX = 4;
constexpr int PORT_REGEX_INDEX = 5;
constexpr int DOC_REGEX_INDEX = 6;

const string DOMEN_REGEX = "([A-Za-z0-9\\-\\.]+)";

const string URL_REGEX = "(([Hh][Tt][Tt][Pp][Ss]?)"
						 "(://)"
	+ DOMEN_REGEX + "(:[0-9]{0,})?"
					"(\\/.{0,})?)";

const string HTTP = "http";
const string HTTPS = "https";

CHttpUrl::CHttpUrl(string const& url)
{
	smatch result;
	std::regex regular(URL_REGEX);

	if (!regex_match(url, result, regular))
	{
		throw CUrlParsingError("Invalid url!");
	}

	m_protocol = GetProtocolByString(result[PROT_REGEX_INDEX].str());
	m_domain = result[DOMAIN_REGEX_INDEX].str();
	m_port = result[PORT_REGEX_INDEX].str().empty() ? GetPortByProtocol() : GetPortByString(result[PORT_REGEX_INDEX].str());
	m_document = result[DOC_REGEX_INDEX].str().empty() ? "/" : result[DOC_REGEX_INDEX].str();
}

CHttpUrl::CHttpUrl(const string& domain, const string& document, Protocol protocol)
{
	regex domenReg(DOMEN_REGEX);
	if (regex_match(domain, domenReg))
	{
		throw CUrlParsingError("Invalid domen!");
	}
	m_protocol = protocol;
	m_domain = domain;
	m_document = document[0] == '/' ? document : '/' + document;
	m_port = GetPortByProtocol();
}

CHttpUrl::CHttpUrl(const string& domain, const string& document, Protocol protocol, short port)
{
	// сделать так чтобы тесты находили ошибки
	if (domain == "")
	{
		throw CUrlParsingError("The domain cannot be empty");
	}
	if (port > PORT_MAX || port < PORT_MIN)
	{
		throw CUrlParsingError("Invalid port! Port out of range("
			+ to_string(PORT_MIN) + " <= " + to_string(PORT_MAX) + ")");
	}
	m_protocol = protocol;
	m_domain = domain;
	m_document = document[0] == '/' ? document : '/' + document;
	m_port = port;
}

CHttpUrl::Protocol CHttpUrl::GetProtocolByString(const string& str) const
{
	string protocol = str;
	// ту ловер сделать лучге
	transform(protocol.begin(), protocol.end(), protocol.begin(),
		[](unsigned char c) {
			return std::tolower(static_cast<unsigned char>(c));
		});

	if (protocol == HTTP)
	{
		return Protocol::HTTP;
	}

	if (protocol == HTTPS)
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Not expected URL!");
}

unsigned short CHttpUrl::GetPortByString(const string& str) const
{
	string port = str.substr(1, str.length());
	try
	{
		size_t pos;
		int result = stoi(port, &pos);
		// доработать тесты чтобы они проверяли порт макс и порт мин сделать проверку границ
		if (result > PORT_MAX || result < PORT_MIN)
		{
			throw CUrlParsingError("Invalid port! Port out of range("
				+ to_string(PORT_MIN) + " <= " + to_string(PORT_MAX) + ")");
		}
		if (pos != port.length())
		{
			throw CUrlParsingError("Invalid port: " + str);
		}

		return result;
	}
	catch (const invalid_argument&)
	{
		throw CUrlParsingError("Invalid port: '" + str + "'");
	}
	catch (const out_of_range&)
	{
		throw CUrlParsingError("Invalid port! Port out of range("
			+ to_string(PORT_MIN) + " <= " + to_string(PORT_MAX) + ")");
	}
}

unsigned short CHttpUrl::GetPortByProtocol() const
{
	switch (m_protocol)
	{
	case CHttpUrl::Protocol::HTTP:
		return HTTP_PORT;
	case CHttpUrl::Protocol::HTTPS:
		return HTTPS_PORT;
	}

	throw CUrlParsingError("Invalid protocol!");
}

string GetProtocolAsString(CHttpUrl::Protocol protocol)
{
	switch (protocol)
	{
	case CHttpUrl::Protocol::HTTP:
		return HTTP;
	case CHttpUrl::Protocol::HTTPS:
		return HTTPS;
	}

	throw CUrlParsingError("Unknown protocol!");
}

string CHttpUrl::GetURL() const
{
	if ((m_protocol == CHttpUrl::Protocol::HTTP && m_port == HTTP_PORT)
		|| (m_protocol == CHttpUrl::Protocol::HTTPS && m_port == HTTPS_PORT))
	{
		return GetProtocolAsString(m_protocol) + "://" + m_domain + m_document;
	}

	return GetProtocolAsString(m_protocol) + "://" + m_domain + ':' + to_string(m_port) + m_document;
}

string CHttpUrl::GetDomain() const
{
	return m_domain;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

string CHttpUrl::GetDocument() const
{
	return m_document;
}
