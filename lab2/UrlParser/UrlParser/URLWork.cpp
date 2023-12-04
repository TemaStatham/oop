#include "URLWork.h"
#include "URLWorkTest.h"

constexpr int MAX_PORT = 65535;
constexpr int MIN_PORT = 0;
constexpr int HTTP_PORT = 80;
constexpr int HTTPS_PORT = 443;
constexpr int FTP_PORT = 21;
constexpr int PROT_REGEX_INDEX = 2;
constexpr int HOST_REGEX_INDEX = 3;
constexpr int PORT_REGEX_INDEX = 4;
constexpr int DOC_REGEX_INDEX = 5;
constexpr int ERROR_PORT = -1;

const std::string URL_REGEX = "((http|https|ftp?)://([0-9A-Za-z\-.]+)(?::([0-9]+))?(?:/(.*))?)";
const std::string HTTP = "http";
const std::string HTTPS = "https";
const std::string FTP = "ftp";

void TransformStringToLowerCase(std::string& str)
{
	for (char& ch : str)
	{
		ch = std::tolower(static_cast<unsigned char>(ch));
	}
}

Protocol ParseProtocol(const std::string& protocol)
{
	if (protocol == HTTP) return Protocol::HTTP;
	if (protocol == HTTPS) return Protocol::HTTPS;
	if (protocol == FTP) return Protocol::FTP;
}

int ParsePort(Protocol protocol, const std::string& portString)
{
	if (portString != "")
	{
		int port = std::stoi(portString);
		if (port > MAX_PORT || port < MIN_PORT) return ERROR_PORT;
		return port;
	}
	if (protocol == Protocol::HTTP)
	{
		return HTTP_PORT;
	}
	if (protocol == Protocol::HTTPS)
	{
		return HTTPS_PORT;
	}
	if (protocol == Protocol::FTP)
	{
		return FTP_PORT;
	}
	return ERROR_PORT;
}

bool ParseURL(std::string const& url, Protocol& protocol,
	int& port, std::string& host, std::string& document)
{
	std::regex regex(URL_REGEX, std::regex_constants::icase);
	std::cmatch result;

	if (!std::regex_match(url.c_str(), result, regex)) return false;

	std::string prot = std::string(result[PROT_REGEX_INDEX]);
	TransformStringToLowerCase(prot);
	if (prot != HTTP && prot != HTTPS && prot != FTP) return false;
	protocol = ParseProtocol(prot);

	host = std::string(result[HOST_REGEX_INDEX]);

	port = ParsePort(protocol, std::string(result[PORT_REGEX_INDEX]));
	if (port == ERROR_PORT) return false;

	document = std::string(result[DOC_REGEX_INDEX]);

	return true;
}

void URLWork(std::istream& in, std::ostream& out)
{
	std::string url;

	while (std::getline(in, url))
	{
		Protocol protocol;
		int port = 0;
		std::string host, document;

		if (ParseURL(url, protocol, port, host, document))
		{
			out << url << std::endl
				<< "HOST : " << host << std::endl
				<< "PORT : " << port << std::endl
				<< "DOC : " << document << std::endl;
		}
	}
}