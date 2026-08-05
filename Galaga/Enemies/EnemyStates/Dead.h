#include "Core/GameObject.h"

namespace dae
{
	class Dead : public Component
	{
	public:
		Dead(GameObject* owner);
		virtual ~Dead() = default;
		Dead(const Dead& other) = delete;
		Dead(Dead&& other) = delete;
		Dead& operator=(const Dead& other) = delete;
		Dead& operator=(Dead&& other) = delete;

		void Update() override;

	private:
		float m_Time = 0;
		int m_Index = 0;
	};
}