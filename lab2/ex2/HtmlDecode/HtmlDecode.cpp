#include <iostream>
#include <string>
#include <vector>

struct HtmlTemplates
{
	std::string encodedHtml;
	char decodedHtml;

	HtmlTemplates(const std::string& encoded, char decoded)
		: encodedHtml(encoded)
		, decodedHtml(decoded)
	{}
};

std::vector<HtmlTemplates> Templates = {
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' },
	{ "&quot;", '"' },
	{ "&apos;", '\'' },
};

std::string HtmlDecode(std::string const& html)
{
	std::string decoded;
	decoded.reserve(html.size());

	for (size_t i = 0; i < html.size(); ++i)
	{
		if (html[i] == '&')
		{
			bool isFoundTemplate = false;
			for (const auto& htmlTemplate : Templates)
			{
				if (html.compare(i, htmlTemplate.encodedHtml.size(), htmlTemplate.encodedHtml) == 0)
				{
					decoded.push_back(htmlTemplate.decodedHtml);
					i += htmlTemplate.encodedHtml.size() - 1;
					isFoundTemplate = true;
					break;
				}
			}

			if (!isFoundTemplate)
			{
				decoded.push_back(html[i]);
			}
		}
		else
		{
			decoded.push_back(html[i]);
		}
	}

	return decoded;
}

int main()
{
	std::string line;

	while (std::getline(std::cin, line))
	{
		std::cout << HtmlDecode(line) << std::endl;
	}

	return EXIT_SUCCESS;
}