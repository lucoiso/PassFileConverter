// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: https://github.com/lucoiso/PassFileConverter

#include "DataLoader.h"
#include "HelperLib.h"
#include <filesystem>
#include <fstream>

void DataLoader::loadFile(const std::string& path, const LoginDataType& type)
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
		case LoginDataType::Kapersky:
			readKaperskyData(stream);
			break;

		case LoginDataType::Google:
			readGoogleData(stream);
			break;

		case LoginDataType::Microsoft:
			readMicrosoftData(stream);
			break;

		default:
			throw std::invalid_argument("not implemented yet");
			break;
	}

	stream.close();
}

void DataLoader::saveFile(const std::string& path, const LoginDataType& type)
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
		case LoginDataType::Kapersky:
			outputKaperskyData(stream);
			break;
			
		case LoginDataType::Google:
			outputGoogleData(stream);
			break;

		case LoginDataType::Microsoft:
			outputMicrosoftData(stream);
			break;

		default:
			throw std::invalid_argument("not implemented yet");
			break;
	}

	stream.close();
}

void DataLoader::exportInvalidData(const std::string& path, const LoginDataType& type)
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
		stream << iterator.getDataString(type) << std::endl;
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

void DataLoader::outputKaperskyData(std::ofstream& stream) const
{
	throw std::invalid_argument("not implemented yet");
}

void DataLoader::readGoogleData(std::ifstream& stream)
{
	throw std::invalid_argument("not implemented yet");
}

void DataLoader::outputGoogleData(std::ofstream& stream) const
{
	stream << "name,url,username,password" << std::endl;

	for (const LoginData& iterator : m_valid_data)
	{
		stream << iterator.getDataString(LoginDataType::Google) << std::endl;
	}
}

void DataLoader::readMicrosoftData(std::ifstream& stream)
{
	throw std::invalid_argument("not implemented yet");
}

void DataLoader::outputMicrosoftData(std::ofstream& stream) const
{
	throw std::invalid_argument("not implemented yet");
}
