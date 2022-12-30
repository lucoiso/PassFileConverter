// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: https://github.com/lucoiso/PassFileConverter

#include "DataLoader.h"
#include "HelperLib.h"
#include "Constants.h"
#include <filesystem>
#include <fstream>

const bool DataLoader::hasInvalidData() const
{
	return !m_invalid_data.empty();
}

void DataLoader::loadFile(const std::string& path)
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

	switch (Helper::inputType)
	{
		case LoginDataType::Kapersky:
			readKaperskyData(stream);
			break;

		case LoginDataType::Google:
		case LoginDataType::Microsoft:
			readCSVPasswordData(stream);
			break;

		default:
			throw std::invalid_argument("not implemented yet");
			break;
	}

	stream.close();
}

void DataLoader::saveFile(const std::string& path)
{
	writeData(path, m_valid_data);
}

void DataLoader::exportInvalidData(const std::string& path)
{
	writeData(path, m_invalid_data);
}

void DataLoader::writeData(const std::string& path, const std::vector<LoginData>& data)
{
	if (data.empty())
	{
		return;
	}

	std::filesystem::path filePath(path);
	std::ofstream stream(filePath);

	if (!stream.is_open())
	{
		return;
	}

	switch (Helper::outputType)
	{
		case LoginDataType::Kapersky:
			writeKaperskyData(stream, data);
			break;

		case LoginDataType::Google:
		case LoginDataType::Microsoft:
			writeCSVPasswordData(stream, data);
			break;

		default:
			throw std::invalid_argument("not implemented yet");
			break;
	}

	stream.close();
}

void DataLoader::insertData(const LoginData& data)
{
	if (Helper::outputType != LoginDataType::Google)
	{
		m_valid_data.push_back(data);
		return;
	}
	
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

void DataLoader::writeKaperskyData(std::ofstream& stream, const std::vector<LoginData>& data) const
{
	throw std::invalid_argument("not implemented yet");
}

void DataLoader::readCSVPasswordData(std::ifstream& stream)
{
	throw std::invalid_argument("not implemented yet");
}

void DataLoader::writeCSVPasswordData(std::ofstream& stream, const std::vector<LoginData>& data) const
{
	stream << "name,url,username,password" << std::endl;

	for (const LoginData& iterator : data)
	{
		stream << iterator.getDataString() << std::endl;
	}
}