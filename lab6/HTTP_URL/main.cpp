#include "CHttpUrl.h"

int main()
{
	std::string str;
	while (std::cin >> str)
	{
		try
		{
			CHttpUrl url(str);
			std::cout << "URL: '" << url.GetURL() << std::endl
					  << "\tProtocol: '" << GetProtocolAsString(url.GetProtocol()) << std::endl
					  << "\tDomain: '" << url.GetDomain() << std::endl
					  << "\tPort: '" << url.GetPort() << std::endl
					  << "\tDocument: '" << url.GetDocument() << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	return 0;
}