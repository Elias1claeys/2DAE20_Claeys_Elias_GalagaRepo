#include "StateMachine/GameState.h"
#include "Components/Transform.h"

namespace dae
{
	class Flying : public GameState
	{

	public:
		struct BezierSegment
		{
			glm::vec2 startPoint;
			glm::vec2 endPoint;
			glm::vec2 curvePoint;
		};

		enum class Phase
		{
			preLoop,
			loop,
			postLoop
		};

		explicit Flying(State* state, BezierSegment bezier, float loopPoint);
		explicit Flying(State* state, BezierSegment bezier);
		virtual ~Flying() = default;
		Flying(const Flying& other) = delete;
		Flying(Flying&& other) = delete;
		Flying& operator=(const Flying& other) = delete;
		Flying& operator=(Flying&& other) = delete;

		void OnEnter() override;
		void Update(float) override;
		void OnExit() override;

		std::unique_ptr<GameState> GoToNextState() override;

	private:
		Phase m_Phase = Phase::preLoop;
		BezierSegment m_BezierSegment{};
		glm::vec2 m_RotationCenter{};
		float m_LoopStartAngle{};
		float m_LoopAngle{};
		float m_LoopPoint{};
		float m_T = 0.f;

		void BezierMovement(float deltaTime, Transform* transform);
		void Looping(float deltaTime, Transform* transform);
	};
}