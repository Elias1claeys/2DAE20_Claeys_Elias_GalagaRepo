#include "Core/GameObject.h"
#include "Components/Transform.h"

namespace dae
{
	class BezierPath : public Component
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

		BezierPath(GameObject* owner, BezierSegment bezier, float loopPoint);
		BezierPath(GameObject* owner, BezierSegment bezier);
		virtual ~BezierPath() = default;
		BezierPath(const BezierPath& other) = delete;
		BezierPath(BezierPath&& other) = delete;
		BezierPath& operator=(const BezierPath& other) = delete;
		BezierPath& operator=(BezierPath&& other) = delete;

		void Update() override;

	private:
		Phase m_Phase = Phase::preLoop;
		BezierSegment m_BezierSegment{};
		glm::vec2 m_RotationCenter{};
		float m_LoopStartAngle{};
		float m_LoopAngle{};
		float m_LoopPoint{};
		float m_T = 0.f;

		void BezierMovement(Transform* transform);
		void Looping(Transform* transform);
		bool ReachedEnd();
	};
}