// Author: Lucas Oliveira Vilas-B�as
// Year: 2022
// Repository: 

#pragma once

#include <string>

enum class DataOutputMode
{
    Undef,
    Csv,
    NameOnly,
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
    
    const std::string getDataString(const DataOutputMode& mode) const;

protected:
    std::string m_name;
    std::string m_url;
    std::string m_username;
    std::string m_password;
};