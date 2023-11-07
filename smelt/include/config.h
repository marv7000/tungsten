#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "shared.h"

namespace smelt
{
    using Properties = std::unordered_map<std::string, std::vector<std::string>>;

    class Config
    {
        Properties mProps{};
    public:
		/// \brief 		Parses a config file and stores its values in a map.
		/// \param path Relative or absolute path to the file.
        explicit Config(const std::string& path);

		/// \brief 		Gets a single string entry from the config by key.
		/// \param key 	The key to get.
		/// \return 	A value if successful, otherwise throws an error.
        const std::string& GetString(const std::string& key);

	    /// \brief 		Gets a string array entry from the config by key.
	    /// \param key 	The key to get.
	    /// \return 	A value if successful, otherwise throws an error.
        const std::vector<std::string>& GetStringArray(const std::string& key);

	    /// \brief 		Gets an integer entry from the config by key.
	    /// \param key 	The key to get.
	    /// \return 	A value if successful, otherwise throws an error.
        i64 GetNum(const std::string& key);
    };
}