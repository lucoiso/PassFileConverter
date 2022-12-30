// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: https://github.com/lucoiso/PassFileConverter

#pragma once

#include <string>

enum class LoginDataType
{
    Undefined,
    Kapersky,
    Google,
    Microsoft,
    MAX
};

class LoginData
{
public:
    constexpr LoginData() = default;
    constexpr ~LoginData() = default;

#pragma region Getters and Setters
    void setName(const std::string value);
    const std::string getName() const;

    void setUrl(const std::string value);
    const std::string getUrl() const;

    void setUsername(const std::string value);
    const std::string getUsername() const;

    void setPassword(const std::string value);
    const std::string getPassword() const;
#pragma endregion Getters and Setters

    const bool hasEmptyData() const;
    const bool hasInvalidData() const;
    
    void resetData();
    
    const std::string getDataString() const;

protected:
    std::string m_name;
    std::string m_url;
    std::string m_username;
    std::string m_password;
};