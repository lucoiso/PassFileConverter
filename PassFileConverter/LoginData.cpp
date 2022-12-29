// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: https://github.com/lucoiso/PassFileConverter

#include "LoginData.h"
#include "HelperLib.h"

#pragma region Getters and Setters
void LoginData::setName(const std::string value)
{
	Helper::setMemberValue(value, m_name);
}

const std::string LoginData::getName() const
{
	return m_name;
}

void LoginData::setUrl(const std::string value)
{
	Helper::setMemberValue(value, m_url);

	if (!m_url.contains("http"))
	{
		m_url = "https://" + m_url;
	}
}

const std::string LoginData::getUrl() const
{
	return m_url;
}

void LoginData::setUsername(const std::string value)
{
	Helper::setMemberValue(value, m_username);
}

const std::string LoginData::getUsername() const
{
	return m_username;
}

void LoginData::setPassword(const std::string value)
{
	Helper::setMemberValue(value, m_password);
}

const std::string LoginData::getPassword() const
{
	return m_password;
}
#pragma endregion Getters and Setters

const bool LoginData::hasEmptyData() const
{
	return Helper::hasEmptyData(m_name, m_url, m_username, m_password);
}

const bool LoginData::hasInvalidData() const
{
	return Helper::hasInvalidData(m_name, m_url, m_username, m_password);
}

void LoginData::resetData()
{
	m_name.clear();
	m_url.clear();
	m_username.clear();
	m_password.clear();
}

const std::string LoginData::getDataString(const LoginDataType& mode) const
{
	switch (mode)
	{
		case LoginDataType::Google:
			return m_name + "," + m_url + "," + m_username + "," + m_password;
			
		default:
			throw std::invalid_argument("not implemented yet");
			break;
	}

	return std::string();
}
