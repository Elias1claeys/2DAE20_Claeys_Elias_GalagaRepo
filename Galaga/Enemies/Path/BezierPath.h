#pragma once

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
			float loopPoint = 0.f;
		};

		enum class Phase
		{
			preLoop,
			loop,
			postLoop
		};

		BezierPath(GameObject* owner);
		virtual ~BezierPath() = default;
		BezierPath(const BezierPath& other) = delete;
		BezierPath(BezierPath&& other) = delete;
		BezierPath& operator=(const BezierPath& other) = delete;
		BezierPath& operator=(BezierPath&& other) = delete;

		void SetNewPath(glm::vec2 curvePoint, glm::vec2 endPoint, float loopPoint = 0.f);
		void SetWeavePath(glm::vec2 endPoint, int numSegments, float amplitude);
		void Update() override;
		glm::vec2 CalculateCurvePoint(glm::vec2 start, glm::vec2 end, float curveAmount);
		float CurrentPos() { return m_T; }

	private:
		Phase m_Phase = Phase::preLoop;
		BezierSegment m_BezierSegment{};
		glm::vec2 m_RotationCenter{};

		float m_LoopStartAngle{};
		float m_LoopAngle{};
		float m_T = 1.f;
		float m_loopDirection = 1.f;
		int m_PathIndex = 0;

		//Weave
		std::vector<BezierSegment> m_WeaveSegments;
		size_t m_WeaveIndex = 0;
		bool m_IsWeaving = false;

		void BezierMovement(Transform* transform);
		void Looping(Transform* transform);
		bool ReachedEnd();
	};
}