#include "FlyingToFormation.h"
#include "Enemies/Path/BezierPath.h"
#include "Enemies/Enemy.h"
#include "Enemies/EnemyStates/InFormation.h"
#include "StateMachine/State.h"
#include "GameEvents.h"

namespace dae
{
	class BeamAttack : public EnemyState
	{
	public:
		explicit BeamAttack(State* state);
		virtual ~BeamAttack() = default;
		BeamAttack(const BeamAttack& other) = delete;
		BeamAttack(BeamAttack&& other) = delete;
		BeamAttack& operator=(const BeamAttack& other) = delete;
		BeamAttack& operator=(BeamAttack&& other) = delete;

		void OnEnter() override {};
		void Update(float) override;
		void OnExit() override;

		std::unique_ptr<GameState> GoToNextState() override;
	
	private:
		bool m_PlayerInBeam = false;
		bool m_EndReached = false;
		std::unique_ptr<GameObject> m_Beam;
	};
}