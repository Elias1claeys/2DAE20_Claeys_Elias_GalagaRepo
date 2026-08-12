#include "FlyingToFormation.h"
#include "Enemies/Path/BezierPath.h"
#include "Enemies/Enemy.h"
#include "Enemies/EnemyStates/InFormation.h"
#include "StateMachine/State.h"
#include "GameEvents.h"

namespace dae
{
	class Flying : public EnemyState
	{
	public:
		explicit Flying(State* state, glm::vec2 curvePoint, glm::vec2 endPoint, float loopPoint = 0.f);
		virtual ~Flying() = default;
		Flying(const Flying& other) = delete;
		Flying(Flying&& other) = delete;
		Flying& operator=(const Flying& other) = delete;
		Flying& operator=(Flying&& other) = delete;

		void OnEnter() override;
		void Update(float) override {};
		void OnExit() override {};

		void EnemyHit() override;

		std::unique_ptr<GameState> GoToNextState() override;
		glm::vec2 m_EndPoint{};
		glm::vec2 m_CurvePoint{};
		float m_LoopPoint{};
	};
}