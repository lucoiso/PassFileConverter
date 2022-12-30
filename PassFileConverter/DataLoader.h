// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: https://github.com/lucoiso/PassFileConverter

#pragma once

#include "LoginData.h"
#include <vector>

class DataLoader
{
public:
	constexpr DataLoader() = default;
	constexpr ~DataLoader() = default;

	const bool hasInvalidData() const;
	
	void loadFile(const std::string& path);
	void saveFile(const std::string& path);
	void exportInvalidData(const std::string& path);

private:
	std::vector<LoginData> m_valid_data;
	std::vector<LoginData> m_invalid_data;

	void writeData(const std::string& path, const std::vector<LoginData>& data);	
	virtual void insertData(const LoginData& data);

	void readKaperskyData(std::ifstream& stream);
	void writeKaperskyData(std::ofstream& stream, const std::vector<LoginData>& data) const;

	void readCSVPasswordData(std::ifstream& stream);
	void writeCSVPasswordData(std::ofstream& stream, const std::vector<LoginData>& data) const;

};