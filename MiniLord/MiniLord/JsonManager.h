#pragma once
#include "Singleton.h"
#include <nlohmann/json.hpp>
namespace MiniLord
{
	class JsonManager final : public Singleton<JsonManager>
	{
	public:
		void Init(const std::string& Data);
		nlohmann::json LoadJsonDoc(const std::string& file) const;
	private:
		friend class Singleton;
		JsonManager() = default;
		std::string m_DataPath;
	};

}
