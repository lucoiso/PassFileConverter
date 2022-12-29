// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: 

#include "DataLoader.h"
#include "HelperLib.h"
#include <filesystem>
#include <fstream>

void DataLoader::loadFile(const std::string& path, const LoginDataOrigin& type)
{
	if (!std::filesystem::exists(path))
	{
		throw std::invalid_argument("file does not exists");
	}

	std::filesystem::path filePath(path);
	std::ifstream stream(filePath);
	
	if (!stream.is_open())
	{
		return;
	}

	m_valid_data.clear();
	m_invalid_data.clear();

	switch (type)
	{
	case LoginDataOrigin::Kapersky:
		readKaperskyData(stream);
		break;

	default:
		throw std::invalid_argument("not implemented yet");
		break;
	}

	stream.close();
}

void DataLoader::saveFile(const std::string& path, const LoginDataOrigin& type)
{
	if (m_valid_data.empty())
	{
		throw std::invalid_argument("no data to save");
	}

	std::filesystem::path filePath(path);
	std::ofstream stream(filePath);

	if (!stream.is_open())
	{
		return;
	}

	switch (type)
	{
		case LoginDataOrigin::Google:
			outputGoogleData(stream);
			break;

		default:
			throw std::invalid_argument("not implemented yet");
			break;
	}

	stream.close();
}

void DataLoader::exportInvalidData(const std::string& path)
{
	if (m_invalid_data.empty())
	{
		return;
	}

	std::filesystem::path filePath(path);
	std::ofstream stream(filePath);

	if (!stream.is_open())
	{
		return;
	}

	stream << "name,url,username,password" << std::endl;

	for (const LoginData& iterator : m_invalid_data)
	{
		stream << iterator.getDataString(DataOutputMode::Csv) << std::endl;
	}

	stream.close();
}

const bool DataLoader::hasInvalidData() const
{
	return !m_invalid_data.empty();
}

void DataLoader::insertData(const LoginData& data)
{
	if (data.hasInvalidData())
	{
		m_invalid_data.push_back(data);
	}
	else
	{
		m_valid_data.push_back(data);
	}
}

void DataLoader::readKaperskyData(std::ifstream& stream)
{
	LoginData currentData;
	std::string currentLine;
	while (std::getline(stream, currentLine))
	{
		if (!currentLine.contains(':'))
		{
			currentData.resetData();
			continue;
		}

		if (currentLine.contains("Application") || currentLine.contains("Notes"))
		{
			break;
		}

		const unsigned int separatorIndex = static_cast<unsigned int>(currentLine.find(':'));
		const std::string key = currentLine.substr(0, separatorIndex);
		const std::string value = currentLine.substr(separatorIndex + 2, currentLine.size() - separatorIndex - 1);

		if (key == "Website name")
		{
			currentData.setName(value);
		}
		else if (key == "Website URL")
		{
			currentData.setUrl(value);
		}
		else if (key == "Login")
		{
			currentData.setUsername(value);
		}
		else if (key == "Password")
		{
			currentData.setPassword(value);

			insertData(currentData);
			currentData.resetData();
		}
	}
}

void DataLoader::outputGoogleData(std::ofstream& stream) const
{
	stream << "name,url,username,password" << std::endl;

	for (const LoginData& iterator : m_valid_data)
	{
		stream << iterator.getDataString(DataOutputMode::Csv) << std::endl;
	}
}