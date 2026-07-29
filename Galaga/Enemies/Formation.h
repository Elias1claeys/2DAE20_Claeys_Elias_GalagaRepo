#include "StateMachine/GameState.h"
#include "Components/Transform.h"

namespace dae
{
	class Formation : public GameState
	{

	public:
		explicit Formation(State* state, glm::vec2 startPoint, glm::vec2 endPoint, glm::vec2 curvePoint);
		virtual ~Formation() = default;
		Formation(const Formation& other) = delete;
		Formation(Formation&& other) = delete;
		Formation& operator=(const Formation& other) = delete;
		Formation& operator=(Formation&& other) = delete;

		void OnEnter() override;
		void Update(float) override;
		void OnExit() override;

		std::unique_ptr<GameState> GoToNextState() override;

	private:
		glm::vec2 m_StartPoint;
		glm::vec2 m_EndPoint;
		glm::vec2 m_CurvePoint;
		float m_T = 0.f;
	};
}