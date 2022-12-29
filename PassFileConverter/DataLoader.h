// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: https://github.com/lucoiso/PassFileConverter

#pragma once

#include "LoginData.h"
#include <vector>

enum class LoginDataOrigin
{
	Undef,
	Kapersky,
	Microsoft,
	Google,
	MAX
};

class DataLoader
{
public:
	constexpr DataLoader() = default;
	constexpr ~DataLoader() = default;

	void loadFile(const std::string& path, const LoginDataOrigin& type);
	void saveFile(const std::string& path, const LoginDataOrigin& type);
	void exportInvalidData(const std::string& path);

	const bool hasInvalidData() const;

protected:
	virtual void insertData(const LoginData& data);
	
private:
	std::vector<LoginData> m_valid_data;
	std::vector<LoginData> m_invalid_data;

	void readKaperskyData(std::ifstream& stream);
	void outputGoogleData(std::ofstream& stream) const;
};