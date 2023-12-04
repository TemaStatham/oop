#pragma once

#include <string>
#include <iostream>
#include <vector>

void ProcessHtmlText(std::istream& in, std::ostream& out);

std::string HtmlDecode(std::string const& html);