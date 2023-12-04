#include "Dictionary.h"
#include "CaseTransferString.h"

void PrintDictionary(const Dictionary& dictionary, std::ostream& file)
{
	for (const auto& el : dictionary)
	{
		file << el.first << " " << el.second << "\n";
	}
}

Dictionary GetDictionary(const std::string& fileName, std::ostream& out)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		out << "Cловаря " << fileName << " нет. Будет создан новый словарь\n";
		return Dictionary();
	}

	Dictionary dictionary;

	while (true)
	{
		std::string engWord, rusWord;

		if (!(file >> engWord) || !(file >> rusWord))
		{
			break;
		}

		TransformStringToLowerCase(engWord);
		
		dictionary.emplace(engWord, rusWord);
	}
	
	return dictionary;
}

bool GetTranslation(Dictionary& dictionary, std::istream& in, std::ostream& out)
{
	//change name
	std::string engWord;
	
	bool isChange = false;

	while (true)
	{
		getline(in, engWord);

		if (engWord == "...")
		{
			break;
		}

		if (engWord.empty())
		{
			continue;
		}

		TransformStringToLowerCase(engWord);
		
		auto item = dictionary.find(engWord);
		if (item != dictionary.end())
		{
			out << item->second << '\n';
			continue;
		}

		out << "Неизвестное слово “"<< engWord << "”. Введите перевод или пустую строку для отказа.\n";

		std::string translate;
		getline(in, translate);
		
		if (translate.empty())
		{
			out << "Слово " << engWord <<" проигнорировано.\n";
			continue;
		}

		dictionary.emplace(engWord, translate);
		out << "Слово “" << engWord <<"” сохранено в словаре как “" << translate <<"”.\n";
		isChange = true;
	}

	return isChange;
}

void SaveDictionary(const Dictionary& dictionary, const std::string& fileName, std::ostream& out)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		out << "Cловарь " << fileName << " не может быть сохранен\n";
		return;
	}

	PrintDictionary(dictionary, file);
	out << "Изменения сохранены. До свидания.\n";
}

void WorkWithDictionary(std::istream& in, std::ostream& out)
{
	setlocale(LC_ALL, "Russian");
	std::system("chcp 1251");//лишнее
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string fileName;
	in >> fileName;

	Dictionary dictionary = GetDictionary(fileName, out);

	//change name translationn
	if (GetTranslation(dictionary, in, out))
	{
		out << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
		
		std::string saver;//change name 
		
		getline(in, saver);
		if (saver == "Y" || saver == "y")
		{
			SaveDictionary(dictionary, fileName, out);
			return;
		}
	}
}
